#include "stdafx.h"
#include "ExternalCrossValidation.h"

CExternalCrossValidation *pExternalCrossValidation = NULL;

CExternalCrossValidation::CExternalCrossValidation()
{

	m_cs = CLASSIFIER_NONE;
	memset(&m_EvaluationInfo, 0, sizeof(EVALUATIONINFO));
	memset(&m_SelectionInfo, 0, sizeof(SELECTIONINFO));
	m_EvaluationResultContainer = NULL;

	SetExternalCrossValidationDesignCallBackFunction(CExternalCrossValidation::ExternalCrossValidationDesignCB);
	m_pExternalCrossValidationClassificationCallBack = NULL;

}

CExternalCrossValidation::CExternalCrossValidation(ExternalCrossValidationDesignCallBack pExternalCrossValidationDesignCallBack, ExternalCrossValidationClassificationCallBack pExternalCrossValidationClassificationCallBack)
{

	m_cs = CLASSIFIER_NONE;
	memset(&m_EvaluationInfo, 0, sizeof(EVALUATIONINFO));
	memset(&m_SelectionInfo, 0, sizeof(SELECTIONINFO));
	m_EvaluationResultContainer = NULL;
	
	SetExternalCrossValidationDesignCallBackFunction(pExternalCrossValidationDesignCallBack);
	SetExternalCrossValidationClassificationCallBackFunction(pExternalCrossValidationClassificationCallBack);

}

CExternalCrossValidation::~CExternalCrossValidation()
{

}

/*
CALLBACK EXAMPLE

void ExternalCrossValidationDesignCB (int iFold, CDataSet *pDesignDataset, CDataSet *pClassificationDataSet, CEvaluationResultContainer* pEvaluationResultContainer, ClassificationScheme cs, EVALUATIONINFO *pEvaluationInfo, SELECTIONINFO *pSelectionInfo){


}

void ExternalCrossValidationClassificationCB (int iFold, CDataSet *pDesignDataset, CDataSet *pClassificationDataSet, CEvaluationResultContainer* pEvaluationResultContainer, ClassificationScheme cs, EVALUATIONINFO *pEvaluationInfo, SELECTIONINFO *pSelectionInfo){


}

*/

void CExternalCrossValidation::ExternalCrossValidation(CDataSet *pDataSet, int iNumberOfFolds, ClassificationScheme cs, EVALUATIONINFO *pEvaluationInfo, SELECTIONINFO *pSelectionInfo){

	if ((iNumberOfFolds == 0) || (iNumberOfFolds == 1)){
		return;
	}

	m_cs = cs;
	memcpy(&m_EvaluationInfo, pEvaluationInfo, sizeof(EVALUATIONINFO));
	memcpy(&m_SelectionInfo, pSelectionInfo, sizeof(SELECTIONINFO));

	pExternalCrossValidation = this;

	int i, j, k;
	int iClassClassificationFeatures = 0;
	int *iClassificationPatternIndexes = NULL;
	CClass *ExtractedClass = NULL;
	CDataSet *ClassificationDataSet = NULL;
	CDataSet *DesignDataset = NULL;

	pDataSet->GetTruthTable()->ResetTruthTable();

	for (k=0;k<iNumberOfFolds;k++){
		
		ClassificationDataSet = new CDataSet();
		DesignDataset = pDataSet->CopyDataSet();
		m_EvaluationResultContainer = new CEvaluationResultContainer();

		for (i=0;i<pDataSet->GetNumberOfClasses();i++){
			iClassClassificationFeatures = pDataSet->GetClass(i)->GetNumberOfPatterns() / iNumberOfFolds;

			iClassificationPatternIndexes = new int [iClassClassificationFeatures];
			for (j=0;j<iClassClassificationFeatures;j++){
				iClassificationPatternIndexes[j] = ((k * iClassClassificationFeatures) + j);
			}	

			ExtractedClass = DesignDataset->GetClass(i)->ExtractPatterns(iClassificationPatternIndexes, iClassClassificationFeatures);
			ClassificationDataSet->AddClass(ExtractedClass->CopyClass());
			
			delete ExtractedClass;
			ExtractedClass = NULL;
			delete [] iClassificationPatternIndexes;
			iClassificationPatternIndexes = NULL;
		}

		switch (pSelectionInfo->fsm){
			case FEATURESELECTION_EXCHAUSTIVESEARCH:
				ExternalCrossValidationExchaustiveSearch(DesignDataset, ClassificationDataSet, cs, pEvaluationInfo, pSelectionInfo);
				break;
		}

		if (m_pExternalCrossValidationDesignCallBack != NULL){
			m_pExternalCrossValidationDesignCallBack(k, DesignDataset, ClassificationDataSet, m_EvaluationResultContainer, cs, pEvaluationInfo, pSelectionInfo);
		}
		else{
			CExternalCrossValidation::ExternalCrossValidationDesignCB(k, DesignDataset, ClassificationDataSet, m_EvaluationResultContainer, cs, pEvaluationInfo, pSelectionInfo);
		}

		delete m_EvaluationResultContainer;
		m_EvaluationResultContainer = NULL;
		delete DesignDataset;
		DesignDataset = NULL;
		delete ClassificationDataSet;
		ClassificationDataSet = NULL;

	}

	delete DesignDataset;
	DesignDataset = NULL;
	delete ClassificationDataSet;
	ClassificationDataSet = NULL;

}

