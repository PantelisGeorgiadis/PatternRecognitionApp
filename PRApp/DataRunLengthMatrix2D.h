#if !defined(AFX_DATARUNLENGTHMATRIX2D_H__7EBF1E4E_891D_4B51_A792_AB1994D41072__INCLUDED_)
#define AFX_DATARUNLENGTHMATRIX2D_H__7EBF1E4E_891D_4B51_A792_AB1994D41072__INCLUDED_

#include "DataMatrix2D.h"

class CDataRunLengthMatrix2D  
{
public:
	CDataRunLengthMatrix2D();
	CDataRunLengthMatrix2D(CDataMatrix2D *pDataMatrix2D, int iDepth, MatrixRotationDegrees mrd);
	virtual ~CDataRunLengthMatrix2D();

	void CreateDataMatrix (CDataMatrix2D *pDataMatrix2D, int iDepth, MatrixRotationDegrees mrd);
	void CreateDataMatrix (int iDepth, int iLenght, MatrixRotationDegrees mrd);
	void DeleteDataMatrix (void);
	void Zeros (void);
	void FillDataRunLenghtMatrix (CDataMatrix2D *pDataMatrix2D);
	CDataRunLengthMatrix2D *CopyRunLengthMatrix2D (void);
	int GetNumberOfRows (void) { return m_iNumberOfRows; }
	int GetNumberOfColumns (void) { return m_iNumberOfColumns; }
	int GetLenght (void) { return m_iDepth; }
	int GetDepth (void) { return m_iDepth; }
	MatrixRotationDegrees GetMatrixRotationDegrees (void) { return m_mrd; }
	double GetMatrixValue (int iRowIndex, int iColumnIndex);
	void SetMatrixValue (int iRowIndex, int iColumnIndex, double dblValue);
	CDataMatrix2D *CopyRunLengthDataMatrixToDataMatrix2D (void);
	void WriteRunLengthMatrixDataToFile (char *szFileName);

protected:

	int m_iLenght;
	int m_iDepth;
	int m_iNumberOfRows;
	int m_iNumberOfColumns;
	double *m_dblData;
	MatrixRotationDegrees m_mrd;

};

#endif 
