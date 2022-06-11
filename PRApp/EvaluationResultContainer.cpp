#include "stdafx.h"
#include "EvaluationResultContainer.h"

CEvaluationResultContainer::CEvaluationResultContainer()
{

	m_EvaluationResult = NULL;

}

CEvaluationResultContainer::~CEvaluationResultContainer()
{

	RemoveAllEvaluationResults();

}

void CEvaluationResultContainer::AddEvaluationResult(double dblAccuracy, CCombination *pCombination, CTruthTable *pTruthTable){

	m_EvaluationResult = NULL;
	
	m_EvaluationResult = new CEvaluationResult(dblAccuracy, pCombination, pTruthTable);
	m_vEvaluationResults.push_back(m_EvaluationResult);

}

void CEvaluationResultContainer::AddEvaluationResult(CEvaluationResult *pEvaluationResult){

	m_vEvaluationResults.push_back(pEvaluationResult);

}

CEvaluationResult *CEvaluationResultContainer::GetEvaluationResult (int iEvaluationResult){

	if (iEvaluationResult > GetNumberOfEvaluationResults()){
		return NULL;
	}

	return (CEvaluationResult *)m_vEvaluationResults[iEvaluationResult];

}

void CEvaluationResultContainer::RemoveEvaluationResult (int iEvaluationResult){

	CEvaluationResult *EvaluationResult = NULL;
	EvaluationResult = GetEvaluationResult(iEvaluationResult);
	EvaluationResult->DeleteEvaluationResult ();
	delete EvaluationResult;
	EvaluationResult = NULL;

	std::vector<CEvaluationResult*>::iterator it = m_vEvaluationResults.begin() + iEvaluationResult;
	m_vEvaluationResults.erase(it);

}

void CEvaluationResultContainer::RemoveAllEvaluationResults (void){

	CEvaluationResult *EvaluationResult = NULL;

	for (int i=0;i<GetNumberOfEvaluationResults();i++){
		EvaluationResult = GetEvaluationResult(i);
		EvaluationResult->DeleteEvaluationResult ();
		delete EvaluationResult;
		EvaluationResult = NULL;
	}

	if (!m_vEvaluationResults.empty()){
		m_vEvaluationResults.clear();
	}

}

CEvaluationResultContainer *CEvaluationResultContainer::CopyEvaluationResultContainer (void){

	CEvaluationResultContainer *CoppiedEvaluationResultContainer = new CEvaluationResultContainer();
	for (int i=0;i<GetNumberOfEvaluationResults();i++){
		CoppiedEvaluationResultContainer->AddEvaluationResult(GetEvaluationResult(i)->GetEvaluationResultAccuracy(), GetEvaluationResult(i)->GetEvaluationResultCombination(), GetEvaluationResult(i)->GetEvaluationResultTruthTable());
	}
	return CoppiedEvaluationResultContainer;

}

void CEvaluationResultContainer::WriteEvaluationResultContainerToFile (char *szFileName){

	FILE *fp;

	fp = fopen(szFileName, "w");
	if (fp == NULL){
		return;
	}

	CEvaluationResult *EvaluationResult = NULL;

	for (int i=0;i<GetNumberOfEvaluationResults();i++){
		EvaluationResult = GetEvaluationResult(i);
		fprintf(fp, "%.9lf\t", EvaluationResult->GetEvaluationResultAccuracy());
		for (int j=0;j<EvaluationResult->GetEvaluationResultCombination()->GetCombinationVectorSize();j++){
			fprintf(fp, "%d\t", EvaluationResult->GetEvaluationResultCombination()->GetCombinationVectorValue(j));
		}
		for (int k=0;k<EvaluationResult->GetEvaluationResultTruthTable()->GetNumberOfClasses();k++){
			for (int l=0;l<EvaluationResult->GetEvaluationResultTruthTable()->GetNumberOfClasses();l++){
				fprintf(fp, " %d%d:%d", k, l, EvaluationResult->GetEvaluationResultTruthTable()->GetTruthTableValue(k, l));
			}
		}
		fprintf(fp, "\n");
	}

	fclose(fp);

}

void CEvaluationResultContainer::WriteEvaluationResultContainerToExcelFile (char *szFileName){

	
	CExcelWriter ExcelWriter;
	int iColumnIndexHelper = 0;
	char szTruthTable[255];
	char szTruthTableHelper[255];

	memset(szTruthTable, 0, 255 * sizeof(char));
	memset(szTruthTableHelper, 0, 255 * sizeof(char));

	CEvaluationResult *EvaluationResult = NULL;

	for (int i=0;i<GetNumberOfEvaluationResults();i++){
		iColumnIndexHelper = 0;
		
		EvaluationResult = GetEvaluationResult(i);
		ExcelWriter(i, iColumnIndexHelper) = EvaluationResult->GetEvaluationResultAccuracy();
		iColumnIndexHelper++;
		
		for (int j=0;j<EvaluationResult->GetEvaluationResultCombination()->GetCombinationVectorSize();j++){
			ExcelWriter(i, iColumnIndexHelper) = EvaluationResult->GetEvaluationResultCombination()->GetCombinationVectorValue(j);
			iColumnIndexHelper++;
		}

		strcpy(szTruthTable, "");

		for (int k=0;k<EvaluationResult->GetEvaluationResultTruthTable()->GetNumberOfClasses();k++){
			for (int l=0;l<EvaluationResult->GetEvaluationResultTruthTable()->GetNumberOfClasses();l++){
				sprintf(szTruthTableHelper, " %d%d:%d", k, l, EvaluationResult->GetEvaluationResultTruthTable()->GetTruthTableValue(k, l));
				strcat(szTruthTable, szTruthTableHelper);
			}
		}

		ExcelWriter(i, iColumnIndexHelper) = szTruthTable;
		
	}

	ExcelWriter.SaveAs(szFileName);

}
