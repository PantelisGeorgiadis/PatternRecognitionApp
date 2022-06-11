#include "stdafx.h"
#include "TraceToFile.h"

CTraceToFile::CTraceToFile()
{

}

CTraceToFile::~CTraceToFile()
{

}

void CTraceToFile::AppendStringToFile (char *szFileName, char *szString){

	FILE *fp = fopen(szFileName, "a");
	if (fp == NULL){
		return;
	}

	fwrite("\n", strlen("\n"), 1, fp);
	fwrite(szString, strlen(szString), 1, fp);
	fwrite("\n", strlen("\n"), 1, fp);

	fclose(fp);

}

void CTraceToFile::AppendExchaustiveSearchCombinationToFile (char *szFileName, CCombination* pCombination, CDataSet* pDataSet){

	int i, j, k;
	char szConsoleOut[256];

	FILE *fp = fopen(szFileName, "a");
	if (fp == NULL){
		return;
	}

	memset(szConsoleOut, 0, 256 * sizeof(char));
	sprintf(szConsoleOut, "%lf", pDataSet->GetTruthTable()->GetOverallAccuracyPercent());

	fwrite(szConsoleOut, strlen(szConsoleOut), 1, fp);
	fwrite("\t", strlen("\t"), 1, fp);

	for (i=0;i<pCombination->GetCombinationVectorSize();i++){
		memset(szConsoleOut, 0, 256 * sizeof(char));
		sprintf(szConsoleOut, "Feature: (%d)\t", pCombination->GetCombinationVectorValue(i));
		fwrite(szConsoleOut, strlen(szConsoleOut), 1, fp);
		
	}

	fwrite("TT:", strlen("TT:"), 1, fp);

	for (j=0;j<pDataSet->GetNumberOfClasses();j++){
		for (k=0;k<pDataSet->GetNumberOfClasses();k++){
			memset(szConsoleOut, 0, 256 * sizeof(char));
			sprintf(szConsoleOut, " %d%d:%d", j, k, pDataSet->GetTruthTable()->GetTruthTableValue(j, k));
			fwrite(szConsoleOut, strlen(szConsoleOut), 1, fp);
		}
	}

	fwrite("\n", strlen("\n"), 1, fp);

	fclose(fp);
	
}

void CTraceToFile::WriteExchaustiveSearchCombinationToFile (char *szFileName, CCombination* pCombination, CDataSet* pDataSet){

	int i, j, k;
	char szConsoleOut[256];

	FILE *fp = fopen(szFileName, "w");
	if (fp == NULL){
		return;
	}

	memset(szConsoleOut, 0, 256 * sizeof(char));
	sprintf(szConsoleOut, "%lf", pDataSet->GetTruthTable()->GetOverallAccuracyPercent());

	fwrite(szConsoleOut, strlen(szConsoleOut), 1, fp);
	fwrite("\t", strlen("\t"), 1, fp);

	for (i=0;i<pCombination->GetCombinationVectorSize();i++){
		memset(szConsoleOut, 0, 256 * sizeof(char));
		sprintf(szConsoleOut, "Feature: (%d)\t", pCombination->GetCombinationVectorValue(i));
		fwrite(szConsoleOut, strlen(szConsoleOut), 1, fp);
		
	}

	fwrite("TT:", strlen("TT:"), 1, fp);

	for (j=0;j<pDataSet->GetNumberOfClasses();j++){
		for (k=0;k<pDataSet->GetNumberOfClasses();k++){
			memset(szConsoleOut, 0, 256 * sizeof(char));
			sprintf(szConsoleOut, " %d%d:%d", j, k, pDataSet->GetTruthTable()->GetTruthTableValue(j, k));
			fwrite(szConsoleOut, strlen(szConsoleOut), 1, fp);
		}
	}

	fwrite("\n", strlen("\n"), 1, fp);

	fclose(fp);
	
}
