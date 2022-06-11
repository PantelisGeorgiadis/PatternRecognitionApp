#if !defined(AFX_FEATURE2DRUNLENGTHNONUNIFORMITY_H__BA3D6915_2182_4B33_AAF4_6603F3FD3AF1__INCLUDED_)
#define AFX_FEATURE2DRUNLENGTHNONUNIFORMITY_H__BA3D6915_2182_4B33_AAF4_6603F3FD3AF1__INCLUDED_

#include <cmath>
#include "DataMatrix2D.h"
#include "Feature2DSum.h"

class CFeature2DRunLengthNonUniformity  
{
public:
	CFeature2DRunLengthNonUniformity();
	virtual ~CFeature2DRunLengthNonUniformity();

	void CalculateRunLengthNonUniformity (CDataMatrix2D *pDataMatrix2D);
	double GetRunLengthNonUniformity (void) { return m_dblRunLengthNonUniformity; }

protected:

	double m_dblRunLengthNonUniformity;

};

#endif 
