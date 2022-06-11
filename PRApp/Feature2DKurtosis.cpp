#include "stdafx.h"
#include "Feature2DKurtosis.h"

CFeature2DKurtosis::CFeature2DKurtosis()
{

	m_dblKurtosis = 0.0f;

}

CFeature2DKurtosis::~CFeature2DKurtosis()
{

}

void CFeature2DKurtosis::CalculateKurtosis (CDataMatrix2D *pDataMatrix2D){

	double dblSum = 0.0f;

	CFeature2DStandardDeviation *FeatureStandardDeviation = new CFeature2DStandardDeviation();
	FeatureStandardDeviation->CalculateStandardDeviation(pDataMatrix2D);
	CFeature2DMeanValue *FeatureMeanValue = new CFeature2DMeanValue();
	FeatureMeanValue->CalculateMeanValue(pDataMatrix2D);

	for (int i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		for (int j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			dblSum = dblSum + pow((pDataMatrix2D->GetMatrixValue(i, j) - FeatureMeanValue->GetMeanValue()), 4);
		}
	}

	m_dblKurtosis = dblSum / (double)(((pDataMatrix2D->GetNumberOfRows() * pDataMatrix2D->GetNumberOfColumns())/* - 1.0f*/) * pow(FeatureStandardDeviation->GetStandardDeviation(), 4));

	delete FeatureMeanValue;
	FeatureMeanValue = NULL;
	delete FeatureStandardDeviation;
	FeatureStandardDeviation = NULL;

}
