#include "stdafx.h"
#include "Centroid.h"

CCentroid::CCentroid()
{

}

CCentroid::~CCentroid()
{

}

CPattern *CCentroid::CalculateClassCentroid (CClass *pClass, CentroidType ct){

	CPattern *Pattern = new CPattern(pClass->GetNumberOfFeaturesPerPattern());
	CMeanValue *MeanValue = new CMeanValue();
	
	for (int i=0;i<pClass->GetNumberOfFeaturesPerPattern();i++){
		MeanValue->CalculateFeaturesMeanValue(pClass, i);
		Pattern->GetFeature(i)->SetFeatureValue(MeanValue->GetMeanValue());
	}

	delete MeanValue;
	MeanValue = NULL;

	return Pattern;

}
