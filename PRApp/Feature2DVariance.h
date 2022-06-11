#if !defined(AFX_FEATURE2DVARIANCE_H__70674326_93D4_46DE_9595_DC9219649D71__INCLUDED_)
#define AFX_FEATURE2DVARIANCE_H__70674326_93D4_46DE_9595_DC9219649D71__INCLUDED_

#include <cmath>
#include "DataMatrix2D.h"
#include "Feature2DMeanValue.h"

class CFeature2DVariance  
{
public:
	CFeature2DVariance();
	virtual ~CFeature2DVariance();

	void CalculateVariance (CDataMatrix2D *pDataMatrix2D);
	double GetVariance (void) { return m_dblVariance; }

protected:

	double m_dblVariance;

};

#endif 
