#include "stdafx.h"
#include "Feature2DDifferenceEntropy.h"
#include "DataRowsCollumnsOperationsMatrix2D.h"

CFeature2DDifferenceEntropy::CFeature2DDifferenceEntropy()
{

	m_dblDifferenceEntropy = 0.0f;

}

CFeature2DDifferenceEntropy::~CFeature2DDifferenceEntropy()
{

}

void CFeature2DDifferenceEntropy::CalculateDifferenceEntropy (CDataMatrix2D *pDataMatrix2D){

	double dblSum = 0.0f;

	CDataMatrix2D *RowsCollumnsSubtractionMatrix = NULL;
	CDataRowsCollumnsOperationsMatrix2D *RowsCollumnsSubtraction = new CDataRowsCollumnsOperationsMatrix2D();
	RowsCollumnsSubtractionMatrix = RowsCollumnsSubtraction->RowsCollumnsSubtraction(pDataMatrix2D);

	for (int i=0;i<(pDataMatrix2D->GetNumberOfRows());i++){
		if (RowsCollumnsSubtractionMatrix->GetMatrixValue(0, i) == 0){
			dblSum = dblSum + (RowsCollumnsSubtractionMatrix->GetMatrixValue(0, i) * log(1.0f));
		}
		else{
			dblSum = dblSum + (RowsCollumnsSubtractionMatrix->GetMatrixValue(0, i) * log(RowsCollumnsSubtractionMatrix->GetMatrixValue(0, i)));
		}
	}

	m_dblDifferenceEntropy = -dblSum;

	delete RowsCollumnsSubtraction;
	RowsCollumnsSubtraction = NULL;
	delete RowsCollumnsSubtractionMatrix;
	RowsCollumnsSubtractionMatrix = NULL;

}
