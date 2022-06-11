#include "stdafx.h"
#include "SelfConsistency.h"

CSelfConsistency::CSelfConsistency()
{

}

CSelfConsistency::~CSelfConsistency()
{

}

void CSelfConsistency::SelfConsistencyMinimumDistance (CDataSet *pDataSet){

	int i, j;
	
	CMinimumDistanceClassifier *MinimumDistanceClassifier = new CMinimumDistanceClassifier();

	pDataSet->GetTruthTable()->ResetTruthTable();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			MinimumDistanceClassifier->Classify(pDataSet, pDataSet->GetClass(i)->GetPattern(j));
			pDataSet->GetTruthTable()->SetTruthTableValue(i, MinimumDistanceClassifier->GetClassifierOutput(), pDataSet->GetTruthTable()->GetTruthTableValue(i, MinimumDistanceClassifier->GetClassifierOutput()) + 1);
		}	
	}
	
	delete MinimumDistanceClassifier;
	MinimumDistanceClassifier = NULL;

}

void CSelfConsistency::SelfConsistencyKNearestNeighborAverage (CDataSet *pDataSet, int k){

	int i, j;
	
	CKNearestNeighborClassifier *KNearestNeighborClassifier = new CKNearestNeighborClassifier();

	pDataSet->GetTruthTable()->ResetTruthTable();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			KNearestNeighborClassifier->ClassifyAverage(pDataSet, pDataSet->GetClass(i)->GetPattern(j), k);
			pDataSet->GetTruthTable()->SetTruthTableValue(i, KNearestNeighborClassifier->GetClassifierOutput(), pDataSet->GetTruthTable()->GetTruthTableValue(i, KNearestNeighborClassifier->GetClassifierOutput()) + 1);
		}	
	}
	
	delete KNearestNeighborClassifier;
	KNearestNeighborClassifier = NULL;

}

void CSelfConsistency::SelfConsistencyKNearestNeighborMajorityVote (CDataSet *pDataSet, int k){

	int i, j;
	
	CKNearestNeighborClassifier *KNearestNeighborClassifier = new CKNearestNeighborClassifier();

	pDataSet->GetTruthTable()->ResetTruthTable();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			KNearestNeighborClassifier->ClassifyMajorityVote(pDataSet, pDataSet->GetClass(i)->GetPattern(j), k);
			pDataSet->GetTruthTable()->SetTruthTableValue(i, KNearestNeighborClassifier->GetClassifierOutput(), pDataSet->GetTruthTable()->GetTruthTableValue(i, KNearestNeighborClassifier->GetClassifierOutput()) + 1);
			
		}	
	}
	
	delete KNearestNeighborClassifier;
	KNearestNeighborClassifier = NULL;

}

void CSelfConsistency::SelfConsistencyProbabilisticNeuralNetworkGaussian (CDataSet *pDataSet, double dblSmoothingParameter){

	int i, j;
	
	CProbabilisticNeuralNetwork *ProbabilisticNeuralNetwork = new CProbabilisticNeuralNetwork();

	pDataSet->GetTruthTable()->ResetTruthTable();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			ProbabilisticNeuralNetwork->ClassifyGaussian(pDataSet, pDataSet->GetClass(i)->GetPattern(j), dblSmoothingParameter);
			pDataSet->GetTruthTable()->SetTruthTableValue(i, ProbabilisticNeuralNetwork->GetClassifierOutput(), pDataSet->GetTruthTable()->GetTruthTableValue(i, ProbabilisticNeuralNetwork->GetClassifierOutput()) + 1);
		}	
	}
	
	delete ProbabilisticNeuralNetwork;
	ProbabilisticNeuralNetwork = NULL;

}

void CSelfConsistency::SelfConsistencyProbabilisticNeuralNetworkExponential (CDataSet *pDataSet, double dblSmoothingParameter){

	int i, j;
	
	CProbabilisticNeuralNetwork *ProbabilisticNeuralNetwork = new CProbabilisticNeuralNetwork();

	pDataSet->GetTruthTable()->ResetTruthTable();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			ProbabilisticNeuralNetwork->ClassifyExponential(pDataSet, pDataSet->GetClass(i)->GetPattern(j), dblSmoothingParameter);
			pDataSet->GetTruthTable()->SetTruthTableValue(i, ProbabilisticNeuralNetwork->GetClassifierOutput(), pDataSet->GetTruthTable()->GetTruthTableValue(i, ProbabilisticNeuralNetwork->GetClassifierOutput()) + 1);
		}	
	}
	
	delete ProbabilisticNeuralNetwork;
	ProbabilisticNeuralNetwork = NULL;

}

void CSelfConsistency::SelfConsistencyProbabilisticNeuralNetworkReciprocal (CDataSet *pDataSet, double dblSmoothingParameter){

	int i, j;

	CProbabilisticNeuralNetwork *ProbabilisticNeuralNetwork = new CProbabilisticNeuralNetwork();

	pDataSet->GetTruthTable()->ResetTruthTable();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			ProbabilisticNeuralNetwork->ClassifyReciprocal(pDataSet, pDataSet->GetClass(i)->GetPattern(j), dblSmoothingParameter);
			pDataSet->GetTruthTable()->SetTruthTableValue(i, ProbabilisticNeuralNetwork->GetClassifierOutput(), pDataSet->GetTruthTable()->GetTruthTableValue(i, ProbabilisticNeuralNetwork->GetClassifierOutput()) + 1);
		}	
	}
	
	delete ProbabilisticNeuralNetwork;
	ProbabilisticNeuralNetwork = NULL;

}

