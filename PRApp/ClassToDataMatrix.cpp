#include "stdafx.h"
#include "ClassToDataMatrix.h"

CClassToDataMatrix::CClassToDataMatrix()
{

}

CClassToDataMatrix::~CClassToDataMatrix()
{

}

CDataMatrix2D *CClassToDataMatrix::ClassToDataMatrix (CClass *pClass){

	CDataMatrix2D *DataMatrix2D = new CDataMatrix2D(pClass->GetNumberOfPatterns(), pClass->GetNumberOfFeaturesPerPattern());

	for (int i=0;i<DataMatrix2D->GetNumberOfRows();i++){
		for (int j=0;j<DataMatrix2D->GetNumberOfColumns();j++){
			DataMatrix2D->SetMatrixValue(i, j, pClass->GetPattern(i)->GetFeature(j)->GetFeatureValue());
		}
	}

	return DataMatrix2D;

}

CDataMatrix2D *CClassToDataMatrix::PatternToDataMatrix2D (CPattern *pPattern){

	CDataMatrix2D *DataMatrix2D = new CDataMatrix2D(1, pPattern->GetNumberOfFeatures());

	for (int i=0;i<DataMatrix2D->GetNumberOfColumns();i++){
		DataMatrix2D->SetMatrixValue(0, i, pPattern->GetFeature(i)->GetFeatureValue());
	}
	
	return DataMatrix2D;

}

CDataMatrix1D *CClassToDataMatrix::PatternToDataMatrix1D (CPattern *pPattern){

	CDataMatrix1D *DataMatrix1D = new CDataMatrix1D(pPattern->GetNumberOfFeatures());

	for (int i=0;i<DataMatrix1D->GetNumberOfColumns();i++){
		DataMatrix1D->SetMatrixValue(i, pPattern->GetFeature(i)->GetFeatureValue());
	}
	
	return DataMatrix1D;

}

CClass *CClassToDataMatrix::DataMatrixToClass (CDataMatrix2D *pDataMatrix2D){

	CClass *Class = new CClass(pDataMatrix2D->GetNumberOfRows(), pDataMatrix2D->GetNumberOfColumns());

	for (int i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		for (int j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			Class->GetPattern(i)->GetFeature(j)->SetFeatureValue(pDataMatrix2D->GetMatrixValue(i, j));
		}
	}

	return Class;

}

CPattern *CClassToDataMatrix::DataMatrixToPattern (CDataMatrix1D *pDataMatrix1D){

	CPattern *Pattern = new CPattern(pDataMatrix1D->GetNumberOfColumns());

	for (int i=0;i<pDataMatrix1D->GetNumberOfColumns();i++){
		Pattern->GetFeature(i)->SetFeatureValue(pDataMatrix1D->GetMatrixValue(i));
	}

	return Pattern;

}
