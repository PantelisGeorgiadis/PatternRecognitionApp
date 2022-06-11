#include "stdafx.h"
#include "KFold.h"

CKFold::CKFold()
{

}

CKFold::CKFold(int k)
{

	SetNumberOfFolds(k);

}

CKFold::~CKFold()
{

}

void CKFold::KFoldMinimumDistance (CDataSet *pDataSet){

	int i, j, k;

	if (GetNumberOfFolds() <= 0){
		return;
	}

	pDataSet->GetTruthTable()->ResetTruthTable();

	if (GetNumberOfFolds() == 1){
		CSelfConsistency *SelfConsistency = new CSelfConsistency();
		SelfConsistency->SelfConsistencyMinimumDistance(pDataSet);
		delete SelfConsistency;
		SelfConsistency = NULL;
		return;
	}
	
	CMinimumDistanceClassifier *MinimumDistanceClassifier = new CMinimumDistanceClassifier();
	CDataSet *CoppiedDataSet = NULL;
	CClass *ExtractedClass = NULL;
	int *iFoldPatternIndexes = NULL;
	int iClassFeaturesPerFold = 0;
	
	CTruthTable *FoldTruthTable = new CTruthTable[GetNumberOfFolds()];
	for (k=0;k<GetNumberOfFolds();k++){
		FoldTruthTable[k].CreateTruthTable(pDataSet->GetNumberOfClasses());
	}

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (k=0;k<GetNumberOfFolds();k++){

			iClassFeaturesPerFold = pDataSet->GetClass(i)->GetNumberOfPatterns() / GetNumberOfFolds();

			iFoldPatternIndexes = new int [iClassFeaturesPerFold];
			for (j=0;j<(iClassFeaturesPerFold);j++){
				iFoldPatternIndexes[j] = ((k * iClassFeaturesPerFold) + j);
			}	

			CoppiedDataSet = pDataSet->CopyDataSet();

			ExtractedClass = CoppiedDataSet->GetClass(i)->ExtractPatterns(iFoldPatternIndexes, iClassFeaturesPerFold);

			for (j=0;j<ExtractedClass->GetNumberOfPatterns();j++){
				MinimumDistanceClassifier->Classify(CoppiedDataSet, ExtractedClass->GetPattern(j));
				FoldTruthTable[k].SetTruthTableValue(i, MinimumDistanceClassifier->GetClassifierOutput(), FoldTruthTable[k].GetTruthTableValue(i, MinimumDistanceClassifier->GetClassifierOutput()) + 1);
			}

			delete ExtractedClass;
			ExtractedClass = NULL;
			delete CoppiedDataSet;
			CoppiedDataSet = NULL;
			delete [] iFoldPatternIndexes;
			iFoldPatternIndexes = NULL;

		}
	}

	for (k=0;k<GetNumberOfFolds();k++){
		for (i=0;i<pDataSet->GetNumberOfClasses();i++){
			for (j=0;j<pDataSet->GetNumberOfClasses();j++){
				pDataSet->GetTruthTable()->SetTruthTableValue(i, j, (pDataSet->GetTruthTable()->GetTruthTableValue(i, j) + FoldTruthTable[k].GetTruthTableValue(i, j)));
			}
		}
	}

	delete [] FoldTruthTable;
	FoldTruthTable = NULL;
	delete MinimumDistanceClassifier;
	MinimumDistanceClassifier = NULL;
	
}

