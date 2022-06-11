#include "stdafx.h"
#include "DataMatrix2D.h"
#include "DataIdentityMatrix2D.h"
#include "Feature2DSum.h"

CDataMatrix2D::CDataMatrix2D()
{

	m_dblData = NULL;
	m_iNumberOfRows = 0;
	m_iNumberOfColumns = 0;

}

CDataMatrix2D::CDataMatrix2D(int iNumberOfRows, int iNumberOfColumns)
{

	m_dblData = NULL;
	CreateDataMatrix(iNumberOfRows, iNumberOfColumns);

}

CDataMatrix2D::~CDataMatrix2D()
{

	DeleteDataMatrix();

}

void CDataMatrix2D::CreateDataMatrix (int iNumberOfRows, int iNumberOfColumns){

	if ((iNumberOfRows <= 0) || (iNumberOfColumns <= 0)){
		return;
	}

	m_iNumberOfRows = iNumberOfRows;
	m_iNumberOfColumns = iNumberOfColumns;
	
	if (m_dblData == NULL){
		m_dblData = new double [(iNumberOfRows * iNumberOfColumns)];
		Zeros();
	}

}

void CDataMatrix2D::CreateDataMatrixFromFile (char *szFileName, int iElementsPerLine, int iElementDigits){

	if (iElementsPerLine > 0){
		CFileReader *FileReader = new CFileReader();

		if (FileReader->ParseFile(szFileName)){
			if (FileReader->GetLineCount() > 0){
				if (FileReader->LongestLine() > 0){
					char *szLineBuffer = new char[(FileReader->LongestLine() + 1)];
					char *szElementBuffer = new char[iElementDigits + 1];

					CreateDataMatrix(FileReader->GetLineCount(), iElementsPerLine);
					
					for (int i=0;i<(int)(FileReader->GetLineCount());i++){
						memset(szLineBuffer, 0, (FileReader->LongestLine() + 1) * sizeof(char));
						FileReader->GetLine(i, szLineBuffer, FileReader->LongestLine());
											
						for (int j=0;j<iElementsPerLine;j++){
							memset(szElementBuffer, 0, (iElementDigits + 1) * sizeof(char));
							strncpy(szElementBuffer, szLineBuffer + ((iElementDigits + 1) * j), iElementDigits);
							SetMatrixValue(i, j, (atof(szElementBuffer)));
						}
					}

					delete [] szElementBuffer;
					szElementBuffer = NULL;
					delete [] szLineBuffer;
					szLineBuffer = NULL;
				}
			}
			FileReader->Clear();
		}

		delete FileReader;
		FileReader = NULL;
	}

}

void CDataMatrix2D::CreateDataMatrixFromBMPFile8 (char *szFileName){

	FILE *fp;

	unsigned long int iHeight, iWidth, iImageOffset;
	unsigned short int bpp;
	unsigned char uCurChar, uP;
	int iPaddedWidth;
	int i, j;

	fp = fopen(szFileName, "rb");
	if (fp == NULL){
		return;
	}

	if ((fgetc(fp) != 'B') || (fgetc(fp) != 'M')){
		return;
	}

	fseek(fp, 18, SEEK_SET);
	fread(&iWidth, 4, 1, fp);
	fread(&iHeight, 4, 1, fp);
	fseek(fp, 28, SEEK_SET);
	fread(&bpp, 2, 1, fp);
	fseek(fp, 10, SEEK_SET);
	fread(&iImageOffset, 4, 1, fp);
	
	if (iWidth <= 0){
		return;
	}
	if (iHeight <= 0){
		return;
	}
	if (bpp != 8){
		return;
	}

	CreateDataMatrix(iHeight, iWidth);

	fseek(fp, 54, SEEK_SET);
	for(i=0;i<256;i++){
		uP = fgetc(fp);
		uP = fgetc(fp);
		uP = fgetc(fp);
		uCurChar = fgetc(fp);
	}

	fseek(fp, iImageOffset, SEEK_SET);
	iPaddedWidth = iWidth;
	while(iPaddedWidth%4!=0){
		iPaddedWidth++;
	}

	for (i=(iHeight - 1);i>=0;i--){
		for (j=0;j<iPaddedWidth;j++){
			uCurChar = fgetc(fp);
			if (j <= (int)(iWidth - 1)){
				SetMatrixValue(i, j, uCurChar);
			}
		}
	}

	fclose(fp);

}

