#if !defined(AFX_FEATURE2DANGULARSECONDMOMENT_H__782B396F_3A35_46C9_A509_A2954B87A42E__INCLUDED_)
#define AFX_FEATURE2DANGULARSECONDMOMENT_H__782B396F_3A35_46C9_A509_A2954B87A42E__INCLUDED_

#include <cmath>
#include "DataMatrix2D.h"

class CFeature2DAngularSecondMoment  
{
public:
	CFeature2DAngularSecondMoment();
	virtual ~CFeature2DAngularSecondMoment();

	void CalculateAngularSecondMoment (CDataMatrix2D *pDataMatrix2D);
	double GetAngularSecondMoment (void) { return m_dblAngularSecondMoment; }

protected:

	double m_dblAngularSecondMoment;

};

#endif 
