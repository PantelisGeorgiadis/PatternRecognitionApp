#include "stdafx.h"
#include "Feature3DSum.h"

CFeature3DSum::CFeature3DSum()
{

	m_dblSum = 0.0f;

}

CFeature3DSum::~CFeature3DSum()
{

}

void CFeature3DSum::CalculateSum (CDataMatrix3D *pDataMatrix3D){

	double dblSum = 0.0f;

	for (int i=0;i<pDataMatrix3D->GetNumberOfLayers();i++){
		for (int j=0;j<pDataMatrix3D->GetNumberOfRows();j++){
			for (int k=0;k<pDataMatrix3D->GetNumberOfColumns();k++){
				dblSum = dblSum + pDataMatrix3D->GetMatrixValue(i, j, k);
			}
		}
	}

	m_dblSum = dblSum;

}
