#include "stdafx.h"
#include <windows.h>
#include "PRLib.h"

int iNumberOfCombinations = 0;
int iCombinationCount = 0;
CTimeEstimate TimeEstimate;

//////////////////////////////////////////////////////////////////////////
typedef std::vector<CCombination*> vCombinations;

typedef void (*ExhaustiveSearchEnsembleCallBack)(CCombination*, CDataSet*, CDataSet*, CDataSet*, CEvaluationResultContainer*);

class CExhaustiveSearchEnsemble  
{
public:
	CExhaustiveSearchEnsemble();
	CExhaustiveSearchEnsemble(int n, int k, ExhaustiveSearchEnsembleCallBack pExhaustiveSearchEnsebleCallBack = NULL);
	virtual ~CExhaustiveSearchEnsemble();
	
	long CreateCombinations (int n, int k);
	void DeleteCombinations (void);
	long GetNumberOfCombinations (void) { return m_vCombinations.size(); }
	CCombination *GetCombination (int iCombinationIndex);
	void SetExhaustiveSearchCallBackFunction (ExhaustiveSearchEnsembleCallBack pExhaustiveSearchEnsembleCallBack) { m_pExhaustiveSearchEnsebleCallBack = pExhaustiveSearchEnsembleCallBack; }
	
	void ExhaustiveSearchEnsemble (CDataSet *pDataSet1, CDataSet *pDataSet2, CDataSet *pDataSet3, CEvaluationResultContainer *pEvaluationResultContainer = NULL);
	
protected:
	
	long m_NumberOfCombinations;
	
	CCombination *Combination;
	vCombinations m_vCombinations;
	
	ExhaustiveSearchEnsembleCallBack m_pExhaustiveSearchEnsebleCallBack;
	
	_int64 NChooseK (int n, int k);
	_int64 Factorial (_int64 n);
	void FillCombinationVector (int n, int k);
	
};

CExhaustiveSearchEnsemble::CExhaustiveSearchEnsemble()
{

	m_NumberOfCombinations = 0;
	Combination = NULL;
	m_pExhaustiveSearchEnsebleCallBack = NULL;

}

CExhaustiveSearchEnsemble::CExhaustiveSearchEnsemble(int n, int k, ExhaustiveSearchEnsembleCallBack pExhaustiveSearchEnsebleCallBack)
{

	m_NumberOfCombinations = 0;
	Combination = NULL;
	m_pExhaustiveSearchEnsebleCallBack = NULL;

	SetExhaustiveSearchCallBackFunction(pExhaustiveSearchEnsebleCallBack);
	CreateCombinations(n, k);

}

CExhaustiveSearchEnsemble::~CExhaustiveSearchEnsemble()
{

	DeleteCombinations();

}

