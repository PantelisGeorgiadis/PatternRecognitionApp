#include "stdafx.h"
#include "EvaluationResultSort.h"

CEvaluationResultSort::CEvaluationResultSort()
{

}

CEvaluationResultSort::~CEvaluationResultSort()
{

}

void CEvaluationResultSort::SortEvaluationResultContainerAscending (CEvaluationResultContainer *pEvaluationResultContainer){

	double dblAccuracyTemp = 0.0f;
	CCombination *pCombinationTemp = NULL;
	CTruthTable *pTruthTableTemp = NULL;

	for (int i=0;i<(pEvaluationResultContainer->GetNumberOfEvaluationResults() - 1);i++){
		for (int j=(i + 1);j<pEvaluationResultContainer->GetNumberOfEvaluationResults();j++){
			if (pEvaluationResultContainer->GetEvaluationResult(i)->GetEvaluationResultAccuracy() > pEvaluationResultContainer->GetEvaluationResult(j)->GetEvaluationResultAccuracy()){
				dblAccuracyTemp = pEvaluationResultContainer->GetEvaluationResult(i)->GetEvaluationResultAccuracy();
				pCombinationTemp = pEvaluationResultContainer->GetEvaluationResult(i)->GetEvaluationResultCombination();
				pTruthTableTemp = pEvaluationResultContainer->GetEvaluationResult(i)->GetEvaluationResultTruthTable();
				pEvaluationResultContainer->GetEvaluationResult(i)->SetEvaluationResultAccuracy(pEvaluationResultContainer->GetEvaluationResult(j)->GetEvaluationResultAccuracy());
				pEvaluationResultContainer->GetEvaluationResult(i)->SetEvaluationResultCombination(pEvaluationResultContainer->GetEvaluationResult(j)->GetEvaluationResultCombination());
				pEvaluationResultContainer->GetEvaluationResult(i)->SetEvaluationResultTruthTable(pEvaluationResultContainer->GetEvaluationResult(j)->GetEvaluationResultTruthTable());
				pEvaluationResultContainer->GetEvaluationResult(j)->SetEvaluationResultAccuracy(dblAccuracyTemp);
				pEvaluationResultContainer->GetEvaluationResult(j)->SetEvaluationResultCombination(pCombinationTemp);
				pEvaluationResultContainer->GetEvaluationResult(j)->SetEvaluationResultTruthTable(pTruthTableTemp);
			}
		}
	}

}


void CEvaluationResultSort::SortEvaluationResultContainerDescending (CEvaluationResultContainer *pEvaluationResultContainer){

	double dblAccuracyTemp = 0.0f;
	CCombination *pCombinationTemp = NULL;
	CTruthTable *pTruthTableTemp = NULL;

	for (int i=0;i<(pEvaluationResultContainer->GetNumberOfEvaluationResults() - 1);i++){
		for (int j=(i + 1);j<pEvaluationResultContainer->GetNumberOfEvaluationResults();j++){
			if (pEvaluationResultContainer->GetEvaluationResult(i)->GetEvaluationResultAccuracy() < pEvaluationResultContainer->GetEvaluationResult(j)->GetEvaluationResultAccuracy()){
				dblAccuracyTemp = pEvaluationResultContainer->GetEvaluationResult(i)->GetEvaluationResultAccuracy();
				pCombinationTemp = pEvaluationResultContainer->GetEvaluationResult(i)->GetEvaluationResultCombination();
				pTruthTableTemp = pEvaluationResultContainer->GetEvaluationResult(i)->GetEvaluationResultTruthTable();
				pEvaluationResultContainer->GetEvaluationResult(i)->SetEvaluationResultAccuracy(pEvaluationResultContainer->GetEvaluationResult(j)->GetEvaluationResultAccuracy());
				pEvaluationResultContainer->GetEvaluationResult(i)->SetEvaluationResultCombination(pEvaluationResultContainer->GetEvaluationResult(j)->GetEvaluationResultCombination());
				pEvaluationResultContainer->GetEvaluationResult(i)->SetEvaluationResultTruthTable(pEvaluationResultContainer->GetEvaluationResult(j)->GetEvaluationResultTruthTable());
				pEvaluationResultContainer->GetEvaluationResult(j)->SetEvaluationResultAccuracy(dblAccuracyTemp);
				pEvaluationResultContainer->GetEvaluationResult(j)->SetEvaluationResultCombination(pCombinationTemp);
				pEvaluationResultContainer->GetEvaluationResult(j)->SetEvaluationResultTruthTable(pTruthTableTemp);
			}
		}
	}
	
}
