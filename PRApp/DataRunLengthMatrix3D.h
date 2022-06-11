#if !defined(AFX_DATARUNLENGTHMATRIX3D_H__3D9C2E95_E58C_4F0B_9199_ED5637490F50__INCLUDED_)
#define AFX_DATARUNLENGTHMATRIX3D_H__3D9C2E95_E58C_4F0B_9199_ED5637490F50__INCLUDED_

#include "DataMatrix2D.h"
#include "DataMatrix3D.h"

class CDataRunLengthMatrix3D  
{
public:
	CDataRunLengthMatrix3D();
	virtual ~CDataRunLengthMatrix3D();

	void FillDataRunLengthMatrixes (CDataMatrix3D *pDataMatrix3D, int iDepth);
	CDataMatrix2D *GetDataRunLengthMatrix (int iIndex);
	void CreateDataRunLengthMatrixes (void);
	void DeleteDataRunLengthMatrixes (void);

protected:

	CDataMatrix2D *m_pDataRunLengthMatrixes;

};

#endif
