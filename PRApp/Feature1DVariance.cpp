#include "stdafx.h"
#include "Feature1DVariance.h"

CFeature1DVariance::CFeature1DVariance()
{

	m_dblVariance = 0.0f;

}

CFeature1DVariance::~CFeature1DVariance()
{

}

void CFeature1DVariance::CalculateVariance (CDataMatrix1D *pDataMatrix1D){

	CFeature2DVariance *Feature2DVariance = new CFeature2DVariance();

	Feature2DVariance->CalculateVariance(pDataMatrix1D->GetDataMatrix1DAsDataMatrix2D());
	m_dblVariance = Feature2DVariance->GetVariance();

	delete Feature2DVariance;
	Feature2DVariance = NULL;

}
