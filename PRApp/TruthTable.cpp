#include "stdafx.h"
#include "TruthTable.h"

CTruthTable::CTruthTable()
{

	m_iNumberOfClasses = 0;
	m_iTruthTable = NULL;

}

CTruthTable::CTruthTable(int iNumberOfClasses)
{

	CreateTruthTable(iNumberOfClasses);

}

CTruthTable::~CTruthTable()
{

	DeleteTruthTable();

}

void CTruthTable::CreateTruthTable (int iNumberOfClasses){

	m_iNumberOfClasses = iNumberOfClasses;

	if (iNumberOfClasses > 0){
		m_iTruthTable = new int [iNumberOfClasses * iNumberOfClasses];
	}

	ResetTruthTable();

}

void CTruthTable::ResetTruthTable (void){

	for (int i=0;i<(GetNumberOfClasses() * GetNumberOfClasses());i++){
		m_iTruthTable[i] = 0;
	}

}

void CTruthTable::DeleteTruthTable (void){

	if (m_iTruthTable){
		delete [] m_iTruthTable;
		m_iTruthTable = NULL;
	}

}

int CTruthTable::GetTruthTableValue (int iClassBelongingIndex, int iClassClassifiedIndex){

	if ((iClassBelongingIndex > GetNumberOfClasses()) || (iClassClassifiedIndex > GetNumberOfClasses())){
		return 0;
	}

	return m_iTruthTable[(iClassBelongingIndex * GetNumberOfClasses()) + iClassClassifiedIndex];

}

void CTruthTable::SetTruthTableValue (int iClassBelongingIndex, int iClassClassifiedIndex, int iValue){

	if ((iClassBelongingIndex > GetNumberOfClasses()) || (iClassClassifiedIndex > GetNumberOfClasses())){
		return;
	}

	m_iTruthTable[(iClassBelongingIndex * GetNumberOfClasses()) + iClassClassifiedIndex] = iValue;

}

CTruthTable *CTruthTable::CopyTruthTable (void){

	CTruthTable *CoppiedTruthTable = new CTruthTable(GetNumberOfClasses());

	for (int i=0;i<GetNumberOfClasses();i++){
		for (int j=0;j<GetNumberOfClasses();j++){
			CoppiedTruthTable->SetTruthTableValue(i, j, GetTruthTableValue(i, j));
		}
	}

	return CoppiedTruthTable;

}

void CTruthTable::CopyTruthTable (CTruthTable *pTruthTableDest, CTruthTable *pTruthTableSrc){

	if (pTruthTableDest->GetNumberOfClasses() != pTruthTableSrc->GetNumberOfClasses()){
		return;
	}

	for (int i=0;i<pTruthTableDest->GetNumberOfClasses();i++){
		for (int j=0;j<pTruthTableSrc->GetNumberOfClasses();j++){
			pTruthTableDest->SetTruthTableValue(i, j, pTruthTableSrc->GetTruthTableValue(i, j));
		}
	}

}

double CTruthTable::GetOverallAccuracyPercent (void){
	
	double dblCorrectlyClassifiedSum = 0.0f;
	double dblClassifiedSum = 0.0f;
	double dblOverallAccuracyPercent = 0.0f;

	for (int i=0;i<GetNumberOfClasses();i++){
		for (int j=0;j<GetNumberOfClasses();j++){
			if (i == j){
				dblCorrectlyClassifiedSum = dblCorrectlyClassifiedSum + GetTruthTableValue(i, j);
			}
			dblClassifiedSum = dblClassifiedSum + GetTruthTableValue(i, j);
		}
	}

	if (dblClassifiedSum == 0.0f){
		return 0.0f;
	}

	dblOverallAccuracyPercent = ((100.0f * dblCorrectlyClassifiedSum) / dblClassifiedSum);

	return dblOverallAccuracyPercent;

}

void CTruthTable::WriteTruthTableToFile (char *szFileName){

	FILE *fp;
	int i, j;

	fp = fopen(szFileName, "w");
	if (fp == NULL){
		return;
	}

	for (i=0;i<GetNumberOfClasses();i++){
		fprintf(fp, "\tClass %d", i + 1); 
	}
	
	fprintf(fp, "\n");
	
	for (i=0;i<GetNumberOfClasses();i++){
		fprintf(fp, "Class %d", (i + 1));
		for (j=0;j<GetNumberOfClasses();j++){
			fprintf(fp, "\t%d", GetTruthTableValue(i, j));
		}
		fprintf(fp, "\n");
	}

	fprintf(fp, "\n\nOverall Accuracy: %.4lf", GetOverallAccuracyPercent());
		
	fclose(fp);

}
