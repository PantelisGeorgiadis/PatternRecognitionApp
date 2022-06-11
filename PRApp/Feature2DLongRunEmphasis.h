#if !defined(AFX_FEATURE2DLONGRUNEMPHASIS_H__1F12E834_E646_4923_8B93_C0ABAC29D83B__INCLUDED_)
#define AFX_FEATURE2DLONGRUNEMPHASIS_H__1F12E834_E646_4923_8B93_C0ABAC29D83B__INCLUDED_

#include <cmath>
#include "DataMatrix2D.h"
#include "Feature2DSum.h"

class CFeature2DLongRunEmphasis  
{
public:
	CFeature2DLongRunEmphasis();
	virtual ~CFeature2DLongRunEmphasis();

	void CalculateLongRunEmphasis (CDataMatrix2D *pDataMatrix2D);
	double GetLongRunEmphasis (void) { return m_dblLongRunEmphasis; }

protected:

	double m_dblLongRunEmphasis;

};

#endif 
