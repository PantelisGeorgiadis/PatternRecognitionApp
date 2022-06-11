#include "stdafx.h"
#include "LeaveOneOut.h"

CLeaveOneOut::CLeaveOneOut()
{

}

CLeaveOneOut::~CLeaveOneOut()
{

}

void CLeaveOneOut::LeaveOneOutMinimumDistance (CDataSet *pDataSet){

	int i, j;
	
	CDataSet *CoppiedDataSet = NULL;
	CPattern *UnknownPattern = NULL;
	CMinimumDistanceClassifier *MinimumDistanceClassifier = new CMinimumDistanceClassifier();

	pDataSet->GetTruthTable()->ResetTruthTable();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			
			CoppiedDataSet = pDataSet->CopyDataSet();
			UnknownPattern = CoppiedDataSet->GetClass(i)->ExtractPattern(j);
			
			MinimumDistanceClassifier->Classify(CoppiedDataSet, UnknownPattern);
			
			pDataSet->GetTruthTable()->SetTruthTableValue(i, MinimumDistanceClassifier->GetClassifierOutput(), pDataSet->GetTruthTable()->GetTruthTableValue(i, MinimumDistanceClassifier->GetClassifierOutput()) + 1);
		
			delete UnknownPattern;
			UnknownPattern = NULL;
			delete CoppiedDataSet;
			CoppiedDataSet = NULL;
		
		}	
	}

	delete MinimumDistanceClassifier;
	MinimumDistanceClassifier = NULL;
	

}

void CLeaveOneOut::LeaveOneOutKNearestNeighborAverage (CDataSet *pDataSet, int k){

	int i, j;
	
	CDataSet *CoppiedDataSet = NULL;
	CPattern *UnknownPattern = NULL;
	CKNearestNeighborClassifier *KNearestNeighborClassifier = new CKNearestNeighborClassifier();

	pDataSet->GetTruthTable()->ResetTruthTable();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			
			CoppiedDataSet = pDataSet->CopyDataSet();
			UnknownPattern = CoppiedDataSet->GetClass(i)->ExtractPattern(j);
			
			KNearestNeighborClassifier->ClassifyAverage(CoppiedDataSet, UnknownPattern, k);
			
			pDataSet->GetTruthTable()->SetTruthTableValue(i, KNearestNeighborClassifier->GetClassifierOutput(), pDataSet->GetTruthTable()->GetTruthTableValue(i, KNearestNeighborClassifier->GetClassifierOutput()) + 1);
		
			delete UnknownPattern;
			UnknownPattern = NULL;
			delete CoppiedDataSet;
			CoppiedDataSet = NULL;
		
		}	
	}

	delete KNearestNeighborClassifier;
	KNearestNeighborClassifier = NULL;
	

}

void CLeaveOneOut::LeaveOneOutKNearestNeighborMajorityVote (CDataSet *pDataSet, int k){

	int i, j;
	
	CDataSet *CoppiedDataSet = NULL;
	CPattern *UnknownPattern = NULL;
	CKNearestNeighborClassifier *KNearestNeighborClassifier = new CKNearestNeighborClassifier();

	pDataSet->GetTruthTable()->ResetTruthTable();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			
			CoppiedDataSet = pDataSet->CopyDataSet();
			UnknownPattern = CoppiedDataSet->GetClass(i)->ExtractPattern(j);
			
			KNearestNeighborClassifier->ClassifyMajorityVote(CoppiedDataSet, UnknownPattern, k);
			
			pDataSet->GetTruthTable()->SetTruthTableValue(i, KNearestNeighborClassifier->GetClassifierOutput(), pDataSet->GetTruthTable()->GetTruthTableValue(i, KNearestNeighborClassifier->GetClassifierOutput()) + 1);
		
			delete UnknownPattern;
			UnknownPattern = NULL;
			delete CoppiedDataSet;
			CoppiedDataSet = NULL;
		
		}	
	}

	delete KNearestNeighborClassifier;
	KNearestNeighborClassifier = NULL;
	
}

void CLeaveOneOut::LeaveOneOutProbabilisticNeuralNetworkGaussian (CDataSet *pDataSet, double dblSmoothingParameter){

	int i, j;
	
	CDataSet *CoppiedDataSet = NULL;
	CPattern *UnknownPattern = NULL;
	CProbabilisticNeuralNetwork *ProbabilisticNeuralNetwork = new CProbabilisticNeuralNetwork();

	pDataSet->GetTruthTable()->ResetTruthTable();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			
			CoppiedDataSet = pDataSet->CopyDataSet();
			UnknownPattern = CoppiedDataSet->GetClass(i)->ExtractPattern(j);

			ProbabilisticNeuralNetwork->ClassifyGaussian(CoppiedDataSet, UnknownPattern, dblSmoothingParameter);
		
			pDataSet->GetTruthTable()->SetTruthTableValue(i, ProbabilisticNeuralNetwork->GetClassifierOutput(), pDataSet->GetTruthTable()->GetTruthTableValue(i, ProbabilisticNeuralNetwork->GetClassifierOutput()) + 1);
		
			delete UnknownPattern;
			UnknownPattern = NULL;
			delete CoppiedDataSet;
			CoppiedDataSet = NULL;
		
		}	
	}

	delete ProbabilisticNeuralNetwork;
	ProbabilisticNeuralNetwork = NULL;

}

