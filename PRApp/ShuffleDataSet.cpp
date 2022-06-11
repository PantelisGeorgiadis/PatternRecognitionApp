#include "stdafx.h"
#include "ShuffleDataSet.h"

CShuffleDataSet::CShuffleDataSet()
{

}

CShuffleDataSet::~CShuffleDataSet()
{

}

CDataSet *CShuffleDataSet::ShuffleDataSet (CDataSet *pDataSet, int iShuffleIterations){

	CDataSet *ShuffledDataSet = new CDataSet();
	CClass *ShuffledClass = NULL;
	
	for (int i=0;i<pDataSet->GetNumberOfClasses();i++){
		ShuffledClass = ShuffleClass(pDataSet->GetClass(i), iShuffleIterations);
		ShuffledDataSet->AddClass(ShuffledClass);
	}

	return ShuffledDataSet;

}

CClass *CShuffleDataSet::ShuffleClass (CClass *pClass, int iShuffleIterations){

	int i, j;
	
	CClass *ShuffledClass = new CClass(pClass->GetNumberOfPatterns(), pClass->GetNumberOfFeaturesPerPattern());
	
	CMersenneTwister *MersenneTwister = new CMersenneTwister(time(0));
	int *iClassShuffledPatterns = new int[pClass->GetNumberOfPatterns()];

	for (i=0;i<pClass->GetNumberOfPatterns();i++){
		iClassShuffledPatterns[i] = i;
	}

	int iFromIndex = 0;
	int iToIndex = 0;
	int iTempIndex = 0;

	for (i=0;i<iShuffleIterations;i++){
		for (j=0;j<pClass->GetNumberOfPatterns();j++){
		  iFromIndex = j;
		  iToIndex = (int)ceil(MersenneTwister->Random() * pClass->GetNumberOfPatterns()) - 1.0;

		  iTempIndex = iClassShuffledPatterns[iFromIndex];
		  iClassShuffledPatterns[iFromIndex] = iClassShuffledPatterns[iToIndex];
		  iClassShuffledPatterns[iToIndex] = iTempIndex;
		}
	}

	for (i=0;i<pClass->GetNumberOfPatterns();i++){
		CopyPattern(ShuffledClass->GetPattern(i), pClass->GetPattern(iClassShuffledPatterns[i]));
	}

	delete [] iClassShuffledPatterns;
	iClassShuffledPatterns = NULL;
	delete MersenneTwister;
	MersenneTwister = NULL;

	return ShuffledClass;

}

void CShuffleDataSet::CopyPattern (CPattern *pPatternDest, CPattern *pPatternSrc){

	if (pPatternDest->GetNumberOfFeatures() != pPatternSrc->GetNumberOfFeatures()){
		return;
	}

	for (int i=0;i<pPatternDest->GetNumberOfFeatures();i++){
		pPatternDest->GetFeature(i)->SetFeatureValue(pPatternSrc->GetFeature(i)->GetFeatureValue());
	}

	pPatternDest->SetReservedValue(pPatternSrc->GetReservedValue());

}
