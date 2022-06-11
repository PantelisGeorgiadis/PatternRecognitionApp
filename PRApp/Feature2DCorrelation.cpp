#include "stdafx.h"
#include "Feature2DCorrelation.h"
#include "Feature2DMeanValue.h"
#include "Feature2DStandardDeviation.h"

CFeature2DCorrelation::CFeature2DCorrelation()
{

	m_dblCorrelation = 0.0f;

}

CFeature2DCorrelation::~CFeature2DCorrelation()
{

}

void CFeature2DCorrelation::CalculateCorrelation (CDataMatrix2D *pDataMatrix2D){

	double dblSum = 0.0f;
	double dblRowsMeanValue = 0.0f;
	double dblColumnsMeanValue = 0.0f;
	double dblRowsStandardDeviation = 0.0f;
	double dblColumnsStandardDeviation = 0.0f;

	CDataRowsCollumnsOperationsMatrix2D *MatrixOperation = new CDataRowsCollumnsOperationsMatrix2D();
	MatrixOperation->RowsMean(pDataMatrix2D);
	dblRowsMeanValue = MatrixOperation->GetRowsMean();
	dblColumnsMeanValue = MatrixOperation->GetRowsMean();
	MatrixOperation->RowsStandardDeviation(pDataMatrix2D);
	dblRowsStandardDeviation = MatrixOperation->GetRowsStandardDeviation();
	dblColumnsStandardDeviation = MatrixOperation->GetRowsStandardDeviation();

	for (int i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		for (int j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			dblSum = dblSum + ((i - dblRowsMeanValue) * (j - dblColumnsMeanValue) * pDataMatrix2D->GetMatrixValue(i, j));
		}
	}
	
	m_dblCorrelation = dblSum / (dblRowsStandardDeviation * dblColumnsStandardDeviation);

	delete MatrixOperation;
	MatrixOperation = NULL;

}
