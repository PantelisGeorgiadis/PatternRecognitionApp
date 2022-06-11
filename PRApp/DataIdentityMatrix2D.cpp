#include "stdafx.h"
#include "DataIdentityMatrix2D.h"

CDataIdentityMatrix2D::CDataIdentityMatrix2D()
{

	m_dblData = NULL;
	m_iNumberOfRows = 0;
	m_iNumberOfColumns = 0;
	m_iRank = 0;

}

CDataIdentityMatrix2D::CDataIdentityMatrix2D(int iRank)
{

	m_dblData = NULL;
	CreateDataMatrix(iRank);

}

CDataIdentityMatrix2D::~CDataIdentityMatrix2D()
{

	DeleteDataMatrix();

}

void CDataIdentityMatrix2D::CreateDataMatrix (int iRank){

	if (iRank <= 0){
		return;
	}

	m_iNumberOfRows = iRank;
	m_iNumberOfColumns = iRank;
	m_iRank = iRank;
	
	if (m_dblData == NULL){
		m_dblData = new double [iRank * iRank];
		Zeros();
		FillDataIdentityMatrix();
	}

}

void CDataIdentityMatrix2D::DeleteDataMatrix (void){
	
	if (m_dblData != NULL){
		delete [] m_dblData;
		m_dblData = NULL;
	}

}

void CDataIdentityMatrix2D::Zeros (void){

	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<GetNumberOfColumns();j++){
			SetMatrixValue(i, j, 0.0f);
		}
	}

}

void CDataIdentityMatrix2D::FillDataIdentityMatrix (void){

	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<GetNumberOfColumns();j++){
			if (i == j){
				SetMatrixValue(i, j, 1.0f);
			}
			else{
				SetMatrixValue(i, j, 0.0f);
			}
		}
	}

}

CDataIdentityMatrix2D *CDataIdentityMatrix2D::CopyIdentityDataMatrix2D (void){

	CDataIdentityMatrix2D *CopiedDataIdentityMatrix2D = new CDataIdentityMatrix2D(GetIdentityMatrixRank());

	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<GetNumberOfColumns();j++){
			CopiedDataIdentityMatrix2D->SetMatrixValue(i, j, GetMatrixValue(i, j));
		}
	}

	return CopiedDataIdentityMatrix2D;

}

double CDataIdentityMatrix2D::GetMatrixValue (int iRowIndex, int iColumnIndex){

	if ((iRowIndex > GetNumberOfRows()) || (iColumnIndex > GetNumberOfColumns())){
		return 0.0f;
	}

	return m_dblData[(iRowIndex * GetNumberOfColumns()) + iColumnIndex];

}

void CDataIdentityMatrix2D::SetMatrixValue (int iRowIndex, int iColumnIndex, double dblValue){

	if ((iRowIndex > GetNumberOfRows()) || (iColumnIndex > GetNumberOfColumns())){
		return;
	}

	m_dblData[(iRowIndex * GetNumberOfColumns()) + iColumnIndex] = dblValue;

}

CDataMatrix2D *CDataIdentityMatrix2D::CopyIdentityDataMatrixToDataMatrix2D (void){

	CDataMatrix2D *CopiedDataMatrix2D = new CDataMatrix2D(GetIdentityMatrixRank(), GetIdentityMatrixRank());

	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<GetNumberOfColumns();j++){
			CopiedDataMatrix2D->SetMatrixValue(i, j, GetMatrixValue(i, j));
		}
	}

	return CopiedDataMatrix2D;

}

void CDataIdentityMatrix2D::WriteIdentityMatrixDataToFile (char *szFileName){

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
