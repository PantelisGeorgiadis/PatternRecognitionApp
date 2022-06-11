#include "stdafx.h"
#include "Feature3DKurtosis.h"

CFeature3DKurtosis::CFeature3DKurtosis()
{

	m_dblKurtosis = 0.0f;

}

CFeature3DKurtosis::~CFeature3DKurtosis()
{

}

void CFeature3DKurtosis::CalculateKurtosis (CDataMatrix3D *pDataMatrix3D){

	double dblSum = 0.0f;

	CFeature3DStandardDeviation *FeatureStandardDeviation = new CFeature3DStandardDeviation();
	FeatureStandardDeviation->CalculateStandardDeviation(pDataMatrix3D);
	CFeature3DMeanValue *FeatureMeanValue = new CFeature3DMeanValue();
	FeatureMeanValue->CalculateMeanValue(pDataMatrix3D);

	for (int i=0;i<pDataMatrix3D->GetNumberOfLayers();i++){
		for (int j=0;j<pDataMatrix3D->GetNumberOfRows();j++){
			for (int k=0;k<pDataMatrix3D->GetNumberOfColumns();k++){
				dblSum = dblSum + pow((pDataMatrix3D->GetMatrixValue(i, j, k) - FeatureMeanValue->GetMeanValue()), 4);
			}
		}
	}

	m_dblKurtosis = dblSum / (double)(((pDataMatrix3D->GetNumberOfLayers() * pDataMatrix3D->GetNumberOfRows() * pDataMatrix3D->GetNumberOfColumns())/* - 1.0f*/) * pow(FeatureStandardDeviation->GetStandardDeviation(), 4));

	delete FeatureMeanValue;
	FeatureMeanValue = NULL;
	delete FeatureStandardDeviation;
	FeatureStandardDeviation = NULL;

}
