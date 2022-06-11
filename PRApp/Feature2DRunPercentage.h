#if !defined(AFX_FEATURE2DRUNPERCENTAGE_H__12E0A595_CDA3_4217_91AD_A667E1940430__INCLUDED_)
#define AFX_FEATURE2DRUNPERCENTAGE_H__12E0A595_CDA3_4217_91AD_A667E1940430__INCLUDED_

#include "DataMatrix2D.h"

class CFeature2DRunPercentage  
{
public:
	CFeature2DRunPercentage();
	virtual ~CFeature2DRunPercentage();

	void CalculateRunPercentage (CDataMatrix2D *pDataMatrix2D, int iImageWidth, int iImageHeight);
	double GetRunPercentage (void) { return m_dblRunPercentage; }

protected:

	double m_dblRunPercentage;

};

#endif 
