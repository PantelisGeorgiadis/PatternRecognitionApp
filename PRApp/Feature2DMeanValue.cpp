#include "stdafx.h"
#include "Feature2DMeanValue.h"

CFeature2DMeanValue::CFeature2DMeanValue()
{

	m_dblMeanValue = 0.0f;

}

CFeature2DMeanValue::~CFeature2DMeanValue()
{

}

void CFeature2DMeanValue::CalculateMeanValue (CDataMatrix2D *pDataMatrix2D){

	double dblSum = 0.0f;

	CFeature2DSum *FeatureSum = new CFeature2DSum();
	FeatureSum->CalculateSum(pDataMatrix2D);
	dblSum = FeatureSum->GetSum();

	m_dblMeanValue = (double)(dblSum / (double)(pDataMatrix2D->GetNumberOfRows() * pDataMatrix2D->GetNumberOfColumns()));

	delete FeatureSum;
	FeatureSum = NULL;

}
