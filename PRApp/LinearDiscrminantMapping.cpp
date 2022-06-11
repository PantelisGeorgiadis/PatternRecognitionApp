#include "LinearDiscrminantMapping.h"

CLinearDiscrminantMapping::CLinearDiscrminantMapping()
{

}

CLinearDiscrminantMapping::~CLinearDiscrminantMapping()
{

}

CDataSet *CLinearDiscrminantMapping::LinearDiscrminantMapping (CDataSet *pDataSet){

	int i, j, k;
	
	CDataSetToDataMatrix *DataSetToDataMatrix = new CDataSetToDataMatrix();
	CDataMatrix2D *DataSetDataMatrixes = DataSetToDataMatrix->DataSetToDataMatrix(pDataSet);
	
	CDataMatrix2D *DataSetCovarianceDataMatrixes = new CDataMatrix2D[pDataSet->GetNumberOfClasses()];
	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		DataSetCovarianceDataMatrixes[i].CreateDataMatrix(DataSetDataMatrixes[0].GetNumberOfRows(), DataSetDataMatrixes[0].GetNumberOfColumns());
	}
	
	CCovariance *Covariance = new CCovariance();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		CDataMatrix2D *DataSetCovarianceDataMatrixTmp = NULL;
		
		DataSetCovarianceDataMatrixTmp = Covariance->CalculateMatrixCovariance(&DataSetDataMatrixes[i]);
		DataSetCovarianceDataMatrixTmp->CopyToDataMatrix2D(&DataSetCovarianceDataMatrixes[i]);
		
		delete DataSetCovarianceDataMatrixTmp;
		DataSetCovarianceDataMatrixTmp = NULL;
	}

	CDataMatrix2D *Sw = new CDataMatrix2D(DataSetDataMatrixes[0].GetNumberOfRows(), DataSetDataMatrixes[0].GetNumberOfColumns());
	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		CDataMatrix2D *SwTmp = NULL;
		SwTmp = DataSetCovarianceDataMatrixes[i].CopyDataMatrix2D();
		SwTmp->MultiplyScalarToMatrix(pDataSet->GetClass(i)->GetNumberOfPatterns());

		Sw->AddToDataMatrix(SwTmp);

		delete SwTmp;
		SwTmp = NULL;
	}

	CClass *MergedClass = pDataSet->MergeDataSet();
	CMeanValue *MergedClassMeanValues = new CMeanValue [DataSetDataMatrixes[0].GetNumberOfColumns()];
	for (i=0;i<DataSetDataMatrixes[0].GetNumberOfColumns();i++){
		MergedClassMeanValues[i].CalculateFeaturesMeanValue(MergedClass, i);
	}

	CDataMatrix2D *m0 = new CDataMatrix2D(1, DataSetDataMatrixes[0].GetNumberOfColumns());
	for (i=0;i<DataSetDataMatrixes[0].GetNumberOfColumns();i++){
		m0->SetMatrixValue(0, i, MergedClassMeanValues[i].GetMeanValue());
	}

	CDataMatrix2D *mClass = new CDataMatrix2D[pDataSet->GetNumberOfClasses()];
	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		mClass[i].CreateDataMatrix(1, DataSetDataMatrixes[0].GetNumberOfColumns());

		CMeanValue *ClassMeanValues = new CMeanValue [pDataSet->GetClass(i)->GetNumberOfPatterns()];

		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfFeaturesPerPattern();j++){
			ClassMeanValues[j].CalculateFeaturesMeanValue(pDataSet->GetClass(i), j);
			mClass[i].SetMatrixValue(0, j, ClassMeanValues[j].GetMeanValue());
		
		}

		delete [] ClassMeanValues;
		ClassMeanValues = NULL;

	}


	for (i=0;i<pDataSet->GetNumberOfClasses();i++){


	}



	delete [] mClass;
	mClass = NULL;
	delete m0;
	m0 = NULL;
	delete [] MergedClassMeanValues;
	MergedClassMeanValues = NULL;
	delete MergedClass;
	MergedClass = NULL;
	delete Sw;
	Sw = NULL;
	delete Covariance;
	Covariance = NULL;
	delete [] DataSetCovarianceDataMatrixes;
	DataSetCovarianceDataMatrixes = NULL;
	delete [] DataSetDataMatrixes;
	DataSetDataMatrixes = NULL;
	delete DataSetToDataMatrix;
	DataSetToDataMatrix = NULL;
	
	return NULL;
	
}

CDataMatrix2D *CLinearDiscrminantMapping::CrossProduct (CDataMatrix2D *DataMatrix2D1, CDataMatrix2D *DataMatrix2D2){

	CDataMatrix2D *CrossProduct = NULL; 
	CDataMatrix2D *SubtractedDataMatrix2D = NULL;
	CDataMatrix2D *SubtractedDataMatrix2DTransposed = NULL;
	SubtractedDataMatrix2D = DataMatrix2D1->Subtract(DataMatrix2D2);
	SubtractedDataMatrix2DTransposed = SubtractedDataMatrix2D->TransposeMatrix();

	CrossProduct = SubtractedDataMatrix2D->Multiply(SubtractedDataMatrix2DTransposed);

	delete SubtractedDataMatrix2DTransposed;
	SubtractedDataMatrix2DTransposed = NULL;
	delete SubtractedDataMatrix2D;
	SubtractedDataMatrix2D = NULL;

	return CrossProduct;

}
