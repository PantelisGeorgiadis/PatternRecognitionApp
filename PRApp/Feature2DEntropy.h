#if !defined(AFX_FEATURE2DENTROPY_H__07ACF222_3822_45ED_AF7B_79F9735ED521__INCLUDED_)
#define AFX_FEATURE2DENTROPY_H__07ACF222_3822_45ED_AF7B_79F9735ED521__INCLUDED_

#include <cmath>
#include "DataMatrix2D.h"

class CFeature2DEntropy  
{
public:
	CFeature2DEntropy();
	virtual ~CFeature2DEntropy();

	void CalculateEntropy (CDataMatrix2D *pDataMatrix2D);
	double GetEntropy (void) { return m_dblEntropy; }

protected:

	double m_dblEntropy;

};

#endif 
