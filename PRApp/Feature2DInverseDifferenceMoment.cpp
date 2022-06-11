#include "stdafx.h"
#include "Feature2DInverseDifferenceMoment.h"

CFeature2DInverseDifferenceMoment::CFeature2DInverseDifferenceMoment()
{

	m_dblInverseDifferenceMoment = 0.0f;

}

CFeature2DInverseDifferenceMoment::~CFeature2DInverseDifferenceMoment()
{

}

void CFeature2DInverseDifferenceMoment::CalculateInverseDifferenceMoment (CDataMatrix2D *pDataMatrix2D){

	double dblSum = 0.0f;


	for (int i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		for (int j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			dblSum = dblSum + (pDataMatrix2D->GetMatrixValue(i, j) / (1 + pow((float)(i - j), 2)));		
			
		}
	}

	m_dblInverseDifferenceMoment = dblSum;

}