void CKFold::KFoldKNearestNeighborAverage (CDataSet *pDataSet, int kn){

	int i, j, k;

	if (GetNumberOfFolds() <= 0){
		return;
	}

	pDataSet->GetTruthTable()->ResetTruthTable();

	if (GetNumberOfFolds() == 1){
		CSelfConsistency *SelfConsistency = new CSelfConsistency();
		SelfConsistency->SelfConsistencyKNearestNeighborAverage(pDataSet, kn);
		delete SelfConsistency;
		SelfConsistency = NULL;
		return;
	}
	
	CKNearestNeighborClassifier *KNearestNeighborClassifier = new CKNearestNeighborClassifier();
	CDataSet *CoppiedDataSet = NULL;
	CClass *ExtractedClass = NULL;
	int *iFoldPatternIndexes = NULL;
	int iClassFeaturesPerFold = 0;
	
	CTruthTable *FoldTruthTable = new CTruthTable[GetNumberOfFolds()];
	for (k=0;k<GetNumberOfFolds();k++){
		FoldTruthTable[k].CreateTruthTable(pDataSet->GetNumberOfClasses());
	}

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (k=0;k<GetNumberOfFolds();k++){

			iClassFeaturesPerFold = pDataSet->GetClass(i)->GetNumberOfPatterns() / GetNumberOfFolds();

			iFoldPatternIndexes = new int [iClassFeaturesPerFold];
			for (j=0;j<(iClassFeaturesPerFold);j++){
				iFoldPatternIndexes[j] = ((k * iClassFeaturesPerFold) + j);
			}	

			CoppiedDataSet = pDataSet->CopyDataSet();

			ExtractedClass = CoppiedDataSet->GetClass(i)->ExtractPatterns(iFoldPatternIndexes, iClassFeaturesPerFold);

			for (j=0;j<ExtractedClass->GetNumberOfPatterns();j++){
				KNearestNeighborClassifier->ClassifyAverage(CoppiedDataSet, ExtractedClass->GetPattern(j), kn);
				FoldTruthTable[k].SetTruthTableValue(i, KNearestNeighborClassifier->GetClassifierOutput(), FoldTruthTable[k].GetTruthTableValue(i, KNearestNeighborClassifier->GetClassifierOutput()) + 1);
			}

			delete ExtractedClass;
			ExtractedClass = NULL;
			delete CoppiedDataSet;
			CoppiedDataSet = NULL;
			delete [] iFoldPatternIndexes;
			iFoldPatternIndexes = NULL;

		}
	}

	for (k=0;k<GetNumberOfFolds();k++){
		for (i=0;i<pDataSet->GetNumberOfClasses();i++){
			for (j=0;j<pDataSet->GetNumberOfClasses();j++){
				pDataSet->GetTruthTable()->SetTruthTableValue(i, j, (pDataSet->GetTruthTable()->GetTruthTableValue(i, j) + FoldTruthTable[k].GetTruthTableValue(i, j)));
			}
		}
	}

	delete [] FoldTruthTable;
	FoldTruthTable = NULL;
	delete KNearestNeighborClassifier;
	KNearestNeighborClassifier = NULL;

}

void CKFold::KFoldKNearestNeighborMajorityVote (CDataSet *pDataSet, int kn){

	int i, j, k;

	if (GetNumberOfFolds() <= 0){
		return;
	}

	pDataSet->GetTruthTable()->ResetTruthTable();

	if (GetNumberOfFolds() == 1){
		CSelfConsistency *SelfConsistency = new CSelfConsistency();
		SelfConsistency->SelfConsistencyKNearestNeighborMajorityVote(pDataSet, kn);
		delete SelfConsistency;
		SelfConsistency = NULL;
		return;
	}
	
	CKNearestNeighborClassifier *KNearestNeighborClassifier = new CKNearestNeighborClassifier();
	CDataSet *CoppiedDataSet = NULL;
	CClass *ExtractedClass = NULL;
	int *iFoldPatternIndexes = NULL;
	int iClassFeaturesPerFold = 0;
	
	CTruthTable *FoldTruthTable = new CTruthTable[GetNumberOfFolds()];
	for (k=0;k<GetNumberOfFolds();k++){
		FoldTruthTable[k].CreateTruthTable(pDataSet->GetNumberOfClasses());
	}

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (k=0;k<GetNumberOfFolds();k++){

			iClassFeaturesPerFold = pDataSet->GetClass(i)->GetNumberOfPatterns() / GetNumberOfFolds();

			iFoldPatternIndexes = new int [iClassFeaturesPerFold];
			for (j=0;j<(iClassFeaturesPerFold);j++){
				iFoldPatternIndexes[j] = ((k * iClassFeaturesPerFold) + j);
			}	

			CoppiedDataSet = pDataSet->CopyDataSet();

			ExtractedClass = CoppiedDataSet->GetClass(i)->ExtractPatterns(iFoldPatternIndexes, iClassFeaturesPerFold);

			for (j=0;j<ExtractedClass->GetNumberOfPatterns();j++){
				KNearestNeighborClassifier->ClassifyMajorityVote(CoppiedDataSet, ExtractedClass->GetPattern(j), kn);
				FoldTruthTable[k].SetTruthTableValue(i, KNearestNeighborClassifier->GetClassifierOutput(), FoldTruthTable[k].GetTruthTableValue(i, KNearestNeighborClassifier->GetClassifierOutput()) + 1);
			}

			delete ExtractedClass;
			ExtractedClass = NULL;
			delete CoppiedDataSet;
			CoppiedDataSet = NULL;
			delete [] iFoldPatternIndexes;
			iFoldPatternIndexes = NULL;

		}
	}

	for (k=0;k<GetNumberOfFolds();k++){
		for (i=0;i<pDataSet->GetNumberOfClasses();i++){
			for (j=0;j<pDataSet->GetNumberOfClasses();j++){
				pDataSet->GetTruthTable()->SetTruthTableValue(i, j, (pDataSet->GetTruthTable()->GetTruthTableValue(i, j) + FoldTruthTable[k].GetTruthTableValue(i, j)));
			}
		}
	}

	delete [] FoldTruthTable;
	FoldTruthTable = NULL;
	delete KNearestNeighborClassifier;
	KNearestNeighborClassifier = NULL;
	
}

