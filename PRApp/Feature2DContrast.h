#if !defined(AFX_FEATURE2DCONTRAST_H__79DC832D_E172_4B9B_85EA_28D2E880B743__INCLUDED_)
#define AFX_FEATURE2DCONTRAST_H__79DC832D_E172_4B9B_85EA_28D2E880B743__INCLUDED_

#include <cmath>
#include "DataMatrix2D.h"

class CFeature2DContrast  
{
public:
	CFeature2DContrast();
	virtual ~CFeature2DContrast();

	void CalculateContrast (CDataMatrix2D *pDataMatrix2D);
	double GetContrast (void) { return m_dblContrast; }

protected:

	double m_dblContrast;

};

#endif 
