#include "stdafx.h"
#include "DataSetToDataMatrix.h"

CDataSetToDataMatrix::CDataSetToDataMatrix()
{

}

CDataSetToDataMatrix::~CDataSetToDataMatrix()
{

}

CDataMatrix2D *CDataSetToDataMatrix::DataSetToDataMatrix (CDataSet *pDataSet){

	int i, j, k;
	
	if (pDataSet->GetNumberOfClasses() == 0){
		return NULL;
	}

	CDataMatrix2D *pDataMatrix2D = new CDataMatrix2D[pDataSet->GetNumberOfClasses()];
	
	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		pDataMatrix2D->CreateDataMatrix(pDataSet->GetClass(i)->GetNumberOfPatterns(), pDataSet->GetClass(i)->GetNumberOfFeaturesPerPattern());
	}

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			for (k=0;k<pDataSet->GetClass(i)->GetPattern(j)->GetNumberOfFeatures();k++){
				pDataMatrix2D[i].SetMatrixValue(j, k, pDataSet->GetClass(i)->GetPattern(j)->GetFeature(k)->GetFeatureValue());
			}
		}
	}

	return pDataMatrix2D;

}

CDataSet *CDataSetToDataMatrix::DataMatrixesToDataSet (CDataMatrix2D *pDataMatrix2D, int iNumberOfDataMatrixes){

	if (iNumberOfDataMatrixes == 0){
		return NULL;
	}

	CDataSet *pDataSet = new CDataSet();
	CClassToDataMatrix *ClassToDataMatrix = new CClassToDataMatrix();
	CClass *pClass = NULL;

	for (int i=0;i<iNumberOfDataMatrixes;i++){
		pClass = ClassToDataMatrix->DataMatrixToClass(&pDataMatrix2D[i]);
		pDataSet->AddClass(pClass);
	}

	delete ClassToDataMatrix;
	ClassToDataMatrix = NULL;

	return pDataSet;

}