void CKFold::KFoldProbabilisticNeuralNetworkGaussian (CDataSet *pDataSet, double dblSmoothingParameter){

	int i, j, k;

	if (GetNumberOfFolds() <= 0){
		return;
	}

	pDataSet->GetTruthTable()->ResetTruthTable();

	if (GetNumberOfFolds() == 1){
		CSelfConsistency *SelfConsistency = new CSelfConsistency();
		SelfConsistency->SelfConsistencyProbabilisticNeuralNetworkGaussian(pDataSet, dblSmoothingParameter);
		delete SelfConsistency;
		SelfConsistency = NULL;
		return;
	}
	
	CProbabilisticNeuralNetwork *ProbabilisticNeuralNetwork = new CProbabilisticNeuralNetwork();
	CDataSet *CoppiedDataSet = NULL;
	CClass *ExtractedClass = NULL;
	int *iFoldPatternIndexes = NULL;
	int iClassFeaturesPerFold = 0;
	
	CTruthTable *FoldTruthTable = new CTruthTable[GetNumberOfFolds()];
	for (k=0;k<GetNumberOfFolds();k++){
		FoldTruthTable[k].CreateTruthTable(pDataSet->GetNumberOfClasses());
	}

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (k=0;k<GetNumberOfFolds();k++){

			iClassFeaturesPerFold = pDataSet->GetClass(i)->GetNumberOfPatterns() / GetNumberOfFolds();

			iFoldPatternIndexes = new int [iClassFeaturesPerFold];
			for (j=0;j<(iClassFeaturesPerFold);j++){
				iFoldPatternIndexes[j] = ((k * iClassFeaturesPerFold) + j);
			}	

			CoppiedDataSet = pDataSet->CopyDataSet();

			ExtractedClass = CoppiedDataSet->GetClass(i)->ExtractPatterns(iFoldPatternIndexes, iClassFeaturesPerFold);

			for (j=0;j<ExtractedClass->GetNumberOfPatterns();j++){
				ProbabilisticNeuralNetwork->ClassifyGaussian(CoppiedDataSet, ExtractedClass->GetPattern(j), dblSmoothingParameter);
				FoldTruthTable[k].SetTruthTableValue(i, ProbabilisticNeuralNetwork->GetClassifierOutput(), FoldTruthTable[k].GetTruthTableValue(i, ProbabilisticNeuralNetwork->GetClassifierOutput()) + 1);
			}

			delete ExtractedClass;
			ExtractedClass = NULL;
			delete CoppiedDataSet;
			CoppiedDataSet = NULL;
			delete [] iFoldPatternIndexes;
			iFoldPatternIndexes = NULL;

		}
	}

	for (k=0;k<GetNumberOfFolds();k++){
		for (i=0;i<pDataSet->GetNumberOfClasses();i++){
			for (j=0;j<pDataSet->GetNumberOfClasses();j++){
				pDataSet->GetTruthTable()->SetTruthTableValue(i, j, (pDataSet->GetTruthTable()->GetTruthTableValue(i, j) + FoldTruthTable[k].GetTruthTableValue(i, j)));
			}
		}
	}

	delete [] FoldTruthTable;
	FoldTruthTable = NULL;
	delete ProbabilisticNeuralNetwork;
	ProbabilisticNeuralNetwork = NULL;

}

