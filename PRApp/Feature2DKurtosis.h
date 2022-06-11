#if !defined(AFX_FEATURE2DKURTOSIS_H__5CA41696_22A3_4077_AC28_41A343F847A5__INCLUDED_)
#define AFX_FEATURE2DKURTOSIS_H__5CA41696_22A3_4077_AC28_41A343F847A5__INCLUDED_

#include "DataMatrix2D.h"
#include "Feature2DStandardDeviation.h"

class CFeature2DKurtosis  
{
public:
	CFeature2DKurtosis();
	virtual ~CFeature2DKurtosis();

	void CalculateKurtosis (CDataMatrix2D *pDataMatrix2D);
	double GetKurtosis (void) { return m_dblKurtosis; }

protected:

	double m_dblKurtosis;

};

#endif 
