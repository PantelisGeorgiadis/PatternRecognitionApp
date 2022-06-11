#include "stdafx.h"
#include "FastMath.h"
#include "MarkovRandomFieldSegmentationModel.h"

CMarkovRandomFieldSegmentationModel::CMarkovRandomFieldSegmentationModel()
{

	m_SegmentedDataMatrix2D = NULL;
	m_iNumberOfIterations = 0;
	m_dblEnergy = 0.0f;
	m_dblEnergyOld = 0.0f;
	m_T = 0.0f;
	m_pMarkovRandomFieldSegmentationModelCallBack = NULL;

}

CMarkovRandomFieldSegmentationModel::CMarkovRandomFieldSegmentationModel(MarkovRandomFieldSegmentationModelCallBack pMarkovRandomFieldSegmentationModelCallBack)
{

	m_SegmentedDataMatrix2D = NULL;
	m_iNumberOfIterations = 0;
	m_dblEnergy = 0.0f;
	m_dblEnergyOld = 0.0f;
	m_T = 0.0f;
	m_pMarkovRandomFieldSegmentationModelCallBack = pMarkovRandomFieldSegmentationModelCallBack;

}

CMarkovRandomFieldSegmentationModel::~CMarkovRandomFieldSegmentationModel()
{

	DeleteSegmentedDataMatrix();

}

/*
CALLBACK EXAMPLE

void MrfCB (MarkovRandomFieldOptimizationAlgorithm mrfoa, int iIteration, double dblEnergy, double dblTemperature, CDataMatrix2D* pDataMatrix){


}

*/

void CMarkovRandomFieldSegmentationModel::Segment (CDataMatrix2D *pDataMatrix2D, CRectangle *ClassRegions, int iNumberOfClasses, double alpha, double beta, double t, double T0, double c, MarkovRandomFieldOptimizationAlgorithm mrfoa){

	int i, j, k;
	double dblE = 0.0f, dblE2 = 0.0f;

	if (iNumberOfClasses <= 0){
		return;
	}

	m_iNumberOfClasses = iNumberOfClasses;
	m_alpha = alpha;
	m_beta = beta;
	m_t = t;
	m_T0 = T0;
	m_c = c;

	m_SegmentedDataMatrix2D = new  CDataMatrix2D(pDataMatrix2D->GetNumberOfRows(), pDataMatrix2D->GetNumberOfColumns());

	CDataMatrix2D *RegionDataMatrix = new CDataMatrix2D[iNumberOfClasses];
	CDataMatrix2D *RegionDataMatrixTmp = NULL;
	CFeature2DMeanValue *Feature2DMeanValue = new CFeature2DMeanValue[iNumberOfClasses];
	CFeature2DVariance *Feature2DVariance = new CFeature2DVariance[iNumberOfClasses];
	CDataMatrix2D *ClassesDataMatrix = new CDataMatrix2D(pDataMatrix2D->GetNumberOfRows(), pDataMatrix2D->GetNumberOfColumns());

	for (k=0;k<iNumberOfClasses;k++){
		RegionDataMatrix[k].CreateDataMatrix(ClassRegions[k].GetHeight(), ClassRegions[k].GetWidth());
		RegionDataMatrixTmp = pDataMatrix2D->GetSubDataMatrix(&ClassRegions[k]);
		for (i=0;i<RegionDataMatrixTmp->GetNumberOfRows();i++){
			for (j=0;j<RegionDataMatrixTmp->GetNumberOfColumns();j++){
				RegionDataMatrix[k].SetMatrixValue(i, j, RegionDataMatrixTmp->GetMatrixValue(i, j));
			}
		}
		delete RegionDataMatrixTmp;
		RegionDataMatrixTmp = NULL;
	}

	for (k=0;k<iNumberOfClasses;k++){
		Feature2DMeanValue[k].CalculateMeanValue(&RegionDataMatrix[k]);
		Feature2DVariance[k].CalculateVariance(&RegionDataMatrix[k]);
	}

	// Initialize using Maximum Likelihood (~ max. of singleton energy)
	for (i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		for (j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			dblE = Singleton(pDataMatrix2D, Feature2DMeanValue, Feature2DVariance, i, j, 0);
			ClassesDataMatrix->SetMatrixValue(i, j, 0.0f);
			for (k=1;k<iNumberOfClasses;k++){
				if ((dblE2 = Singleton(pDataMatrix2D, Feature2DMeanValue, Feature2DVariance, i, j, k)) < dblE){
					dblE = dblE2;
					ClassesDataMatrix->SetMatrixValue(i, j, k);
				}
			}
		}
	}

	switch (mrfoa){
		case MRFOA_METROPOLIS:
			Metropolis(pDataMatrix2D, ClassesDataMatrix, Feature2DMeanValue, Feature2DVariance, false);
			break;
		case MRFOA_GIBBS:
			Gibbs(pDataMatrix2D, ClassesDataMatrix, Feature2DMeanValue, Feature2DVariance);
			break;
		case MRFOA_ICM:
			IteratedConditionalModes(pDataMatrix2D, ClassesDataMatrix, Feature2DMeanValue, Feature2DVariance);
			break;
		case MRFOA_MMD:
			Metropolis(pDataMatrix2D, ClassesDataMatrix, Feature2DMeanValue, Feature2DVariance, true);
			break;
	}

	delete ClassesDataMatrix;
	ClassesDataMatrix = NULL;
	delete [] Feature2DVariance;
	Feature2DVariance = NULL;
	delete [] Feature2DMeanValue;
	Feature2DMeanValue = NULL;
	delete [] RegionDataMatrix;
	RegionDataMatrix = NULL;

}

