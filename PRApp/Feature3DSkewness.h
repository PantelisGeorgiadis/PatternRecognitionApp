#if !defined(AFX_FEATURE3DSKEWNESS_H__04078CCF_88BE_4096_AAF2_2C98EFBB2D38__INCLUDED_)
#define AFX_FEATURE3DSKEWNESS_H__04078CCF_88BE_4096_AAF2_2C98EFBB2D38__INCLUDED_

#include "DataMatrix3D.h"
#include "Feature3DStandardDeviation.h"

class CFeature3DSkewness  
{
public:
	CFeature3DSkewness();
	virtual ~CFeature3DSkewness();

	void CalculateSkewness (CDataMatrix3D *pDataMatrix3D);
	double GetSkewness (void) { return m_dblSkewness; }

protected:

	double m_dblSkewness;

};

#endif 
