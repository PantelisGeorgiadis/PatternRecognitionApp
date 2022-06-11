#include "stdafx.h"
#include "Feature3DMeanFeature.h"

CFeature3DMeanFeature::CFeature3DMeanFeature()
{

	m_dblMeanFeatureValue = 0.0f;

}

CFeature3DMeanFeature::~CFeature3DMeanFeature()
{

}

void CFeature3DMeanFeature::CalculateMeanFeatureValue (double f0, double f1, double f2, double f3, double f4, double f5, double f6, double f7, double f8, double f9, double f10, double f11, double f12){

	m_dblMeanFeatureValue = ((f0 + f1 + f2 + f3 + f4 + f5 + f6 + f7 + f8 + f9 + f10 + f11 + f12) / 13.0f);

}
