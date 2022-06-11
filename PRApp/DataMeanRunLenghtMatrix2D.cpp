#include "stdafx.h"
#include "DataMeanRunLenghtMatrix2D.h"

CDataMeanRunLenghtMatrix2D::CDataMeanRunLenghtMatrix2D()
{

}

CDataMeanRunLenghtMatrix2D::~CDataMeanRunLenghtMatrix2D()
{

}

CDataRunLengthMatrix2D *CDataMeanRunLenghtMatrix2D::CalculateMeanRunLenghtMatrix(CDataRunLengthMatrix2D *pDataRunLengthMatrix2D0, CDataRunLengthMatrix2D *pDataRunLengthMatrix2D45, CDataRunLengthMatrix2D *pDataRunLengthMatrix2D90, CDataRunLengthMatrix2D *pDataRunLengthMatrix2D135){

	int i, j;

	CDataRunLengthMatrix2D *MeanRunLengthMatrix = new CDataRunLengthMatrix2D();
	MeanRunLengthMatrix->CreateDataMatrix(pDataRunLengthMatrix2D0->GetDepth(), pDataRunLengthMatrix2D0->GetLenght(), pDataRunLengthMatrix2D0->GetMatrixRotationDegrees());

	for (i=0;i<MeanRunLengthMatrix->GetNumberOfRows();i++){
		for (j=0;j<MeanRunLengthMatrix->GetNumberOfColumns();j++){
			MeanRunLengthMatrix->SetMatrixValue(i, j, (pDataRunLengthMatrix2D0->GetMatrixValue(i, j) + pDataRunLengthMatrix2D45->GetMatrixValue(i, j) + pDataRunLengthMatrix2D90->GetMatrixValue(i, j) + pDataRunLengthMatrix2D135->GetMatrixValue(i, j)));
		}
	}

	for (i=0;i<MeanRunLengthMatrix->GetNumberOfRows();i++){
		for (j=0;j<MeanRunLengthMatrix->GetNumberOfColumns();j++){
			MeanRunLengthMatrix->SetMatrixValue(i, j, (MeanRunLengthMatrix->GetMatrixValue(i, j) / 4));
		}
	}

	return MeanRunLengthMatrix;

}

