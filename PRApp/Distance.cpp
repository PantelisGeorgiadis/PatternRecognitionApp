#include "stdafx.h"
#include "FastMath.h"
#include "Distance.h"

CDistance::CDistance()
{

	m_dblDistance = -1.0f;
	m_iPatternClassIndex1 = -1;
	m_iPatternClassIndex2 = -1;

}

CDistance::~CDistance()
{

}

void CDistance::CalculatePatternsDistance (CPattern *pPattern1, int iPatternClassIndex1, CPattern *pPattern2, int iPatternClassIndex2){

	double dblSum = 0.0f;

	m_iPatternClassIndex1 = iPatternClassIndex1;
	m_iPatternClassIndex2 = iPatternClassIndex2;
	
	if (pPattern1->GetNumberOfFeatures() != pPattern2->GetNumberOfFeatures()){
		return;
	}
	
	for (int i=0;i<pPattern1->GetNumberOfFeatures();i++){
		dblSum = dblSum + pow((pPattern2->GetFeature(i)->GetFeatureValue() - pPattern1->GetFeature(i)->GetFeatureValue()), 2);
	}

	m_dblDistance = CFastMath::FastSqrt(dblSum);

}

void CDistance::CalculatePatternsDistance (CPattern *pPattern1, CPattern *pPattern2){

	CalculatePatternsDistance(pPattern1, -1, pPattern2, -1);

}

CSquaredDistance::CSquaredDistance()
{

	m_dblSquaredDistance = -1.0f;
	m_iPatternClassIndex1 = -1;
	m_iPatternClassIndex2 = -1;

}

CSquaredDistance::~CSquaredDistance()
{

}

void CSquaredDistance::CalculatePatternsSquaredDistance (CPattern *pPattern1, int iPatternClassIndex1, CPattern *pPattern2, int iPatternClassIndex2){

	double dblSquaredSum = 0.0f;

	m_iPatternClassIndex1 = iPatternClassIndex1;
	m_iPatternClassIndex2 = iPatternClassIndex2;
	
	if (pPattern1->GetNumberOfFeatures() != pPattern2->GetNumberOfFeatures()){
		return;
	}
	
	for (int i=0;i<pPattern1->GetNumberOfFeatures();i++){
		dblSquaredSum = dblSquaredSum + pow((pPattern2->GetFeature(i)->GetFeatureValue() - pPattern1->GetFeature(i)->GetFeatureValue()), 2);
	}

	m_dblSquaredDistance = dblSquaredSum;

}

void CSquaredDistance::CalculatePatternsSquaredDistance (CPattern *pPattern1, CPattern *pPattern2){

	CalculatePatternsSquaredDistance(pPattern1, -1, pPattern2, -1);

}