void CExternalCrossValidation::ExternalCrossValidationExchaustiveSearch(CDataSet *DesignDataSet, CDataSet *ClassificationDataSet, ClassificationScheme cs, EVALUATIONINFO *pEvaluationInfo, SELECTIONINFO *pSelectionInfo){

	CExhaustiveSearch *ExhaustiveSearch = NULL;

	for (int i=pSelectionInfo->iNFromFeatureCombinations;i<(pSelectionInfo->iNToFeatureCombinations + 1);i++){
		CExhaustiveSearch *ExhaustiveSearch = new CExhaustiveSearch(DesignDataSet->GetClass(0)->GetNumberOfFeaturesPerPattern(), i, CExternalCrossValidation::ExhaustiveSearchCB);
		ExhaustiveSearch->ExhaustiveSearch(DesignDataSet);
		delete ExhaustiveSearch;
		ExhaustiveSearch = NULL;
	}

}

void CExternalCrossValidation::ExhaustiveSearchCB (CCombination* pCombination, CDataSet* pDataSet, CEvaluationResultContainer *pEvaluationResultContainer){

	CSelfConsistency *SelfConsistency = NULL;
	CLeaveOneOut *LeaveOneOut = NULL;
	CKFold *KFold = NULL;

	switch (pExternalCrossValidation->GetEvaluationInfo()->em){
		case EVALUATIONMETHOD_SELFCONSISTENCY:
			SelfConsistency = new CSelfConsistency();
			
			switch (pExternalCrossValidation->GetClassificationScheme()){
				case CLASSIFIER_MINIMUMDISTANCE:
					SelfConsistency->SelfConsistencyMinimumDistance(pDataSet);
					break;
				case CLASSIFIER_KNN_AVERAGE:
					SelfConsistency->SelfConsistencyKNearestNeighborAverage(pDataSet, pExternalCrossValidation->GetEvaluationInfo()->iNumberOfNeighbors);
					break;
				case CLASSIFIER_KNN_MV:
					SelfConsistency->SelfConsistencyKNearestNeighborMajorityVote(pDataSet, pExternalCrossValidation->GetEvaluationInfo()->iNumberOfNeighbors);
					break;
				case CLASSIFIER_PNN_GAUSSIAN:
					SelfConsistency->SelfConsistencyProbabilisticNeuralNetworkGaussian(pDataSet, pExternalCrossValidation->GetEvaluationInfo()->dblSmoothingFactor);
					break;
				case CLASSIFIER_PNN_EXPONENTIAL:
					SelfConsistency->SelfConsistencyProbabilisticNeuralNetworkExponential(pDataSet, pExternalCrossValidation->GetEvaluationInfo()->dblSmoothingFactor);
					break;
				case CLASSIFIER_PNN_RECIPROCAL:
					SelfConsistency->SelfConsistencyProbabilisticNeuralNetworkReciprocal(pDataSet, pExternalCrossValidation->GetEvaluationInfo()->dblSmoothingFactor);
					break;
				case CLASSIFIER_BAYESIAN:
					SelfConsistency->SelfConsistencyBayesian(pDataSet);
					break;
				case CLASSIFIER_BAYESIAN_QUADRATIC:
					SelfConsistency->SelfConsistencyBayesianQuadratic(pDataSet);
					break;
				case CLASSIFIER_LEASTSQUARES_MINIMUMDISTANCE:
					SelfConsistency->SelfConsistencyLeastSquareMinimumDistance(pDataSet, pExternalCrossValidation->GetEvaluationInfo()->iOrder, 
																			   (CPattern*)pExternalCrossValidation->GetEvaluationInfo()->pClusteringPoints,
																			   pExternalCrossValidation->GetEvaluationInfo()->iNumberOfClusteringPoints);
					break;
				case CLASSIFIER_SUPPORTVECTORMACHINE:
					SelfConsistency->SelfConsistencySupportVectorMachine(pDataSet, &pExternalCrossValidation->GetEvaluationInfo()->svminfo);
					break;
				case CLASSIFIER_SUPPORTVECTORMACHINEEX:
					SelfConsistency->SelfConsistencySupportVectorMachineEx(pDataSet, &pExternalCrossValidation->GetEvaluationInfo()->svminfo);
					break;
			}
			
			delete SelfConsistency;
			SelfConsistency = NULL;
			break;
		case EVALUATIONMETHOD_LEAVEONEOUT:
			LeaveOneOut = new CLeaveOneOut();

			switch (pExternalCrossValidation->GetClassificationScheme()){
				case CLASSIFIER_MINIMUMDISTANCE:
					LeaveOneOut->LeaveOneOutMinimumDistance(pDataSet);
					break;
				case CLASSIFIER_KNN_AVERAGE:
					LeaveOneOut->LeaveOneOutKNearestNeighborAverage(pDataSet, pExternalCrossValidation->GetEvaluationInfo()->iNumberOfNeighbors);
					break;
				case CLASSIFIER_KNN_MV:
					LeaveOneOut->LeaveOneOutKNearestNeighborMajorityVote(pDataSet, pExternalCrossValidation->GetEvaluationInfo()->iNumberOfNeighbors);
					break;
				case CLASSIFIER_PNN_GAUSSIAN:
					LeaveOneOut->LeaveOneOutProbabilisticNeuralNetworkGaussian(pDataSet, pExternalCrossValidation->GetEvaluationInfo()->dblSmoothingFactor);
					break;
				case CLASSIFIER_PNN_EXPONENTIAL:
					LeaveOneOut->LeaveOneOutProbabilisticNeuralNetworkExponential(pDataSet, pExternalCrossValidation->GetEvaluationInfo()->dblSmoothingFactor);
					break;
				case CLASSIFIER_PNN_RECIPROCAL:
					LeaveOneOut->LeaveOneOutProbabilisticNeuralNetworkReciprocal(pDataSet, pExternalCrossValidation->GetEvaluationInfo()->dblSmoothingFactor);
					break;
				case CLASSIFIER_BAYESIAN:
					LeaveOneOut->LeaveOneOutBayesian(pDataSet);
					break;
				case CLASSIFIER_BAYESIAN_QUADRATIC:
					LeaveOneOut->LeaveOneOutBayesianQuadratic(pDataSet);
					break;
				case CLASSIFIER_LEASTSQUARES_MINIMUMDISTANCE:
					LeaveOneOut->LeaveOneOutLeastSquareMinimumDistance(pDataSet, pExternalCrossValidation->GetEvaluationInfo()->iOrder, 
																	   (CPattern*)pExternalCrossValidation->GetEvaluationInfo()->pClusteringPoints,
																	   pExternalCrossValidation->GetEvaluationInfo()->iNumberOfClusteringPoints);
					break;
				case CLASSIFIER_SUPPORTVECTORMACHINE:
					LeaveOneOut->LeaveOneOutSupportVectorMachine(pDataSet, &pExternalCrossValidation->GetEvaluationInfo()->svminfo);
					break;
				case CLASSIFIER_SUPPORTVECTORMACHINEEX:
					LeaveOneOut->LeaveOneOutSupportVectorMachineEx(pDataSet, &pExternalCrossValidation->GetEvaluationInfo()->svminfo);
					break;
			}

			delete LeaveOneOut;
			LeaveOneOut = NULL;
			break;
		case EVALUATIONMETHOD_KFOLD:
			KFold = new CKFold (pExternalCrossValidation->GetEvaluationInfo()->iNumberOfFolds);

			switch (pExternalCrossValidation->GetClassificationScheme()){
				case CLASSIFIER_MINIMUMDISTANCE:
					KFold->KFoldMinimumDistance(pDataSet);
					break;
				case CLASSIFIER_KNN_AVERAGE:
					KFold->KFoldKNearestNeighborAverage(pDataSet, pExternalCrossValidation->GetEvaluationInfo()->iNumberOfNeighbors);
					break;
				case CLASSIFIER_KNN_MV:
					KFold->KFoldKNearestNeighborMajorityVote(pDataSet, pExternalCrossValidation->GetEvaluationInfo()->iNumberOfNeighbors);
					break;
				case CLASSIFIER_PNN_GAUSSIAN:
					KFold->KFoldProbabilisticNeuralNetworkGaussian(pDataSet, pExternalCrossValidation->GetEvaluationInfo()->dblSmoothingFactor);
					break;
				case CLASSIFIER_PNN_EXPONENTIAL:
					KFold->KFoldProbabilisticNeuralNetworkExponential(pDataSet, pExternalCrossValidation->GetEvaluationInfo()->dblSmoothingFactor);
					break;
				case CLASSIFIER_PNN_RECIPROCAL:
					KFold->KFoldProbabilisticNeuralNetworkReciprocal(pDataSet, pExternalCrossValidation->GetEvaluationInfo()->dblSmoothingFactor);
					break;
				case CLASSIFIER_BAYESIAN:
					KFold->KFoldBayesian(pDataSet);
					break;
				case CLASSIFIER_BAYESIAN_QUADRATIC:
					KFold->KFoldBayesianQuadratic(pDataSet);
					break;
				case CLASSIFIER_LEASTSQUARES_MINIMUMDISTANCE:
					KFold->KFoldLeastSquareMinimumDistance(pDataSet, pExternalCrossValidation->GetEvaluationInfo()->iOrder, 
														   (CPattern*)pExternalCrossValidation->GetEvaluationInfo()->pClusteringPoints,
														   pExternalCrossValidation->GetEvaluationInfo()->iNumberOfClusteringPoints);
					break;
				case CLASSIFIER_SUPPORTVECTORMACHINE:
					KFold->KFoldSupportVectorMachine(pDataSet, &pExternalCrossValidation->GetEvaluationInfo()->svminfo);
					break;
				case CLASSIFIER_SUPPORTVECTORMACHINEEX:
					KFold->KFoldSupportVectorMachineEx(pDataSet, &pExternalCrossValidation->GetEvaluationInfo()->svminfo);
					break;
			}

			delete KFold;
			KFold = NULL;
			break;
	}

	pExternalCrossValidation->GetEvaluationResultContainer()->AddEvaluationResult(pDataSet->GetTruthTable()->GetOverallAccuracyPercent(), pCombination, pDataSet->GetTruthTable());
	
}