void CDataMatrix2D::DeleteDataMatrix (void){
	
	if (m_dblData != NULL){
		delete [] m_dblData;
		m_dblData = NULL;
	}

}

void CDataMatrix2D::Zeros (void){

	int j;

#ifdef USE_OPENMP
#pragma omp parallel for private(j)
#endif
	for (int i=0;i<GetNumberOfRows();i++){
		for (j=0;j<GetNumberOfColumns();j++){
			SetMatrixValue(i, j, 0.0f);
		}
	}

}

CDataMatrix2D *CDataMatrix2D::CopyDataMatrix2D (void){

	int j;
	CDataMatrix2D *CopiedDataMatrix2D = new CDataMatrix2D(GetNumberOfRows(), GetNumberOfColumns());

#ifdef USE_OPENMP
#pragma omp parallel for private(j)
#endif
	for (int i=0;i<GetNumberOfRows();i++){
		for (j=0;j<GetNumberOfColumns();j++){
			CopiedDataMatrix2D->SetMatrixValue(i, j, GetMatrixValue(i, j));
		}
	}

	return CopiedDataMatrix2D;

}

void CDataMatrix2D::CopyToDataMatrix2D (CDataMatrix2D *pDestDataMatrix2D){

	if (pDestDataMatrix2D->GetNumberOfRows() != GetNumberOfRows()){
		return;
	}
	
	if (pDestDataMatrix2D->GetNumberOfColumns() != GetNumberOfColumns()){
		return;
	}
	
	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<GetNumberOfColumns();j++){
			pDestDataMatrix2D->SetMatrixValue(i, j, GetMatrixValue(i, j));
		}
	}

}

void CDataMatrix2D::CopyFromDataMatrix2D (CDataMatrix2D *pSrcDataMatrix2D){

	if (pSrcDataMatrix2D->GetNumberOfRows() != GetNumberOfRows()){
		return;
	}
	
	if (pSrcDataMatrix2D->GetNumberOfColumns() != GetNumberOfColumns()){
		return;
	}
	
	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<GetNumberOfColumns();j++){
			SetMatrixValue(i, j, pSrcDataMatrix2D->GetMatrixValue(i, j));
		}
	}

}

double CDataMatrix2D::GetMatrixValue (int iRowIndex, int iColumnIndex){

	if ((iRowIndex > GetNumberOfRows()) || (iColumnIndex > GetNumberOfColumns())){
		return 0.0f;
	}

	return m_dblData[(iRowIndex * GetNumberOfColumns()) + iColumnIndex];

}

void CDataMatrix2D::SetMatrixValue (int iRowIndex, int iColumnIndex, double dblValue){

	if ((iRowIndex > GetNumberOfRows()) || (iColumnIndex > GetNumberOfColumns())){
		return;
	}

	m_dblData[(iRowIndex * GetNumberOfColumns()) + iColumnIndex] = dblValue;

}

CDataMatrix2D *CDataMatrix2D::GetSubDataMatrix (CRectangle *pRectangle){

	if (pRectangle->GetWidth() > GetNumberOfColumns()){
		return NULL;
	}

	if (pRectangle->GetHeight() > GetNumberOfRows()){
		return NULL;
	}

	if ((pRectangle->GetWidth() <= 0) || (pRectangle->GetHeight() <= 0)){
		return NULL;
	}
	
	CDataMatrix2D *SubDataMatrix = new CDataMatrix2D(pRectangle->GetHeight(), pRectangle->GetWidth());

	for (int i=pRectangle->GetYStart();i<pRectangle->GetYEnd();i++){
		for (int j=pRectangle->GetXStart();j<pRectangle->GetXEnd();j++){
			SubDataMatrix->SetMatrixValue((i - pRectangle->GetYStart()), (j - pRectangle->GetXStart()), GetMatrixValue(i, j));
		}
	}

	return SubDataMatrix;

}

