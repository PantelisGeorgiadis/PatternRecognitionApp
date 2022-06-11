#include "stdafx.h"
#include "Bagging.h"

CBagging::CBagging()
{

}

CBagging::~CBagging()
{

}

CDataSet *CBagging::BaggDataSet (CDataSet *pDataSet, int iNumberOfReplicates){

	int i, j, k;

	if (iNumberOfReplicates == 0){
		return NULL;
	}
	
	CDataSet *pBaggedDataSet = new CDataSet[iNumberOfReplicates];
	CDataSet *pTempDataSet = NULL;
	CMersenneTwister *MersenneTwister = new CMersenneTwister(time(0));
	CClass *pExportedClass = NULL;

	int iClassRandomFeatureNumber = 0;
	int *iClassRandomPatternIndexes = NULL;

	for (i=0;i<iNumberOfReplicates;i++){
		pTempDataSet = pDataSet->CopyDataSet();
		
		for (j=0;j<pTempDataSet->GetNumberOfClasses();j++){
			iClassRandomFeatureNumber = pTempDataSet->GetClass(j)->GetNumberOfPatterns();

			iClassRandomPatternIndexes = new int [iClassRandomFeatureNumber];
			for (k=0;k<iClassRandomFeatureNumber;k++){
				iClassRandomPatternIndexes[k] = (int)((MersenneTwister->Random() * (pTempDataSet->GetClass(j)->GetNumberOfPatterns()))) % pTempDataSet->GetClass(j)->GetNumberOfPatterns();
			}

			pExportedClass = pTempDataSet->GetClass(j)->ExportPatterns(iClassRandomPatternIndexes, iClassRandomFeatureNumber);
			pBaggedDataSet[i].AddClass(pExportedClass->CopyClass());

			delete pExportedClass;
			pExportedClass = NULL;
			delete [] iClassRandomPatternIndexes;
			iClassRandomPatternIndexes = NULL;
		}

		delete pTempDataSet;
		pTempDataSet = NULL;
	}

	delete MersenneTwister;
	MersenneTwister = NULL;

	return pBaggedDataSet;

}
