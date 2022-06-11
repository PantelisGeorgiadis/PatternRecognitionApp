#if !defined(AFX_EVALUATIONRESULTCONTAINER_H__713A77F4_5C4B_44D6_A936_8180BF9F2132__INCLUDED_)
#define AFX_EVALUATIONRESULTCONTAINER_H__713A77F4_5C4B_44D6_A936_8180BF9F2132__INCLUDED_

#ifndef __GNUC__
#pragma warning(disable : 4786)
#endif

#include <vector>
#include <stdio.h>
#include "EvaluationResult.h"
#include "ExcelWriter.h"

typedef std::vector<CEvaluationResult*> vEvaluationResults;

class CEvaluationResultContainer  
{
public:
	CEvaluationResultContainer();
	virtual ~CEvaluationResultContainer();

	void AddEvaluationResult(double dblAccuracy, CCombination *pCombination, CTruthTable *pTruthTable);
	void AddEvaluationResult(CEvaluationResult *pEvaluationResult);
	void RemoveEvaluationResult (int iEvaluationResult);
	void RemoveAllEvaluationResults (void);
	CEvaluationResult *GetEvaluationResult (int iEvaluationResult);
	int GetNumberOfEvaluationResults(void) { return m_vEvaluationResults.size(); }
	CEvaluationResultContainer *CopyEvaluationResultContainer (void);
	void WriteEvaluationResultContainerToFile (char *szFileName);
	void WriteEvaluationResultContainerToExcelFile (char *szFileName);

protected:

	CEvaluationResult *m_EvaluationResult;
	vEvaluationResults m_vEvaluationResults;

};

#endif 
