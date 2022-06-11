#include "stdafx.h"
#include "Feature1DMeanValue.h"

CFeature1DMeanValue::CFeature1DMeanValue()
{

	m_dblMeanValue = 0.0f;

}

CFeature1DMeanValue::~CFeature1DMeanValue()
{

}

void CFeature1DMeanValue::CalculateMeanValue (CDataMatrix1D *pDataMatrix1D){

	CFeature2DMeanValue *Feature2DMeanValue = new CFeature2DMeanValue();

	Feature2DMeanValue->CalculateMeanValue(pDataMatrix1D->GetDataMatrix1DAsDataMatrix2D());
	m_dblMeanValue = Feature2DMeanValue->GetMeanValue();

	delete Feature2DMeanValue;
	Feature2DMeanValue = NULL;

}