CDataMatrix2D *CDataMatrix2D::CreateDataMatrixBinaryMask (CRectangle *pRectangle){

	if (pRectangle->GetWidth() > GetNumberOfColumns()){
		return NULL;
	}

	if (pRectangle->GetHeight() > GetNumberOfRows()){
		return NULL;
	}

	if ((pRectangle->GetWidth() <= 0) || (pRectangle->GetHeight() <= 0)){
		return NULL;
	}
	
	CDataMatrix2D *BinaryDataMatrixMask = new CDataMatrix2D(GetNumberOfRows(), GetNumberOfColumns());

	for (int i=pRectangle->GetYStart();i<pRectangle->GetYEnd();i++){
		for (int j=pRectangle->GetXStart();j<pRectangle->GetXEnd();j++){
			BinaryDataMatrixMask->SetMatrixValue(i, j, 1.0f);
		}
	}

	return BinaryDataMatrixMask;

}

CDataMatrix2D *CDataMatrix2D::Add (CDataMatrix2D *pDataMatrix2D){

	if ((GetNumberOfRows() != pDataMatrix2D->GetNumberOfRows()) || (GetNumberOfColumns() != pDataMatrix2D->GetNumberOfColumns())){
		return NULL;
	}
	
	CDataMatrix2D *AddedMatrix2D = new CDataMatrix2D(pDataMatrix2D->GetNumberOfRows(), pDataMatrix2D->GetNumberOfColumns());

	for (int i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		for (int j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			AddedMatrix2D->SetMatrixValue(i, j, (GetMatrixValue(i, j) + pDataMatrix2D->GetMatrixValue(i, j)));
		}
	}

	return AddedMatrix2D;

}

void CDataMatrix2D::AddToDataMatrix (CDataMatrix2D *pDataMatrix2D){

	if ((GetNumberOfRows() != pDataMatrix2D->GetNumberOfRows()) || (GetNumberOfColumns() != pDataMatrix2D->GetNumberOfColumns())){
		return;
	}
	
	for (int i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		for (int j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			SetMatrixValue(i, j, (GetMatrixValue(i, j) + pDataMatrix2D->GetMatrixValue(i, j)));
		}
	}

}

CDataMatrix2D *CDataMatrix2D::Subtract (CDataMatrix2D *pDataMatrix2D){

	if ((GetNumberOfRows() != pDataMatrix2D->GetNumberOfRows()) || (GetNumberOfColumns() != pDataMatrix2D->GetNumberOfColumns())){
		return NULL;
	}
	
	CDataMatrix2D *SubtractedMatrix2D = new CDataMatrix2D(pDataMatrix2D->GetNumberOfRows(), pDataMatrix2D->GetNumberOfColumns());

	for (int i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		for (int j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			SubtractedMatrix2D->SetMatrixValue(i, j, (GetMatrixValue(i, j) - pDataMatrix2D->GetMatrixValue(i, j)));
		}
	}

	return SubtractedMatrix2D;

}


void CDataMatrix2D::SubtractFromDataMatrix (CDataMatrix2D *pDataMatrix2D){

	if ((GetNumberOfRows() != pDataMatrix2D->GetNumberOfRows()) || (GetNumberOfColumns() != pDataMatrix2D->GetNumberOfColumns())){
		return;
	}
	
	for (int i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		for (int j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			SetMatrixValue(i, j, (GetMatrixValue(i, j) - pDataMatrix2D->GetMatrixValue(i, j)));
		}
	}

}

