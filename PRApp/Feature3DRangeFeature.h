#if !defined(AFX_FEATURE3DRANGEFEATURE_H__1543957E_5B72_4DB0_A774_CBF1906E097A__INCLUDED_)
#define AFX_FEATURE3DRANGEFEATURE_H__1543957E_5B72_4DB0_A774_CBF1906E097A__INCLUDED_

#include <limits>

class CFeature3DRangeFeature  
{
public:
	CFeature3DRangeFeature();
	virtual ~CFeature3DRangeFeature();

	void CalculateRangeFeatureValue (double f0, double f1, double f2, double f3, double f4, double f5, double f6, double f7, double f8, double f9, double f10, double f11, double f12);
	double GetRangeFeatureValue (void) { return m_dblRangeFeatureValue; }

protected:

	double m_dblRangeFeatureValue;

};

#endif 
