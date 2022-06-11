#if !defined(AFX_FEATURE3DKURTOSIS_H__A2ED9C85_7CD1_4763_9EB8_565D1181558D__INCLUDED_)
#define AFX_FEATURE3DKURTOSIS_H__A2ED9C85_7CD1_4763_9EB8_565D1181558D__INCLUDED_

#include "DataMatrix3D.h"
#include "Feature3DStandardDeviation.h"

class CFeature3DKurtosis  
{
public:
	CFeature3DKurtosis();
	virtual ~CFeature3DKurtosis();

	void CalculateKurtosis (CDataMatrix3D *pDataMatrix3D);
	double GetKurtosis (void) { return m_dblKurtosis; }

protected:

	double m_dblKurtosis;

};

#endif 
