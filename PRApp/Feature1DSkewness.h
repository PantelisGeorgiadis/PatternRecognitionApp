#if !defined(AFX_FEATURE1DSKEWNESS_H__C1782124_B6F7_4CE9_B283_89E79DC053C6__INCLUDED_)
#define AFX_FEATURE1DSKEWNESS_H__C1782124_B6F7_4CE9_B283_89E79DC053C6__INCLUDED_

#include "DataMatrix1D.h"
#include "Feature2DSkewness.h"

class CFeature1DSkewness  
{
public:
	CFeature1DSkewness();
	virtual ~CFeature1DSkewness();

	void CalculateSkewness (CDataMatrix1D *pDataMatrix1D);
	double GetSkewness (void) { return m_dblSkewness; }

protected:

	double m_dblSkewness;

};

#endif 