void CKFold::KFoldProbabilisticNeuralNetworkExponential (CDataSet *pDataSet, double dblSmoothingParameter){

	int i, j, k;

	if (GetNumberOfFolds() <= 0){
		return;
	}

	pDataSet->GetTruthTable()->ResetTruthTable();

	if (GetNumberOfFolds() == 1){
		CSelfConsistency *SelfConsistency = new CSelfConsistency();
		SelfConsistency->SelfConsistencyProbabilisticNeuralNetworkExponential(pDataSet, dblSmoothingParameter);
		delete SelfConsistency;
		SelfConsistency = NULL;
		return;
	}
	
	CProbabilisticNeuralNetwork *ProbabilisticNeuralNetwork = new CProbabilisticNeuralNetwork();
	CDataSet *CoppiedDataSet = NULL;
	CClass *ExtractedClass = NULL;
	int *iFoldPatternIndexes = NULL;
	int iClassFeaturesPerFold = 0;
	
	CTruthTable *FoldTruthTable = new CTruthTable[GetNumberOfFolds()];
	for (k=0;k<GetNumberOfFolds();k++){
		FoldTruthTable[k].CreateTruthTable(pDataSet->GetNumberOfClasses());
	}

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (k=0;k<GetNumberOfFolds();k++){

			iClassFeaturesPerFold = pDataSet->GetClass(i)->GetNumberOfPatterns() / GetNumberOfFolds();

			iFoldPatternIndexes = new int [iClassFeaturesPerFold];
			for (j=0;j<(iClassFeaturesPerFold);j++){
				iFoldPatternIndexes[j] = ((k * iClassFeaturesPerFold) + j);
			}	

			CoppiedDataSet = pDataSet->CopyDataSet();

			ExtractedClass = CoppiedDataSet->GetClass(i)->ExtractPatterns(iFoldPatternIndexes, iClassFeaturesPerFold);

			for (j=0;j<ExtractedClass->GetNumberOfPatterns();j++){
				ProbabilisticNeuralNetwork->ClassifyExponential(CoppiedDataSet, ExtractedClass->GetPattern(j), dblSmoothingParameter);
				FoldTruthTable[k].SetTruthTableValue(i, ProbabilisticNeuralNetwork->GetClassifierOutput(), FoldTruthTable[k].GetTruthTableValue(i, ProbabilisticNeuralNetwork->GetClassifierOutput()) + 1);
			}

			delete ExtractedClass;
			ExtractedClass = NULL;
			delete CoppiedDataSet;
			CoppiedDataSet = NULL;
			delete [] iFoldPatternIndexes;
			iFoldPatternIndexes = NULL;

		}
	}

	for (k=0;k<GetNumberOfFolds();k++){
		for (i=0;i<pDataSet->GetNumberOfClasses();i++){
			for (j=0;j<pDataSet->GetNumberOfClasses();j++){
				pDataSet->GetTruthTable()->SetTruthTableValue(i, j, (pDataSet->GetTruthTable()->GetTruthTableValue(i, j) + FoldTruthTable[k].GetTruthTableValue(i, j)));
			}
		}
	}

	delete [] FoldTruthTable;
	FoldTruthTable = NULL;
	delete ProbabilisticNeuralNetwork;
	ProbabilisticNeuralNetwork = NULL;


}

