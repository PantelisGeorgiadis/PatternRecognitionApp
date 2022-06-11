#if !defined(AFX_DETERMINANT_H__3405E35C_E8A4_4CA2_A1CD_18D63C6D9245__INCLUDED_)
#define AFX_DETERMINANT_H__3405E35C_E8A4_4CA2_A1CD_18D63C6D9245__INCLUDED_

#include <cmath>
#include "DataMatrix2D.h"

class CDeterminant  
{
public:
	CDeterminant();
	virtual ~CDeterminant();

	double CalculateMatrixDeterminant (CDataMatrix2D *pDataMatrix2D);

};

#endif 
