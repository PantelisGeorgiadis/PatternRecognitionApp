#include "stdafx.h"
#include "Feature2DSumEntropy.h"
#include "DataRowsCollumnsOperationsMatrix2D.h"

CFeature2DSumEntropy::CFeature2DSumEntropy()
{

	m_dblSumEntropy = 0.0f;

}

CFeature2DSumEntropy::~CFeature2DSumEntropy()
{

}

void CFeature2DSumEntropy::CalculateSumEntropy (CDataMatrix2D *pDataMatrix2D){

	double dblSum = 0.0f;

	CDataMatrix2D *RowsCollumnsAdditionMatrix = NULL; 
	CDataRowsCollumnsOperationsMatrix2D *RowsCollumnsAddition = new CDataRowsCollumnsOperationsMatrix2D();
	RowsCollumnsAdditionMatrix = RowsCollumnsAddition->RowsCollumnsAddition(pDataMatrix2D);

	for (int i=2;i<((2 * pDataMatrix2D->GetNumberOfRows()) + 1);i++){
		if (RowsCollumnsAdditionMatrix->GetMatrixValue(0, i) == 0){
			dblSum = dblSum + (RowsCollumnsAdditionMatrix->GetMatrixValue(0, i) * log(1.0f));
		}
		else{
			dblSum = dblSum + (RowsCollumnsAdditionMatrix->GetMatrixValue(0, i) * log(RowsCollumnsAdditionMatrix->GetMatrixValue(0, i)));
		}
	}

	m_dblSumEntropy = -dblSum;

	delete RowsCollumnsAddition;
	RowsCollumnsAddition = NULL;
	delete RowsCollumnsAdditionMatrix;
	RowsCollumnsAdditionMatrix = NULL;

}

