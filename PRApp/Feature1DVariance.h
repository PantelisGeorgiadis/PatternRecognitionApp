#if !defined(AFX_FEATURE1DVARIANCE_H__3705223F_3C1F_4C64_9BC0_A87586498391__INCLUDED_)
#define AFX_FEATURE1DVARIANCE_H__3705223F_3C1F_4C64_9BC0_A87586498391__INCLUDED_

#include "DataMatrix1D.h"
#include "Feature2DVariance.h"

class CFeature1DVariance  
{
public:
	CFeature1DVariance();
	virtual ~CFeature1DVariance();

	void CalculateVariance (CDataMatrix1D *pDataMatrix1D);
	double GetVariance (void) { return m_dblVariance; }

protected:

	double m_dblVariance;

};

#endif 
