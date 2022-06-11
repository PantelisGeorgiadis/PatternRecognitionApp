#if !defined(AFX_STANDARDDEVIATION_H__30A42FCA_28F5_4B34_BF22_0AF41833442F__INCLUDED_)
#define AFX_STANDARDDEVIATION_H__30A42FCA_28F5_4B34_BF22_0AF41833442F__INCLUDED_

#include <cmath>
#include "Class.h"

class CStandardDeviation  
{
public:
	CStandardDeviation();
	virtual ~CStandardDeviation();

	void CalculateFeaturesStandardDeviation (CClass *pClass, double dblFeaturesMeanValue, int iFeaturesIndex);
	double GetStandardDeviation(void) { return m_dblStandardDeviation; }

protected:

	double m_dblStandardDeviation;

};

#endif 
