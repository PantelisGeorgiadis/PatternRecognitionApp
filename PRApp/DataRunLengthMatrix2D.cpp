#include "stdafx.h"
#include "DataRunLengthMatrix2D.h"

CDataRunLengthMatrix2D::CDataRunLengthMatrix2D()
{

	m_dblData = NULL;
	m_iNumberOfRows = 0;
	m_iNumberOfColumns = 0;
	m_iDepth = 0;
	m_iLenght = 0;
	m_mrd = DEGREES_0;

}

CDataRunLengthMatrix2D::CDataRunLengthMatrix2D(CDataMatrix2D *pDataMatrix2D, int iDepth, MatrixRotationDegrees mrd)
{

	m_dblData = NULL;
	m_iNumberOfRows = 0;
	m_iNumberOfColumns = 0;
	m_iLenght = 0;
	CreateDataMatrix(pDataMatrix2D, iDepth, mrd);

}

CDataRunLengthMatrix2D::~CDataRunLengthMatrix2D()
{

	DeleteDataMatrix();

}

void CDataRunLengthMatrix2D::CreateDataMatrix (CDataMatrix2D *pDataMatrix2D, int iDepth, MatrixRotationDegrees mrd){

	if (iDepth <= 0){
		return;
	}

	m_iNumberOfRows = iDepth;
	m_iNumberOfColumns = pDataMatrix2D->GetNumberOfColumns();
	m_iDepth = iDepth;
	m_iLenght = m_iNumberOfColumns;
	m_mrd = mrd;
	
	if (m_dblData == NULL){
		m_dblData = new double [iDepth * m_iLenght];
		Zeros();
		FillDataRunLenghtMatrix(pDataMatrix2D);
	}

}

void CDataRunLengthMatrix2D::CreateDataMatrix (int iDepth, int iLenght, MatrixRotationDegrees mrd){

	if (iDepth <= 0){
		return;
	}

	m_iNumberOfRows = iDepth;
	m_iNumberOfColumns = iLenght;
	m_iDepth = iDepth;
	m_iLenght = iLenght;
	m_mrd = mrd;
	
	if (m_dblData == NULL){
		m_dblData = new double [iDepth * iLenght];
		Zeros();
	}

}

void CDataRunLengthMatrix2D::DeleteDataMatrix (void){
	
	if (m_dblData != NULL){
		delete [] m_dblData;
		m_dblData = NULL;
	}

}

void CDataRunLengthMatrix2D::Zeros (void){

	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<GetNumberOfColumns();j++){
			SetMatrixValue(i, j, 0.0f);
		}
	}

}

void CDataRunLengthMatrix2D::FillDataRunLenghtMatrix (CDataMatrix2D *pDataMatrix2D){

	int iCounter = 0;
	int i, j;

	switch (GetMatrixRotationDegrees()){
		case DEGREES_0:
		case DEGREES_90:
			for (i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
				for (j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
					if (pDataMatrix2D->GetMatrixValue(i, j) != -1){
						iCounter = 0;
						while ((pDataMatrix2D->GetMatrixValue(i, j) == pDataMatrix2D->GetMatrixValue(i, (j + 1))) && ((j + 1) < pDataMatrix2D->GetNumberOfColumns())){	
							j++;
							iCounter++;
						}
						SetMatrixValue((int)(pDataMatrix2D->GetMatrixValue(i, j)), iCounter, GetMatrixValue((int)(pDataMatrix2D->GetMatrixValue(i, j)), iCounter) + 1);
					}
				}
			}
			break;
		case DEGREES_45:
		case DEGREES_135:
			for (i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
				for (j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
					if (pDataMatrix2D->GetMatrixValue(i, j) != -1){
						iCounter = 0;
						while ((pDataMatrix2D->GetMatrixValue(i, j) == pDataMatrix2D->GetMatrixValue(i, (j + 2))) && ((j + 2) < pDataMatrix2D->GetNumberOfColumns())){	
							j = j + 2;
							iCounter++;
						}
						SetMatrixValue((int)(pDataMatrix2D->GetMatrixValue(i, j)), iCounter, GetMatrixValue((int)(pDataMatrix2D->GetMatrixValue(i, j)), iCounter) + 1);
					}
				}
			}
			break;
	}
	
}

CDataRunLengthMatrix2D *CDataRunLengthMatrix2D::CopyRunLengthMatrix2D (void){

	CDataRunLengthMatrix2D *CopiedDataRunLenghtMatrix2D = new CDataRunLengthMatrix2D();
	CopiedDataRunLenghtMatrix2D->CreateDataMatrix(GetDepth(), GetLenght(), GetMatrixRotationDegrees());

	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<GetNumberOfColumns();j++){
			CopiedDataRunLenghtMatrix2D->SetMatrixValue(i, j, GetMatrixValue(i, j));
		}
	}

	return CopiedDataRunLenghtMatrix2D;

}

double CDataRunLengthMatrix2D::GetMatrixValue (int iRowIndex, int iColumnIndex){

	if ((iRowIndex > GetNumberOfRows()) || (iColumnIndex > GetNumberOfColumns())){
		return 0.0f;
	}

	return m_dblData[(iRowIndex * GetNumberOfColumns()) + iColumnIndex];

}

void CDataRunLengthMatrix2D::SetMatrixValue (int iRowIndex, int iColumnIndex, double dblValue){

	if ((iRowIndex > GetNumberOfRows()) || (iColumnIndex > GetNumberOfColumns())){
		return;
	}

	m_dblData[(iRowIndex * GetNumberOfColumns()) + iColumnIndex] = dblValue;

}

CDataMatrix2D *CDataRunLengthMatrix2D::CopyRunLengthDataMatrixToDataMatrix2D (void){

	CDataMatrix2D *CopiedDataMatrix2D = new CDataMatrix2D(GetDepth(), GetLenght());

	for (int i=0;i<CopiedDataMatrix2D->GetNumberOfRows();i++){
		for (int j=0;j<CopiedDataMatrix2D->GetNumberOfColumns();j++){
			CopiedDataMatrix2D->SetMatrixValue(i, j, GetMatrixValue(i, j));
		}
	}

	return CopiedDataMatrix2D;

}

void CDataRunLengthMatrix2D::WriteRunLengthMatrixDataToFile (char *szFileName){

	FILE *fp;

	fp = fopen(szFileName, "w");
	if (fp == NULL){
		return;
	}

	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<GetNumberOfColumns();j++){
			fprintf(fp, "%.16lf", GetMatrixValue(i, j)); 
			if (j != (GetNumberOfColumns() - 1)){
				fprintf(fp, "\t");
			}
		}
		fprintf(fp, "\r\n"); 
	}

	fclose(fp);

}