void CMarkovRandomFieldSegmentationModel::DeleteSegmentedDataMatrix (void){

	if (m_SegmentedDataMatrix2D != NULL){
		delete m_SegmentedDataMatrix2D;
		m_SegmentedDataMatrix2D = NULL;
	}

}

double CMarkovRandomFieldSegmentationModel::Singleton(CDataMatrix2D *pDataMatrix2D, CFeature2DMeanValue *Feature2DMeanValue, CFeature2DVariance *Feature2DVariance, int i, int j, int iLabel){
	
	return log(CFastMath::FastSqrt(2.0f * PI * Feature2DVariance[iLabel].GetVariance())) + pow((double)pDataMatrix2D->GetMatrixValue(i, j) - Feature2DMeanValue[iLabel].GetMeanValue(), 2) / (2.0f * Feature2DVariance[iLabel].GetVariance());
	
}

double CMarkovRandomFieldSegmentationModel::Doubleton(CDataMatrix2D *ClassesDataMatrix, int i, int j, int iLabel){

	double dblEnergy = 0.0f;
	
	// South
	if (i != (ClassesDataMatrix->GetNumberOfRows() - 1)){     
		if (iLabel == ClassesDataMatrix->GetMatrixValue((i + 1), j)){ 
			dblEnergy -= GetBeta();
		}
		else{
			dblEnergy += GetBeta();
		}
    }

	// East
	if (j != (ClassesDataMatrix->GetNumberOfColumns() - 1)){
		if (iLabel == ClassesDataMatrix->GetMatrixValue(i, (j + 1))){
			dblEnergy -= GetBeta();
		}
		else{
			dblEnergy += GetBeta();
		}
    }

	// North
	if (i != 0){
		if (iLabel == ClassesDataMatrix->GetMatrixValue((i - 1), j)){
			dblEnergy -= GetBeta();
		}
		else{
			dblEnergy += GetBeta();
		}
    }

	// West
	if (j != 0){
		if (iLabel == ClassesDataMatrix->GetMatrixValue(i, (j - 1))){
			dblEnergy -= GetBeta();
		}
		else{
			dblEnergy += GetBeta();
		}
    }

	return dblEnergy;

}

double CMarkovRandomFieldSegmentationModel::CalculateEnergy(CDataMatrix2D *pDataMatrix2D, CDataMatrix2D *ClassesDataMatrix, CFeature2DMeanValue *Feature2DMeanValue, CFeature2DVariance *Feature2DVariance){

	double dblSingletons = 0.0f;
	double dblDoubletons = 0.0f;
	int k = 0;

	for (int i=0;i<ClassesDataMatrix->GetNumberOfRows();i++){
		for (int j=0;j<ClassesDataMatrix->GetNumberOfColumns();j++){
			k = (int)(ClassesDataMatrix->GetMatrixValue(i, j));
			dblSingletons += Singleton(pDataMatrix2D, Feature2DMeanValue, Feature2DVariance, i, j, k);
			dblDoubletons += Doubleton(ClassesDataMatrix, i, j, k);
		}
	}
	
	return dblSingletons + dblDoubletons / 2.0f; 

}

