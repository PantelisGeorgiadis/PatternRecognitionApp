#include "stdafx.h"
#include "Feature2DRangeFeature.h"

CFeature2DRangeFeature::CFeature2DRangeFeature()
{

	m_dblRangeFeatureValue = 0.0f;

}

CFeature2DRangeFeature::~CFeature2DRangeFeature()
{

}

void CFeature2DRangeFeature::CalculateRangeFeatureValue (double f0, double f45, double f90, double f135){

	double dblFeatureMatrix[4];
	int i;

	double dblMin = (std::numeric_limits<double>::max)();
	double dblMax = (std::numeric_limits<double>::min)();

	dblFeatureMatrix[0] = f0;
	dblFeatureMatrix[1] = f45;
	dblFeatureMatrix[2] = f90;
	dblFeatureMatrix[3] = f135;

	dblMax = dblFeatureMatrix[0];

	for (i=0;i<4;i++){
		if (dblFeatureMatrix[i] > dblMax){
			dblMax = dblFeatureMatrix[i];
		}
	}

	dblMin = dblFeatureMatrix[0];

	for (i=0;i<4;i++){
		if (dblFeatureMatrix[i] < dblMin){
			dblMin = dblFeatureMatrix[i];
		}
	}

	m_dblRangeFeatureValue = dblMax - dblMin;

}
