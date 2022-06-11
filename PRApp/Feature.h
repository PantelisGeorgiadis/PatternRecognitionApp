#if !defined(AFX_FEATURE_H__EE608584_9C02_40A5_8D63_8613F7E7C1F0__INCLUDED_)
#define AFX_FEATURE_H__EE608584_9C02_40A5_8D63_8613F7E7C1F0__INCLUDED_

class CFeature  
{
public:
	CFeature();
	virtual ~CFeature();

	void SetFeatureValue (double dbValue) { m_dbFeatureValue = dbValue; }
	double GetFeatureValue (void) { return m_dbFeatureValue; }

protected:

	double m_dbFeatureValue;

};

#endif 

