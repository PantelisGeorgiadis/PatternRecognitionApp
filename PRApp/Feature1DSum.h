#if !defined(AFX_FEATURE1DSUM_H__B1D19758_15E8_41FB_BC4F_3655764D4030__INCLUDED_)
#define AFX_FEATURE1DSUM_H__B1D19758_15E8_41FB_BC4F_3655764D4030__INCLUDED_

#include "DataMatrix1D.h"
#include "Feature2DSum.h"

class CFeature1DSum  
{
public:
	CFeature1DSum();
	virtual ~CFeature1DSum();

	void CalculateSum (CDataMatrix1D *pDataMatrix1D);
	double GetSum (void) { return m_dblSum; }

protected:

	double m_dblSum;

};

#endif 
