#include "stdafx.h"
#include "Determinant.h"

CDeterminant::CDeterminant()
{

}

CDeterminant::~CDeterminant()
{

}

double CDeterminant::CalculateMatrixDeterminant (CDataMatrix2D *pDataMatrix2D){

	double dblSum = 0.0f;
	int i, j, k, l;
	
	if (pDataMatrix2D->GetNumberOfRows() != pDataMatrix2D->GetNumberOfColumns()){
		return 0.0f;
	}

	if (pDataMatrix2D->GetNumberOfRows() == 1){
		return pDataMatrix2D->GetMatrixValue(0, 0);
	}
	else if (pDataMatrix2D->GetNumberOfRows() == 2){
		return ((pDataMatrix2D->GetMatrixValue(0, 0) * pDataMatrix2D->GetMatrixValue(1, 1)) - ((pDataMatrix2D->GetMatrixValue(1, 0) * pDataMatrix2D->GetMatrixValue(0, 1))));
	}
	else{
		for (k=0;k<pDataMatrix2D->GetNumberOfRows();k++){
			CDataMatrix2D *SubMatrix = new CDataMatrix2D((pDataMatrix2D->GetNumberOfRows() - 1), (pDataMatrix2D->GetNumberOfColumns() - 1));
			for (i=1;i<pDataMatrix2D->GetNumberOfRows();i++){
				l = 0;
				for (j=0;j<pDataMatrix2D->GetNumberOfRows();j++){
					if (j == k){
						continue;
					}
					SubMatrix->SetMatrixValue((i - 1), l, pDataMatrix2D->GetMatrixValue(i, j));
					l++;
				}
			}
			dblSum = dblSum + pow(-1.0f, (1.0f + k + 1.0f)) * pDataMatrix2D->GetMatrixValue(0, k) * CalculateMatrixDeterminant(SubMatrix);
			delete SubMatrix;
			SubMatrix = NULL;
		}
	}

	return dblSum;

}
