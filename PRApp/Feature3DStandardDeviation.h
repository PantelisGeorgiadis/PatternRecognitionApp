#if !defined(AFX_FEATURE3DSTANDARDDEVIATION_H__ED1A4F5C_BA1F_438E_942A_AEFFF1EBA45D__INCLUDED_)
#define AFX_FEATURE3DSTANDARDDEVIATION_H__ED1A4F5C_BA1F_438E_942A_AEFFF1EBA45D__INCLUDED_

#include "DataMatrix3D.h"
#include "Feature3DVariance.h"

class CFeature3DStandardDeviation  
{
public:
	CFeature3DStandardDeviation();
	virtual ~CFeature3DStandardDeviation();

	void CalculateStandardDeviation (CDataMatrix3D *pDataMatrix3D);
	double GetStandardDeviation (void) { return m_dblStandardDeviation; }

protected:

	double m_dblStandardDeviation;

};

#endif 