long CExhaustiveSearchEnsemble::CreateCombinations (int n, int k){

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

void CExhaustiveSearchEnsemble::FillCombinationVector (int n, int k){

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

void CExhaustiveSearchEnsemble::DeleteCombinations (void){

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

CCombination *CExhaustiveSearchEnsemble::GetCombination (int iCombinationIndex){

	if (iCombinationIndex > GetNumberOfCombinations()){
		return NULL;
	}

	return (CCombination *)m_vCombinations[iCombinationIndex];

}

_int64 CExhaustiveSearchEnsemble::NChooseK (int n, int k){

	_int64 lRes = 1;

	for (_int64 i=(n - k + 1);i<=n;i++){
		lRes*=i;
	}
	
	return (lRes / Factorial(k));

}

_int64 CExhaustiveSearchEnsemble::Factorial (_int64 n){
	
	_int64 iRes = 1;
#ifdef USE_OPENMP
#pragma omp parallel for reduction(*:iRes)
#endif
	for (_int64 i=2;i<=n;i++){
		iRes*=i;
	}

	return iRes;

}

void CExhaustiveSearchEnsemble::ExhaustiveSearchEnsemble (CDataSet *pDataSet1, CDataSet *pDataSet2, CDataSet *pDataSet3, CEvaluationResultContainer *pEvaluationResultContainer){

	CDataSet *CoppiedDataSet1 = NULL;
	CDataSet *CoppiedDataSet2 = NULL;
	CDataSet *CoppiedDataSet3 = NULL;

	for (int i=0;i<GetNumberOfCombinations();i++){
		CoppiedDataSet1 = pDataSet1->CopyDataSetFromCombination(GetCombination(i));
		CoppiedDataSet2 = pDataSet2->CopyDataSetFromCombination(GetCombination(i));
		CoppiedDataSet3 = pDataSet3->CopyDataSetFromCombination(GetCombination(i));
		if (m_pExhaustiveSearchEnsebleCallBack != NULL){
			m_pExhaustiveSearchEnsebleCallBack(GetCombination(i), CoppiedDataSet1, CoppiedDataSet2, CoppiedDataSet3, pEvaluationResultContainer);
		}
		delete CoppiedDataSet1;
		CoppiedDataSet1 = NULL;
		delete CoppiedDataSet2;
		CoppiedDataSet2 = NULL;
		delete CoppiedDataSet3;
		CoppiedDataSet3 = NULL;
	}

}

//////////////////////////////////////////////////////////////////////////
int MajorityVoteRule (int *iClassifierOutputs, int iNumberOfClassifiers, int iNumberOfClasses){
	
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
//////////////////////////////////////////////////////////////////////////
void ExhaustiveSearchEnsembleCB (CCombination* pCombination, CDataSet *pDataSet1, CDataSet *pDataSet2, CDataSet *pDataSet3, CEvaluationResultContainer* pEvaluationResultContainer){
	
	CDataSet *CoppiedDataSet1 = NULL;
	CPattern *UnknownPattern1 = NULL;

	CDataSet *CoppiedDataSet2 = NULL;
	CPattern *UnknownPattern2 = NULL;

	CDataSet *CoppiedDataSet3 = NULL;
	CPattern *UnknownPattern3 = NULL;

	pDataSet1->GetTruthTable()->ResetTruthTable();
	pDataSet2->GetTruthTable()->ResetTruthTable();
	pDataSet3->GetTruthTable()->ResetTruthTable();

	int *iClassifierDecisions = new int[3];
	int iEnsembleDecision;

	SVMINFO svminfo;

	svminfo.dblTolerance = 0.001;
	svminfo.dblCostEx = 10;
	svminfo.svmkt = SVMKERNELTYPE_RBF;
	svminfo.iPolynomialDegree = 2; 
	svminfo.dblGammaEx = 0.1;
	svminfo.dblCoef0Ex = 0.2;

	CSupportVectorMachineClassifierEx::LabelDataSet(pDataSet1);
	CSupportVectorMachineClassifierEx::LabelDataSet(pDataSet2);
	CSupportVectorMachineClassifierEx::LabelDataSet(pDataSet3);
	CSupportVectorMachineClassifierEx *SupportVectorMachineClassifierEx = new CSupportVectorMachineClassifierEx(&svminfo);

	// Assume Equal Classes
	for (int i=0;i<pDataSet1->GetNumberOfClasses();i++){
		for (int j=0;j<pDataSet1->GetClass(i)->GetNumberOfPatterns();j++){
			
			CoppiedDataSet1 = pDataSet1->CopyDataSet();
			UnknownPattern1 = CoppiedDataSet1->GetClass(i)->ExtractPattern(j);

			CoppiedDataSet2 = pDataSet2->CopyDataSet();
			UnknownPattern2 = CoppiedDataSet2->GetClass(i)->ExtractPattern(j);

			CoppiedDataSet3 = pDataSet3->CopyDataSet();
			UnknownPattern3 = CoppiedDataSet3->GetClass(i)->ExtractPattern(j);
			
			SupportVectorMachineClassifierEx->Classify(CoppiedDataSet1, UnknownPattern1);
			iClassifierDecisions[0] = SupportVectorMachineClassifierEx->GetClassifierOutput();
			SupportVectorMachineClassifierEx->Classify(CoppiedDataSet2, UnknownPattern2);
			iClassifierDecisions[1] = SupportVectorMachineClassifierEx->GetClassifierOutput();
			SupportVectorMachineClassifierEx->Classify(CoppiedDataSet3, UnknownPattern3);
			iClassifierDecisions[2] = SupportVectorMachineClassifierEx->GetClassifierOutput();
			
			iEnsembleDecision = MajorityVoteRule(iClassifierDecisions, 3, pDataSet1->GetNumberOfClasses());

			pDataSet1->GetTruthTable()->SetTruthTableValue(i, iEnsembleDecision, pDataSet1->GetTruthTable()->GetTruthTableValue(i, iEnsembleDecision) + 1);
			
			delete UnknownPattern1;
			UnknownPattern1 = NULL;
			delete CoppiedDataSet1;
			CoppiedDataSet1 = NULL;

			delete UnknownPattern2;
			UnknownPattern2 = NULL;
			delete CoppiedDataSet2;
			CoppiedDataSet2 = NULL;

			delete UnknownPattern3;
			UnknownPattern3 = NULL;
			delete CoppiedDataSet3;
			CoppiedDataSet3 = NULL;
			
		}	
	}

	delete SupportVectorMachineClassifierEx;
	SupportVectorMachineClassifierEx = NULL;

	delete [] iClassifierDecisions;
	iClassifierDecisions = NULL;


	CTraceToFile::AppendExchaustiveSearchCombinationToFile("Results.txt", pCombination, pDataSet1);
	
	iCombinationCount++;
	TimeEstimate.OffsetProcessPosition(1);
	
	char szEstimateTime[50];
	memset(szEstimateTime, 0, 50 * sizeof(char));
	TimeEstimate.GetProcessEstimatedTime(szEstimateTime);
	
	printf("Running Combination %d of %d (%.2lf%%), Remaining Time: %s\r", iCombinationCount, iNumberOfCombinations, (double)((double)(iCombinationCount) * 100.0f / (double)(iNumberOfCombinations)), szEstimateTime);

	
}
//////////////////////////////////////////////////////////////////////////


int main(int argc, char* argv[])
{

	iNumberOfCombinations = 0;
 	iCombinationCount = 0;
	
	CDataSet *DataSet1 = new CDataSet();
 	CDataSet *DataSetNormalized1 = NULL;

	CDataSet *DataSet2 = new CDataSet();
 	CDataSet *DataSetNormalized2 = NULL;

	CDataSet *DataSet3 = new CDataSet();
 	CDataSet *DataSetNormalized3 = NULL;


	DataSet1->AddClassFromFile("Post-Radiation\\Post-Radiation.T1.txt");
	DataSet1->AddClassFromFile("Pre-Radiation\\Pre-Radiation.T1.txt");
	DataSetNormalized1 = DataSet1->NormalizeDataSet();


	DataSet2->AddClassFromFile("Post-Radiation.T2.txt");
	DataSet2->AddClassFromFile("Pre-Radiation.T2.txt");
	DataSetNormalized2 = DataSet2->NormalizeDataSet();


	DataSet3->AddClassFromFile("Post-Radiation.STIR.txt");
	DataSet3->AddClassFromFile("Pre-Radiation.STIR.txt");
	DataSetNormalized3 = DataSet3->NormalizeDataSet();


	for (int i=1;i<4;i++){
		iCombinationCount = 0;
		CExhaustiveSearchEnsemble *ExhaustiveSearchEnsemble = new CExhaustiveSearchEnsemble(DataSetNormalized1->GetClass(0)->GetNumberOfFeaturesPerPattern(), i, ExhaustiveSearchEnsembleCB);
		iNumberOfCombinations = ExhaustiveSearchEnsemble->GetNumberOfCombinations();
		TimeEstimate.SetProcessSize(iNumberOfCombinations);
		TimeEstimate.StartProcess();
		ExhaustiveSearchEnsemble->ExhaustiveSearchEnsemble(DataSetNormalized1, DataSetNormalized2, DataSetNormalized3, NULL);
		TimeEstimate.StopProcess();
		printf("\n");
		delete ExhaustiveSearchEnsemble;
		ExhaustiveSearchEnsemble = NULL;
	}


	delete DataSetNormalized1;
	DataSetNormalized1 = NULL;

	delete DataSetNormalized2;
	DataSetNormalized2 = NULL;

	delete DataSetNormalized3;
	DataSetNormalized3 = NULL;

	delete DataSet1;
	DataSet1 = NULL;

	delete DataSet2;
	DataSet2 = NULL;

	delete DataSet3;
	DataSet3 = NULL;
	
	return 0;
	
}