CDataMatrix2D *CDataMatrix2D::Multiply (CDataMatrix2D *pDataMatrix2D){

	if (GetNumberOfColumns() != pDataMatrix2D->GetNumberOfRows()){
		return NULL;
	}
	
	CDataMatrix2D *MultipliedMatrix2D = new CDataMatrix2D(GetNumberOfRows(), pDataMatrix2D->GetNumberOfColumns());

	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			for (int k=0;k<GetNumberOfColumns();k++){
				MultipliedMatrix2D->SetMatrixValue(i, j, (MultipliedMatrix2D->GetMatrixValue(i, j) + (GetMatrixValue(i, k) * pDataMatrix2D->GetMatrixValue(k, j))));
			}
		}
	}

	return MultipliedMatrix2D;

}

/*CDataMatrix2D *CDataMatrix2D::Divide (CDataMatrix2D *pDataMatrix2D){

	CDataMatrix2D *DividedMatrix2D = new CDataMatrix2D(GetNumberOfRows(), pDataMatrix2D->GetNumberOfColumns());

	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			for (int k=0;k<GetNumberOfColumns();k++){
				DividedMatrix2D->SetMatrixValue(i, j, (DividedMatrix2D->GetMatrixValue(i, j) + (GetMatrixValue(i, k) / pDataMatrix2D->GetMatrixValue(k, j))));
			}
		}
	}

	return DividedMatrix2D;

}*/

CDataMatrix2D *CDataMatrix2D::AddScalar (double dblScalar){
	
	CDataMatrix2D *ScalarAddedMatrix2D = new CDataMatrix2D(GetNumberOfRows(), GetNumberOfColumns());

	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<GetNumberOfColumns();j++){
			ScalarAddedMatrix2D->SetMatrixValue(i, j, (GetMatrixValue(i, j) + dblScalar));
		}
	}

	return ScalarAddedMatrix2D;

}

CDataMatrix2D *CDataMatrix2D::SubtractScalar (double dblScalar){
	
	CDataMatrix2D *ScalarSubtractedMatrix2D = new CDataMatrix2D(GetNumberOfRows(), GetNumberOfColumns());

	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<GetNumberOfColumns();j++){
			ScalarSubtractedMatrix2D->SetMatrixValue(i, j, (GetMatrixValue(i, j) - dblScalar));
		}
	}

	return ScalarSubtractedMatrix2D;

}

CDataMatrix2D *CDataMatrix2D::MultiplyScalar (double dblScalar){
	
	CDataMatrix2D *ScalarMultipliedMatrix2D = new CDataMatrix2D(GetNumberOfRows(), GetNumberOfColumns());

	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<GetNumberOfColumns();j++){
			ScalarMultipliedMatrix2D->SetMatrixValue(i, j, (GetMatrixValue(i, j) * dblScalar));
		}
	}

	return ScalarMultipliedMatrix2D;

}

CDataMatrix2D *CDataMatrix2D::DivideScalar (double dblScalar){
	
	CDataMatrix2D *ScalarDividededMatrix2D = new CDataMatrix2D(GetNumberOfRows(), GetNumberOfColumns());

	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<GetNumberOfColumns();j++){
			ScalarDividededMatrix2D->SetMatrixValue(i, j, (GetMatrixValue(i, j) / dblScalar));
		}
	}

	return ScalarDividededMatrix2D;

}

void CDataMatrix2D::AddScalarToMatrix (double dblScalar){
	
	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<GetNumberOfColumns();j++){
			SetMatrixValue(i, j, (GetMatrixValue(i, j) + dblScalar));
		}
	}

}

void CDataMatrix2D::SubtractScalarFromMatrix (double dblScalar){
	
	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<GetNumberOfColumns();j++){
			SetMatrixValue(i, j, (GetMatrixValue(i, j) - dblScalar));
		}
	}

}

void CDataMatrix2D::MultiplyScalarToMatrix (double dblScalar){
	
	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<GetNumberOfColumns();j++){
			SetMatrixValue(i, j, (GetMatrixValue(i, j) * dblScalar));
		}
	}

}

