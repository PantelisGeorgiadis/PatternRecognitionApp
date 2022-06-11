#include "stdafx.h"
#include <windows.h>
#include "PRLib.h"

int iNumberOfCombinations = 0;
int iCombinationCount = 0;
CTimeEstimate TimeEstimate;

void ExternalCrossValidationDesignCB (int iFold, CDataSet *pDesignDataset, CDataSet *pClassificationDataSet, CEvaluationResultContainer* pEvaluationResultContainer, ClassificationScheme cs, EVALUATIONINFO *pEvaluationInfo, SELECTIONINFO *pSelectionInfo){

	CEvaluationResultSort ers;
	CEvaluationResultContainer* pEvaluationResultContainerSorted;

	pEvaluationResultContainerSorted = pEvaluationResultContainer->CopyEvaluationResultContainer();
	ers.SortEvaluationResultContainerDescending(pEvaluationResultContainerSorted);

	printf("Fold: %d Internal (%d Features)", iFold,
		pEvaluationResultContainerSorted->GetEvaluationResult(0)->GetEvaluationResultCombination()->GetCombinationVectorSize()
		);
	CTrace::PrintTruthTableToConsole(pEvaluationResultContainerSorted->GetEvaluationResult(0)->GetEvaluationResultTruthTable(), "TT");
	printf("\n");

	delete pEvaluationResultContainerSorted;
	pEvaluationResultContainerSorted = NULL;

	CExternalCrossValidation::ExternalCrossValidationDesignCB(iFold, pDesignDataset, pClassificationDataSet, pEvaluationResultContainer, cs, pEvaluationInfo, pSelectionInfo);

}

void ExternalCrossValidationClassificationCB (int iFold, CDataSet *pDesignDataset, CDataSet *pClassificationDataSet, CEvaluationResultContainer* pEvaluationResultContainer, ClassificationScheme cs, EVALUATIONINFO *pEvaluationInfo, SELECTIONINFO *pSelectionInfo){


	printf("Fold: %d External", iFold);
	CTrace::PrintTruthTableToConsole(pClassificationDataSet->GetTruthTable(), "TT");
	printf("\n");

}
 
int main(int argc, char* argv[])
{

 	CDataSet *DataSet = new CDataSet();
 	CDataSet *DataSetNormalized = NULL;
	CDataSet *DataSetNormalizedShuffled = NULL;

 
 	iNumberOfCombinations = 0;
 	iCombinationCount = 0;
 
 	printf("\nLoading Data ...");
 
	DataSet->AddClassFromFile("C:\\Meningiomas2.txt");
	DataSet->AddClassFromFile("C:\\Secondary2.txt");

 	printf("\nData Loaded...");
 	printf("\n");

	DataSetNormalized = DataSet->NormalizeDataSet();
	
	printf("\nData Normalized...");
	printf("\n");

	CShuffleDataSet *ShuffleDataSet = new CShuffleDataSet();
	DataSetNormalizedShuffled = ShuffleDataSet->ShuffleDataSet(DataSetNormalized, 100);
	delete ShuffleDataSet;
	ShuffleDataSet = NULL;

	printf("\nData Shuffled...");
	printf("\n");

	ClassificationScheme cs;
	EVALUATIONINFO EvaluationInfo;
	SELECTIONINFO SelectionInfo;

	cs = CLASSIFIER_SUPPORTVECTORMACHINEEX;

	EvaluationInfo.svminfo.dblTolerance = 0.001;//1e-3;
	EvaluationInfo.svminfo.dblCostEx = 10;
	EvaluationInfo.svminfo.svmkt = SVMKERNELTYPE_RBF;
	EvaluationInfo.svminfo.iPolynomialDegree = 2; 
	EvaluationInfo.svminfo.dblGammaEx = 0.1;
	EvaluationInfo.svminfo.dblCoef0Ex = 0.2;
	
	SelectionInfo.fsm = FEATURESELECTION_EXCHAUSTIVESEARCH;
	SelectionInfo.iNFromFeatureCombinations = 1;
	SelectionInfo.iNToFeatureCombinations = 2;

	EvaluationInfo.dblSmoothingFactor = 0.3f;
	EvaluationInfo.em = EVALUATIONMETHOD_LEAVEONEOUT;
	
	CExternalCrossValidation *ecv = new CExternalCrossValidation(ExternalCrossValidationDesignCB, ExternalCrossValidationClassificationCB);
	ecv->ExternalCrossValidation(DataSetNormalizedShuffled, 3, cs, &EvaluationInfo, &SelectionInfo);
	delete ecv;
	ecv = NULL;
	
	delete DataSetNormalizedShuffled;
	DataSetNormalizedShuffled = NULL;
	delete DataSetNormalized;
	DataSetNormalized = NULL;
	delete DataSet;
	DataSet = NULL;

	printf("\n");

	return 0;

}

