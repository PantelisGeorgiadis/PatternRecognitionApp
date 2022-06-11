#if !defined(AFX_DISCRIMINANTFUNCTION_H__0E9D48E5_E06B_43C5_9FB9_38F8E34DF4E5__INCLUDED_)
#define AFX_DISCRIMINANTFUNCTION_H__0E9D48E5_E06B_43C5_9FB9_38F8E34DF4E5__INCLUDED_

class CDiscriminantFunction  
{
public:
	CDiscriminantFunction();
	virtual ~CDiscriminantFunction();
	
	void SetDiscriminantFunctionValue (double dblDiscriminantFunctionValue) { m_dblDiscriminantFunctionValue = dblDiscriminantFunctionValue; }
	double GetDiscriminantFunctionValue (void) { return m_dblDiscriminantFunctionValue; }

protected:

	double m_dblDiscriminantFunctionValue;

};

#endif 