void CDataMatrix2D::DivideScalarFromMatrix (double dblScalar){
	
	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<GetNumberOfColumns();j++){
			SetMatrixValue(i, j, (GetMatrixValue(i, j) / dblScalar));
		}
	}

}

CDataMatrix2D *CDataMatrix2D::RotateMatrix (MatrixRotationDegrees mrd){

	CDataMatrix2D *RotatedDataMatrix2D = new CDataMatrix2D();
	int iTmpRows = 0;
	int iTmpColumns = 0;
	int m;
	int i, j, ii, jj;
	
	switch (mrd){
		case DEGREES_0:
			RotatedDataMatrix2D->CreateDataMatrix(GetNumberOfRows(), GetNumberOfColumns());

			for (i=0;i<GetNumberOfRows();i++){
				for (j=0;j<GetNumberOfColumns();j++){
					RotatedDataMatrix2D->SetMatrixValue(i, j, GetMatrixValue(i, j));
				}
			}

			break;
		case DEGREES_45:
			RotatedDataMatrix2D->CreateDataMatrix(GetNumberOfRows() + GetNumberOfColumns() + 1, GetNumberOfRows() + GetNumberOfColumns() + 1);

			iTmpColumns = GetNumberOfColumns() - 1;
			iTmpRows = GetNumberOfRows() - 1;

			for (i=0;i<(GetNumberOfRows() + GetNumberOfColumns() + 1);i++){
				for (j=0;j<(GetNumberOfRows() + GetNumberOfColumns() + 1);j++){
					RotatedDataMatrix2D->SetMatrixValue(i, j, -1.0f);
				}
			}

			m = 1;
			ii = 0;
			jj = 0;
			for (i=0;i<GetNumberOfRows();i++){
				m--;
				jj = iTmpColumns + m;
				ii = i;
				for (j=0;j<GetNumberOfColumns();j++){
					RotatedDataMatrix2D->SetMatrixValue(ii, jj, GetMatrixValue(i, j));
					jj++;
					ii++;
				}
			}

			break;
		case DEGREES_90:
			RotatedDataMatrix2D->CreateDataMatrix(GetNumberOfColumns(), GetNumberOfRows());

			for (i=0;i<GetNumberOfRows();i++){
				for (j=0;j<GetNumberOfColumns();j++){
					RotatedDataMatrix2D->SetMatrixValue(i, j, -1.0f);
				}
			}

			for (i=(GetNumberOfColumns() - 1);i>=0;i--){
				for (j=(GetNumberOfRows() - 1);j>=0;j--){
					m = abs(i - (GetNumberOfRows() - 1));
					RotatedDataMatrix2D->SetMatrixValue(j, m, GetMatrixValue(i, j));
				}
			}

			break;
		case DEGREES_135:
			RotatedDataMatrix2D->CreateDataMatrix(GetNumberOfRows() + GetNumberOfColumns() + 1, GetNumberOfRows() + GetNumberOfColumns() + 1);

			iTmpColumns = GetNumberOfColumns() - 1;
			iTmpRows = GetNumberOfRows() - 1;

			for (i=0;i<(GetNumberOfRows() + GetNumberOfColumns() + 1);i++){
				for (j=0;j<(GetNumberOfRows() + GetNumberOfColumns() + 1);j++){
					RotatedDataMatrix2D->SetMatrixValue(i, j, -1.0f);
				}
			}

			m = 1;
			ii = 0;
			jj = 0;
			for (j=0;j<GetNumberOfRows();j++){	
				m--;
				ii = j;
				jj = GetNumberOfRows() - 1 + m;
				for (i=GetNumberOfColumns() - 1;i>=0;i--){	
					RotatedDataMatrix2D->SetMatrixValue(ii, jj, GetMatrixValue(i, j));
					ii++;
					jj++;
				}
			}

			break;
		default:
			return NULL;
	}

	return RotatedDataMatrix2D;

}