void CKFold::KFoldProbabilisticNeuralNetworkReciprocal (CDataSet *pDataSet, double dblSmoothingParameter){

	int i, j, k;

	if (GetNumberOfFolds() <= 0){
		return;
	}

	pDataSet->GetTruthTable()->ResetTruthTable();

	if (GetNumberOfFolds() == 1){
		CSelfConsistency *SelfConsistency = new CSelfConsistency();
		SelfConsistency->SelfConsistencyProbabilisticNeuralNetworkReciprocal(pDataSet, dblSmoothingParameter);
		delete SelfConsistency;
		SelfConsistency = NULL;
		return;
	}
	
	CProbabilisticNeuralNetwork *ProbabilisticNeuralNetwork = new CProbabilisticNeuralNetwork();
	CDataSet *CoppiedDataSet = NULL;
	CClass *ExtractedClass = NULL;
	int *iFoldPatternIndexes = NULL;
	int iClassFeaturesPerFold = 0;
	
	CTruthTable *FoldTruthTable = new CTruthTable[GetNumberOfFolds()];
	for (k=0;k<GetNumberOfFolds();k++){
		FoldTruthTable[k].CreateTruthTable(pDataSet->GetNumberOfClasses());
	}

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (k=0;k<GetNumberOfFolds();k++){

			iClassFeaturesPerFold = pDataSet->GetClass(i)->GetNumberOfPatterns() / GetNumberOfFolds();

			iFoldPatternIndexes = new int [iClassFeaturesPerFold];
			for (j=0;j<(iClassFeaturesPerFold);j++){
				iFoldPatternIndexes[j] = ((k * iClassFeaturesPerFold) + j);
			}	

			CoppiedDataSet = pDataSet->CopyDataSet();

			ExtractedClass = CoppiedDataSet->GetClass(i)->ExtractPatterns(iFoldPatternIndexes, iClassFeaturesPerFold);

			for (j=0;j<ExtractedClass->GetNumberOfPatterns();j++){
				ProbabilisticNeuralNetwork->ClassifyReciprocal(CoppiedDataSet, ExtractedClass->GetPattern(j), dblSmoothingParameter);
				FoldTruthTable[k].SetTruthTableValue(i, ProbabilisticNeuralNetwork->GetClassifierOutput(), FoldTruthTable[k].GetTruthTableValue(i, ProbabilisticNeuralNetwork->GetClassifierOutput()) + 1);
			}

			delete ExtractedClass;
			ExtractedClass = NULL;
			delete CoppiedDataSet;
			CoppiedDataSet = NULL;
			delete [] iFoldPatternIndexes;
			iFoldPatternIndexes = NULL;

		}
	}

	for (k=0;k<GetNumberOfFolds();k++){
		for (i=0;i<pDataSet->GetNumberOfClasses();i++){
			for (j=0;j<pDataSet->GetNumberOfClasses();j++){
				pDataSet->GetTruthTable()->SetTruthTableValue(i, j, (pDataSet->GetTruthTable()->GetTruthTableValue(i, j) + FoldTruthTable[k].GetTruthTableValue(i, j)));
			}
		}
	}

	delete [] FoldTruthTable;
	FoldTruthTable = NULL;
	delete ProbabilisticNeuralNetwork;
	ProbabilisticNeuralNetwork = NULL;

}

void CKFold::KFoldBayesian (CDataSet *pDataSet){

	int i, j, k;

	if (GetNumberOfFolds() <= 0){
		return;
	}

	pDataSet->GetTruthTable()->ResetTruthTable();

	if (GetNumberOfFolds() == 1){
		CSelfConsistency *SelfConsistency = new CSelfConsistency();
		SelfConsistency->SelfConsistencyBayesian(pDataSet);
		delete SelfConsistency;
		SelfConsistency = NULL;
		return;
	}
	
	CBayesianClassifier *BayesianClassifier = new CBayesianClassifier();
	CDataSet *CoppiedDataSet = NULL;
	CClass *ExtractedClass = NULL;
	int *iFoldPatternIndexes = NULL;
	int iClassFeaturesPerFold = 0;
	
	CTruthTable *FoldTruthTable = new CTruthTable[GetNumberOfFolds()];
	for (k=0;k<GetNumberOfFolds();k++){
		FoldTruthTable[k].CreateTruthTable(pDataSet->GetNumberOfClasses());
	}

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (k=0;k<GetNumberOfFolds();k++){

			iClassFeaturesPerFold = pDataSet->GetClass(i)->GetNumberOfPatterns() / GetNumberOfFolds();

			iFoldPatternIndexes = new int [iClassFeaturesPerFold];
			for (j=0;j<(iClassFeaturesPerFold);j++){
				iFoldPatternIndexes[j] = ((k * iClassFeaturesPerFold) + j);
			}	

			CoppiedDataSet = pDataSet->CopyDataSet();

			ExtractedClass = CoppiedDataSet->GetClass(i)->ExtractPatterns(iFoldPatternIndexes, iClassFeaturesPerFold);

			for (j=0;j<ExtractedClass->GetNumberOfPatterns();j++){
				BayesianClassifier->Classify(CoppiedDataSet, ExtractedClass->GetPattern(j));
				FoldTruthTable[k].SetTruthTableValue(i, BayesianClassifier->GetClassifierOutput(), FoldTruthTable[k].GetTruthTableValue(i, BayesianClassifier->GetClassifierOutput()) + 1);
			}

			delete ExtractedClass;
			ExtractedClass = NULL;
			delete CoppiedDataSet;
			CoppiedDataSet = NULL;
			delete [] iFoldPatternIndexes;
			iFoldPatternIndexes = NULL;

		}
	}

	for (k=0;k<GetNumberOfFolds();k++){
		for (i=0;i<pDataSet->GetNumberOfClasses();i++){
			for (j=0;j<pDataSet->GetNumberOfClasses();j++){
				pDataSet->GetTruthTable()->SetTruthTableValue(i, j, (pDataSet->GetTruthTable()->GetTruthTableValue(i, j) + FoldTruthTable[k].GetTruthTableValue(i, j)));
			}
		}
	}

	delete [] FoldTruthTable;
	FoldTruthTable = NULL;
	delete BayesianClassifier;
	BayesianClassifier = NULL;

}

