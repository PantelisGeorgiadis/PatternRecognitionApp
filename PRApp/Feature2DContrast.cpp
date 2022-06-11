#include "stdafx.h"
#include "Feature2DContrast.h"

CFeature2DContrast::CFeature2DContrast()
{

	m_dblContrast = 0.0f;

}

CFeature2DContrast::~CFeature2DContrast()
{

}

void CFeature2DContrast::CalculateContrast (CDataMatrix2D *pDataMatrix2D){

	double dblSum1 = 0.0f;
	double dblSum2 = 0.0f;

	for (int n=0;n<(pDataMatrix2D->GetNumberOfRows() - 1);n++){
		dblSum1 = 0.0f;
		for (int i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
			for (int j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
				if ((abs(i - j)) == n){
					dblSum1 = dblSum1 + pDataMatrix2D->GetMatrixValue(i, j);
				}
			}
		}
		dblSum2 = dblSum2 + (pow((float)(n), 2) * dblSum1);
	}

	m_dblContrast = dblSum2;

}

