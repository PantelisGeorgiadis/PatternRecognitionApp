#include "stdafx.h"
#include "Feature2DShortRunEmphasis.h"

CFeature2DShortRunEmphasis::CFeature2DShortRunEmphasis()
{

	m_dblShortRunEmphasis = 0.0f;

}

CFeature2DShortRunEmphasis::~CFeature2DShortRunEmphasis()
{

}

void CFeature2DShortRunEmphasis::CalculateShortRunEmphasis (CDataMatrix2D *pDataMatrix2D){

	double dblSum = 0.0f;
	int i, j;

	CFeature2DSum *Sum = new CFeature2DSum();

	for (i=1;i<(pDataMatrix2D->GetNumberOfRows() + 1);i++){
		for (j=1;j<(pDataMatrix2D->GetNumberOfColumns() + 1);j++){
			dblSum = dblSum + (pDataMatrix2D->GetMatrixValue((i - 1), (j - 1)) / pow((float)(j), 2));
		}
	}

	Sum->CalculateSum(pDataMatrix2D);

	m_dblShortRunEmphasis = (dblSum / Sum->GetSum());

	delete Sum;
	Sum = NULL;

}

