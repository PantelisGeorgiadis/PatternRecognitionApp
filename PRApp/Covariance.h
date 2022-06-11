#if !defined(AFX_COVARIANCE_H__E1BC85CA_1EBA_4241_AF5F_40DFF190F201__INCLUDED_)
#define AFX_COVARIANCE_H__E1BC85CA_1EBA_4241_AF5F_40DFF190F201__INCLUDED_

#include "DataMatrix2D.h"
#include "DataMatrix1D.h"

class CCovariance  
{
public:
	CCovariance();
	virtual ~CCovariance();

	CDataMatrix2D *CalculateMatrixCovariance (CDataMatrix2D *pDataMatrix2D, bool bDoNotDivideByRowsMinusOne = false);

};

#endif 
