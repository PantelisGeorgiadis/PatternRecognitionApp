#if !defined(AFX_DATAMEANRUNLENGHTMATRIX2D_H__F63B3946_2D3D_4AD4_A946_EB165BFEC2A3__INCLUDED_)
#define AFX_DATAMEANRUNLENGHTMATRIX2D_H__F63B3946_2D3D_4AD4_A946_EB165BFEC2A3__INCLUDED_

#include "DataRunLengthMatrix2D.h"

class CDataMeanRunLenghtMatrix2D  
{
public:
	CDataMeanRunLenghtMatrix2D();
	virtual ~CDataMeanRunLenghtMatrix2D();

	CDataRunLengthMatrix2D *CalculateMeanRunLenghtMatrix(CDataRunLengthMatrix2D *pDataRunLengthMatrix2D0, CDataRunLengthMatrix2D *pDataRunLengthMatrix2D45, CDataRunLengthMatrix2D *pDataRunLengthMatrix2D90, CDataRunLengthMatrix2D *pDataRunLengthMatrix2D135);


};

#endif 
