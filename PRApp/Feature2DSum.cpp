#include "stdafx.h"
#include "Feature2DSum.h"

CFeature2DSum::CFeature2DSum()
{

	m_dblSum = 0.0f;

}

CFeature2DSum::~CFeature2DSum()
{

}

void CFeature2DSum::CalculateSum (CDataMatrix2D *pDataMatrix2D){

	double dblSum = 0.0f;

	for (int i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		for (int j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			dblSum = dblSum + pDataMatrix2D->GetMatrixValue(i, j);
		}
	}

	m_dblSum = dblSum;

}

