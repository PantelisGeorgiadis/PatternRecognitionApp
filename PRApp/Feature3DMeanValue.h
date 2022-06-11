#if !defined(AFX_FEATURE3DMEANVALUE_H__B1E10791_5414_4B41_A9F0_29090212426D__INCLUDED_)
#define AFX_FEATURE3DMEANVALUE_H__B1E10791_5414_4B41_A9F0_29090212426D__INCLUDED_

#include "DataMatrix3D.h"
#include "Feature3DSum.h"

class CFeature3DMeanValue  
{
public:
	CFeature3DMeanValue();
	virtual ~CFeature3DMeanValue();

	void CalculateMeanValue (CDataMatrix3D *pDataMatrix3D);
	double GetMeanValue (void) { return m_dblMeanValue; }

protected:

	double m_dblMeanValue;

};

#endif 
