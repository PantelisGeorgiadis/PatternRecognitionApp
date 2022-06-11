#include "stdafx.h"
#include "Feature1DSum.h"

CFeature1DSum::CFeature1DSum()
{

	m_dblSum = 0.0f;

}

CFeature1DSum::~CFeature1DSum()
{

}

void CFeature1DSum::CalculateSum (CDataMatrix1D *pDataMatrix1D){

	CFeature2DSum *Feature2DSum = new CFeature2DSum();

	Feature2DSum->CalculateSum(pDataMatrix1D->GetDataMatrix1DAsDataMatrix2D());
	m_dblSum = Feature2DSum->GetSum();

	delete Feature2DSum;
	Feature2DSum = NULL;

}
