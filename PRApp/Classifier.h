#if !defined(AFX_CLASSIFIER_H__BBFDA3C1_93B6_4E01_8427_11436E25DA51__INCLUDED_)
#define AFX_CLASSIFIER_H__BBFDA3C1_93B6_4E01_8427_11436E25DA51__INCLUDED_

class CClassifier  
{
public:
	CClassifier();
	virtual ~CClassifier();

	void SetClassifierOutput (int iClassifierOutput) { m_iClassifierOutput = iClassifierOutput; }
	int GetClassifierOutput (void) { return m_iClassifierOutput; }

protected:

	int m_iClassifierOutput;

};

#endif 
