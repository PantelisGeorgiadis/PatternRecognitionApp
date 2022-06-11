#include "stdafx.h"
#include "DataMatrixToFeatureDataMatrix.h"

CDataMatrixToFeatureDataMatrix::CDataMatrixToFeatureDataMatrix()
{

	m_FeatureDataMatrices = NULL;

}

CDataMatrixToFeatureDataMatrix::~CDataMatrixToFeatureDataMatrix()
{

	DeleteFeatureDataMatrices();

}

void CDataMatrixToFeatureDataMatrix::DeleteFeatureDataMatrices (void){

	if (m_FeatureDataMatrices != NULL){
		delete [] m_FeatureDataMatrices;
		m_FeatureDataMatrices = NULL;
	}

}

void CDataMatrixToFeatureDataMatrix::DataMatrixToFeatureDataMatrices (CDataMatrix2D *pDataMatrix, int iKernelSize, int iDepth){

	int i, j;
	int ii, jj;
	int k, l;
	double dblKernelFeatureValue = 0.0f;

	if (iKernelSize > pDataMatrix->GetNumberOfColumns()){
		return;
	}

	if ((iKernelSize % 2) == 0){
		return;
	}

	m_FeatureDataMatrices = new CDataMatrix2D[NUMBEROFFEATURES];
	for (i=0;i<NUMBEROFFEATURES;i++){
		m_FeatureDataMatrices[i].CreateDataMatrix(pDataMatrix->GetNumberOfRows(), pDataMatrix->GetNumberOfColumns());
	}

	// Copy original matrix?
	
	CPattern *Pattern = NULL;
	CROIToPattern *ROIToPattern = new CROIToPattern(); 
	unsigned char *pu8KernelData = new unsigned char [iKernelSize * iKernelSize];
	
	for (i=(int)(iKernelSize / 2);i<(pDataMatrix->GetNumberOfRows() - (int)(iKernelSize / 2));i++){
		for (j=(int)(iKernelSize / 2);j<(pDataMatrix->GetNumberOfColumns() - (int)(iKernelSize / 2));j++){
			k = 0;
			for (ii=(i - (int)(iKernelSize / 2));ii<=(i + (int)(iKernelSize / 2));ii++){
				for (jj=(j - 1);jj<=(j + 1);jj++){
					pu8KernelData[k] = (unsigned char)(pDataMatrix->GetMatrixValue(ii, jj));
					k++;
				}
			}
			
			Pattern = ROIToPattern->ROIToPattern8(pu8KernelData, iKernelSize, iKernelSize, iDepth);
			
			for (l=0;l<NUMBEROFFEATURES;l++){
				m_FeatureDataMatrices[l].SetMatrixValue(i, j, Pattern->GetFeature(l)->GetFeatureValue());
			}

			delete Pattern;
			Pattern = NULL;
		}
	}

	delete ROIToPattern;
	ROIToPattern = NULL;
	delete [] pu8KernelData;
	pu8KernelData = NULL;
	
}

void CDataMatrixToFeatureDataMatrix::WriteFeatureDataMatricesToFile (char *szFileNamePattern, char *szExtension){

	char szFileName[255];
	char szFeatureName[255];
	
	if (m_FeatureDataMatrices != NULL){	
		for (int i=0;i<NUMBEROFFEATURES;i++){
			memset(szFeatureName, 0, 255 * sizeof(char));
			CROIToPattern::GetFeatureName(i, szFeatureName);
			sprintf(szFileName, "%s_%s%s", szFileNamePattern, szFeatureName, szExtension);
			m_FeatureDataMatrices[i].WriteMatrixDataToFile(szFileName);
		}
	}

}

void CDataMatrixToFeatureDataMatrix::WriteFeatureDataMatricesToBMPFile8 (char *szFileNamePattern, char *szExtension){

	char szFileName[255];
	char szFeatureName[255];
	CDataMatrix2D *NormalizedDataMatrix = NULL;
	
	if (m_FeatureDataMatrices != NULL){	
		for (int i=0;i<NUMBEROFFEATURES;i++){
			memset(szFeatureName, 0, 255 * sizeof(char));
			CROIToPattern::GetFeatureName(i, szFeatureName);
			sprintf(szFileName, "%s_%s%s", szFileNamePattern, szFeatureName, szExtension);
			NormalizedDataMatrix = NormalizeToGrayscale(&m_FeatureDataMatrices[i]);
			NormalizedDataMatrix->WriteMatrixDataToBMPFile8(szFileName);
			delete NormalizedDataMatrix;
			NormalizedDataMatrix = NULL;
		}
	}

}

CDataMatrix2D *CDataMatrixToFeatureDataMatrix::NormalizeToGrayscale (CDataMatrix2D *pDataMatrix){

	CDataMatrix2D *NormalizedDataMatrix = new CDataMatrix2D(pDataMatrix->GetNumberOfRows(), pDataMatrix->GetNumberOfColumns());

	int i, j;
	double dblMax = (std::numeric_limits<double>::min)();
	double dblMin = (std::numeric_limits<double>::max)();
	
	for (i=0;i<pDataMatrix->GetNumberOfRows();i++){
		for (j=0;j<pDataMatrix->GetNumberOfColumns();j++){
			if (dblMax < pDataMatrix->GetMatrixValue(i, j)){
				dblMax = pDataMatrix->GetMatrixValue(i, j);
			}
		}
	}

	for (i=0;i<pDataMatrix->GetNumberOfRows();i++){
		for (j=0;j<pDataMatrix->GetNumberOfColumns();j++){
			if (dblMin > pDataMatrix->GetMatrixValue(i, j)){
				dblMin = pDataMatrix->GetMatrixValue(i, j);
			}
		}
	}

	for (i=0;i<pDataMatrix->GetNumberOfRows();i++){
		for (j=0;j<pDataMatrix->GetNumberOfColumns();j++){
			NormalizedDataMatrix->SetMatrixValue(i, j, (double)((pDataMatrix->GetMatrixValue(i, j) * 255.0f) / (dblMax - dblMin)));
		}
	}

	return NormalizedDataMatrix;

}
