#include "stdafx.h"
#include "FastMath.h"
#include "StandardDeviation.h"

CStandardDeviation::CStandardDeviation()
{

	m_dblStandardDeviation = 0.0f;

}

CStandardDeviation::~CStandardDeviation()
{

}

void CStandardDeviation::CalculateFeaturesStandardDeviation (CClass *pClass, double dblFeaturesMeanValue, int iFeaturesIndex){

	double dblSum = 0.0f;
	
	for (int i=0;i<pClass->GetNumberOfPatterns();i++){ 
		dblSum = dblSum + pow((pClass->GetPattern(i)->GetFeature(iFeaturesIndex)->GetFeatureValue() - dblFeaturesMeanValue), 2);
	}

	m_dblStandardDeviation = CFastMath::FastSqrt((double)(dblSum / (double)(pClass->GetNumberOfPatterns() - 1)));

}
