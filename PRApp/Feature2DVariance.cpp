#include "stdafx.h"
#include "Feature2DVariance.h"

CFeature2DVariance::CFeature2DVariance()
{

	m_dblVariance = 0.0f;

}

CFeature2DVariance::~CFeature2DVariance()
{

}

void CFeature2DVariance::CalculateVariance (CDataMatrix2D *pDataMatrix2D){

	double dblSum = 0.0f;

	CFeature2DMeanValue *FeatureMeanValue = new CFeature2DMeanValue();
	FeatureMeanValue->CalculateMeanValue(pDataMatrix2D);

	for (int i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		for (int j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			dblSum = dblSum + pow((pDataMatrix2D->GetMatrixValue(i, j) - FeatureMeanValue->GetMeanValue()), 2);
		}
	}

	m_dblVariance = dblSum / (double)((pDataMatrix2D->GetNumberOfRows() * pDataMatrix2D->GetNumberOfColumns()));

	delete FeatureMeanValue;
	FeatureMeanValue = NULL;

}
