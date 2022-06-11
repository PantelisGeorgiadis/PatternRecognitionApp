#if !defined(AFX_MEANVALUE_H__FF30E665_9947_4A51_847F_D5981EA11D2D__INCLUDED_)
#define AFX_MEANVALUE_H__FF30E665_9947_4A51_847F_D5981EA11D2D__INCLUDED_

#include "Class.h"

class CMeanValue  
{
public:
	CMeanValue();
	virtual ~CMeanValue();

	void CalculateFeaturesMeanValue (CClass *pClass, int iFeaturesIndex);
	double GetMeanValue (void) { return m_dblMeanValue; }

protected:

	double m_dblMeanValue;

};

#endif 