void CExternalCrossValidation::ExternalCrossValidationDesignCB (int iFold, CDataSet *pDesignDataset, CDataSet *pClassificationDataSet, CEvaluationResultContainer* pEvaluationResultContainer, ClassificationScheme cs, EVALUATIONINFO *pEvaluationInfo, SELECTIONINFO *pSelectionInfo){
	
	CEvaluationResultSort *EvaluationResultSort = new CEvaluationResultSort();
	CDataSet *ExtractedDesignDataSet = NULL;
	CDataSet *ExtractedClassificationDataSet = NULL;
	
	EvaluationResultSort->SortEvaluationResultContainerDescending(pEvaluationResultContainer);
	
	ExtractedDesignDataSet = pDesignDataset->CopyDataSetFromCombination(pEvaluationResultContainer->GetEvaluationResult(0)->GetEvaluationResultCombination());
	ExtractedClassificationDataSet = pClassificationDataSet->CopyDataSetFromCombination(pEvaluationResultContainer->GetEvaluationResult(0)->GetEvaluationResultCombination());
	ExtractedClassificationDataSet->GetTruthTable()->ResetTruthTable();

	CMinimumDistanceClassifier *MinimumDistanceClassifier = NULL;
	CKNearestNeighborClassifier *KNearestNeighborClassifier = NULL;
	CProbabilisticNeuralNetwork *ProbabilisticNeuralNetwork = NULL;
	CBayesianClassifier *BayesianClassifier = NULL;
	CLeastSquaresMinimumDistanceClassifier *LeastSquaresMinimumDistanceClassifier = NULL;

	CSupportVectorMachineClassifierEx *SupportVectorMachineClassifierEx = NULL;

 	switch (pExternalCrossValidation->GetClassificationScheme()){
		case CLASSIFIER_MINIMUMDISTANCE:
			MinimumDistanceClassifier = new CMinimumDistanceClassifier();
			MinimumDistanceClassifier->Classify(ExtractedDesignDataSet, ExtractedClassificationDataSet);
			delete MinimumDistanceClassifier;
			MinimumDistanceClassifier = NULL;
 			break;
		case CLASSIFIER_KNN_AVERAGE:
			KNearestNeighborClassifier = new CKNearestNeighborClassifier();
			KNearestNeighborClassifier->ClassifyAverage(ExtractedDesignDataSet, ExtractedClassificationDataSet, pExternalCrossValidation->GetEvaluationInfo()->iNumberOfNeighbors);
			delete KNearestNeighborClassifier;
			KNearestNeighborClassifier = NULL;
			break;
		case CLASSIFIER_KNN_MV:
			KNearestNeighborClassifier = new CKNearestNeighborClassifier();
			KNearestNeighborClassifier->ClassifyMajorityVote(ExtractedDesignDataSet, ExtractedClassificationDataSet, pExternalCrossValidation->GetEvaluationInfo()->iNumberOfNeighbors);
			delete KNearestNeighborClassifier;
			KNearestNeighborClassifier = NULL;
			break;
		case CLASSIFIER_PNN_GAUSSIAN:
			ProbabilisticNeuralNetwork = new CProbabilisticNeuralNetwork();
			ProbabilisticNeuralNetwork->ClassifyGaussian(ExtractedDesignDataSet, ExtractedClassificationDataSet, pExternalCrossValidation->GetEvaluationInfo()->dblSmoothingFactor);
			delete ProbabilisticNeuralNetwork;
			ProbabilisticNeuralNetwork = NULL;
			break;
		case CLASSIFIER_PNN_EXPONENTIAL:
			ProbabilisticNeuralNetwork = new CProbabilisticNeuralNetwork();
			ProbabilisticNeuralNetwork->ClassifyExponential(ExtractedDesignDataSet, ExtractedClassificationDataSet, pExternalCrossValidation->GetEvaluationInfo()->dblSmoothingFactor);
			delete ProbabilisticNeuralNetwork;
			ProbabilisticNeuralNetwork = NULL;
			break;
		case CLASSIFIER_PNN_RECIPROCAL:
			ProbabilisticNeuralNetwork = new CProbabilisticNeuralNetwork();
			ProbabilisticNeuralNetwork->ClassifyReciprocal(ExtractedDesignDataSet, ExtractedClassificationDataSet, pExternalCrossValidation->GetEvaluationInfo()->dblSmoothingFactor);
			delete ProbabilisticNeuralNetwork;
			ProbabilisticNeuralNetwork = NULL;
			break;
		case CLASSIFIER_BAYESIAN:
			BayesianClassifier = new CBayesianClassifier();
			BayesianClassifier->Classify(ExtractedDesignDataSet, ExtractedClassificationDataSet);
			delete BayesianClassifier;
			BayesianClassifier = NULL;
			break;
		case CLASSIFIER_BAYESIAN_QUADRATIC:
			BayesianClassifier = new CBayesianClassifier();
			BayesianClassifier->ClassifyQuadratic(ExtractedDesignDataSet, ExtractedClassificationDataSet);
			delete BayesianClassifier;
			BayesianClassifier = NULL;
			break;
// 		case CLASSIFIER_LEASTSQUARES_MINIMUMDISTANCE:
// 			LeastSquaresMinimumDistanceClassifier = new CLeastSquaresMinimumDistanceClassifier()
// 
// 
// 			SelfConsistency->SelfConsistencyLeastSquareMinimumDistance(ExtractedClassificationDataSet, pExternalCrossValidation->GetEvaluationInfo()->iOrder, 
// 																	   (CPattern*)pExternalCrossValidation->GetEvaluationInfo()->pClusteringPoints,
// 																	   pExternalCrossValidation->GetEvaluationInfo()->iNumberOfClusteringPoints);
// 			break;
// 		case CLASSIFIER_SUPPORTVECTORMACHINE:
// 			SelfConsistency->SelfConsistencySupportVectorMachine(ExtractedClassificationDataSet, &pExternalCrossValidation->GetEvaluationInfo()->svminfo);
// 			break;
 		case CLASSIFIER_SUPPORTVECTORMACHINEEX:
			CSupportVectorMachineClassifierEx::LabelDataSet(ExtractedDesignDataSet);
			CSupportVectorMachineClassifierEx::LabelDataSet(ExtractedClassificationDataSet);
			
			SupportVectorMachineClassifierEx = new CSupportVectorMachineClassifierEx(&pExternalCrossValidation->GetEvaluationInfo()->svminfo);
			SupportVectorMachineClassifierEx->Classify(ExtractedDesignDataSet, ExtractedClassificationDataSet);
			delete SupportVectorMachineClassifierEx;
			SupportVectorMachineClassifierEx = NULL;
			break;
 	}
			
	if (pExternalCrossValidation->GetExternalCrossValidationClassificationCallBackFunction() != NULL){
		pExternalCrossValidation->GetExternalCrossValidationClassificationCallBackFunction()(iFold, ExtractedDesignDataSet, ExtractedClassificationDataSet, pEvaluationResultContainer, cs, pEvaluationInfo, pSelectionInfo);
	}

	delete ExtractedClassificationDataSet;
	ExtractedClassificationDataSet = NULL;
	delete ExtractedDesignDataSet;
	ExtractedDesignDataSet = NULL;
	delete EvaluationResultSort;
	EvaluationResultSort = NULL;

}