void CKFold::KFoldBayesianQuadratic (CDataSet *pDataSet){

	int i, j, k;

	if (GetNumberOfFolds() <= 0){
		return;
	}

	pDataSet->GetTruthTable()->ResetTruthTable();

	if (GetNumberOfFolds() == 1){
		CSelfConsistency *SelfConsistency = new CSelfConsistency();
		SelfConsistency->SelfConsistencyBayesianQuadratic(pDataSet);
		delete SelfConsistency;
		SelfConsistency = NULL;
		return;
	}
	
	CBayesianClassifier *BayesianClassifier = new CBayesianClassifier();
	CDataSet *CoppiedDataSet = NULL;
	CClass *ExtractedClass = NULL;
	int *iFoldPatternIndexes = NULL;
	int iClassFeaturesPerFold = 0;
	
	CTruthTable *FoldTruthTable = new CTruthTable[GetNumberOfFolds()];
	for (k=0;k<GetNumberOfFolds();k++){
		FoldTruthTable[k].CreateTruthTable(pDataSet->GetNumberOfClasses());
	}

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (k=0;k<GetNumberOfFolds();k++){

			iClassFeaturesPerFold = pDataSet->GetClass(i)->GetNumberOfPatterns() / GetNumberOfFolds();

			iFoldPatternIndexes = new int [iClassFeaturesPerFold];
			for (j=0;j<(iClassFeaturesPerFold);j++){
				iFoldPatternIndexes[j] = ((k * iClassFeaturesPerFold) + j);
			}	

			CoppiedDataSet = pDataSet->CopyDataSet();

			ExtractedClass = CoppiedDataSet->GetClass(i)->ExtractPatterns(iFoldPatternIndexes, iClassFeaturesPerFold);

			for (j=0;j<ExtractedClass->GetNumberOfPatterns();j++){
				BayesianClassifier->ClassifyQuadratic(CoppiedDataSet, ExtractedClass->GetPattern(j));
				FoldTruthTable[k].SetTruthTableValue(i, BayesianClassifier->GetClassifierOutput(), FoldTruthTable[k].GetTruthTableValue(i, BayesianClassifier->GetClassifierOutput()) + 1);
			}

			delete ExtractedClass;
			ExtractedClass = NULL;
			delete CoppiedDataSet;
			CoppiedDataSet = NULL;
			delete [] iFoldPatternIndexes;
			iFoldPatternIndexes = NULL;

		}
	}

	for (k=0;k<GetNumberOfFolds();k++){
		for (i=0;i<pDataSet->GetNumberOfClasses();i++){
			for (j=0;j<pDataSet->GetNumberOfClasses();j++){
				pDataSet->GetTruthTable()->SetTruthTableValue(i, j, (pDataSet->GetTruthTable()->GetTruthTableValue(i, j) + FoldTruthTable[k].GetTruthTableValue(i, j)));
			}
		}
	}

	delete [] FoldTruthTable;
	FoldTruthTable = NULL;
	delete BayesianClassifier;
	BayesianClassifier = NULL;

}