CDataMatrix2D *CDataMatrix2D::TransposeMatrix (void){

	CDataMatrix2D *TransposedMatrix = new CDataMatrix2D(GetNumberOfColumns(), GetNumberOfRows());

	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<GetNumberOfColumns();j++){
			TransposedMatrix->SetMatrixValue(j, i, GetMatrixValue(i, j));
		}
	}

	return TransposedMatrix;

}

CDataMatrix2D *CDataMatrix2D::InverseMatrix (void){

	if (GetNumberOfColumns() != GetNumberOfRows()){
		return NULL;
	}

	int i, j, k;

	double dblTemp1 = 0.0f;
	double dblTemp2 = 0.0f;

	CDataMatrix2D *InverseDataMatrix = NULL;
	CDataMatrix2D *TempDataMatrix = CopyDataMatrix2D();

	CDataIdentityMatrix2D *IdentityMatrix = new CDataIdentityMatrix2D(TempDataMatrix->GetNumberOfRows());
	InverseDataMatrix = IdentityMatrix->CopyIdentityDataMatrixToDataMatrix2D();
	delete IdentityMatrix;
	IdentityMatrix = NULL;

	for (j=0;j<TempDataMatrix->GetNumberOfColumns();j++){
		for (i=0;i<TempDataMatrix->GetNumberOfRows();i++){
			if (i != j){
				dblTemp1 = TempDataMatrix->GetDataMatrixRawData()[j * TempDataMatrix->GetNumberOfColumns() + j];
				dblTemp2 = TempDataMatrix->GetDataMatrixRawData()[i * TempDataMatrix->GetNumberOfColumns() + j];
				for (k=0;k<TempDataMatrix->GetNumberOfColumns();k++){
					TempDataMatrix->GetDataMatrixRawData()[i * TempDataMatrix->GetNumberOfColumns() + k] = TempDataMatrix->GetDataMatrixRawData()[i * TempDataMatrix->GetNumberOfColumns() + k] * dblTemp1 - TempDataMatrix->GetDataMatrixRawData()[j * TempDataMatrix->GetNumberOfColumns() + k] * dblTemp2;
					InverseDataMatrix->GetDataMatrixRawData()[i * TempDataMatrix->GetNumberOfColumns() + k] = InverseDataMatrix->GetDataMatrixRawData()[i * TempDataMatrix->GetNumberOfColumns() + k] * dblTemp1 - InverseDataMatrix->GetDataMatrixRawData()[j * TempDataMatrix->GetNumberOfColumns() + k] * dblTemp2;
				}
			}
		}
	}

	for (i=0;i<TempDataMatrix->GetNumberOfRows();i++){
		dblTemp1 = TempDataMatrix->GetDataMatrixRawData()[i * TempDataMatrix->GetNumberOfColumns() + i];
		if (dblTemp1 == 0){
			// Matrix uninvertible
			delete TempDataMatrix;
			TempDataMatrix = NULL;
			InverseDataMatrix->Zeros();
			return InverseDataMatrix; // NULL ???
			//delete InverseDataMatrix;
			//InverseDataMatrix = NULL;
			//return NULL;
		}      
		for (k=0;k<InverseDataMatrix->GetNumberOfColumns();k++){
			InverseDataMatrix->GetDataMatrixRawData()[i * TempDataMatrix->GetNumberOfColumns() + k] /= dblTemp1;
		}
	}

	delete TempDataMatrix;
	TempDataMatrix = NULL;

	return InverseDataMatrix;

}

CDataMatrix2D *CDataMatrix2D::NormalizeMax (void){

	int i, j;
	double dblMax = 0.0f;

	for (i=0;i<GetNumberOfRows();i++){
		for (j=0;j<GetNumberOfColumns();j++){
			if (dblMax < GetMatrixValue(i, j)){
				dblMax = GetMatrixValue(i, j);
			}
		}
	}

	if (dblMax == 0.0f){
		return NULL;
	}

	CDataMatrix2D *NormalizedDataMatrix2D = new CDataMatrix2D(GetNumberOfRows(), GetNumberOfColumns());

	for (i=0;i<GetNumberOfRows();i++){
		for (j=0;j<GetNumberOfColumns();j++){
			NormalizedDataMatrix2D->SetMatrixValue(i, j, (GetMatrixValue(i, j) / dblMax));
		}
	}

	return NormalizedDataMatrix2D;

}

