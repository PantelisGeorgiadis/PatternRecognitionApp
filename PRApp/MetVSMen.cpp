#include "stdafx.h"
#include <windows.h>
#include "PRLib.h"

int iNumberOfCombinations = 0;
int iCombinationCount = 0;
CTimeEstimate TimeEstimate;

void LeaveOneOut (void);

void ExhaustiveSearchCB (CCombination* pCombination, CDataSet* pDataSet, CEvaluationResultContainer *pEvaluationResultContainer){

	CLeaveOneOut loo;
	loo.LeaveOneOutProbabilisticNeuralNetworkGaussian(pDataSet, 0.3f);
	
// 	pEvaluationResultContainer->AddEvaluationResult(
// 		pDataSet->GetTruthTable()->GetOverallAccuracyPercent(),
// 		pCombination,
// 		pDataSet->GetTruthTable()
// 		);


	CTraceToFile::AppendExchaustiveSearchCombinationToFile("Results.txt", pCombination, pDataSet);

	iCombinationCount++;
	TimeEstimate.OffsetProcessPosition(1);
	
	char szEstimateTime[50];
	memset(szEstimateTime, 0, 50 * sizeof(char));
	TimeEstimate.GetProcessEstimatedTime(szEstimateTime);

	printf("Running Combination %d of %d (%.2lf%%), Remaining Time: %s\r", iCombinationCount, iNumberOfCombinations, (double)((double)(iCombinationCount) * 100.0f / (double)(iNumberOfCombinations)), szEstimateTime);

}

 
int main(int argc, char* argv[])
{

	CPerformanceTimer p(true);
 	LeaveOneOut();

	printf("\n\nElapsed Seconds: %0.4f\n\n",p.Elapsed());

	return 0;

}

void LeaveOneOut (void){

	CDataSet *DataSet = new CDataSet();
 	CDataSet *DataSetNormalized = NULL;
//	CEvaluationResultContainer *EvaluationResultContainer = new CEvaluationResultContainer();
 
 	iNumberOfCombinations = 0;
 	iCombinationCount = 0;
 
 	printf("\nLoading Data ...");
 
	DataSet->AddClassFromFile("Post-Radiation.FattyConversion.T1.txt");
	DataSet->AddClassFromFile("Post-Radiation.Oedema.T1.txt");
	
 	printf("\nData Loaded...");
 	printf("\n");

	DataSetNormalized = DataSet->NormalizeDataSet();
	
	printf("\nData Normalized...");
	printf("\n");

	for (int i=1;i<6;i++){
		iCombinationCount = 0;
		CExhaustiveSearch *ExhaustiveSearch = new CExhaustiveSearch(DataSetNormalized->GetClass(0)->GetNumberOfFeaturesPerPattern(), i, ExhaustiveSearchCB);
		iNumberOfCombinations = ExhaustiveSearch->GetNumberOfCombinations();
		TimeEstimate.SetProcessSize(iNumberOfCombinations);
		TimeEstimate.StartProcess();
		ExhaustiveSearch->ExhaustiveSearch(DataSetNormalized, /*EvaluationResultContainer*/NULL);
		TimeEstimate.StopProcess();
		printf("\n");
		delete ExhaustiveSearch;
		ExhaustiveSearch = NULL;
	}

	printf("\nWriting Excel File...");
 	printf("\n");
//	EvaluationResultContainer->WriteEvaluationResultContainerToExcelFile("Results.xls");
	
// 	delete EvaluationResultContainer;
// 	EvaluationResultContainer = NULL;
	delete DataSetNormalized;
	DataSetNormalized = NULL;
	delete DataSet;
	DataSet = NULL;

	printf("\nDone !!!");
 	printf("\n");
	
}