void CKFold::KFoldLeastSquareMinimumDistance (CDataSet *pDataSet, int iOrder, CPattern *pClusteringPoints, int iClusteringPointsSize){

	int i, j, k;

	if (GetNumberOfFolds() <= 0){
		return;
	}

	pDataSet->GetTruthTable()->ResetTruthTable();

	if (GetNumberOfFolds() == 1){
		CSelfConsistency *SelfConsistency = new CSelfConsistency();
		SelfConsistency->SelfConsistencyLeastSquareMinimumDistance(pDataSet, iOrder, pClusteringPoints, iClusteringPointsSize);
		delete SelfConsistency;
		SelfConsistency = NULL;
		return;
	}
	
	CLeastSquaresMinimumDistanceClassifier *LeastSquaresMinimumDistanceClassifier = new CLeastSquaresMinimumDistanceClassifier();
	LeastSquaresMinimumDistanceClassifier->InitializeClassifier(pDataSet, iOrder, pClusteringPoints, iClusteringPointsSize);
		
	CDataSet *CoppiedDataSet = NULL;
	CClass *ExtractedClass = NULL;
	int *iFoldPatternIndexes = NULL;
	int iClassFeaturesPerFold = 0;
	
	CTruthTable *FoldTruthTable = new CTruthTable[GetNumberOfFolds()];
	for (k=0;k<GetNumberOfFolds();k++){
		FoldTruthTable[k].CreateTruthTable(pDataSet->GetNumberOfClasses());
	}

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (k=0;k<GetNumberOfFolds();k++){

			iClassFeaturesPerFold = pDataSet->GetClass(i)->GetNumberOfPatterns() / GetNumberOfFolds();

			iFoldPatternIndexes = new int [iClassFeaturesPerFold];
			for (j=0;j<(iClassFeaturesPerFold);j++){
				iFoldPatternIndexes[j] = ((k * iClassFeaturesPerFold) + j);
			}	

			CoppiedDataSet = pDataSet->CopyDataSet();

			ExtractedClass = CoppiedDataSet->GetClass(i)->ExtractPatterns(iFoldPatternIndexes, iClassFeaturesPerFold);

			for (j=0;j<ExtractedClass->GetNumberOfPatterns();j++){
				LeastSquaresMinimumDistanceClassifier->Classify(CoppiedDataSet, ExtractedClass->GetPattern(j));
				FoldTruthTable[k].SetTruthTableValue(i, LeastSquaresMinimumDistanceClassifier->GetClassifierOutput(), FoldTruthTable[k].GetTruthTableValue(i, LeastSquaresMinimumDistanceClassifier->GetClassifierOutput()) + 1);
			}

			delete ExtractedClass;
			ExtractedClass = NULL;
			delete CoppiedDataSet;
			CoppiedDataSet = NULL;
			delete [] iFoldPatternIndexes;
			iFoldPatternIndexes = NULL;

		}
	}

	for (k=0;k<GetNumberOfFolds();k++){
		for (i=0;i<pDataSet->GetNumberOfClasses();i++){
			for (j=0;j<pDataSet->GetNumberOfClasses();j++){
				pDataSet->GetTruthTable()->SetTruthTableValue(i, j, (pDataSet->GetTruthTable()->GetTruthTableValue(i, j) + FoldTruthTable[k].GetTruthTableValue(i, j)));
			}
		}
	}

	delete [] FoldTruthTable;
	FoldTruthTable = NULL;
	delete LeastSquaresMinimumDistanceClassifier;
	LeastSquaresMinimumDistanceClassifier = NULL;

}

void CKFold::KFoldSupportVectorMachine (CDataSet *pDataSet, SVMINFO *svmi){

	int i, j, k;

	if (GetNumberOfFolds() <= 0){
		return;
	}

	if (pDataSet->GetNumberOfClasses() > 2){
		return;
	}

	CSupportVectorMachineClassifier::LabelDataSet(pDataSet);

	pDataSet->GetTruthTable()->ResetTruthTable();

	if (GetNumberOfFolds() == 1){
		CSelfConsistency *SelfConsistency = new CSelfConsistency();
		SelfConsistency->SelfConsistencySupportVectorMachine(pDataSet, svmi);
		delete SelfConsistency;
		SelfConsistency = NULL;
		return;
	}
	
	CSupportVectorMachineClassifier *SupportVectorMachineClassifier = new CSupportVectorMachineClassifier(svmi);
	CDataSet *CoppiedDataSet = NULL;
	CClass *ExtractedClass = NULL;
	int *iFoldPatternIndexes = NULL;
	int iClassFeaturesPerFold = 0;
	
	CTruthTable *FoldTruthTable = new CTruthTable[GetNumberOfFolds()];
	for (k=0;k<GetNumberOfFolds();k++){
		FoldTruthTable[k].CreateTruthTable(pDataSet->GetNumberOfClasses());
	}

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (k=0;k<GetNumberOfFolds();k++){

			iClassFeaturesPerFold = pDataSet->GetClass(i)->GetNumberOfPatterns() / GetNumberOfFolds();

			iFoldPatternIndexes = new int [iClassFeaturesPerFold];
			for (j=0;j<(iClassFeaturesPerFold);j++){
				iFoldPatternIndexes[j] = ((k * iClassFeaturesPerFold) + j);
			}	

			CoppiedDataSet = pDataSet->CopyDataSet();
			// NOTE: Check label extraction
			ExtractedClass = CoppiedDataSet->GetClass(i)->ExtractPatterns(iFoldPatternIndexes, iClassFeaturesPerFold);

			for (j=0;j<ExtractedClass->GetNumberOfPatterns();j++){
				SupportVectorMachineClassifier->Classify(CoppiedDataSet, ExtractedClass->GetPattern(j));
				FoldTruthTable[k].SetTruthTableValue(i, SupportVectorMachineClassifier->GetClassifierOutput(), FoldTruthTable[k].GetTruthTableValue(i, SupportVectorMachineClassifier->GetClassifierOutput()) + 1);
			}

			delete ExtractedClass;
			ExtractedClass = NULL;
			delete CoppiedDataSet;
			CoppiedDataSet = NULL;
			delete [] iFoldPatternIndexes;
			iFoldPatternIndexes = NULL;

		}
	}

	for (k=0;k<GetNumberOfFolds();k++){
		for (i=0;i<pDataSet->GetNumberOfClasses();i++){
			for (j=0;j<pDataSet->GetNumberOfClasses();j++){
				pDataSet->GetTruthTable()->SetTruthTableValue(i, j, (pDataSet->GetTruthTable()->GetTruthTableValue(i, j) + FoldTruthTable[k].GetTruthTableValue(i, j)));
			}
		}
	}

	delete [] FoldTruthTable;
	FoldTruthTable = NULL;
	delete SupportVectorMachineClassifier;
	SupportVectorMachineClassifier = NULL;

}

