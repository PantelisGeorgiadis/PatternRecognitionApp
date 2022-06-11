#include "stdafx.h"
#include "Feature2DMeanFeature.h"

CFeature2DMeanFeature::CFeature2DMeanFeature()
{

	m_dblMeanFeatureValue = 0.0f;

}

CFeature2DMeanFeature::~CFeature2DMeanFeature()
{

}

void CFeature2DMeanFeature::CalculateMeanFeatureValue (double f0, double f45, double f90, double f135){

	m_dblMeanFeatureValue = ((f0 + f45 + f90 + f135) / 4.0f);

}

