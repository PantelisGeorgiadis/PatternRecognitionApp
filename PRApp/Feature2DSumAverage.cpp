#include "stdafx.h"
#include "Feature2DSumAverage.h"
#include "DataRowsCollumnsOperationsMatrix2D.h"

CFeature2DSumAverage::CFeature2DSumAverage()
{

	m_dblSumAverage = 0.0f;

}

CFeature2DSumAverage::~CFeature2DSumAverage()
{

}

void CFeature2DSumAverage::CalculateSumAverage (CDataMatrix2D *pDataMatrix2D){

	double dblSum = 0.0f;

	CDataMatrix2D *RowsCollumnsAdditionMatrix = NULL; 
	CDataRowsCollumnsOperationsMatrix2D *RowsCollumnsAddition = new CDataRowsCollumnsOperationsMatrix2D();
	RowsCollumnsAdditionMatrix = RowsCollumnsAddition->RowsCollumnsAddition(pDataMatrix2D);

	for (int i=2;i<((2 * pDataMatrix2D->GetNumberOfRows()) + 1);i++){
		dblSum = dblSum + (i * RowsCollumnsAdditionMatrix->GetMatrixValue(0, i));
	}

	m_dblSumAverage = dblSum;

	delete RowsCollumnsAddition;
	RowsCollumnsAddition = NULL;
	delete RowsCollumnsAdditionMatrix;
	RowsCollumnsAdditionMatrix = NULL;

}
