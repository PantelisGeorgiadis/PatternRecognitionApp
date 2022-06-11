#include "stdafx.h"
#include "Feature2DEntropy.h"

CFeature2DEntropy::CFeature2DEntropy()
{

	m_dblEntropy = 0.0f;

}

CFeature2DEntropy::~CFeature2DEntropy()
{

}

void CFeature2DEntropy::CalculateEntropy (CDataMatrix2D *pDataMatrix2D){

	double dblSum = 0.0f;
	
	for (int i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		for (int j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			if (pDataMatrix2D->GetMatrixValue(i, j) == 0){
				dblSum = dblSum + (pDataMatrix2D->GetMatrixValue(i, j) * log(1.0f));
			}
			else{
				dblSum = dblSum + (pDataMatrix2D->GetMatrixValue(i, j) * log(pDataMatrix2D->GetMatrixValue(i, j)));
			}
			
		}
	}
		
	m_dblEntropy = -dblSum;

}

