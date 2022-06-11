#if !defined(AFX_DATAROWSCOLLUMNSOPERATIONSMATRIX2D_H__AE59EF0C_DB8D_45EC_80E9_67199A46DDA1__INCLUDED_)
#define AFX_DATAROWSCOLLUMNSOPERATIONSMATRIX2D_H__AE59EF0C_DB8D_45EC_80E9_67199A46DDA1__INCLUDED_

#include <cmath>
#include "DataMatrix2D.h"

class CDataRowsCollumnsOperationsMatrix2D  
{
public:
	CDataRowsCollumnsOperationsMatrix2D();
	virtual ~CDataRowsCollumnsOperationsMatrix2D();

	CDataMatrix2D *RowsCollumnsAddition (CDataMatrix2D *pDataMatrix2D);
	CDataMatrix2D *RowsCollumnsSubtraction (CDataMatrix2D *pDataMatrix2D);
	void RowsMean (CDataMatrix2D *pDataMatrix2D);
	void RowsStandardDeviation (CDataMatrix2D *pDataMatrix2D);

	double GetRowsMean (void) { return m_dblRowsMean; }
	double GetRowsStandardDeviation (void) { return m_dblRowsStandardDeviation; }

protected:

	double m_dblRowsMean;
	double m_dblRowsStandardDeviation;

};

#endif 
