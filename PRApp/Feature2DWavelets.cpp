#include "stdafx.h"
#include "Feature2DWavelets.h"

CFeature2DWavelets::CFeature2DWavelets()
{

	m_dblWavelet = 0.0f;

}

CFeature2DWavelets::~CFeature2DWavelets()
{

}


void CFeature2DWavelets::WaveletTransform (double *dpData, int iDataLenght){
	
	if (iDataLenght < 4) {
		return;
	}
	
    int i, j;
    int iHalf = iDataLenght>>1;
	
	double *dblTempArray = new double [iDataLenght];	
	
	i = 0;
	for (j=0;j<(iDataLenght - 3);j=(j + 2)){
		*(dblTempArray + i) = *(dpData + j) * h0 + *(dpData + j + 1) * h1 + *(dpData + j + 2) * h2 + *(dpData + j + 3) * h3;
		*(dblTempArray + i + iHalf) = *(dpData + j) * g0 + *(dpData + j + 1) * g1 + *(dpData + j + 2) * g2 + *(dpData + j + 3) * g3;
		i++;
	}
	
	*(dblTempArray + i) = *(dpData + iDataLenght - 2) * h0 + *(dpData + iDataLenght - 1) * h1 + *(dpData) * h2 + *(dpData + 1) * h3;
	*(dblTempArray + i + iHalf) = *(dpData + iDataLenght - 2) * g0 + *(dpData + iDataLenght - 1) * g1 + *(dpData) * g2 + *(dpData + 1) * g3;
	
	for (i=0;i<iDataLenght;i++){
		*(dpData + i) = *(dblTempArray + i);
	}

	delete [] dblTempArray;
	dblTempArray = NULL;
	
}

void CFeature2DWavelets::InverseWaveletTransform (double *dpData, int iDataLenght){
	
	if (iDataLenght < 4) {
		return;
	}
	
	int i, j;
	int iHalf = iDataLenght>>1;

	double *dblTempArray = new double [iDataLenght];
		
	*(dblTempArray) = *(dpData + iHalf - 1) * Ih0 + *(dpData + iDataLenght - 1) * Ih1 + *(dpData) * Ih2 + *(dpData + iHalf) * Ih3;
	*(dblTempArray + 1) = *(dpData + iHalf - 1) * Ig0 + *(dpData + iDataLenght - 1) * Ig1 + *(dpData) * Ig2 + *(dpData + iHalf) * Ig3;
	j = 2;
	for (i=0;i<(iHalf - 1);i++){
		*(dblTempArray + j++) = *(dpData + i) * Ih0 + *(dpData + i + iHalf) * Ih1 + *(dpData + i + 1) * Ih2 + *(dpData + i + (iHalf + 1)) * Ih3;
		*(dblTempArray + j++) = *(dpData + i) * Ig0 + *(dpData + i + iHalf) * Ig1 + *(dpData + i + 1) * Ig2 + *(dpData + i + (iHalf + 1)) * Ig3;
	}
	for (i=0;i<iDataLenght;i++){
		*(dpData + i) = *(dblTempArray + i);
	}

	delete [] dblTempArray;
	dblTempArray = NULL;
	
}

void CFeature2DWavelets::CalculateWavelet (CDataMatrix2D *pDataMatrix2D, int iLevel){
	
	int i, j;

	if (pDataMatrix2D->GetNumberOfRows() != pDataMatrix2D->GetNumberOfColumns()){
		return;
	}

	CDataMatrix2D *WaveletMatrix = new CDataMatrix2D(pDataMatrix2D->GetNumberOfRows(), pDataMatrix2D->GetNumberOfColumns());
	double *dblTempArray = new double [pDataMatrix2D->GetNumberOfRows()];

	for (i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		for (j=0;j<pDataMatrix2D->GetNumberOfRows();j++){
			*(dblTempArray + j) = pDataMatrix2D->GetMatrixValue(i, j);
		}
		
		WaveletTransform(dblTempArray, pDataMatrix2D->GetNumberOfRows());

		for (j=0;j<pDataMatrix2D->GetNumberOfRows();j++){
			WaveletMatrix->SetMatrixValue(i, j, *(dblTempArray + j));
		}
	}

	for (j=0;j<pDataMatrix2D->GetNumberOfRows();j++){
		for (i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
			*(dblTempArray + i) = WaveletMatrix->GetMatrixValue(i, j);
		}
		
		WaveletTransform(dblTempArray, pDataMatrix2D->GetNumberOfRows());

		for (i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
			WaveletMatrix->SetMatrixValue(i, j, *(dblTempArray + i));
		}
	}

	WaveletMatrix->WriteMatrixDataToBMPFile8("C:\\test.bmp");

	delete [] dblTempArray;
	dblTempArray = NULL;
	delete WaveletMatrix;
	WaveletMatrix = NULL;


}
