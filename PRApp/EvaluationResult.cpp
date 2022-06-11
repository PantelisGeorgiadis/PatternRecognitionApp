#include "stdafx.h"
#include "EvaluationResult.h"

CEvaluationResult::CEvaluationResult()
{

	m_dblAccuracy = 0.0f;
	m_pCombination = NULL;
	m_pTruthTable = NULL;
	
}

CEvaluationResult::CEvaluationResult(double dblAccuracy, CCombination *pCombination, CTruthTable *pTruthTable)
{

	CreateEvaluationResult(dblAccuracy, pCombination, pTruthTable);	

}

CEvaluationResult::~CEvaluationResult()
{

	DeleteEvaluationResult();

}

void CEvaluationResult::CreateEvaluationResult(double dblAccuracy, CCombination *pCombination, CTruthTable *pTruthTable){

	m_dblAccuracy = dblAccuracy;
	m_pCombination = NULL;
	m_pTruthTable = NULL;

	int i, j;

	m_pCombination = new CCombination(pCombination->GetCombinationVectorSize());
	for (i=0;i<pCombination->GetCombinationVectorSize();i++){
		m_pCombination->SetCombinationVectorValue(i, pCombination->GetCombinationVectorValue(i));
	}

	m_pTruthTable = new CTruthTable(pTruthTable->GetNumberOfClasses());
	for (i=0;i<pTruthTable->GetNumberOfClasses();i++){
		for (j=0;j<pTruthTable->GetNumberOfClasses();j++){
			m_pTruthTable->SetTruthTableValue(i, j, pTruthTable->GetTruthTableValue(i, j));
		}
	}

}

CEvaluationResult *CEvaluationResult::CopyEvaluationResult (void){

	CEvaluationResult *EvaluationResult = new CEvaluationResult();
	EvaluationResult->CreateEvaluationResult(GetEvaluationResultAccuracy(), GetEvaluationResultCombination(), GetEvaluationResultTruthTable());
	
	return EvaluationResult;

}

void CEvaluationResult::DeleteEvaluationResult(void){

	if (m_pCombination != NULL){
		delete m_pCombination;
		m_pCombination = NULL;
	}

	if (m_pTruthTable != NULL){
		delete m_pTruthTable;
		m_pTruthTable = NULL;
	}

}
