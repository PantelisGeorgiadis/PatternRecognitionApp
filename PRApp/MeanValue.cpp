#include "stdafx.h"
#include "MeanValue.h"

CMeanValue::CMeanValue()
{

	m_dblMeanValue = 0.0f;

}

CMeanValue::~CMeanValue()
{

}

void CMeanValue::CalculateFeaturesMeanValue (CClass *pClass, int iFeaturesIndex){

	double dblSum = 0.0f;
	
	for (int i=0;i<pClass->GetNumberOfPatterns();i++){ 
		dblSum = dblSum + pClass->GetPattern(i)->GetFeature(iFeaturesIndex)->GetFeatureValue();
	}

	m_dblMeanValue = (double)(dblSum / (double)(pClass->GetNumberOfPatterns()));

}
