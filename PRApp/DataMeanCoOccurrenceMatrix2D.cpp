#include "stdafx.h"
#include "DataMeanCoOccurrenceMatrix2D.h"

CDataMeanCoOccurrenceMatrix2D::CDataMeanCoOccurrenceMatrix2D()
{

}

CDataMeanCoOccurrenceMatrix2D::~CDataMeanCoOccurrenceMatrix2D()
{

}

CDataCoOccurrenceMatrix2D *CDataMeanCoOccurrenceMatrix2D::CalculateMeanCoOccurrenceMatrix(CDataCoOccurrenceMatrix2D *pDataCoOccurrenceMatrix2D0, CDataCoOccurrenceMatrix2D *pDataCoOccurrenceMatrix2D45, CDataCoOccurrenceMatrix2D *pDataCoOccurrenceMatrix2D90, CDataCoOccurrenceMatrix2D *pDataCoOccurrenceMatrix2D135){

	int i, j;

	CDataCoOccurrenceMatrix2D *MeanCoOccurrenceMatrix = new CDataCoOccurrenceMatrix2D();
	MeanCoOccurrenceMatrix->CreateDataMatrix(pDataCoOccurrenceMatrix2D0->GetDepth(), pDataCoOccurrenceMatrix2D0->GetMatrixRotationDegrees());

	for (i=0;i<MeanCoOccurrenceMatrix->GetNumberOfRows();i++){
		for (j=0;j<MeanCoOccurrenceMatrix->GetNumberOfColumns();j++){
			MeanCoOccurrenceMatrix->SetMatrixValue(i, j, (pDataCoOccurrenceMatrix2D0->GetMatrixValue(i, j) + pDataCoOccurrenceMatrix2D45->GetMatrixValue(i, j) + pDataCoOccurrenceMatrix2D90->GetMatrixValue(i, j) + pDataCoOccurrenceMatrix2D135->GetMatrixValue(i, j)));
		}
	}

	for (i=0;i<MeanCoOccurrenceMatrix->GetNumberOfRows();i++){
		for (j=0;j<MeanCoOccurrenceMatrix->GetNumberOfColumns();j++){
			MeanCoOccurrenceMatrix->SetMatrixValue(i, j, (MeanCoOccurrenceMatrix->GetMatrixValue(i, j) / 4));
		}
	}

	return MeanCoOccurrenceMatrix;

}

