#include "stdafx.h"
#include "Gradient.h"

CGradient::CGradient()
{

	m_GradientDataMatrix2DX = NULL;
	m_GradientDataMatrix2DY = NULL;

}

CGradient::~CGradient()
{

	DeleteGradientDataMatrixes();

}

void CGradient::DeleteGradientDataMatrixes (void){

	if (m_GradientDataMatrix2DX != NULL){
		delete m_GradientDataMatrix2DX;
		m_GradientDataMatrix2DX = NULL;
	}

	if (m_GradientDataMatrix2DY != NULL){
		delete m_GradientDataMatrix2DY;
		m_GradientDataMatrix2DY = NULL;
	}

}

void CGradient::CalculateMatrixGradient (CDataMatrix2D *pDataMatrix2D){

	int i, j;
	
	m_GradientDataMatrix2DX = new CDataMatrix2D(pDataMatrix2D->GetNumberOfRows(), pDataMatrix2D->GetNumberOfColumns());
	m_GradientDataMatrix2DY = new CDataMatrix2D(pDataMatrix2D->GetNumberOfRows(), pDataMatrix2D->GetNumberOfColumns());

	for (i=0;i<m_GradientDataMatrix2DX->GetNumberOfRows();i++){
		m_GradientDataMatrix2DX->SetMatrixValue(i, 0, (pDataMatrix2D->GetMatrixValue(i, 1) - pDataMatrix2D->GetMatrixValue(i, 0)));
		m_GradientDataMatrix2DX->SetMatrixValue(i, (pDataMatrix2D->GetNumberOfColumns() - 1), (pDataMatrix2D->GetMatrixValue(i, (pDataMatrix2D->GetNumberOfColumns() - 1)) - pDataMatrix2D->GetMatrixValue(i, (pDataMatrix2D->GetNumberOfColumns() - 2))));
	}

	for (i=0;i<m_GradientDataMatrix2DX->GetNumberOfRows();i++){
		for (j=1;j<(m_GradientDataMatrix2DX->GetNumberOfColumns() - 1);j++){
			m_GradientDataMatrix2DX->SetMatrixValue(i, j, ((pDataMatrix2D->GetMatrixValue(i, (j + 1)) - pDataMatrix2D->GetMatrixValue(i, (j - 1))) / 2.0f));
		}
	}


	for (i=0;i<m_GradientDataMatrix2DY->GetNumberOfColumns();i++){
		m_GradientDataMatrix2DY->SetMatrixValue(0, i, (pDataMatrix2D->GetMatrixValue(1, i) - pDataMatrix2D->GetMatrixValue(0, i)));
		m_GradientDataMatrix2DY->SetMatrixValue((pDataMatrix2D->GetNumberOfRows() - 1), i, (pDataMatrix2D->GetMatrixValue((pDataMatrix2D->GetNumberOfRows() - 1), i) - pDataMatrix2D->GetMatrixValue((pDataMatrix2D->GetNumberOfRows() - 2), i)));
	}

	for (i=1;i<(m_GradientDataMatrix2DY->GetNumberOfRows() - 1);i++){
		for (j=0;j<m_GradientDataMatrix2DY->GetNumberOfColumns();j++){
			m_GradientDataMatrix2DY->SetMatrixValue(i, j, ((pDataMatrix2D->GetMatrixValue((i + 1), j) - pDataMatrix2D->GetMatrixValue((i - 1), j)) / 2.0f));
		}
	}

}
