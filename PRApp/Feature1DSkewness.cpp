#include "stdafx.h"
#include "Feature1DSkewness.h"

CFeature1DSkewness::CFeature1DSkewness()
{

	m_dblSkewness = 0.0f;

}

CFeature1DSkewness::~CFeature1DSkewness()
{

}

void CFeature1DSkewness::CalculateSkewness (CDataMatrix1D *pDataMatrix1D){

	CFeature2DSkewness *Feature2DSkewness = new CFeature2DSkewness();

	Feature2DSkewness->CalculateSkewness(pDataMatrix1D->GetDataMatrix1DAsDataMatrix2D());
	m_dblSkewness = Feature2DSkewness->GetSkewness();

	delete Feature2DSkewness;
	Feature2DSkewness = NULL;

}
