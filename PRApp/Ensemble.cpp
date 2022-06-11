#include "stdafx.h"
#include "Ensemble.h"

CEnsemble::CEnsemble()
{

}

CEnsemble::~CEnsemble()
{

}

void CEnsemble::CombineClassifiers (CDataSet *pDataSet, ENSEMBLEINFO *pEnsembleInfo, int iEnsembleInfoSize, EVALUATIONINFO *pEvaluationInfo, EnsembleClassificationRule ecr){

	int i, j, k;

	int *iClassifierOutputs = new int[iEnsembleInfoSize];
	int iRuleOutput = -1;
	CDataSet *CoppiedDataSet = NULL;
	CPattern *UnknownPattern = NULL;
	CMinimumDistanceClassifier *MinimumDistanceClassifier = NULL;
	CKNearestNeighborClassifier *KNearestNeighborClassifier = NULL;
	CProbabilisticNeuralNetwork *ProbabilisticNeuralNetwork = NULL;
	CBayesianClassifier *BayesianClassifier = NULL;
	CLeastSquaresMinimumDistanceClassifier *LeastSquaresMinimumDistanceClassifier = NULL;

	for (i=0;i<iEnsembleInfoSize;i++){
		iClassifierOutputs[i] = -1;
	}
	
	switch (pEvaluationInfo->em){
		case EVALUATIONMETHOD_SELFCONSISTENCY:

			pDataSet->GetTruthTable()->ResetTruthTable();

			for (i=0;i<pDataSet->GetNumberOfClasses();i++){
				for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
					for (k=0;k<iEnsembleInfoSize;k++){
						switch (pEnsembleInfo[k].cs){
							case CLASSIFIER_MINIMUMDISTANCE:	
								MinimumDistanceClassifier = new CMinimumDistanceClassifier();
								MinimumDistanceClassifier->Classify(pDataSet, pDataSet->GetClass(i)->GetPattern(j));
								iClassifierOutputs[k] = MinimumDistanceClassifier->GetClassifierOutput();
								delete MinimumDistanceClassifier;
								MinimumDistanceClassifier = NULL;
								break;
							case CLASSIFIER_KNN_AVERAGE:
								KNearestNeighborClassifier = new CKNearestNeighborClassifier();
								KNearestNeighborClassifier->ClassifyAverage(pDataSet, pDataSet->GetClass(i)->GetPattern(j), pEvaluationInfo->iNumberOfNeighbors);
								iClassifierOutputs[k] = KNearestNeighborClassifier->GetClassifierOutput();
								delete KNearestNeighborClassifier;
								KNearestNeighborClassifier = NULL;
								break;
							case CLASSIFIER_KNN_MV:
								KNearestNeighborClassifier = new CKNearestNeighborClassifier();
								KNearestNeighborClassifier->ClassifyMajorityVote(pDataSet, pDataSet->GetClass(i)->GetPattern(j), pEvaluationInfo->iNumberOfNeighbors);
								iClassifierOutputs[k] = KNearestNeighborClassifier->GetClassifierOutput();
								delete KNearestNeighborClassifier;
								KNearestNeighborClassifier = NULL;
								break;
							case CLASSIFIER_PNN_GAUSSIAN:
								ProbabilisticNeuralNetwork = new CProbabilisticNeuralNetwork();
								ProbabilisticNeuralNetwork->ClassifyGaussian(pDataSet, pDataSet->GetClass(i)->GetPattern(j), pEvaluationInfo->dblSmoothingFactor);
								iClassifierOutputs[k] = ProbabilisticNeuralNetwork->GetClassifierOutput();
								delete ProbabilisticNeuralNetwork;
								ProbabilisticNeuralNetwork = NULL;
								break;
							case CLASSIFIER_PNN_EXPONENTIAL:
								ProbabilisticNeuralNetwork = new CProbabilisticNeuralNetwork();
								ProbabilisticNeuralNetwork->ClassifyExponential(pDataSet, pDataSet->GetClass(i)->GetPattern(j), pEvaluationInfo->dblSmoothingFactor);
								iClassifierOutputs[k] = ProbabilisticNeuralNetwork->GetClassifierOutput();
								delete ProbabilisticNeuralNetwork;
								ProbabilisticNeuralNetwork = NULL;
								break;
							case CLASSIFIER_PNN_RECIPROCAL:
								ProbabilisticNeuralNetwork = new CProbabilisticNeuralNetwork();
								ProbabilisticNeuralNetwork->ClassifyReciprocal(pDataSet, pDataSet->GetClass(i)->GetPattern(j), pEvaluationInfo->dblSmoothingFactor);
								iClassifierOutputs[k] = ProbabilisticNeuralNetwork->GetClassifierOutput();
								delete ProbabilisticNeuralNetwork;
								ProbabilisticNeuralNetwork = NULL;
								break;
							case CLASSIFIER_BAYESIAN:
								BayesianClassifier = new CBayesianClassifier();
								BayesianClassifier->Classify(pDataSet, pDataSet->GetClass(i)->GetPattern(j));
								iClassifierOutputs[k] = BayesianClassifier->GetClassifierOutput();
								delete BayesianClassifier;
								BayesianClassifier = NULL;
								break;
							case CLASSIFIER_BAYESIAN_QUADRATIC:
								BayesianClassifier = new CBayesianClassifier();
								BayesianClassifier->ClassifyQuadratic(pDataSet, pDataSet->GetClass(i)->GetPattern(j));
								iClassifierOutputs[k] = BayesianClassifier->GetClassifierOutput();
								delete BayesianClassifier;
								BayesianClassifier = NULL;
								break;
							case CLASSIFIER_LEASTSQUARES_MINIMUMDISTANCE:
								LeastSquaresMinimumDistanceClassifier = new CLeastSquaresMinimumDistanceClassifier(pDataSet, pEvaluationInfo->iOrder, (CPattern*)(pEvaluationInfo->pClusteringPoints), pEvaluationInfo->iNumberOfClusteringPoints);
								LeastSquaresMinimumDistanceClassifier->Classify(pDataSet, pDataSet->GetClass(i)->GetPattern(j));
								iClassifierOutputs[k] = LeastSquaresMinimumDistanceClassifier->GetClassifierOutput();
								delete LeastSquaresMinimumDistanceClassifier;
								LeastSquaresMinimumDistanceClassifier = NULL;
								break;
						}
					}	
					switch (ecr){
						case CLASSIFICATIONRULE_MAJORITYVOTE:
							iRuleOutput = MajorityVoteRule(iClassifierOutputs, iEnsembleInfoSize, pDataSet->GetNumberOfClasses());
							break;
						case CLASSIFICATIONRULE_AVERAGE:
							iRuleOutput = AverageRule(iClassifierOutputs, iEnsembleInfoSize, pDataSet->GetNumberOfClasses());
							break;
					}
					pDataSet->GetTruthTable()->SetTruthTableValue(i, iRuleOutput, pDataSet->GetTruthTable()->GetTruthTableValue(i, iRuleOutput) + 1);
				}
			}
			break;
		case EVALUATIONMETHOD_LEAVEONEOUT:
			
			pDataSet->GetTruthTable()->ResetTruthTable();
			
			for (i=0;i<pDataSet->GetNumberOfClasses();i++){
				for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
					for (k=0;k<iEnsembleInfoSize;k++){
						CoppiedDataSet = pDataSet->CopyDataSet();
						UnknownPattern = CoppiedDataSet->GetClass(i)->ExtractPattern(j);
						switch (pEnsembleInfo[k].cs){
							case CLASSIFIER_MINIMUMDISTANCE:	
								MinimumDistanceClassifier = new CMinimumDistanceClassifier();
								MinimumDistanceClassifier->Classify(CoppiedDataSet, UnknownPattern);
								iClassifierOutputs[k] = MinimumDistanceClassifier->GetClassifierOutput();
								delete MinimumDistanceClassifier;
								MinimumDistanceClassifier = NULL;
								break;
							case CLASSIFIER_KNN_AVERAGE:
								KNearestNeighborClassifier = new CKNearestNeighborClassifier();
								KNearestNeighborClassifier->ClassifyAverage(CoppiedDataSet, UnknownPattern, pEvaluationInfo->iNumberOfNeighbors);
								iClassifierOutputs[k] = KNearestNeighborClassifier->GetClassifierOutput();
								delete KNearestNeighborClassifier;
								KNearestNeighborClassifier = NULL;
								break;
							case CLASSIFIER_KNN_MV:
								KNearestNeighborClassifier = new CKNearestNeighborClassifier();
								KNearestNeighborClassifier->ClassifyMajorityVote(CoppiedDataSet, UnknownPattern, pEvaluationInfo->iNumberOfNeighbors);
								iClassifierOutputs[k] = KNearestNeighborClassifier->GetClassifierOutput();
								delete KNearestNeighborClassifier;
								KNearestNeighborClassifier = NULL;
								break;
							case CLASSIFIER_PNN_GAUSSIAN:
								ProbabilisticNeuralNetwork = new CProbabilisticNeuralNetwork();
								ProbabilisticNeuralNetwork->ClassifyGaussian(CoppiedDataSet, UnknownPattern, pEvaluationInfo->dblSmoothingFactor);
								iClassifierOutputs[k] = ProbabilisticNeuralNetwork->GetClassifierOutput();
								delete ProbabilisticNeuralNetwork;
								ProbabilisticNeuralNetwork = NULL;
								break;
							case CLASSIFIER_PNN_EXPONENTIAL:
								ProbabilisticNeuralNetwork = new CProbabilisticNeuralNetwork();
								ProbabilisticNeuralNetwork->ClassifyExponential(CoppiedDataSet, UnknownPattern, pEvaluationInfo->dblSmoothingFactor);
								iClassifierOutputs[k] = ProbabilisticNeuralNetwork->GetClassifierOutput();
								delete ProbabilisticNeuralNetwork;
								ProbabilisticNeuralNetwork = NULL;
								break;
							case CLASSIFIER_PNN_RECIPROCAL:
								ProbabilisticNeuralNetwork = new CProbabilisticNeuralNetwork();
								ProbabilisticNeuralNetwork->ClassifyReciprocal(CoppiedDataSet, UnknownPattern, pEvaluationInfo->dblSmoothingFactor);
								iClassifierOutputs[k] = ProbabilisticNeuralNetwork->GetClassifierOutput();
								delete ProbabilisticNeuralNetwork;
								ProbabilisticNeuralNetwork = NULL;
								break;
							case CLASSIFIER_BAYESIAN:
								BayesianClassifier = new CBayesianClassifier();
								BayesianClassifier->Classify(CoppiedDataSet, UnknownPattern);
								iClassifierOutputs[k] = BayesianClassifier->GetClassifierOutput();
								delete BayesianClassifier;
								BayesianClassifier = NULL;
								break;
							case CLASSIFIER_BAYESIAN_QUADRATIC:
								BayesianClassifier = new CBayesianClassifier();
								BayesianClassifier->ClassifyQuadratic(CoppiedDataSet, UnknownPattern);
								iClassifierOutputs[k] = BayesianClassifier->GetClassifierOutput();
								delete BayesianClassifier;
								BayesianClassifier = NULL;
								break;
							case CLASSIFIER_LEASTSQUARES_MINIMUMDISTANCE:
								LeastSquaresMinimumDistanceClassifier = new CLeastSquaresMinimumDistanceClassifier(pDataSet, pEvaluationInfo->iOrder, (CPattern*)(pEvaluationInfo->pClusteringPoints), pEvaluationInfo->iNumberOfClusteringPoints);
								LeastSquaresMinimumDistanceClassifier->Classify(pDataSet, pDataSet->GetClass(i)->GetPattern(j));
								iClassifierOutputs[k] = LeastSquaresMinimumDistanceClassifier->GetClassifierOutput();
								delete LeastSquaresMinimumDistanceClassifier;
								LeastSquaresMinimumDistanceClassifier = NULL;
								break;
						}
						
						delete UnknownPattern;
						UnknownPattern = NULL;
						delete CoppiedDataSet;
						CoppiedDataSet = NULL;
					}
					switch (ecr){
						case CLASSIFICATIONRULE_MAJORITYVOTE:
							iRuleOutput = MajorityVoteRule(iClassifierOutputs, iEnsembleInfoSize, pDataSet->GetNumberOfClasses());
							break;
						case CLASSIFICATIONRULE_AVERAGE:
							iRuleOutput = AverageRule(iClassifierOutputs, iEnsembleInfoSize, pDataSet->GetNumberOfClasses());
							break;
					}
					pDataSet->GetTruthTable()->SetTruthTableValue(i, iRuleOutput, pDataSet->GetTruthTable()->GetTruthTableValue(i, iRuleOutput) + 1);
				}	
			}
			break;
	}

	delete [] iClassifierOutputs;
	iClassifierOutputs = NULL;

}

int CEnsemble::MajorityVoteRule (int *iClassifierOutputs, int iNumberOfClassifiers, int iNumberOfClasses){

	int iMaxClassVotes = 0;
	int iMaxClassVotesIndex = 0;
	int i;
	
	int *iClassVotes = new int [iNumberOfClasses];

	for (i=0;i<iNumberOfClasses;i++){
		iClassVotes[i] = 0;
	}
	
	for (i=0;i<iNumberOfClassifiers;i++){
		iClassVotes[iClassifierOutputs[i]]++;
	}

	iMaxClassVotes = iClassVotes[0];
	
	for (i=0;i<iNumberOfClasses;i++){
		if (iClassVotes[i] > iMaxClassVotes){
			iMaxClassVotes = iClassVotes[i];
			iMaxClassVotesIndex = i;
		}
	}

	delete [] iClassVotes;
	iClassVotes = NULL;

	return iMaxClassVotesIndex;

}

int CEnsemble::AverageRule (int *iClassifierOutputs, int iNumberOfClassifiers, int iNumberOfClasses){

	return 0;

}
