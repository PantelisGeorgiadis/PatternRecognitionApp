#if !defined(AFX_DATAMATRIX2D_H__48C372F3_84B1_467E_8DAB_FD841C9BDB16__INCLUDED_)
#define AFX_DATAMATRIX2D_H__48C372F3_84B1_467E_8DAB_FD841C9BDB16__INCLUDED_

#include <string.h>
#include "Globals.h"
#include "FileReader.h"
#include "Rectangle.h"

class CDataMatrix2D  
{
public:

	CDataMatrix2D();
	CDataMatrix2D(int iNumberOfRows, int iNumberOfColumns);
	virtual ~CDataMatrix2D();

	void CreateDataMatrix (int iNumberOfRows, int iNumberOfColumns);
	void CreateDataMatrixFromFile (char *szFileName, int iElementsPerLine, int iElementDigits);
	void CreateDataMatrixFromBMPFile8 (char *szFileName);
	void DeleteDataMatrix (void);
	void Zeros (void);
	CDataMatrix2D *CopyDataMatrix2D (void);
	void CopyToDataMatrix2D (CDataMatrix2D *pDestDataMatrix2D);
	void CopyFromDataMatrix2D (CDataMatrix2D *pSrcDataMatrix2D);
	int GetNumberOfRows (void) { return m_iNumberOfRows; }
	int GetNumberOfColumns (void) { return m_iNumberOfColumns; }
	double GetMatrixValue (int iRowIndex, int iColumnIndex);
	void SetMatrixValue (int iRowIndex, int iColumnIndex, double dblValue);
	CDataMatrix2D *GetSubDataMatrix (CRectangle *pRectangle);
	CDataMatrix2D *CreateDataMatrixBinaryMask (CRectangle *pRectangle);
	CDataMatrix2D *Add (CDataMatrix2D *pDataMatrix2D);
	void AddToDataMatrix (CDataMatrix2D *pDataMatrix2D);
	CDataMatrix2D *Subtract (CDataMatrix2D *pDataMatrix2D);
	void SubtractFromDataMatrix (CDataMatrix2D *pDataMatrix2D);
	CDataMatrix2D *Multiply (CDataMatrix2D *pDataMatrix2D);
//	CDataMatrix2D *Divide (CDataMatrix2D *pDataMatrix2D);
	CDataMatrix2D *AddScalar (double dblScalar);
	CDataMatrix2D *SubtractScalar (double dblScalar);
	CDataMatrix2D *MultiplyScalar (double dblScalar);
	CDataMatrix2D *DivideScalar (double dblScalar);
	void AddScalarToMatrix (double dblScalar);
	void SubtractScalarFromMatrix (double dblScalar);
	void MultiplyScalarToMatrix (double dblScalar);
	void DivideScalarFromMatrix (double dblScalar);
	CDataMatrix2D *RotateMatrix (MatrixRotationDegrees mrd);
	CDataMatrix2D *TransposeMatrix (void);
	CDataMatrix2D *InverseMatrix (void);
	double *GetDataMatrixRawData (void) { if (m_dblData){ return m_dblData; } return NULL; }
	CDataMatrix2D *NormalizeMax (void);
	CDataMatrix2D *NormalizeSum (void);
	bool IsEqual (CDataMatrix2D *pDataMatrix2D);
	void WriteMatrixDataToBMPFile8 (char *szFileName);
	void WriteMatrixDataToFile (char *szFileName);

protected:

	int m_iNumberOfRows;
	int m_iNumberOfColumns;
	double *m_dblData;

};

#endif 
