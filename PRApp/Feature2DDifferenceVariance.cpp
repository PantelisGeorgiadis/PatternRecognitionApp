#include "stdafx.h"
#include "Feature2DDifferenceVariance.h"
#include "DataRowsCollumnsOperationsMatrix2D.h"

CFeature2DDifferenceVariance::CFeature2DDifferenceVariance()
{

	m_dblDifferenceVariance = 0.0f;

}

CFeature2DDifferenceVariance::~CFeature2DDifferenceVariance()
{

}

void CFeature2DDifferenceVariance::CalculateDifferenceVariance (CDataMatrix2D *pDataMatrix2D){

	int i;
	int iIndex = 0;
	double dblSum1 = 0.0f;
	double dblSum2 = 0.0f;

	CDataMatrix2D *MatrixDx = new CDataMatrix2D(1, pDataMatrix2D->GetNumberOfRows());

	for (i=1;i<(pDataMatrix2D->GetNumberOfRows() + 1);i++){
		for (int j=1;j<(pDataMatrix2D->GetNumberOfColumns() + 1);j++){
			iIndex = abs((i - 1) - (j - 1));
			MatrixDx->SetMatrixValue(0, (iIndex + 1), (MatrixDx->GetMatrixValue(0, (iIndex + 1)) + pDataMatrix2D->GetMatrixValue((i - 1), (j - 1))));
		}
	}

	for (i=1;i<(pDataMatrix2D->GetNumberOfRows() + 1);i++){
		dblSum1 = dblSum1 + ((i - 1) * MatrixDx->GetMatrixValue(0, i));
	}

	for (i=1;i<(pDataMatrix2D->GetNumberOfRows() + 1);i++){
		dblSum2 = dblSum2 + (pow((i - 1) - dblSum1, 2) * MatrixDx->GetMatrixValue(0, i));
	}

	m_dblDifferenceVariance = dblSum2;

	delete MatrixDx;
	MatrixDx = NULL;

}

