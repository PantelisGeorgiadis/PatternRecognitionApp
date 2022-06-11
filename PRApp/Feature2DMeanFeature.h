#if !defined(AFX_FEATURE2DMEANFEATURE_H__87738277_EDF4_4DEF_86CD_C0DF79D54341__INCLUDED_)
#define AFX_FEATURE2DMEANFEATURE_H__87738277_EDF4_4DEF_86CD_C0DF79D54341__INCLUDED_

class CFeature2DMeanFeature  
{
public:
	CFeature2DMeanFeature();
	virtual ~CFeature2DMeanFeature();

	void CalculateMeanFeatureValue (double f0, double f45, double f90, double f135);
	double GetMeanFeatureValue (void) { return m_dblMeanFeatureValue; }

protected:

	double m_dblMeanFeatureValue;

};

#endif 
