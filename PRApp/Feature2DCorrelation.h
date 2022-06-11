#if !defined(AFX_FEATURE2DCORRELATION_H__D7BD3A4F_E14E_4C31_8E79_47F14E08E322__INCLUDED_)
#define AFX_FEATURE2DCORRELATION_H__D7BD3A4F_E14E_4C31_8E79_47F14E08E322__INCLUDED_

#include "DataMatrix2D.h"
#include "DataRowsCollumnsOperationsMatrix2D.h"

class CFeature2DCorrelation  
{
public:
	CFeature2DCorrelation();
	virtual ~CFeature2DCorrelation();

	void CalculateCorrelation (CDataMatrix2D *pDataMatrix2D);
	double GetCorrelation (void) { return m_dblCorrelation; }

protected:

	double m_dblCorrelation;

};

#endif 
