#include "stdafx.h"
#include "Feature2DGrayLevelNonUniformity.h"

CFeature2DGrayLevelNonUniformity::CFeature2DGrayLevelNonUniformity()
{

	m_dblGrayLevelNonUniformity = 0.0f;

}

CFeature2DGrayLevelNonUniformity::~CFeature2DGrayLevelNonUniformity()
{

}

void CFeature2DGrayLevelNonUniformity::CalculateGrayLevelNonUniformity (CDataMatrix2D *pDataMatrix2D){

	double dblSum1 = 0.0f;
	double dblSum2 = 0.0f;

	CFeature2DSum *Sum = new CFeature2DSum();

	for (int i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		for (int j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			dblSum1 = dblSum1 + pDataMatrix2D->GetMatrixValue(i, j);
		}
		dblSum2 = dblSum2 + pow(dblSum1, 2);
		dblSum1 = 0.0f;
	}

	Sum->CalculateSum(pDataMatrix2D);

	m_dblGrayLevelNonUniformity = (dblSum2 / Sum->GetSum());

	delete Sum;
	Sum = NULL;

}

