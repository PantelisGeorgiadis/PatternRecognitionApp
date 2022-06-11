#if !defined(AFX_DATAIDENTITYMATRIX2D_H__B32CF928_8571_430B_94A5_47983FD260A5__INCLUDED_)
#define AFX_DATAIDENTITYMATRIX2D_H__B32CF928_8571_430B_94A5_47983FD260A5__INCLUDED_

#include "DataMatrix2D.h"

class CDataIdentityMatrix2D  
{
public:
	CDataIdentityMatrix2D();
	CDataIdentityMatrix2D(int iRank);
	virtual ~CDataIdentityMatrix2D();

	void CreateDataMatrix (int iRank);
	void DeleteDataMatrix (void);
	void Zeros (void);
	CDataIdentityMatrix2D *CopyIdentityDataMatrix2D (void);
	int GetNumberOfRows (void) { return m_iNumberOfRows; }
	int GetNumberOfColumns (void) { return m_iNumberOfColumns; }
	int GetIdentityMatrixRank (void) { return m_iRank; }
	double GetMatrixValue (int iRowIndex, int iColumnIndex);
	void SetMatrixValue (int iRowIndex, int iColumnIndex, double dblValue);
	CDataMatrix2D *CopyIdentityDataMatrixToDataMatrix2D (void);
	void WriteIdentityMatrixDataToFile (char *szFileName);

protected:

	int m_iRank;
	int m_iNumberOfRows;
	int m_iNumberOfColumns;
	double *m_dblData;

	void FillDataIdentityMatrix (void);

};

#endif 
