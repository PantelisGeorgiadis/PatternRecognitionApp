#include "stdafx.h"
#include "Trace.h"
#include "ROIToPattern.h"

#ifdef MSC_IDE
#include <windows.h>
#endif

CTrace::CTrace()
{

}

CTrace::~CTrace()
{

}

void CTrace::PrintCombinationToConsole (CCombination *pCombination, char *szDescription){

	int i;
	char szConsoleOut[256];

#ifdef MSC_IDE
	OutputDebugString("\n");
	OutputDebugString(szDescription);
	OutputDebugString("\n");
	OutputDebugString("Combination: ");
#else
	printf("\n");
	printf(szDescription);
	printf("\n");
	printf("Combination: ");
#endif

	for (i=0;i<pCombination->GetCombinationVectorSize();i++){
		sprintf(szConsoleOut, "%d ", pCombination->GetCombinationVectorValue(i));
#ifdef MSC_IDE
		OutputDebugString(szConsoleOut);
#else
		printf(szConsoleOut);
#endif
	}

}

void CTrace::PrintDataMatrix1DToConsole (CDataMatrix1D *pDataMatrix1D, char *szDescription){

	int i;
	char szConsoleOut[256];

#ifdef MSC_IDE
	OutputDebugString("\n");
	OutputDebugString(szDescription);
	OutputDebugString("\n");
#else
	printf("\n");
	printf(szDescription);
	printf("\n");
#endif

	
	for (i=0;i<pDataMatrix1D->GetNumberOfColumns();i++){
		sprintf(szConsoleOut, "%lf ", pDataMatrix1D->GetMatrixValue(i));
#ifdef MSC_IDE
		OutputDebugString(szConsoleOut);
#else
		printf(szConsoleOut);
#endif
	}
#ifdef MSC_IDE
	OutputDebugString("\n");
#else
	printf("\n");
#endif
	

}

void CTrace::PrintDataMatrix2DToConsole (CDataMatrix2D *pDataMatrix2D, char *szDescription){

	int i, j;
	char szConsoleOut[256];

#ifdef MSC_IDE
	OutputDebugString("\n");
	OutputDebugString(szDescription);
	OutputDebugString("\n");
#else
	printf("\n");
	printf(szDescription);
	printf("\n");
#endif

	for (i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		for (j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			sprintf(szConsoleOut, "%lf ", pDataMatrix2D->GetMatrixValue(i, j));
#ifdef MSC_IDE
			OutputDebugString(szConsoleOut);
#else
			printf(szConsoleOut);
#endif
		}
#ifdef MSC_IDE
		OutputDebugString("\n");
#else
		printf("\n");
#endif
	}

}

void CTrace::PrintClassToConsole (CClass *pClass, char *szDescription){

	int i, j;
	char szConsoleOut[256];

#ifdef MSC_IDE
	OutputDebugString("\n");
	OutputDebugString(szDescription);
	OutputDebugString("\n");
#else
	printf("\n");
	printf(szDescription);
	printf("\n");
#endif

	for (i=0;i<pClass->GetNumberOfPatterns();i++){
		sprintf(szConsoleOut, "Pattern: %d --> ",  i + 1);
#ifdef MSC_IDE
		OutputDebugString(szConsoleOut);
#else
		printf(szConsoleOut);
#endif
		for (j=0;j<pClass->GetNumberOfFeaturesPerPattern();j++){
			sprintf(szConsoleOut, "f%d: %.6lf ", j + 1, pClass->GetPattern(i)->GetFeature(j)->GetFeatureValue());
#ifdef MSC_IDE
			OutputDebugString(szConsoleOut);
#else
			printf(szConsoleOut);
#endif
		}
		sprintf(szConsoleOut, "Reserved: %d ", pClass->GetPattern(i)->GetReservedValue());
#ifdef MSC_IDE
		OutputDebugString(szConsoleOut);
		OutputDebugString("\n");
#else
		printf(szConsoleOut);
		printf("\n");
#endif

	}

}

