#if !defined(AFX_FEATURE2DSUMOFSQUARES_H__BA0CE65F_0B72_4FC5_A866_C1BA0D5B9E20__INCLUDED_)
#define AFX_FEATURE2DSUMOFSQUARES_H__BA0CE65F_0B72_4FC5_A866_C1BA0D5B9E20__INCLUDED_

#include <cmath>
#include "DataMatrix2D.h"
#include "DataRowsCollumnsOperationsMatrix2D.h"

class CFeature2DSumOfSquares  
{
public:
	CFeature2DSumOfSquares();
	virtual ~CFeature2DSumOfSquares();

	void CalculateSumOfSquares (CDataMatrix2D *pDataMatrix2D);
	double GetSumOfSquares (void) { return m_dblSumOfSquares; }

protected:

	double m_dblSumOfSquares;

};

#endif 
