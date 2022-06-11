#if !defined(AFX_CLASSTODATAMATRIX_H__A591FEB3_8152_45F2_8507_61B059D97C67__INCLUDED_)
#define AFX_CLASSTODATAMATRIX_H__A591FEB3_8152_45F2_8507_61B059D97C67__INCLUDED_

#include "Class.h"
#include "DataMatrix2D.h"
#include "DataMatrix1D.h"

class CClassToDataMatrix  
{
public:
	CClassToDataMatrix();
	virtual ~CClassToDataMatrix();

	CDataMatrix2D *ClassToDataMatrix (CClass *pClass);
	CClass *DataMatrixToClass (CDataMatrix2D *pDataMatrix2D);
	CDataMatrix2D *PatternToDataMatrix2D (CPattern *pPattern);
	CDataMatrix1D *PatternToDataMatrix1D (CPattern *pPattern);
	CPattern *DataMatrixToPattern (CDataMatrix1D *pDataMatrix1D);

};

#endif 
