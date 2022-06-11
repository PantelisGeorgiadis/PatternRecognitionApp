#include "stdafx.h"
#include "ExhaustiveSearch.h"


CExhaustiveSearch::CExhaustiveSearch()
{

	m_NumberOfCombinations = 0;
	Combination = NULL;
	m_pExhaustiveSearchCallBack = NULL;

}

CExhaustiveSearch::CExhaustiveSearch(int n, int k, ExhaustiveSearchCallBack pExhaustiveSearchCallBack)
{

	m_NumberOfCombinations = 0;
	Combination = NULL;
	m_pExhaustiveSearchCallBack = NULL;

	SetExhaustiveSearchCallBackFunction(pExhaustiveSearchCallBack);
	CreateCombinations(n, k);

}

CExhaustiveSearch::~CExhaustiveSearch()
{

	DeleteCombinations();

}

long CExhaustiveSearch::CreateCombinations (int n, int k){

	m_NumberOfCombinations = 0;
	Combination = NULL;
	
	if ((n > 0) && (k > 0)){
		m_NumberOfCombinations = NChooseK(n, k);

		// OPTIMIZATION: No push_back
		m_vCombinations.resize(m_NumberOfCombinations);
	
		for (int i=0;i<m_NumberOfCombinations;i++){
			Combination = NULL;
			Combination = new CCombination (k);
			m_vCombinations[i] = Combination;
		}

		FillCombinationVector(n, k);
	}

	return m_NumberOfCombinations;

}

void CExhaustiveSearch::FillCombinationVector (int n, int k){

	_int64 i, j, l;
	int inCount = 0;
	int ikCount = 0;		

	_int64 iEndingIndex = (UNIT64 << n);

	ikCount = 0;
	for (i=((UNIT64<<k) - 1);i<iEndingIndex;){		
		inCount = 0;
		for (j=0;(UNIT64<<j)<=i;j+=1){
			if ((UNIT64<<j)&i){
				GetCombination(ikCount)->SetCombinationVectorValue(inCount, j);
				inCount++;
			}
		}
		j = i&~(i>>1);
		j &= -j;
		l = i&(j - 1);
		i+= j - l + l / (i&-i);
		ikCount++;
	}

}

void CExhaustiveSearch::DeleteCombinations (void){

	CCombination *Combination = NULL;

	for (int i=0;i<GetNumberOfCombinations();i++){
		Combination = GetCombination(i);
		delete Combination;
		Combination = NULL;
	}

	if (!m_vCombinations.empty()){
		m_vCombinations.clear();
	}

}

CCombination *CExhaustiveSearch::GetCombination (int iCombinationIndex){

	if (iCombinationIndex > GetNumberOfCombinations()){
		return NULL;
	}

	return (CCombination *)m_vCombinations[iCombinationIndex];

}

_int64 CExhaustiveSearch::NChooseK (int n, int k){

	_int64 lRes = 1;

	for (_int64 i=(n - k + 1);i<=n;i++){
		lRes*=i;
	}
	
	return (lRes / Factorial(k));

}

_int64 CExhaustiveSearch::Factorial (_int64 n){
	
	_int64 iRes = 1;
#ifdef USE_OPENMP
#pragma omp parallel for reduction(*:iRes)
#endif
	for (_int64 i=2;i<=n;i++){
		iRes*=i;
	}

	return iRes;

}

/*
CALLBACK EXAMPLE

void ExhaustiveSearchCB (CCombination* pCombination, CDataSet* pDataSet, CEvaluationResultContainer* pEvaluationResultContainer){


}

*/

void CExhaustiveSearch::ExhaustiveSearch (CDataSet *pDataSet, CEvaluationResultContainer *pEvaluationResultContainer){

	CDataSet *CoppiedDataSet = NULL;

	for (int i=0;i<GetNumberOfCombinations();i++){
		CoppiedDataSet = pDataSet->CopyDataSetFromCombination(GetCombination(i));
		if (m_pExhaustiveSearchCallBack != NULL){
			m_pExhaustiveSearchCallBack(GetCombination(i), CoppiedDataSet, pEvaluationResultContainer);
		}
		delete CoppiedDataSet;
		CoppiedDataSet = NULL;
	}

}