double CMarkovRandomFieldSegmentationModel::LocalEnergy(CDataMatrix2D *pDataMatrix2D, CDataMatrix2D *ClassesDataMatrix, CFeature2DMeanValue *Feature2DMeanValue, CFeature2DVariance *Feature2DVariance, int i, int j, int iLabel){

	return Singleton(pDataMatrix2D, Feature2DMeanValue, Feature2DVariance, i, j, iLabel) + Doubleton(ClassesDataMatrix, i, j, iLabel);

}

void CMarkovRandomFieldSegmentationModel::CreateSegmentedDataMatrix (CDataMatrix2D *ClassesDataMatrix){

	for (int i=0;i<ClassesDataMatrix->GetNumberOfRows();i++){
		for (int j=0;j<ClassesDataMatrix->GetNumberOfColumns();j++){
			m_SegmentedDataMatrix2D->SetMatrixValue(i, j, (double)(((int)(ClassesDataMatrix->GetMatrixValue(i, j)) * 255 / GetNumberOfClasses())));
		}
	}

}

void CMarkovRandomFieldSegmentationModel::Metropolis(CDataMatrix2D *pDataMatrix2D, CDataMatrix2D *ClassesDataMatrix, CFeature2DMeanValue *Feature2DMeanValue, CFeature2DVariance *Feature2DVariance, bool bModifiedMetropolisDynamics){

	CMersenneTwister *MersenneTwister = new CMersenneTwister(time(0));
	double dblSumDeltaE = 0.0f;
	int i, j, r;

	m_iNumberOfIterations = 0;
	double dblKszi = log(GetAlpha());

	m_T = m_T0;
	m_dblEnergyOld = CalculateEnergy(pDataMatrix2D, ClassesDataMatrix, Feature2DMeanValue, Feature2DVariance);

	do{
		dblSumDeltaE = 0.0f;
		for (i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
			for (j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
				// Generate a new label different from the current one with uniform distribution.
				if (GetNumberOfClasses() == 2){
					r = (1 - (int)(ClassesDataMatrix->GetMatrixValue(i, j)));
				}
				else{
					r = ((int)(ClassesDataMatrix->GetMatrixValue(i, j)) + (int)(MersenneTwister->Random() * (GetNumberOfClasses() - 1)) + 1) % GetNumberOfClasses();
				}
				if (!bModifiedMetropolisDynamics){
					dblKszi = log(MersenneTwister->Random()); 
				}
				if (dblKszi <= (LocalEnergy(pDataMatrix2D, ClassesDataMatrix, Feature2DMeanValue, Feature2DVariance, i, j, (int)(ClassesDataMatrix->GetMatrixValue(i, j))) - LocalEnergy(pDataMatrix2D, ClassesDataMatrix, Feature2DMeanValue, Feature2DVariance, i, j, r)) / m_T){
					dblSumDeltaE += fabs(LocalEnergy(pDataMatrix2D, ClassesDataMatrix, Feature2DMeanValue, Feature2DVariance, i, j, r) - LocalEnergy(pDataMatrix2D, ClassesDataMatrix, Feature2DMeanValue, Feature2DVariance, i, j, (int)(ClassesDataMatrix->GetMatrixValue(i, j))));
					m_dblEnergyOld = m_dblEnergy = m_dblEnergyOld -  LocalEnergy(pDataMatrix2D, ClassesDataMatrix, Feature2DMeanValue, Feature2DVariance, i, j, (int)(ClassesDataMatrix->GetMatrixValue(i, j))) + LocalEnergy(pDataMatrix2D, ClassesDataMatrix, Feature2DMeanValue, Feature2DVariance, i, j, r);
					ClassesDataMatrix->SetMatrixValue(i, j, r);
				}
			}
		}
		
		// Decrease temperature
		m_T *= m_c;				
		m_iNumberOfIterations++;	     
		CreateSegmentedDataMatrix(ClassesDataMatrix);

		if (m_pMarkovRandomFieldSegmentationModelCallBack != NULL){
			if (!bModifiedMetropolisDynamics){
				m_pMarkovRandomFieldSegmentationModelCallBack(MRFOA_METROPOLIS, m_iNumberOfIterations, m_dblEnergy, m_T, GetSegmentedDataMatrix());
			}
			else{
				m_pMarkovRandomFieldSegmentationModelCallBack(MRFOA_MMD, m_iNumberOfIterations, m_dblEnergy, m_T, GetSegmentedDataMatrix());
			}
		}
    
	} 
	// Stop when energy change is small
	while (dblSumDeltaE > m_t); 
	
	delete MersenneTwister;
	MersenneTwister = NULL;

}

