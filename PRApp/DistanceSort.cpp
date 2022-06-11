#include "stdafx.h"
#include "DistanceSort.h"

CDistanceSort::CDistanceSort()
{

}

CDistanceSort::~CDistanceSort()
{

}

void CDistanceSort::SortDistancesAscending (CDistance *pDistances, int iDistancesSize){

	double dbTemp = 0.0f;
	int iPattern1ClassIndexTmp = 0;
	int iPattern2ClassIndexTmp = 0;

	for (int i=0;i<(iDistancesSize - 1);i++){
		for (int j=(i + 1);j<iDistancesSize;j++){
			if (pDistances[i].GetDistanceValue() > pDistances[j].GetDistanceValue()){
				dbTemp = pDistances[i].GetDistanceValue();
				iPattern1ClassIndexTmp = pDistances[i].GetPattern1ClassIndex();
				iPattern2ClassIndexTmp = pDistances[i].GetPattern2ClassIndex();
				pDistances[i].SetDistanceValue(pDistances[j].GetDistanceValue());
				pDistances[i].SetPattern1ClassIndex(pDistances[j].GetPattern1ClassIndex());
				pDistances[i].SetPattern2ClassIndex(pDistances[j].GetPattern2ClassIndex());
				pDistances[j].SetDistanceValue(dbTemp);
				pDistances[j].SetPattern1ClassIndex(iPattern1ClassIndexTmp);
				pDistances[j].SetPattern2ClassIndex(iPattern2ClassIndexTmp);
			}
		}
	}

}

void CDistanceSort::SortDistancesDescending (CDistance *pDistances, int iDistancesSize){

	double dbTemp = 0.0f;
	int iPattern1ClassIndexTmp = 0;
	int iPattern2ClassIndexTmp = 0;

	for (int i=0;i<(iDistancesSize - 1);i++){
		for (int j=(i + 1);j<iDistancesSize;j++){
			if (pDistances[i].GetDistanceValue() < pDistances[j].GetDistanceValue()){
				dbTemp = pDistances[i].GetDistanceValue();
				iPattern1ClassIndexTmp = pDistances[i].GetPattern1ClassIndex();
				iPattern2ClassIndexTmp = pDistances[i].GetPattern2ClassIndex();
				pDistances[i].SetDistanceValue(pDistances[j].GetDistanceValue());
				pDistances[i].SetPattern1ClassIndex(pDistances[j].GetPattern1ClassIndex());
				pDistances[i].SetPattern2ClassIndex(pDistances[j].GetPattern2ClassIndex());
				pDistances[j].SetDistanceValue(dbTemp);
				pDistances[j].SetPattern1ClassIndex(iPattern1ClassIndexTmp);
				pDistances[j].SetPattern2ClassIndex(iPattern2ClassIndexTmp);
			}
		}
	}	

}

void CDistanceSort::SortSquaredDistancesAscending (CSquaredDistance *pSquaredDistances, int iSquaredDistancesSize){

	double dbTemp = 0.0f;
	int iPattern1ClassIndexTmp = 0;
	int iPattern2ClassIndexTmp = 0;

	for (int i=0;i<(iSquaredDistancesSize - 1);i++){
		for (int j=(i + 1);j<iSquaredDistancesSize;j++){
			if (pSquaredDistances[i].GetSquaredDistanceValue() > pSquaredDistances[j].GetSquaredDistanceValue()){
				dbTemp = pSquaredDistances[i].GetSquaredDistanceValue();
				iPattern1ClassIndexTmp = pSquaredDistances[i].GetPattern1ClassIndex();
				iPattern2ClassIndexTmp = pSquaredDistances[i].GetPattern2ClassIndex();
				pSquaredDistances[i].SetSquaredDistanceValue(pSquaredDistances[j].GetSquaredDistanceValue());
				pSquaredDistances[i].SetPattern1ClassIndex(pSquaredDistances[j].GetPattern1ClassIndex());
				pSquaredDistances[i].SetPattern2ClassIndex(pSquaredDistances[j].GetPattern2ClassIndex());
				pSquaredDistances[j].SetSquaredDistanceValue(dbTemp);
				pSquaredDistances[j].SetPattern1ClassIndex(iPattern1ClassIndexTmp);
				pSquaredDistances[j].SetPattern2ClassIndex(iPattern2ClassIndexTmp);
			}
		}
	}

}

void CDistanceSort::SortSquaredDistancesDescending (CSquaredDistance *pSquaredDistances, int iSquaredDistancesSize){

	double dbTemp = 0.0f;
	int iPattern1ClassIndexTmp = 0;
	int iPattern2ClassIndexTmp = 0;

	for (int i=0;i<(iSquaredDistancesSize - 1);i++){
		for (int j=(i + 1);j<iSquaredDistancesSize;j++){
			if (pSquaredDistances[i].GetSquaredDistanceValue() < pSquaredDistances[j].GetSquaredDistanceValue()){
				dbTemp = pSquaredDistances[i].GetSquaredDistanceValue();
				iPattern1ClassIndexTmp = pSquaredDistances[i].GetPattern1ClassIndex();
				iPattern2ClassIndexTmp = pSquaredDistances[i].GetPattern2ClassIndex();
				pSquaredDistances[i].SetSquaredDistanceValue(pSquaredDistances[j].GetSquaredDistanceValue());
				pSquaredDistances[i].SetPattern1ClassIndex(pSquaredDistances[j].GetPattern1ClassIndex());
				pSquaredDistances[i].SetPattern2ClassIndex(pSquaredDistances[j].GetPattern2ClassIndex());
				pSquaredDistances[j].SetSquaredDistanceValue(dbTemp);
				pSquaredDistances[j].SetPattern1ClassIndex(iPattern1ClassIndexTmp);
				pSquaredDistances[j].SetPattern2ClassIndex(iPattern2ClassIndexTmp);
			}
		}
	}	

}
