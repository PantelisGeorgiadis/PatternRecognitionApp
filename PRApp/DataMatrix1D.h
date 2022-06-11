#if !defined(AFX_DATAMATRIX1D_H__AA845330_6596_4388_87FC_6B197B20F490__INCLUDED_)
#define AFX_DATAMATRIX1D_H__AA845330_6596_4388_87FC_6B197B20F490__INCLUDED_

#include "DataMatrix2D.h"

class CDataMatrix1D : public CDataMatrix2D
{
public:
	CDataMatrix1D();
	CDataMatrix1D(int iNumberOfColumns);
	virtual ~CDataMatrix1D();

	void CreateDataMatrix (int iNumberOfColumns);
	void DeleteDataMatrix (void);
	void Zeros (void);
	CDataMatrix1D *CopyDataMatrix1D (void);
	int GetNumberOfColumns (void) { return m_iNumberOfColumns; }
	int GetNumberOfRows (void) { return 1; }
	double GetMatrixValue (int iColumnIndex);
	void SetMatrixValue (int iColumnIndex, double dblValue);
	CDataMatrix2D *GetDataMatrix1DAsDataMatrix2D (void);
	void WriteMatrixDataToFile (char *szFileName);

protected:

	int m_iNumberOfColumns;

	CDataMatrix2D *m_DataMatrix2D;

};

#endif 
