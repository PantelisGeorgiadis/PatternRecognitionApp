#if !defined(AFX_FEATURE1DSTANDARDDEVIATION_H__6451EF13_DEF6_4C50_BBDC_AEB5A777F9DE__INCLUDED_)
#define AFX_FEATURE1DSTANDARDDEVIATION_H__6451EF13_DEF6_4C50_BBDC_AEB5A777F9DE__INCLUDED_

#include "DataMatrix1D.h"
#include "Feature2DStandardDeviation.h"

class CFeature1DStandardDeviation  
{
public:
	CFeature1DStandardDeviation();
	virtual ~CFeature1DStandardDeviation();

	void CalculateStandardDeviation (CDataMatrix1D *pDataMatrix1D);
	double GetStandardDeviation (void) { return m_dblStandardDeviation; }

protected:

	double m_dblStandardDeviation;

};

#endif 
