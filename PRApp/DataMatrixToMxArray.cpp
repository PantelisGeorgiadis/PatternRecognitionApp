#include "stdafx.h"
#include "DataMatrixToMxArray.h"

#ifdef USE_MATLAB_ENGINE

CDataMatrixToMxArray::CDataMatrixToMxArray()
{

}

CDataMatrixToMxArray::~CDataMatrixToMxArray()
{

}

mxArray *CDataMatrixToMxArray::DataMatrix2DToMxArray(CDataMatrix2D *pDataMatrix){

	mxArray *Array = NULL;
	Array = mxCreateDoubleMatrix(pDataMatrix->GetNumberOfRows(), pDataMatrix->GetNumberOfColumns(), mxREAL);
	
	for (int i=0;i<pDataMatrix->GetNumberOfRows();i++){
		for (int j=0;j<pDataMatrix->GetNumberOfColumns();j++){
			mxGetPr(Array)[(i * pDataMatrix->GetNumberOfColumns()) + j] = pDataMatrix->GetMatrixValue(i, j);
		}
	}
	
	return Array;

}

CDataMatrix2D *CDataMatrixToMxArray::MxArrayToDataMatrix2D(mxArray *Array){

	
	CDataMatrix2D *pDataMatrix = new CDataMatrix2D(mxGetM(Array), mxGetN(Array));
	
	for (int i=0;i<pDataMatrix->GetNumberOfRows();i++){
		for (int j=0;j<pDataMatrix->GetNumberOfColumns();j++){
			pDataMatrix->SetMatrixValue(i, j, mxGetPr(Array)[(i * pDataMatrix->GetNumberOfColumns()) + j]);
		}
	}
	
	return pDataMatrix;

}

mxArray *CDataMatrixToMxArray::DataMatrix1DToMxArray(CDataMatrix1D *pDataMatrix){

	mxArray *Array = NULL;
	Array = mxCreateDoubleMatrix(1, pDataMatrix->GetNumberOfColumns(), mxREAL);
	
	for (int i=0;i<pDataMatrix->GetNumberOfColumns();i++){
		mxGetPr(Array)[i] = pDataMatrix->GetMatrixValue(i);
	}
	
	return Array;

}

CDataMatrix1D *CDataMatrixToMxArray::MxArrayToDataMatrix1D(mxArray *Array){

	
	CDataMatrix1D *pDataMatrix = new CDataMatrix1D(mxGetN(Array));
	
	for (int i=0;i<pDataMatrix->GetNumberOfColumns();i++){
		pDataMatrix->SetMatrixValue(i, mxGetPr(Array)[i]);
	}
	
	return pDataMatrix;

}

#endif