void CTrace::PrintPatternToConsole (CPattern *pPattern, char *szDescription){

	int i;
	char szConsoleOut[256];

#ifdef MSC_IDE
	OutputDebugString("\n");
	OutputDebugString(szDescription);
	OutputDebugString("\n");
#else
	printf("\n");
	printf(szDescription);
	printf("\n");
#endif

	for (i=0;i<pPattern->GetNumberOfFeatures();i++){
		sprintf(szConsoleOut, "f%d: %.6lf ", i + 1, pPattern->GetFeature(i)->GetFeatureValue());
#ifdef MSC_IDE
		OutputDebugString(szConsoleOut);
#else
		printf(szConsoleOut);
#endif
	}

}

void CTrace::PrintTruthTableToConsole (CTruthTable *pTruthTable, char *szDescription){

	int i, j;
	char szConsoleOut[256];

#ifdef MSC_IDE
	OutputDebugString("\n");
	OutputDebugString(szDescription);
	OutputDebugString("\n");
#else
	printf("\n");
	printf(szDescription);
	printf("\n");
#endif

	for (i=0;i<pTruthTable->GetNumberOfClasses();i++){
		sprintf(szConsoleOut, "\tClass %d",  i + 1);
#ifdef MSC_IDE
		OutputDebugString(szConsoleOut);
#else
		printf(szConsoleOut);
#endif
	}

#ifdef MSC_IDE
		OutputDebugString("\n");
#else
		printf("\n");
#endif

	for (i=0;i<pTruthTable->GetNumberOfClasses();i++){
		sprintf(szConsoleOut, "Class %d",  i + 1);
#ifdef MSC_IDE
		OutputDebugString(szConsoleOut);
#else
		printf(szConsoleOut);
#endif
		for (j=0;j<pTruthTable->GetNumberOfClasses();j++){
			sprintf(szConsoleOut, "\t%d",  pTruthTable->GetTruthTableValue(i, j));
#ifdef MSC_IDE
			OutputDebugString(szConsoleOut);
#else
			printf(szConsoleOut);
#endif
		}
#ifdef MSC_IDE
		OutputDebugString("\n");
#else
		printf("\n");
#endif
	}

	sprintf(szConsoleOut, "\nOverall Accuracy: %.4lf", pTruthTable->GetOverallAccuracyPercent());

#ifdef MSC_IDE
			OutputDebugString(szConsoleOut);
			OutputDebugString("\n");
#else
			printf(szConsoleOut);
			printf("\n");
#endif

}

void CTrace::PrintExchaustiveSearchCombinationToConsole (CCombination* pCombination, CDataSet* pDataSet){

	int i, j, k;
	char szConsoleOut[256];

	memset(szConsoleOut, 0, 256 * sizeof(char));
	sprintf(szConsoleOut, "%lf", pDataSet->GetTruthTable()->GetOverallAccuracyPercent());
	
#ifdef MSC_IDE
	OutputDebugString(szConsoleOut);
	OutputDebugString("\t");
#else
	printf(szConsoleOut);
	printf("\t");
#endif

	for (i=0;i<pCombination->GetCombinationVectorSize();i++){
		memset(szConsoleOut, 0, 256 * sizeof(char));
		sprintf(szConsoleOut, "Feature: (%d)", pCombination->GetCombinationVectorValue(i));
#ifdef MSC_IDE
		OutputDebugString(szConsoleOut);
		OutputDebugString("\tTT:");
#else
		printf(szConsoleOut);
		printf("\tTT:");
#endif

		for (j=0;j<pDataSet->GetNumberOfClasses();j++){
			for (k=0;k<pDataSet->GetNumberOfClasses();k++){
				memset(szConsoleOut, 0, 256 * sizeof(char));
				sprintf(szConsoleOut, " %d%d:%d", j, k, pDataSet->GetTruthTable()->GetTruthTableValue(j, k));
#ifdef MSC_IDE
				OutputDebugString(szConsoleOut);
#else
				printf(szConsoleOut);
#endif
			}
		}
	}

#ifdef MSC_IDE
	OutputDebugString("\n");
#else
	printf("\n");
#endif
	
}
