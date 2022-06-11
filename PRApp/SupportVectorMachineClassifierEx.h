#if !defined(AFX_SUPPORTVECTORMACHINECLASSIFIEREX_H__533CED1E_7FFD_4BA5_A1D8_04F2C78CFBDC__INCLUDED_)
#define AFX_SUPPORTVECTORMACHINECLASSIFIEREX_H__533CED1E_7FFD_4BA5_A1D8_04F2C78CFBDC__INCLUDED_

#include "DataSet.h"
#include "Classifier.h"
#include "LibSupportVectorMachine.h"

class CSupportVectorMachineClassifierEx : public CClassifier 
{
public:
	CSupportVectorMachineClassifierEx();
	CSupportVectorMachineClassifierEx(SVMINFO *svmi);
	virtual ~CSupportVectorMachineClassifierEx();

	void SetSupportVectorMachineInfo (SVMINFO *svmi);
	static void LabelDataSet (CDataSet *pDataSet);
	void Classify (CDataSet *pDataSet, CPattern *pUnknownPattern);

	void Classify (CDataSet *pDataSet, CDataSet *pUnknownPatterns);

protected:

	SVMINFO m_svmi;

};

#endif 
