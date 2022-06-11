#if !defined(AFX_FEATURE2DSKEWNESS_H__BD91D628_ADE9_4463_84C9_72974758E211__INCLUDED_)
#define AFX_FEATURE2DSKEWNESS_H__BD91D628_ADE9_4463_84C9_72974758E211__INCLUDED_

#include "DataMatrix2D.h"
#include "Feature2DStandardDeviation.h"

class CFeature2DSkewness  
{
public:
	CFeature2DSkewness();
	virtual ~CFeature2DSkewness();

	void CalculateSkewness (CDataMatrix2D *pDataMatrix2D);
	double GetSkewness (void) { return m_dblSkewness; }

protected:

	double m_dblSkewness;

};

#endif 
