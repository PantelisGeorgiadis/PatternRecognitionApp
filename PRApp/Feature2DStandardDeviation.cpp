#include "stdafx.h"
#include "FastMath.h"
#include "Feature2DStandardDeviation.h"

CFeature2DStandardDeviation::CFeature2DStandardDeviation()
{

	m_dblStandardDeviation = 0.0f;

}

CFeature2DStandardDeviation::~CFeature2DStandardDeviation()
{

}

void CFeature2DStandardDeviation::CalculateStandardDeviation (CDataMatrix2D *pDataMatrix2D){

	CFeature2DVariance *FeatureVariance = new CFeature2DVariance();
	FeatureVariance->CalculateVariance(pDataMatrix2D);

	m_dblStandardDeviation = CFastMath::FastSqrt(FeatureVariance->GetVariance());

	delete FeatureVariance;
	FeatureVariance = NULL;

}
