#if !defined(AFX_FEATURE2DSUMENTROPY_H__21565566_5882_4A0B_9D7C_4BC8A2F623EB__INCLUDED_)
#define AFX_FEATURE2DSUMENTROPY_H__21565566_5882_4A0B_9D7C_4BC8A2F623EB__INCLUDED_

#include <cmath>
#include "DataMatrix2D.h"

class CFeature2DSumEntropy  
{
public:
	CFeature2DSumEntropy();
	virtual ~CFeature2DSumEntropy();

	void CalculateSumEntropy (CDataMatrix2D *pDataMatrix2D);
	double GetSumEntropy (void) { return m_dblSumEntropy; }

protected:

	double m_dblSumEntropy;

};

#endif 