void CKFold::KFoldSupportVectorMachineEx (CDataSet *pDataSet, SVMINFO *svmi){

	int i, j, k;

	if (GetNumberOfFolds() <= 0){
		return;
	}

	CSupportVectorMachineClassifierEx::LabelDataSet(pDataSet);

	pDataSet->GetTruthTable()->ResetTruthTable();

	if (GetNumberOfFolds() == 1){
		CSelfConsistency *SelfConsistency = new CSelfConsistency();
		SelfConsistency->SelfConsistencySupportVectorMachineEx(pDataSet, svmi);
		delete SelfConsistency;
		SelfConsistency = NULL;
		return;
	}
	
	CSupportVectorMachineClassifierEx *SupportVectorMachineClassifierEx = new CSupportVectorMachineClassifierEx(svmi);
	CDataSet *CoppiedDataSet = NULL;
	CClass *ExtractedClass = NULL;
	int *iFoldPatternIndexes = NULL;
	int iClassFeaturesPerFold = 0;
	
	CTruthTable *FoldTruthTable = new CTruthTable[GetNumberOfFolds()];
	for (k=0;k<GetNumberOfFolds();k++){
		FoldTruthTable[k].CreateTruthTable(pDataSet->GetNumberOfClasses());
	}

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (k=0;k<GetNumberOfFolds();k++){

			iClassFeaturesPerFold = pDataSet->GetClass(i)->GetNumberOfPatterns() / GetNumberOfFolds();

			iFoldPatternIndexes = new int [iClassFeaturesPerFold];
			for (j=0;j<(iClassFeaturesPerFold);j++){
				iFoldPatternIndexes[j] = ((k * iClassFeaturesPerFold) + j);
			}	

			CoppiedDataSet = pDataSet->CopyDataSet();
			// NOTE: Check label extraction
			ExtractedClass = CoppiedDataSet->GetClass(i)->ExtractPatterns(iFoldPatternIndexes, iClassFeaturesPerFold);

			for (j=0;j<ExtractedClass->GetNumberOfPatterns();j++){
				SupportVectorMachineClassifierEx->Classify(CoppiedDataSet, ExtractedClass->GetPattern(j));
				FoldTruthTable[k].SetTruthTableValue(i, (SupportVectorMachineClassifierEx->GetClassifierOutput() - 1), FoldTruthTable[k].GetTruthTableValue(i, (SupportVectorMachineClassifierEx->GetClassifierOutput() - 1)) + 1);
			}

			delete ExtractedClass;
			ExtractedClass = NULL;
			delete CoppiedDataSet;
			CoppiedDataSet = NULL;
			delete [] iFoldPatternIndexes;
			iFoldPatternIndexes = NULL;

		}
	}

	for (k=0;k<GetNumberOfFolds();k++){
		for (i=0;i<pDataSet->GetNumberOfClasses();i++){
			for (j=0;j<pDataSet->GetNumberOfClasses();j++){
				pDataSet->GetTruthTable()->SetTruthTableValue(i, j, (pDataSet->GetTruthTable()->GetTruthTableValue(i, j) + FoldTruthTable[k].GetTruthTableValue(i, j)));
			}
		}
	}

	delete [] FoldTruthTable;
	FoldTruthTable = NULL;
	delete SupportVectorMachineClassifierEx;
	SupportVectorMachineClassifierEx = NULL;

}
