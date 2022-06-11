#if !defined(AFX_FEATURE2DSUMAVERAGE_H__83DAE09E_AC81_4700_BF11_78339849EF08__INCLUDED_)
#define AFX_FEATURE2DSUMAVERAGE_H__83DAE09E_AC81_4700_BF11_78339849EF08__INCLUDED_

#include "DataMatrix2D.h"

class CFeature2DSumAverage  
{
public:
	CFeature2DSumAverage();
	virtual ~CFeature2DSumAverage();

	void CalculateSumAverage (CDataMatrix2D *pDataMatrix2D);
	double GetSumAverage (void) { return m_dblSumAverage; }

protected:

	double m_dblSumAverage;

};

#endif 
