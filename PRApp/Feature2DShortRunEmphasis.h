#if !defined(AFX_FEATURE2DSHORTRUNEMPHASIS_H__DF3E64FB_402D_4C88_A759_DCD1F55E9859__INCLUDED_)
#define AFX_FEATURE2DSHORTRUNEMPHASIS_H__DF3E64FB_402D_4C88_A759_DCD1F55E9859__INCLUDED_

#include <cmath>
#include "DataMatrix2D.h"
#include "Feature2DSum.h"

class CFeature2DShortRunEmphasis  
{
public:
	CFeature2DShortRunEmphasis();
	virtual ~CFeature2DShortRunEmphasis();

	void CalculateShortRunEmphasis (CDataMatrix2D *pDataMatrix2D);
	double GetShortRunEmphasis (void) { return m_dblShortRunEmphasis; }

protected:

	double m_dblShortRunEmphasis;

};

#endif 
