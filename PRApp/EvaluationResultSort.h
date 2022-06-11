#if !defined(AFX_EVALUATIONRESULTSORT_H__F0143032_482E_4C48_8B17_C15D2A72C68B__INCLUDED_)
#define AFX_EVALUATIONRESULTSORT_H__F0143032_482E_4C48_8B17_C15D2A72C68B__INCLUDED_

#include "EvaluationResultContainer.h"

class CEvaluationResultSort  
{
public:
	CEvaluationResultSort();
	virtual ~CEvaluationResultSort();

	// Sort based on overall accuracy
	void SortEvaluationResultContainerAscending (CEvaluationResultContainer *pEvaluationResultContainer);
	void SortEvaluationResultContainerDescending (CEvaluationResultContainer *pEvaluationResultContainer);

};

#endif 
