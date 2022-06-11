#include "stdafx.h"
#include "DataMatrix1D.h"

CDataMatrix1D::CDataMatrix1D()
{

	m_iNumberOfColumns = 0;
	m_DataMatrix2D = NULL;

}

CDataMatrix1D::CDataMatrix1D(int iNumberOfColumns)
{

	CreateDataMatrix(iNumberOfColumns);

}

CDataMatrix1D::~CDataMatrix1D()
{

	DeleteDataMatrix();

}

void CDataMatrix1D::CreateDataMatrix (int iNumberOfColumns){

	if (iNumberOfColumns <= 0){
		return;
	}

	m_iNumberOfColumns = iNumberOfColumns;
	m_DataMatrix2D = new CDataMatrix2D(1, iNumberOfColumns);
	Zeros();

}

void CDataMatrix1D::DeleteDataMatrix (void){

	if (m_DataMatrix2D != NULL){
		delete m_DataMatrix2D;
		m_DataMatrix2D = NULL;
	}

}

void CDataMatrix1D::Zeros (void){

	m_DataMatrix2D->Zeros();

}

CDataMatrix1D *CDataMatrix1D::CopyDataMatrix1D (void){

	CDataMatrix1D *CopiedDataMatrix1D = new CDataMatrix1D(GetNumberOfColumns());

	for (int i=0;i<GetNumberOfColumns();i++){
		CopiedDataMatrix1D->SetMatrixValue(i, GetMatrixValue(i));
	}
	
	return CopiedDataMatrix1D;

}

double CDataMatrix1D::GetMatrixValue (int iColumnIndex){

	if (iColumnIndex > GetNumberOfColumns()){
		return 0.0f;
	}

	return (m_DataMatrix2D->GetMatrixValue(0, iColumnIndex));

}

void CDataMatrix1D::SetMatrixValue (int iColumnIndex, double dblValue){

	if (iColumnIndex > GetNumberOfColumns()){
		return;
	}

	m_DataMatrix2D->SetMatrixValue(0, iColumnIndex, dblValue);
	
}

CDataMatrix2D *CDataMatrix1D::GetDataMatrix1DAsDataMatrix2D (void){

	return m_DataMatrix2D;

}

void CDataMatrix1D::WriteMatrixDataToFile (char *szFileName){

	FILE *fp;

	fp = fopen(szFileName, "w");
	if (fp == NULL){
		return;
	}

	for (int i=0;i<m_DataMatrix2D->GetNumberOfRows();i++){
		for (int j=0;j<m_DataMatrix2D->GetNumberOfColumns();j++){
			fprintf(fp, "%.16lf", m_DataMatrix2D->GetMatrixValue(i, j)); 
			if (j != (m_DataMatrix2D->GetNumberOfColumns() - 1)){
				fprintf(fp, "\t");
			}
		}
		fprintf(fp, "\r\n"); 
	}

	fclose(fp);

}
