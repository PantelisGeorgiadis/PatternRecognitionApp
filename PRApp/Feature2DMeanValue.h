#if !defined(AFX_FEATURE2DMEANVALUE_H__B345291D_8747_4460_98A2_9DFAA954E50C__INCLUDED_)
#define AFX_FEATURE2DMEANVALUE_H__B345291D_8747_4460_98A2_9DFAA954E50C__INCLUDED_

#include "DataMatrix2D.h"
#include "Feature2DSum.h"

class CFeature2DMeanValue  
{
public:
	CFeature2DMeanValue();
	virtual ~CFeature2DMeanValue();

	void CalculateMeanValue (CDataMatrix2D *pDataMatrix2D);
	double GetMeanValue (void) { return m_dblMeanValue; }

protected:

	double m_dblMeanValue;

};

#endif 
