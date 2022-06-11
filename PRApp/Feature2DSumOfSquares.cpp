#include "stdafx.h"
#include "Feature2DSumOfSquares.h"

CFeature2DSumOfSquares::CFeature2DSumOfSquares()
{

	m_dblSumOfSquares = 0.0f;

}

CFeature2DSumOfSquares::~CFeature2DSumOfSquares()
{

}

void CFeature2DSumOfSquares::CalculateSumOfSquares (CDataMatrix2D *pDataMatrix2D){

	double dblSum = 0.0f;

	CDataRowsCollumnsOperationsMatrix2D *RowsMeanValue = new CDataRowsCollumnsOperationsMatrix2D();
	RowsMeanValue->RowsMean(pDataMatrix2D);

	for (int i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		for (int j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			dblSum = dblSum + (pow((i - RowsMeanValue->GetRowsMean()), 2) * pDataMatrix2D->GetMatrixValue(i, j));
		}
	}

	m_dblSumOfSquares = dblSum;

	delete RowsMeanValue;
	RowsMeanValue = NULL;

}


