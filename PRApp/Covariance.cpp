#include "stdafx.h"
#include "Covariance.h"

CCovariance::CCovariance()
{

}

CCovariance::~CCovariance()
{

}

CDataMatrix2D *CCovariance::CalculateMatrixCovariance (CDataMatrix2D *pDataMatrix2D, bool bDoNotDivideByRowsMinusOne){

	int i, j;
	
	CDataMatrix1D *MeanColumns = new CDataMatrix1D(pDataMatrix2D->GetNumberOfColumns());
	CDataMatrix2D *TiledRemovedMeanMatrix = NULL;
	CDataMatrix2D *TiledRemovedMeanMatrixTransposed = NULL;
	CDataMatrix2D *TiledRemovedMeanMatrixTransposedMultiplied = NULL;
	CDataMatrix2D *CovarianceMatrix = NULL;
	
	for (j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
		MeanColumns->SetMatrixValue(j, 0.0f);
		for (i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
			MeanColumns->SetMatrixValue(j, (MeanColumns->GetMatrixValue(j) + pDataMatrix2D->GetMatrixValue(i, j)));
		}
		MeanColumns->SetMatrixValue(j, (MeanColumns->GetMatrixValue(j) / (double)(pDataMatrix2D->GetNumberOfRows())));
    }
		
	CDataMatrix2D *TiledMeanMatrix = new CDataMatrix2D((MeanColumns->GetNumberOfRows() * pDataMatrix2D->GetNumberOfRows()), MeanColumns->GetNumberOfColumns());
	for (i=0;i<TiledMeanMatrix->GetNumberOfRows();i++){
		for (j=0;j<TiledMeanMatrix->GetNumberOfColumns();j++){
			TiledMeanMatrix->SetMatrixValue(i, j, MeanColumns->GetMatrixValue(j));
		}
	}
	
	TiledRemovedMeanMatrix = pDataMatrix2D->Subtract(TiledMeanMatrix);
	TiledRemovedMeanMatrixTransposed = TiledRemovedMeanMatrix->TransposeMatrix();
	TiledRemovedMeanMatrixTransposedMultiplied = TiledRemovedMeanMatrixTransposed->Multiply(TiledRemovedMeanMatrix);
	
	if (bDoNotDivideByRowsMinusOne){
		CovarianceMatrix = TiledRemovedMeanMatrixTransposedMultiplied->DivideScalar(pDataMatrix2D->GetNumberOfRows());
	}
	else{
		CovarianceMatrix = TiledRemovedMeanMatrixTransposedMultiplied->DivideScalar((pDataMatrix2D->GetNumberOfRows() - 1));
	}
	
	delete TiledRemovedMeanMatrixTransposedMultiplied;
	TiledRemovedMeanMatrixTransposedMultiplied = NULL;
	delete TiledRemovedMeanMatrixTransposed;
	TiledRemovedMeanMatrixTransposed = NULL;
	delete TiledRemovedMeanMatrix;
	TiledRemovedMeanMatrix = NULL;
	delete TiledMeanMatrix;
	TiledMeanMatrix = NULL;
	delete MeanColumns;
	MeanColumns = NULL;

	return CovarianceMatrix;

}
