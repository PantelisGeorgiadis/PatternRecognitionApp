#include "stdafx.h"
#include "Feature1DKurtosis.h"

CFeature1DKurtosis::CFeature1DKurtosis()
{

	m_dblKurtosis = 0.0f;

}

CFeature1DKurtosis::~CFeature1DKurtosis()
{

}

void CFeature1DKurtosis::CalculateKurtosis (CDataMatrix1D *pDataMatrix1D){

	CFeature2DKurtosis *Feature2DKurtosis = new CFeature2DKurtosis();

	Feature2DKurtosis->CalculateKurtosis(pDataMatrix1D->GetDataMatrix1DAsDataMatrix2D());
	m_dblKurtosis = Feature2DKurtosis->GetKurtosis();

	delete Feature2DKurtosis;
	Feature2DKurtosis = NULL;

}