void CMarkovRandomFieldSegmentationModel::IteratedConditionalModes(CDataMatrix2D *pDataMatrix2D, CDataMatrix2D *ClassesDataMatrix, CFeature2DMeanValue *Feature2DMeanValue, CFeature2DVariance *Feature2DVariance){
	
	double dblSumDeltaE = 0.0f;
	int i, j, r;
	
	m_iNumberOfIterations = 0;
	
	m_dblEnergyOld = CalculateEnergy(pDataMatrix2D, ClassesDataMatrix, Feature2DMeanValue, Feature2DVariance);
	
	do{
		dblSumDeltaE = 0.0f;
		for (i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
			for (j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
				for (r=0;r<GetNumberOfClasses();r++){
					if (LocalEnergy(pDataMatrix2D, ClassesDataMatrix, Feature2DMeanValue, Feature2DVariance, i, j, (int)(ClassesDataMatrix->GetMatrixValue(i, j))) > LocalEnergy(pDataMatrix2D, ClassesDataMatrix, Feature2DMeanValue, Feature2DVariance, i, j, r)){
						ClassesDataMatrix->SetMatrixValue(i, j, r);
					}
				}
			}
		}
		m_dblEnergy = CalculateEnergy(pDataMatrix2D, ClassesDataMatrix, Feature2DMeanValue, Feature2DVariance);
		dblSumDeltaE += fabs(m_dblEnergyOld - m_dblEnergy);
		m_dblEnergyOld = m_dblEnergy;
		
		m_iNumberOfIterations++;
		CreateSegmentedDataMatrix(ClassesDataMatrix);

		if (m_pMarkovRandomFieldSegmentationModelCallBack != NULL){
			m_pMarkovRandomFieldSegmentationModelCallBack(MRFOA_ICM, m_iNumberOfIterations, m_dblEnergy, m_T, GetSegmentedDataMatrix());
		}
	}
	while (dblSumDeltaE > m_t); 

}

void CMarkovRandomFieldSegmentationModel::Gibbs(CDataMatrix2D *pDataMatrix2D, CDataMatrix2D *ClassesDataMatrix, CFeature2DMeanValue *Feature2DMeanValue, CFeature2DVariance *Feature2DVariance){
	
	CMersenneTwister *MersenneTwister = new CMersenneTwister(time(0));
	double *LocalEnergies = new double [GetNumberOfClasses()];
	double dblSumDeltaE = 0.0f;
	double dblSumEnergy = 0.0f;
	double z = 0.0f;
	double r = 0.0f;
	int i, j, s;

	m_iNumberOfIterations = 0;
	m_T = m_T0;
	m_dblEnergyOld = CalculateEnergy(pDataMatrix2D, ClassesDataMatrix, Feature2DMeanValue, Feature2DVariance);

	do{
		dblSumDeltaE = 0.0f;
		for (i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
			for (j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
				dblSumEnergy = 0.0f;
				for (s=0;s<GetNumberOfClasses();s++){
					LocalEnergies[s] = exp(-LocalEnergy(pDataMatrix2D, ClassesDataMatrix, Feature2DMeanValue, Feature2DVariance, i, j, s) / m_T);
					dblSumEnergy += LocalEnergies[s];
				}
				r = MersenneTwister->Random();
				z = 0.0f;
				for (s=0;s<GetNumberOfClasses();s++){
					z += LocalEnergies[s] / dblSumEnergy; 
					// Choose new label with probability exp(-U/T)
					if (z > r){
						ClassesDataMatrix->SetMatrixValue(i, j, s);
						break;
					}
				}
			}
		}
		m_dblEnergy = CalculateEnergy(pDataMatrix2D, ClassesDataMatrix, Feature2DMeanValue, Feature2DVariance);
		dblSumDeltaE += fabs(m_dblEnergyOld - m_dblEnergy);
		m_dblEnergyOld = m_dblEnergy;
		
		m_T *= m_c;	
		m_iNumberOfIterations++;
		CreateSegmentedDataMatrix(ClassesDataMatrix);

		if (m_pMarkovRandomFieldSegmentationModelCallBack != NULL){
			m_pMarkovRandomFieldSegmentationModelCallBack(MRFOA_GIBBS, m_iNumberOfIterations, m_dblEnergy, m_T, GetSegmentedDataMatrix());
		}
    } 
	while (dblSumDeltaE > m_t); 
	
	delete [] LocalEnergies;
	LocalEnergies = NULL;
	delete MersenneTwister;
	MersenneTwister = NULL;
	
}


