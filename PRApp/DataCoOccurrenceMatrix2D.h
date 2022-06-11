#if !defined(AFX_DATACOOCCURRENCEMATRIX2D_H__87F61C0A_5E16_4C83_A586_72A1A8BA919E__INCLUDED_)
#define AFX_DATACOOCCURRENCEMATRIX2D_H__87F61C0A_5E16_4C83_A586_72A1A8BA919E__INCLUDED_

#include "DataMatrix2D.h"

class CDataCoOccurrenceMatrix2D  
{
public:
	CDataCoOccurrenceMatrix2D();
	CDataCoOccurrenceMatrix2D(CDataMatrix2D *pDataMatrix2D, int iDepth, MatrixRotationDegrees mrd);
	virtual ~CDataCoOccurrenceMatrix2D();

	void CreateDataMatrix (CDataMatrix2D *pDataMatrix2D, int iDepth, MatrixRotationDegrees mrd);
	void CreateDataMatrix (int iDepth, MatrixRotationDegrees mrd);
	void DeleteDataMatrix (void);
	void Zeros (void);
	void FillDataCoOccurrenceMatrix (CDataMatrix2D *pDataMatrix2D);
	CDataCoOccurrenceMatrix2D *CopyCoOccurrenceMatrix2D (void);
	int GetNumberOfRows (void) { return m_iNumberOfRows; }
	int GetNumberOfColumns (void) { return m_iNumberOfColumns; }
	int GetDepth (void) { return m_iDepth; }
	MatrixRotationDegrees GetMatrixRotationDegrees (void) { return m_mrd; }
	double GetMatrixValue (int iRowIndex, int iColumnIndex);
	void SetMatrixValue (int iRowIndex, int iColumnIndex, double dblValue);
	CDataMatrix2D *CopyCoOccurrenceDataMatrixToDataMatrix2D (void);
	void WriteCoOccurrenceMatrixDataToFile (char *szFileName);

protected:

	int m_iDepth;
	int m_iNumberOfRows;
	int m_iNumberOfColumns;
	double *m_dblData;
	MatrixRotationDegrees m_mrd;

};

#endif 