CDataMatrix2D *CDataMatrix2D::NormalizeSum (void){

	CFeature2DSum *Sum = new CFeature2DSum();
	Sum->CalculateSum(this);

	CDataMatrix2D *NormalizedDataMatrix2D = new CDataMatrix2D(GetNumberOfRows(), GetNumberOfColumns());

	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<GetNumberOfColumns();j++){
			NormalizedDataMatrix2D->SetMatrixValue(i, j, (GetMatrixValue(i, j) / Sum->GetSum()));
		}
	}

	delete Sum;
	Sum = NULL;

	return NormalizedDataMatrix2D;

}

bool CDataMatrix2D::IsEqual (CDataMatrix2D *pDataMatrix2D){

	for (int i=0;i<GetNumberOfRows();i++){
		for (int j=0;j<GetNumberOfColumns();j++){
			if (pDataMatrix2D->GetMatrixValue(i, j) != GetMatrixValue(i, j)){
				return false;
			}
		}
	}

	return true;

}

void CDataMatrix2D::WriteMatrixDataToBMPFile8 (char *szFileName){

	FILE *fp;
	int  i, j, iPaddedWidth;
	unsigned long int curlong;
	unsigned short int curint;
	int iPixelValue;

	iPaddedWidth = GetNumberOfColumns();
	while (iPaddedWidth%4!=0){
		iPaddedWidth++;
	}

	if (!(fp = fopen(szFileName, "wb"))){
		return;
	}

	fputc('B', fp);
	fputc('M', fp);
	curlong = 0;
	fwrite(&curlong, 4, 1, fp);
	curint = 0;
	fwrite(&curint, 2, 1, fp);
	fwrite(&curint, 2, 1, fp);
	curlong = 1078;
	fwrite(&curlong, 4, 1, fp);
	
	curlong = 40;
	fwrite(&curlong, 4, 1, fp);
	curlong = GetNumberOfColumns();
	fwrite(&curlong, 4, 1, fp);
	curlong = GetNumberOfRows();
	fwrite(&curlong, 4, 1, fp);
	curint = 1;
	fwrite(&curint, 2, 1, fp);
	curint = 8;
	fwrite(&curint, 2, 1, fp);
	curlong = 0;
	fwrite(&curlong, 4, 1, fp);
	curlong = iPaddedWidth * GetNumberOfRows();
	fwrite(&curlong, 4, 1, fp);
	curlong = 0;
	fwrite(&curlong, 4, 1, fp);
	fwrite(&curlong, 4, 1, fp);
	fwrite(&curlong, 4, 1, fp);
	fwrite(&curlong, 4, 1, fp);
	
	for (i=0;i<256;i++){
		fputc(i, fp);
		fputc(i, fp);
		fputc(i, fp);
		fputc(0, fp);
	}
	
	for (i=0;i<GetNumberOfRows();i++){
		for (j=0;j<iPaddedWidth;j++){
			if (j >= GetNumberOfColumns()){
				fputc(0, fp);
			}
			else{
				iPixelValue = (int)GetDataMatrixRawData()[((GetNumberOfRows() - 1 - i) * GetNumberOfColumns()) + j];
				//if (iPixelValue < 0){
				//	iPixelValue = 0;
				//}
				//if (iPixelValue > 255){
				//	iPixelValue = 255;
				//}
				fputc(iPixelValue, fp);
			}
		}
	}

	curlong = ftell(fp);
	fseek(fp, 2, SEEK_SET);
	fwrite(&curlong, 4, 1, fp);
	fclose(fp);

}

void CDataMatrix2D::WriteMatrixDataToFile (char *szFileName){

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


