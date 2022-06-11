#if !defined(AFX_FEATURE3DVARIANCE_H__143E2258_86C1_4F7C_BCDE_E5E3CE623F7F__INCLUDED_)
#define AFX_FEATURE3DVARIANCE_H__143E2258_86C1_4F7C_BCDE_E5E3CE623F7F__INCLUDED_

#include <cmath>
#include "DataMatrix3D.h"
#include "Feature3DMeanValue.h"

class CFeature3DVariance  
{
public:
	CFeature3DVariance();
	virtual ~CFeature3DVariance();

	void CalculateVariance (CDataMatrix3D *pDataMatrix3D);
	double GetVariance (void) { return m_dblVariance; }

protected:

	double m_dblVariance;

};

#endif
