#include "stdafx.h"
#include "Feature1DStandardDeviation.h"

CFeature1DStandardDeviation::CFeature1DStandardDeviation()
{

	m_dblStandardDeviation = 0.0f;

}

CFeature1DStandardDeviation::~CFeature1DStandardDeviation()
{

}

void CFeature1DStandardDeviation::CalculateStandardDeviation (CDataMatrix1D *pDataMatrix1D){

	CFeature2DStandardDeviation *Feature2DStandardDeviation = new CFeature2DStandardDeviation();

	Feature2DStandardDeviation->CalculateStandardDeviation(pDataMatrix1D->GetDataMatrix1DAsDataMatrix2D());
	m_dblStandardDeviation = Feature2DStandardDeviation->GetStandardDeviation();

	delete Feature2DStandardDeviation;
	Feature2DStandardDeviation = NULL;

}

