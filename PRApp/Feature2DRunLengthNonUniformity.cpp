#include "stdafx.h"
#include "Feature2DRunLengthNonUniformity.h"

CFeature2DRunLengthNonUniformity::CFeature2DRunLengthNonUniformity()
{

	m_dblRunLengthNonUniformity = 0.0f;

}

CFeature2DRunLengthNonUniformity::~CFeature2DRunLengthNonUniformity()
{

}

void CFeature2DRunLengthNonUniformity::CalculateRunLengthNonUniformity (CDataMatrix2D *pDataMatrix2D){

	double dblSum1 = 0.0f;
	double dblSum2 = 0.0f;

	CFeature2DSum *Sum = new CFeature2DSum();

	for (int j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
		for (int i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
			dblSum1 = dblSum1 + pDataMatrix2D->GetMatrixValue(i, j);
		}
		dblSum2 = dblSum2 + pow(dblSum1, 2);
		dblSum1 = 0.0f;
	}

	Sum->CalculateSum(pDataMatrix2D);

	m_dblRunLengthNonUniformity = (dblSum2 / Sum->GetSum());

	delete Sum;
	Sum = NULL;

}

