#if !defined(AFX_FEATURE2DRANGEFEATURE_H__48E846B4_EFB7_402A_A290_DB8B0237BB8D__INCLUDED_)
#define AFX_FEATURE2DRANGEFEATURE_H__48E846B4_EFB7_402A_A290_DB8B0237BB8D__INCLUDED_

#include <limits>

class CFeature2DRangeFeature  
{
public:
	CFeature2DRangeFeature();
	virtual ~CFeature2DRangeFeature();

	void CalculateRangeFeatureValue (double f0, double f45, double f90, double f135);
	double GetRangeFeatureValue (void) { return m_dblRangeFeatureValue; }

protected:

	double m_dblRangeFeatureValue;

};

#endif 
