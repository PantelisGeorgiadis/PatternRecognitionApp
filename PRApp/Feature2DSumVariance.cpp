#include "stdafx.h"
#include "Feature2DSumVariance.h"
#include "Feature2DSumAverage.h"
#include "DataRowsCollumnsOperationsMatrix2D.h"

CFeature2DSumVariance::CFeature2DSumVariance()
{

	m_dblSumVariance = 0.0f;

}

CFeature2DSumVariance::~CFeature2DSumVariance()
{

}

void CFeature2DSumVariance::CalculateSumVariance (CDataMatrix2D *pDataMatrix2D){

	double dblSum = 0.0f;

	CDataMatrix2D *RowsCollumnsAdditionMatrix = NULL; 
	CDataRowsCollumnsOperationsMatrix2D *RowsCollumnsAddition = new CDataRowsCollumnsOperationsMatrix2D();
	CFeature2DSumAverage *SumAverage = new CFeature2DSumAverage();

	RowsCollumnsAdditionMatrix = RowsCollumnsAddition->RowsCollumnsAddition(pDataMatrix2D);
	SumAverage->CalculateSumAverage(pDataMatrix2D);

	for (int i=2;i<((2 * pDataMatrix2D->GetNumberOfRows()) + 1);i++){
		dblSum = dblSum + (pow((i - SumAverage->GetSumAverage()), 2) * RowsCollumnsAdditionMatrix->GetMatrixValue(0, i));
	}

	m_dblSumVariance = dblSum;

	delete SumAverage;
	SumAverage = NULL;
	delete RowsCollumnsAddition;
	RowsCollumnsAddition = NULL;
	delete RowsCollumnsAdditionMatrix;
	RowsCollumnsAdditionMatrix = NULL;

}
