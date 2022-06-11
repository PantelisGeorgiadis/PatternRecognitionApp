#if !defined(AFX_FEATURE1DKURTOSIS_H__03C1CEC2_70AF_41F1_B9BD_11B990124ED7__INCLUDED_)
#define AFX_FEATURE1DKURTOSIS_H__03C1CEC2_70AF_41F1_B9BD_11B990124ED7__INCLUDED_

#include "DataMatrix1D.h"
#include "Feature2DKurtosis.h"

class CFeature1DKurtosis  
{
public:
	CFeature1DKurtosis();
	virtual ~CFeature1DKurtosis();

	void CalculateKurtosis (CDataMatrix1D *pDataMatrix1D);
	double GetKurtosis (void) { return m_dblKurtosis; }

protected:

	double m_dblKurtosis;

};

#endif 