void CLeaveOneOut::LeaveOneOutProbabilisticNeuralNetworkExponential (CDataSet *pDataSet, double dblSmoothingParameter){

	int i, j;
	
	CDataSet *CoppiedDataSet = NULL;
	CPattern *UnknownPattern = NULL;
	CProbabilisticNeuralNetwork *ProbabilisticNeuralNetwork = new CProbabilisticNeuralNetwork();

	pDataSet->GetTruthTable()->ResetTruthTable();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			
			CoppiedDataSet = pDataSet->CopyDataSet();
			UnknownPattern = CoppiedDataSet->GetClass(i)->ExtractPattern(j);
			
			ProbabilisticNeuralNetwork->ClassifyExponential(CoppiedDataSet, UnknownPattern, dblSmoothingParameter);
			
			pDataSet->GetTruthTable()->SetTruthTableValue(i, ProbabilisticNeuralNetwork->GetClassifierOutput(), pDataSet->GetTruthTable()->GetTruthTableValue(i, ProbabilisticNeuralNetwork->GetClassifierOutput()) + 1);
		
			delete UnknownPattern;
			UnknownPattern = NULL;
			delete CoppiedDataSet;
			CoppiedDataSet = NULL;
		
		}	
	}

	delete ProbabilisticNeuralNetwork;
	ProbabilisticNeuralNetwork = NULL;

}

void CLeaveOneOut::LeaveOneOutProbabilisticNeuralNetworkReciprocal (CDataSet *pDataSet, double dblSmoothingParameter){

	int i, j;

	CDataSet *CoppiedDataSet = NULL;
	CPattern *UnknownPattern = NULL;
	CProbabilisticNeuralNetwork *ProbabilisticNeuralNetwork = new CProbabilisticNeuralNetwork();

	pDataSet->GetTruthTable()->ResetTruthTable();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			
			CoppiedDataSet = pDataSet->CopyDataSet();
			UnknownPattern = CoppiedDataSet->GetClass(i)->ExtractPattern(j);
			
			ProbabilisticNeuralNetwork->ClassifyReciprocal(CoppiedDataSet, UnknownPattern, dblSmoothingParameter);
			
			pDataSet->GetTruthTable()->SetTruthTableValue(i, ProbabilisticNeuralNetwork->GetClassifierOutput(), pDataSet->GetTruthTable()->GetTruthTableValue(i, ProbabilisticNeuralNetwork->GetClassifierOutput()) + 1);
		
			delete UnknownPattern;
			UnknownPattern = NULL;
			delete CoppiedDataSet;
			CoppiedDataSet = NULL;
		
		}	
	}

	delete ProbabilisticNeuralNetwork;
	ProbabilisticNeuralNetwork = NULL;

}

void CLeaveOneOut::LeaveOneOutBayesian (CDataSet *pDataSet){

	int i, j;

	CDataSet *CoppiedDataSet = NULL;
	CPattern *UnknownPattern = NULL;
	CBayesianClassifier *BayesianClassifier = new CBayesianClassifier();

	pDataSet->GetTruthTable()->ResetTruthTable();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			
			CoppiedDataSet = pDataSet->CopyDataSet();
			UnknownPattern = CoppiedDataSet->GetClass(i)->ExtractPattern(j);
			
			BayesianClassifier->Classify(CoppiedDataSet, UnknownPattern);
			
			pDataSet->GetTruthTable()->SetTruthTableValue(i, BayesianClassifier->GetClassifierOutput(), pDataSet->GetTruthTable()->GetTruthTableValue(i, BayesianClassifier->GetClassifierOutput()) + 1);
		
			delete UnknownPattern;
			UnknownPattern = NULL;
			delete CoppiedDataSet;
			CoppiedDataSet = NULL;
		
		}	
	}

	delete BayesianClassifier;
	BayesianClassifier = NULL;

}

void CLeaveOneOut::LeaveOneOutBayesianQuadratic (CDataSet *pDataSet){

	int i, j;

	CDataSet *CoppiedDataSet = NULL;
	CPattern *UnknownPattern = NULL;
	CBayesianClassifier *BayesianClassifier = new CBayesianClassifier();

	pDataSet->GetTruthTable()->ResetTruthTable();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			
			CoppiedDataSet = pDataSet->CopyDataSet();
			UnknownPattern = CoppiedDataSet->GetClass(i)->ExtractPattern(j);
			
			BayesianClassifier->ClassifyQuadratic(CoppiedDataSet, UnknownPattern);
			
			pDataSet->GetTruthTable()->SetTruthTableValue(i, BayesianClassifier->GetClassifierOutput(), pDataSet->GetTruthTable()->GetTruthTableValue(i, BayesianClassifier->GetClassifierOutput()) + 1);
		
			delete UnknownPattern;
			UnknownPattern = NULL;
			delete CoppiedDataSet;
			CoppiedDataSet = NULL;
		
		}	
	}

	delete BayesianClassifier;
	BayesianClassifier = NULL;

}

