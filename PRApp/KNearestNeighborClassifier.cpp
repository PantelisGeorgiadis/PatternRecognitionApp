#include "stdafx.h"
#include "KNearestNeighborClassifier.h"

CKNearestNeighborClassifier::CKNearestNeighborClassifier()
{

}

CKNearestNeighborClassifier::~CKNearestNeighborClassifier()
{

}

void CKNearestNeighborClassifier::ClassifyAverage (CDataSet *pDataSet, CPattern *pUnknownPattern, int k){

	int iClassIndexRet = 0;
	int i, j, l;
	double iMinClassAverage = 0.0f;
	int iMinClassAverageIndex = 0;

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		if (pDataSet->GetClass(0)->GetNumberOfFeaturesPerPattern() !=  pDataSet->GetClass(i)->GetNumberOfFeaturesPerPattern()){
			return;
		}
	}

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		if (k > pDataSet->GetClass(i)->GetNumberOfPatterns()){
			return;
		}
	}

	if (k < 0){
		return;
	}

	CDistanceSort *DistancesSort = new CDistanceSort();
	double *iClassAverage = new double [pDataSet->GetNumberOfClasses()];
	double *iClassSum = new double [pDataSet->GetNumberOfClasses()];
	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		iClassAverage[i] = 0.0f;
		iClassSum[i] = 0.0f;
	}

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		CDistance *PatternDistance = new CDistance [pDataSet->GetClass(i)->GetNumberOfPatterns()];
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			PatternDistance[j].CalculatePatternsDistance(pDataSet->GetClass(i)->GetPattern(j), i, pUnknownPattern, -1);
		}
		DistancesSort->SortDistancesAscending(PatternDistance, pDataSet->GetClass(i)->GetNumberOfPatterns());
		for (l=0;l<k;l++){
			iClassSum[i] = iClassSum[i] + PatternDistance[l].GetDistanceValue();
		}
		delete [] PatternDistance;
		PatternDistance = NULL;
	}

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		iClassAverage[i] = (double)(iClassSum[i] / (double)k);
	}

	iMinClassAverage = iClassAverage[0];

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		if (iMinClassAverage > iClassAverage[i]){
			iMinClassAverage = iClassAverage[i];
			iMinClassAverageIndex = i;
		}
	}

	iClassIndexRet = iMinClassAverageIndex;
	
	delete [] iClassSum;
	iClassSum = NULL;
	delete [] iClassAverage;
	iClassAverage = NULL;
	delete DistancesSort;
	DistancesSort = NULL;

	SetClassifierOutput(iClassIndexRet);

}

void CKNearestNeighborClassifier::ClassifyMajorityVote (CDataSet *pDataSet, CPattern *pUnknownPattern, int k){

	int iClassIndexRet = 0;
	int i, j;
	int iPatternMergingIndex = 0;
	int iNumberOfDistances = 0;
	int iMaxClassVotes = 0;
	int iMaxClassVotesIndex = 0;

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		if (pDataSet->GetClass(0)->GetNumberOfFeaturesPerPattern() !=  pDataSet->GetClass(i)->GetNumberOfFeaturesPerPattern()){
			return;
		}
	}

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			iNumberOfDistances++;
		}
	}

	if (k > iNumberOfDistances){
		return;
	}

	if (k < 0){
		return;
	}

	CDistanceSort *DistancesSort = new CDistanceSort();
	CDistance *PatternDistance = new CDistance [iNumberOfDistances];

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			PatternDistance[iPatternMergingIndex + j].CalculatePatternsDistance(pDataSet->GetClass(i)->GetPattern(j), i, pUnknownPattern, -1);
		}
		iPatternMergingIndex = iPatternMergingIndex + pDataSet->GetClass(i)->GetNumberOfPatterns();
	}

	DistancesSort->SortDistancesAscending(PatternDistance, iNumberOfDistances);

	int *iClassVotes = new int [pDataSet->GetNumberOfClasses()];
	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		iClassVotes[i] = 0;
	}

	for (i=0;i<k;i++){
		iClassVotes[PatternDistance[i].GetPattern1ClassIndex()]++;
	}

	iMaxClassVotes = iClassVotes[0];
	
	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		if (iClassVotes[i] > iMaxClassVotes){
			iMaxClassVotes = iClassVotes[i];
			iMaxClassVotesIndex = i;
		}
	}

	iClassIndexRet = iMaxClassVotesIndex;

	delete [] iClassVotes;
	iClassVotes = NULL;
	delete [] PatternDistance;
	PatternDistance = NULL;
	delete DistancesSort;
	DistancesSort = NULL;

	SetClassifierOutput(iClassIndexRet);

}

void CKNearestNeighborClassifier::ClassifyAverage (CDataSet *pDataSet, CDataSet *pUnknownPatterns, int k){

	for (int i=0;i<pUnknownPatterns->GetNumberOfClasses();i++){
		for (int j=0;j<pUnknownPatterns->GetClass(i)->GetNumberOfPatterns();j++){
			ClassifyAverage(pDataSet, pUnknownPatterns->GetClass(i)->GetPattern(j), k);
			pUnknownPatterns->GetTruthTable()->SetTruthTableValue(i, GetClassifierOutput(), pUnknownPatterns->GetTruthTable()->GetTruthTableValue(i, GetClassifierOutput()) + 1);
		}
	}

}

void CKNearestNeighborClassifier::ClassifyMajorityVote (CDataSet *pDataSet, CDataSet *pUnknownPatterns, int k){

	for (int i=0;i<pUnknownPatterns->GetNumberOfClasses();i++){
		for (int j=0;j<pUnknownPatterns->GetClass(i)->GetNumberOfPatterns();j++){
			ClassifyMajorityVote(pDataSet, pUnknownPatterns->GetClass(i)->GetPattern(j), k);
			pUnknownPatterns->GetTruthTable()->SetTruthTableValue(i, GetClassifierOutput(), pUnknownPatterns->GetTruthTable()->GetTruthTableValue(i, GetClassifierOutput()) + 1);
		}
	}

}

