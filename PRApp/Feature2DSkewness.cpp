#include "stdafx.h"
#include "Feature2DSkewness.h"

CFeature2DSkewness::CFeature2DSkewness()
{

	m_dblSkewness = 0.0f;

}

CFeature2DSkewness::~CFeature2DSkewness()
{

}

void CFeature2DSkewness::CalculateSkewness (CDataMatrix2D *pDataMatrix2D){

	double dblSum = 0.0f;

	CFeature2DStandardDeviation *FeatureStandardDeviation = new CFeature2DStandardDeviation();
	FeatureStandardDeviation->CalculateStandardDeviation(pDataMatrix2D);
	CFeature2DMeanValue *FeatureMeanValue = new CFeature2DMeanValue();
	FeatureMeanValue->CalculateMeanValue(pDataMatrix2D);

	for (int i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		for (int j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			dblSum = dblSum + pow((pDataMatrix2D->GetMatrixValue(i, j) - FeatureMeanValue->GetMeanValue()), 3);
		}
	}

	m_dblSkewness = dblSum / (double)((pDataMatrix2D->GetNumberOfRows() * pDataMatrix2D->GetNumberOfColumns()) * pow(FeatureStandardDeviation->GetStandardDeviation(), 3));

	delete FeatureMeanValue;
	FeatureMeanValue = NULL;
	delete FeatureStandardDeviation;
	FeatureStandardDeviation = NULL;

}
