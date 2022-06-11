#if !defined(AFX_FEATURE2DSUMVARIANCE_H__6C9FE890_A57E_46F1_BE84_C7ABED7AD224__INCLUDED_)
#define AFX_FEATURE2DSUMVARIANCE_H__6C9FE890_A57E_46F1_BE84_C7ABED7AD224__INCLUDED_

#include <cmath>
#include "DataMatrix2D.h"

class CFeature2DSumVariance  
{
public:
	CFeature2DSumVariance();
	virtual ~CFeature2DSumVariance();

	void CalculateSumVariance (CDataMatrix2D *pDataMatrix2D);
	double GetSumVariance (void) { return m_dblSumVariance; }

protected:

	double m_dblSumVariance;

};

#endif 
