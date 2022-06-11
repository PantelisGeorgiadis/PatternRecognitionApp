#if !defined(AFX_FEATURE1DMEANVALUE_H__8C4B7A52_31F6_4979_9567_7F5D77B9D308__INCLUDED_)
#define AFX_FEATURE1DMEANVALUE_H__8C4B7A52_31F6_4979_9567_7F5D77B9D308__INCLUDED_

#include "DataMatrix1D.h"
#include "Feature2DMeanValue.h"

class CFeature1DMeanValue  
{
public:
	CFeature1DMeanValue();
	virtual ~CFeature1DMeanValue();

	void CalculateMeanValue (CDataMatrix1D *pDataMatrix1D);
	double GetMeanValue (void) { return m_dblMeanValue; }

protected:

	double m_dblMeanValue;

};

#endif 
