#include "stdafx.h"
#include "Feature3DVariance.h"

CFeature3DVariance::CFeature3DVariance()
{

	m_dblVariance = 0.0f;

}

CFeature3DVariance::~CFeature3DVariance()
{

}

void CFeature3DVariance::CalculateVariance (CDataMatrix3D *pDataMatrix3D){

	double dblSum = 0.0f;

	CFeature3DMeanValue *FeatureMeanValue = new CFeature3DMeanValue();
	FeatureMeanValue->CalculateMeanValue(pDataMatrix3D);

	for (int i=0;i<pDataMatrix3D->GetNumberOfLayers();i++){
		for (int j=0;j<pDataMatrix3D->GetNumberOfRows();j++){
			for (int k=0;k<pDataMatrix3D->GetNumberOfColumns();k++){
				dblSum = dblSum + pow((pDataMatrix3D->GetMatrixValue(i, j, k) - FeatureMeanValue->GetMeanValue()), 2);
			}
		}
	}

	m_dblVariance = dblSum / (double)((pDataMatrix3D->GetNumberOfLayers() * pDataMatrix3D->GetNumberOfRows() * pDataMatrix3D->GetNumberOfColumns()));

	delete FeatureMeanValue;
	FeatureMeanValue = NULL;

}
