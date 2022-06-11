#if !defined(AFX_FEATURE2DSTANDARDDEVIATION_H__DCB49302_369F_46CD_AD00_F69E90E06475__INCLUDED_)
#define AFX_FEATURE2DSTANDARDDEVIATION_H__DCB49302_369F_46CD_AD00_F69E90E06475__INCLUDED_

#include "DataMatrix2D.h"
#include "Feature2DVariance.h"

class CFeature2DStandardDeviation  
{
public:
	CFeature2DStandardDeviation();
	virtual ~CFeature2DStandardDeviation();

	void CalculateStandardDeviation (CDataMatrix2D *pDataMatrix2D);
	double GetStandardDeviation (void) { return m_dblStandardDeviation; }

protected:

	double m_dblStandardDeviation;

};

#endif 
