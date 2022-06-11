#include "stdafx.h"
#include "Feature3DRangeFeature.h"

CFeature3DRangeFeature::CFeature3DRangeFeature()
{

	m_dblRangeFeatureValue = 0.0f;

}

CFeature3DRangeFeature::~CFeature3DRangeFeature()
{

}

void CFeature3DRangeFeature::CalculateRangeFeatureValue (double f0, double f1, double f2, double f3, double f4, double f5, double f6, double f7, double f8, double f9, double f10, double f11, double f12){

	double dblFeatureMatrix[13];
	int i;

	double dblMin = (std::numeric_limits<double>::max)();
	double dblMax = (std::numeric_limits<double>::min)();

	dblFeatureMatrix[0] = f0;
	dblFeatureMatrix[1] = f1;
	dblFeatureMatrix[2] = f2;
	dblFeatureMatrix[3] = f3;
	dblFeatureMatrix[4] = f4;
	dblFeatureMatrix[5] = f5;
	dblFeatureMatrix[6] = f6;
	dblFeatureMatrix[7] = f7;
	dblFeatureMatrix[8] = f8;
	dblFeatureMatrix[9] = f9;
	dblFeatureMatrix[10] = f10;
	dblFeatureMatrix[11] = f11;
	dblFeatureMatrix[12] = f12;

	dblMax = dblFeatureMatrix[0];

	for (i=0;i<13;i++){
		if (dblFeatureMatrix[i] > dblMax){
			dblMax = dblFeatureMatrix[i];
		}
	}

	dblMin = dblFeatureMatrix[0];

	for (i=0;i<13;i++){
		if (dblFeatureMatrix[i] < dblMin){
			dblMin = dblFeatureMatrix[i];
		}
	}

	m_dblRangeFeatureValue = dblMax - dblMin;

}
