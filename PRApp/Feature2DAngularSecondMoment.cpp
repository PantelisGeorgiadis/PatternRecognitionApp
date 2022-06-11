#include "stdafx.h"
#include "Feature2DAngularSecondMoment.h"

CFeature2DAngularSecondMoment::CFeature2DAngularSecondMoment()
{

	m_dblAngularSecondMoment = 0.0f;

}

CFeature2DAngularSecondMoment::~CFeature2DAngularSecondMoment()
{

}

void CFeature2DAngularSecondMoment::CalculateAngularSecondMoment (CDataMatrix2D *pDataMatrix2D){

	double dblSum = 0.0f;

	for (int i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		for (int j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			dblSum = dblSum + pow(pDataMatrix2D->GetMatrixValue(i, j), 2);
		}
	}

	m_dblAngularSecondMoment = dblSum;

}

