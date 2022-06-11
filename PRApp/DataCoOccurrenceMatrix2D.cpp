#include "stdafx.h"
#include "DataCoOccurrenceMatrix2D.h"

CDataCoOccurrenceMatrix2D::CDataCoOccurrenceMatrix2D()
{

	m_dblData = NULL;
	m_iNumberOfRows = 0;
	m_iNumberOfColumns = 0;
	m_iDepth = 0;
	m_mrd = DEGREES_0;

}

CDataCoOccurrenceMatrix2D::CDataCoOccurrenceMatrix2D(CDataMatrix2D *pDataMatrix2D, int iDepth, MatrixRotationDegrees mrd)
{

	m_dblData = NULL;
	m_iNumberOfRows = 0;
	m_iNumberOfColumns = 0;
	CreateDataMatrix(pDataMatrix2D, iDepth, mrd);

}

CDataCoOccurrenceMatrix2D::~CDataCoOccurrenceMatrix2D()
{

	DeleteDataMatrix();

}

void CDataCoOccurrenceMatrix2D::CreateDataMatrix (CDataMatrix2D *pDataMatrix2D, int iDepth, MatrixRotationDegrees mrd){

	if (iDepth <= 0){
		return;
	}

	m_iNumberOfRows = iDepth;
	m_iNumberOfColumns = iDepth;
	m_iDepth = iDepth;
	m_mrd = mrd;
	
	if (m_dblData == NULL){
		m_dblData = new double [iDepth * iDepth];
		Zeros();
		FillDataCoOccurrenceMatrix(pDataMatrix2D);
	}

}

void CDataCoOccurrenceMatrix2D::CreateDataMatrix (int iDepth, MatrixRotationDegrees mrd){

	if (iDepth <= 0){
		return;
	}

	m_iNumberOfRows = iDepth;
	m_iNumberOfColumns = iDepth;
	m_iDepth = iDepth;
	m_mrd = mrd;
	
	if (m_dblData == NULL){
		m_dblData = new double [iDepth * iDepth];
		Zeros();
	}

}

void CDataCoOccurrenceMatrix2D::DeleteDataMatrix (void){
	
	if (m_dblData != NULL){
		delete [] m_dblData;
		m_dblData = NULL;
	}

}

void CDataCoOccurrenceMatrix2D::Zeros (void){

	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<GetNumberOfColumns();j++){
			SetMatrixValue(i, j, 0.0f);
		}
	}

}

void CDataCoOccurrenceMatrix2D::FillDataCoOccurrenceMatrix (CDataMatrix2D *pDataMatrix2D){

	int i, j, k, l;

	for (i=0;i<GetDepth();i++) {
		for (j=0;j<GetDepth();j++) {			
			for (k=0;k<pDataMatrix2D->GetNumberOfRows();k++){
				for (l=0;l<pDataMatrix2D->GetNumberOfColumns();l++){
					if (pDataMatrix2D->GetMatrixValue(k, l) == i){					
						if ((l > 0) && (l < (pDataMatrix2D->GetNumberOfColumns() - 1))){
							if (pDataMatrix2D->GetMatrixValue(k, (l - 1)) == j){
								SetMatrixValue(i, j, GetMatrixValue(i, j) + 1);	
							}
							if ((pDataMatrix2D->GetMatrixValue(k, (l - 1)) == -1) && ((l - 1) > 0)){
								if (pDataMatrix2D->GetMatrixValue(k, (l - 2)) == j){
									SetMatrixValue(i, j, GetMatrixValue(i, j) + 1);
								}
							}	
							if (pDataMatrix2D->GetMatrixValue(k, (l + 1)) == j){
								SetMatrixValue(i, j, GetMatrixValue(i, j) + 1);
							}
							if ((pDataMatrix2D->GetMatrixValue(k, (l + 1)) == -1) && ((l + 1) < (pDataMatrix2D->GetNumberOfRows() - 1))){
								if (pDataMatrix2D->GetMatrixValue(k, (l + 2)) == j){
									SetMatrixValue(i, j, GetMatrixValue(i, j) + 1);
								}
							}
						}							
						else {
							if (l == 0){
								if (pDataMatrix2D->GetMatrixValue(k, (l + 1)) == j){
									SetMatrixValue(i, j, GetMatrixValue(i, j) + 1);
								}
								if (pDataMatrix2D->GetMatrixValue(k, (l + 1)) == -1){
									if (pDataMatrix2D->GetMatrixValue(k, (l + 2)) == j){
										SetMatrixValue(i, j, GetMatrixValue(i, j) + 1);
									}
								}
							}
							if (l == (pDataMatrix2D->GetNumberOfColumns() - 1)){
								if (pDataMatrix2D->GetMatrixValue(k, (l - 1)) == j){
									SetMatrixValue(i, j, GetMatrixValue(i, j) + 1);
								}
								if (pDataMatrix2D->GetMatrixValue(k, (l - 1)) == -1){
									if (pDataMatrix2D->GetMatrixValue(k, (l - 2)) == j){
										SetMatrixValue(i, j, GetMatrixValue(i, j) + 1);
									}
								}	
							}
						}
					}
				}
			}
		}
	}
	
}

CDataCoOccurrenceMatrix2D *CDataCoOccurrenceMatrix2D::CopyCoOccurrenceMatrix2D (void){

	CDataCoOccurrenceMatrix2D *CopiedDataCoOccurrenceMatrix2D = new CDataCoOccurrenceMatrix2D();
	CopiedDataCoOccurrenceMatrix2D->CreateDataMatrix(GetDepth(), GetMatrixRotationDegrees());

	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<GetNumberOfColumns();j++){
			CopiedDataCoOccurrenceMatrix2D->SetMatrixValue(i, j, GetMatrixValue(i, j));
		}
	}

	return CopiedDataCoOccurrenceMatrix2D;

}

double CDataCoOccurrenceMatrix2D::GetMatrixValue (int iRowIndex, int iColumnIndex){

	if ((iRowIndex > GetNumberOfRows()) || (iColumnIndex > GetNumberOfColumns())){
		return 0.0f;
	}

	return m_dblData[(iRowIndex * GetNumberOfColumns()) + iColumnIndex];

}

void CDataCoOccurrenceMatrix2D::SetMatrixValue (int iRowIndex, int iColumnIndex, double dblValue){

	if ((iRowIndex > GetNumberOfRows()) || (iColumnIndex > GetNumberOfColumns())){
		return;
	}

	m_dblData[(iRowIndex * GetNumberOfColumns()) + iColumnIndex] = dblValue;

}

CDataMatrix2D *CDataCoOccurrenceMatrix2D::CopyCoOccurrenceDataMatrixToDataMatrix2D (void){

	CDataMatrix2D *CopiedDataMatrix2D = new CDataMatrix2D(GetDepth(), GetDepth());

	for (int i=0;i<CopiedDataMatrix2D->GetNumberOfRows();i++){
		for (int j=0;j<CopiedDataMatrix2D->GetNumberOfColumns();j++){
			CopiedDataMatrix2D->SetMatrixValue(i, j, GetMatrixValue(i, j));
		}
	}

	return CopiedDataMatrix2D;

}

void CDataCoOccurrenceMatrix2D::WriteCoOccurrenceMatrixDataToFile (char *szFileName){

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

