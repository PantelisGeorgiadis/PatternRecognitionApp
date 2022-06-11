#if !defined(AFX_FEATURE2DSUM_H__087CA9E2_AF27_4860_8A88_21FA7024D08D__INCLUDED_)
#define AFX_FEATURE2DSUM_H__087CA9E2_AF27_4860_8A88_21FA7024D08D__INCLUDED_

#include "DataMatrix2D.h"

class CFeature2DSum  
{
public:
	CFeature2DSum();
	virtual ~CFeature2DSum();

	void CalculateSum (CDataMatrix2D *pDataMatrix2D);
	double GetSum (void) { return m_dblSum; }

protected:

	double m_dblSum;

};

#endif 