void CLeaveOneOut::LeaveOneOutLeastSquareMinimumDistance (CDataSet *pDataSet, int iOrder, CPattern *pClusteringPoints, int iClusteringPointsSize){

	int i, j;

	CDataSet *CoppiedDataSet = NULL;
	CPattern *UnknownPattern = NULL;
	CLeastSquaresMinimumDistanceClassifier *LeastSquaresMinimumDistanceClassifier = new CLeastSquaresMinimumDistanceClassifier();
	LeastSquaresMinimumDistanceClassifier->InitializeClassifier(pDataSet, iOrder, pClusteringPoints, iClusteringPointsSize);

	pDataSet->GetTruthTable()->ResetTruthTable();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			
			CoppiedDataSet = pDataSet->CopyDataSet();
			UnknownPattern = CoppiedDataSet->GetClass(i)->ExtractPattern(j);
			
			LeastSquaresMinimumDistanceClassifier->Classify(CoppiedDataSet, UnknownPattern);
			
			pDataSet->GetTruthTable()->SetTruthTableValue(i, LeastSquaresMinimumDistanceClassifier->GetClassifierOutput(), pDataSet->GetTruthTable()->GetTruthTableValue(i, LeastSquaresMinimumDistanceClassifier->GetClassifierOutput()) + 1);
		
			delete UnknownPattern;
			UnknownPattern = NULL;
			delete CoppiedDataSet;
			CoppiedDataSet = NULL;
		
		}	
	}

	delete LeastSquaresMinimumDistanceClassifier;
	LeastSquaresMinimumDistanceClassifier = NULL;

}

void CLeaveOneOut::LeaveOneOutSupportVectorMachine (CDataSet *pDataSet, SVMINFO *svmi){

	int i, j;

	CDataSet *CoppiedDataSet = NULL;
	CPattern *UnknownPattern = NULL;
	CFeature *ExtendedFeature = new CFeature();
	ExtendedFeature->SetFeatureValue(1.0f);

	if (pDataSet->GetNumberOfClasses() > 2){
		return;
	}

	CSupportVectorMachineClassifier::LabelDataSet(pDataSet);
	CSupportVectorMachineClassifier *SupportVectorMachineClassifier = new CSupportVectorMachineClassifier(svmi);

	pDataSet->GetTruthTable()->ResetTruthTable();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			
			CoppiedDataSet = pDataSet->CopyDataSet();
			UnknownPattern = CoppiedDataSet->GetClass(i)->ExtractPattern(j);
			
			SupportVectorMachineClassifier->Classify(CoppiedDataSet, UnknownPattern);
			
			pDataSet->GetTruthTable()->SetTruthTableValue(i, SupportVectorMachineClassifier->GetClassifierOutput(), pDataSet->GetTruthTable()->GetTruthTableValue(i, SupportVectorMachineClassifier->GetClassifierOutput()) + 1);
		
			delete UnknownPattern;
			UnknownPattern = NULL;
			delete CoppiedDataSet;
			CoppiedDataSet = NULL;
		
		}	
	}

	delete SupportVectorMachineClassifier;
	SupportVectorMachineClassifier = NULL;
	delete ExtendedFeature;
	ExtendedFeature = NULL;

}

void CLeaveOneOut::LeaveOneOutSupportVectorMachineEx (CDataSet *pDataSet, SVMINFO *svmi){
	
	int i, j;
	
	CDataSet *CoppiedDataSet = NULL;
	CPattern *UnknownPattern = NULL;
	
	CSupportVectorMachineClassifierEx::LabelDataSet(pDataSet);
	CSupportVectorMachineClassifierEx *SupportVectorMachineClassifierEx = new CSupportVectorMachineClassifierEx(svmi);
	
	pDataSet->GetTruthTable()->ResetTruthTable();
	
	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			
			CoppiedDataSet = pDataSet->CopyDataSet();
			UnknownPattern = CoppiedDataSet->GetClass(i)->ExtractPattern(j);
			
			SupportVectorMachineClassifierEx->Classify(CoppiedDataSet, UnknownPattern);
			
			pDataSet->GetTruthTable()->SetTruthTableValue(i, (SupportVectorMachineClassifierEx->GetClassifierOutput() - 1), pDataSet->GetTruthTable()->GetTruthTableValue(i, (SupportVectorMachineClassifierEx->GetClassifierOutput() - 1)) + 1);
			
			delete UnknownPattern;
			UnknownPattern = NULL;
			delete CoppiedDataSet;
			CoppiedDataSet = NULL;
			
		}	
	}
	
	delete SupportVectorMachineClassifierEx;
	SupportVectorMachineClassifierEx = NULL;
	
}
