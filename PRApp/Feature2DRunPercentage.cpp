#include "stdafx.h"
#include "Feature2DRunPercentage.h"

CFeature2DRunPercentage::CFeature2DRunPercentage()
{

	m_dblRunPercentage = 0.0f;

}

CFeature2DRunPercentage::~CFeature2DRunPercentage()
{

}

void CFeature2DRunPercentage::CalculateRunPercentage (CDataMatrix2D *pDataMatrix2D, int iImageWidth, int iImageHeight){

	double dblSum = 0.0f;

	for (int i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		for (int j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			dblSum = dblSum + (pDataMatrix2D->GetMatrixValue(i, j) / (iImageWidth * iImageHeight));
		}
	}

	m_dblRunPercentage = dblSum;

}
