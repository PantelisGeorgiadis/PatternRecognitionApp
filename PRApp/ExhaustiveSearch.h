#if !defined(AFX_EXHAUSTIVESEARCH_H__7320E77B_FB47_4280_BC57_CBE5D9408991__INCLUDED_)
#define AFX_EXHAUSTIVESEARCH_H__7320E77B_FB47_4280_BC57_CBE5D9408991__INCLUDED_

#ifndef __GNUC__
#pragma warning(disable : 4786)
#endif

#include <vector>
#include "Globals.h"
#include "Combination.h"
#include "DataSet.h"
#include "EvaluationResultContainer.h"

typedef std::vector<CCombination*> vCombinations;

typedef void (*ExhaustiveSearchCallBack)(CCombination*, CDataSet*, CEvaluationResultContainer*);

class CExhaustiveSearch  
{
public:
	CExhaustiveSearch();
	CExhaustiveSearch(int n, int k, ExhaustiveSearchCallBack pExhaustiveSearchCallBack = NULL);
	virtual ~CExhaustiveSearch();

	long CreateCombinations (int n, int k);
	void DeleteCombinations (void);
	long GetNumberOfCombinations (void) { return m_vCombinations.size(); }
	CCombination *GetCombination (int iCombinationIndex);
	void SetExhaustiveSearchCallBackFunction (ExhaustiveSearchCallBack pExhaustiveSearchCallBack) { m_pExhaustiveSearchCallBack = pExhaustiveSearchCallBack; }

	void ExhaustiveSearch (CDataSet *pDataSet, CEvaluationResultContainer *pEvaluationResultContainer = NULL);

protected:

	long m_NumberOfCombinations;

	CCombination *Combination;
	vCombinations m_vCombinations;

	ExhaustiveSearchCallBack m_pExhaustiveSearchCallBack;

	_int64 NChooseK (int n, int k);
	_int64 Factorial (_int64 n);
	void FillCombinationVector (int n, int k);

};

#endif 
