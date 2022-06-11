#include "stdafx.h"
#include "FastMath.h"
#include "Feature3DStandardDeviation.h"

CFeature3DStandardDeviation::CFeature3DStandardDeviation()
{

	m_dblStandardDeviation = 0.0f;

}

CFeature3DStandardDeviation::~CFeature3DStandardDeviation()
{

}

void CFeature3DStandardDeviation::CalculateStandardDeviation (CDataMatrix3D *pDataMatrix3D){

	CFeature3DVariance *FeatureVariance = new CFeature3DVariance();
	FeatureVariance->CalculateVariance(pDataMatrix3D);

	m_dblStandardDeviation = CFastMath::FastSqrt(FeatureVariance->GetVariance());

	delete FeatureVariance;
	FeatureVariance = NULL;

}
