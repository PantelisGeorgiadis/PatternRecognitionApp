#if !defined(AFX_FEATURE2DDIFFERENCEVARIANCE_H__C480AC90_D401_4FD9_B93D_E52AB6A05458__INCLUDED_)
#define AFX_FEATURE2DDIFFERENCEVARIANCE_H__C480AC90_D401_4FD9_B93D_E52AB6A05458__INCLUDED_

#include <cmath>
#include "DataMatrix2D.h"

class CFeature2DDifferenceVariance  
{
public:
	CFeature2DDifferenceVariance();
	virtual ~CFeature2DDifferenceVariance();

	void CalculateDifferenceVariance (CDataMatrix2D *pDataMatrix2D);
	double GetDifferenceVariance (void) { return m_dblDifferenceVariance; }

protected:

	double m_dblDifferenceVariance;

};

#endif 
