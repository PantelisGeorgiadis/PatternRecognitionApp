#include "stdafx.h"
#include "Feature3DMeanValue.h"

CFeature3DMeanValue::CFeature3DMeanValue()
{

	m_dblMeanValue = 0.0f;

}

CFeature3DMeanValue::~CFeature3DMeanValue()
{

}

void CFeature3DMeanValue::CalculateMeanValue (CDataMatrix3D *pDataMatrix3D){

	double dblSum = 0.0f;

	CFeature3DSum *FeatureSum = new CFeature3DSum();
	FeatureSum->CalculateSum(pDataMatrix3D);
	dblSum = FeatureSum->GetSum();

	m_dblMeanValue = (double)(dblSum / (double)(pDataMatrix3D->GetNumberOfLayers() * pDataMatrix3D->GetNumberOfRows() * pDataMatrix3D->GetNumberOfColumns()));

	delete FeatureSum;
	FeatureSum = NULL;

}
