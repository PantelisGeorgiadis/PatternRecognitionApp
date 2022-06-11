// Feature2DInverseDifferenceMoment.h: interface for the CFeature2DInverseDifferenceMoment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FEATURE2DINVERSEDIFFERENCEMOMENT_H__DA00BC52_1873_41E3_B8D6_266818444823__INCLUDED_)
#define AFX_FEATURE2DINVERSEDIFFERENCEMOMENT_H__DA00BC52_1873_41E3_B8D6_266818444823__INCLUDED_

#include <cmath>
#include "DataMatrix2D.h"

class CFeature2DInverseDifferenceMoment  
{
public:
	CFeature2DInverseDifferenceMoment();
	virtual ~CFeature2DInverseDifferenceMoment();

	void CalculateInverseDifferenceMoment (CDataMatrix2D *pDataMatrix2D);
	double GetInverseDifferenceMoment (void) { return m_dblInverseDifferenceMoment; }

protected:

	double m_dblInverseDifferenceMoment;

};

#endif 
