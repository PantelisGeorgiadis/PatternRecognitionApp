#include "stdafx.h"
#include "FastMath.h"
#include "DataRowsCollumnsOperationsMatrix2D.h"

CDataRowsCollumnsOperationsMatrix2D::CDataRowsCollumnsOperationsMatrix2D()
{

	m_dblRowsMean = 0.0f;
	m_dblRowsStandardDeviation = 0.0f;

}

CDataRowsCollumnsOperationsMatrix2D::~CDataRowsCollumnsOperationsMatrix2D()
{

}

// Px+y(k)

CDataMatrix2D *CDataRowsCollumnsOperationsMatrix2D::RowsCollumnsAddition (CDataMatrix2D *pDataMatrix2D){	
	
	CDataMatrix2D *RowsColumnsAdditionMatrix = new CDataMatrix2D(1, ((2 * pDataMatrix2D->GetNumberOfRows()) + 1)); 
	
	for (int k=2;k<((2 * pDataMatrix2D->GetNumberOfRows()) + 1);k++){
		for (int i=1;i<(pDataMatrix2D->GetNumberOfRows() + 1);i++){
			for (int j=1;j<(pDataMatrix2D->GetNumberOfColumns() + 1);j++){
				if ((i + j) == k){
					RowsColumnsAdditionMatrix->SetMatrixValue(0, k, (RowsColumnsAdditionMatrix->GetMatrixValue(0, k) + pDataMatrix2D->GetMatrixValue((i - 1), (j - 1))));
				}
			}
		}
	}

	return RowsColumnsAdditionMatrix;

}

// Px-y(k)

CDataMatrix2D *CDataRowsCollumnsOperationsMatrix2D::RowsCollumnsSubtraction (CDataMatrix2D *pDataMatrix2D){	
	
	CDataMatrix2D *RowsColumnsSubtractionMatrix = new CDataMatrix2D(1, pDataMatrix2D->GetNumberOfRows()); 
	
	for (int k=0;k<((pDataMatrix2D->GetNumberOfRows() - 1) + 1);k++){
		for (int i=1;i<(pDataMatrix2D->GetNumberOfRows() + 1);i++){
			for (int j=1;j<(pDataMatrix2D->GetNumberOfColumns() + 1);j++){
				if (abs(i - j) == k){
					RowsColumnsSubtractionMatrix->SetMatrixValue(0, (k + 1), (RowsColumnsSubtractionMatrix->GetMatrixValue(0, (k + 1)) + pDataMatrix2D->GetMatrixValue((i - 1), (j - 1))));
				}
			}
		}
	}

	return RowsColumnsSubtractionMatrix;
	
}

void CDataRowsCollumnsOperationsMatrix2D::RowsMean (CDataMatrix2D *pDataMatrix2D){	

	double dblSum = 0.0;
	int i, j;

	CDataMatrix2D *RowSumMatrix = new CDataMatrix2D(1, pDataMatrix2D->GetNumberOfRows());
	
	for (i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		dblSum = 0.0f;
		for (j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			dblSum = dblSum + pDataMatrix2D->GetMatrixValue(i, j);
		}
		RowSumMatrix->SetMatrixValue(0, i, dblSum);
	}

	dblSum = 0.0f;
	for (i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		dblSum = dblSum + (i * RowSumMatrix->GetMatrixValue(0, i));
	}

	delete RowSumMatrix;
	RowSumMatrix = NULL;

	m_dblRowsMean = dblSum;

}

void CDataRowsCollumnsOperationsMatrix2D::RowsStandardDeviation (CDataMatrix2D *pDataMatrix2D){	

	double dblSum = 0.0;
	int i, j;

	CDataMatrix2D *RowSumMatrix = new CDataMatrix2D(1, pDataMatrix2D->GetNumberOfRows());
	
	RowsMean(pDataMatrix2D);
	
	for (i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		dblSum = 0.0f;
		for (j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			dblSum = dblSum + pDataMatrix2D->GetMatrixValue(i, j);
		}
		RowSumMatrix->SetMatrixValue(0, i, dblSum);
	}

	dblSum = 0.0f;
	for (i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		dblSum = dblSum + (pow(i - GetRowsMean(), 2) * RowSumMatrix->GetMatrixValue(0, i));
	}

	delete RowSumMatrix;
	RowSumMatrix = NULL;

	m_dblRowsStandardDeviation = CFastMath::FastSqrt(dblSum);

}
