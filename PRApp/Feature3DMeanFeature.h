#if !defined(AFX_FEATURE3DMEANFEATURE_H__41F939CF_8762_452D_A88F_8064086D267A__INCLUDED_)
#define AFX_FEATURE3DMEANFEATURE_H__41F939CF_8762_452D_A88F_8064086D267A__INCLUDED_

class CFeature3DMeanFeature  
{
public:
	CFeature3DMeanFeature();
	virtual ~CFeature3DMeanFeature();

	void CalculateMeanFeatureValue (double f0, double f1, double f2, double f3, double f4, double f5, double f6, double f7, double f8, double f9, double f10, double f11, double f12);
	double GetMeanFeatureValue (void) { return m_dblMeanFeatureValue; }

protected:

	double m_dblMeanFeatureValue;

};

#endif 