void CSelfConsistency::SelfConsistencyBayesian (CDataSet *pDataSet){

	int i, j;

	CBayesianClassifier *BayesianClassifier = new CBayesianClassifier();

	pDataSet->GetTruthTable()->ResetTruthTable();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			BayesianClassifier->Classify(pDataSet, pDataSet->GetClass(i)->GetPattern(j));
			pDataSet->GetTruthTable()->SetTruthTableValue(i, BayesianClassifier->GetClassifierOutput(), pDataSet->GetTruthTable()->GetTruthTableValue(i, BayesianClassifier->GetClassifierOutput()) + 1);
		}	
	}
	
	delete BayesianClassifier;
	BayesianClassifier = NULL;

}

void CSelfConsistency::SelfConsistencyBayesianQuadratic (CDataSet *pDataSet){

	int i, j;

	CBayesianClassifier *BayesianClassifier = new CBayesianClassifier();

	pDataSet->GetTruthTable()->ResetTruthTable();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			BayesianClassifier->ClassifyQuadratic(pDataSet, pDataSet->GetClass(i)->GetPattern(j));
			pDataSet->GetTruthTable()->SetTruthTableValue(i, BayesianClassifier->GetClassifierOutput(), pDataSet->GetTruthTable()->GetTruthTableValue(i, BayesianClassifier->GetClassifierOutput()) + 1);
		}	
	}
	
	delete BayesianClassifier;
	BayesianClassifier = NULL;

}

void CSelfConsistency::SelfConsistencyLeastSquareMinimumDistance (CDataSet *pDataSet, int iOrder, CPattern *pClusteringPoints, int iClusteringPointsSize){

	int i, j;
	
	CLeastSquaresMinimumDistanceClassifier *LeastSquaresMinimumDistanceClassifier = new CLeastSquaresMinimumDistanceClassifier();
	LeastSquaresMinimumDistanceClassifier->InitializeClassifier(pDataSet, iOrder, pClusteringPoints, iClusteringPointsSize);

	pDataSet->GetTruthTable()->ResetTruthTable();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			LeastSquaresMinimumDistanceClassifier->Classify(pDataSet, pDataSet->GetClass(i)->GetPattern(j));
			pDataSet->GetTruthTable()->SetTruthTableValue(i, LeastSquaresMinimumDistanceClassifier->GetClassifierOutput(), pDataSet->GetTruthTable()->GetTruthTableValue(i, LeastSquaresMinimumDistanceClassifier->GetClassifierOutput()) + 1);
		}	
	}
	
	delete LeastSquaresMinimumDistanceClassifier;
	LeastSquaresMinimumDistanceClassifier = NULL;

}

void CSelfConsistency::SelfConsistencySupportVectorMachine (CDataSet *pDataSet, SVMINFO *svmi){

	int i, j;
	
	if (pDataSet->GetNumberOfClasses() > 2){
		return;
	}

	CSupportVectorMachineClassifier::LabelDataSet(pDataSet);
	CSupportVectorMachineClassifier *SupportVectorMachineClassifier = new CSupportVectorMachineClassifier(svmi);

	pDataSet->GetTruthTable()->ResetTruthTable();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			SupportVectorMachineClassifier->Classify(pDataSet, pDataSet->GetClass(i)->GetPattern(j));
			pDataSet->GetTruthTable()->SetTruthTableValue(i, SupportVectorMachineClassifier->GetClassifierOutput(), pDataSet->GetTruthTable()->GetTruthTableValue(i, SupportVectorMachineClassifier->GetClassifierOutput()) + 1);
		}	
	}
	
	delete SupportVectorMachineClassifier;
	SupportVectorMachineClassifier = NULL;

}

void CSelfConsistency::SelfConsistencySupportVectorMachineEx (CDataSet *pDataSet, SVMINFO *svmi){

	int i, j;

	CSupportVectorMachineClassifierEx::LabelDataSet(pDataSet);
	CSupportVectorMachineClassifierEx *SupportVectorMachineClassifierEx = new CSupportVectorMachineClassifierEx(svmi);

	pDataSet->GetTruthTable()->ResetTruthTable();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			SupportVectorMachineClassifierEx->Classify(pDataSet, pDataSet->GetClass(i)->GetPattern(j));
			pDataSet->GetTruthTable()->SetTruthTableValue(i, (SupportVectorMachineClassifierEx->GetClassifierOutput() - 1), pDataSet->GetTruthTable()->GetTruthTableValue(i, (SupportVectorMachineClassifierEx->GetClassifierOutput() - 1)) + 1);
		}	
	}
	
	delete SupportVectorMachineClassifierEx;
	SupportVectorMachineClassifierEx = NULL;

}
