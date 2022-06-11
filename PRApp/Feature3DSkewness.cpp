#include "stdafx.h"
#include "Feature3DSkewness.h"

CFeature3DSkewness::CFeature3DSkewness()
{

	m_dblSkewness = 0.0f;

}

CFeature3DSkewness::~CFeature3DSkewness()
{

}

void CFeature3DSkewness::CalculateSkewness (CDataMatrix3D *pDataMatrix3D){

	double dblSum = 0.0f;

	CFeature3DStandardDeviation *FeatureStandardDeviation = new CFeature3DStandardDeviation();
	FeatureStandardDeviation->CalculateStandardDeviation(pDataMatrix3D);
	CFeature3DMeanValue *FeatureMeanValue = new CFeature3DMeanValue();
	FeatureMeanValue->CalculateMeanValue(pDataMatrix3D);

	for (int i=0;i<pDataMatrix3D->GetNumberOfLayers();i++){
		for (int j=0;j<pDataMatrix3D->GetNumberOfRows();j++){
			for (int k=0;k<pDataMatrix3D->GetNumberOfColumns();k++){
				dblSum = dblSum + pow((pDataMatrix3D->GetMatrixValue(i, j, k) - FeatureMeanValue->GetMeanValue()), 3);
			}
		}
	}

	m_dblSkewness = dblSum / (double)((pDataMatrix3D->GetNumberOfLayers() * pDataMatrix3D->GetNumberOfRows() * pDataMatrix3D->GetNumberOfColumns()) * pow(FeatureStandardDeviation->GetStandardDeviation(), 3));

	delete FeatureMeanValue;
	FeatureMeanValue = NULL;
	delete FeatureStandardDeviation;
	FeatureStandardDeviation = NULL;

}
