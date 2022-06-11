#if !defined(AFX_FEATURE2DDIFFERENCEENTROPY_H__5CBD7030_07CE_4A99_9BEC_B6AF86F68EB4__INCLUDED_)
#define AFX_FEATURE2DDIFFERENCEENTROPY_H__5CBD7030_07CE_4A99_9BEC_B6AF86F68EB4__INCLUDED_

#include <cmath>
#include "DataMatrix2D.h"

class CFeature2DDifferenceEntropy  
{
public:
	CFeature2DDifferenceEntropy();
	virtual ~CFeature2DDifferenceEntropy();

	void CalculateDifferenceEntropy (CDataMatrix2D *pDataMatrix2D);
	double GetDifferenceEntropy (void) { return m_dblDifferenceEntropy; }

protected:

	double m_dblDifferenceEntropy;

};

#endif 
