#if !defined(AFX_EVALUATIONRESULT_H__BCC9FC4F_6B4E_4C00_93BC_3D575C234C90__INCLUDED_)
#define AFX_EVALUATIONRESULT_H__BCC9FC4F_6B4E_4C00_93BC_3D575C234C90__INCLUDED_

#include "Combination.h"
#include "TruthTable.h"

class CEvaluationResult  
{
public:
	CEvaluationResult();
	CEvaluationResult(double dblAccuracy, CCombination *pCombination, CTruthTable *pTruthTable);
	virtual ~CEvaluationResult();

	void CreateEvaluationResult(double dblAccuracy, CCombination *pCombination, CTruthTable *pTruthTable);
	CEvaluationResult *CopyEvaluationResult (void); 
	void DeleteEvaluationResult(void);
	
	void SetEvaluationResultAccuracy (double dblAccuracy) { m_dblAccuracy = dblAccuracy; }
	double GetEvaluationResultAccuracy (void) { return m_dblAccuracy; }
	
	void SetEvaluationResultCombination (CCombination *pCombination) { m_pCombination = pCombination; }
	CCombination *GetEvaluationResultCombination (void) { return m_pCombination; }

	void SetEvaluationResultTruthTable (CTruthTable *pTruthTable) { m_pTruthTable = pTruthTable; }
	CTruthTable *GetEvaluationResultTruthTable (void) { return m_pTruthTable; }

protected:

	double m_dblAccuracy;
	CCombination *m_pCombination;
	CTruthTable *m_pTruthTable;

};

#endif 
