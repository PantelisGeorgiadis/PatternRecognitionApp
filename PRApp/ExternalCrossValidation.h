#if !defined(AFX_EXTERNALCROSSVALIDATION_H__0A1E4179_91FE_45E1_8C11_0FD22046A39A__INCLUDED_)
#define AFX_EXTERNALCROSSVALIDATION_H__0A1E4179_91FE_45E1_8C11_0FD22046A39A__INCLUDED_

#include "DataSet.h"
#include "ExhaustiveSearch.h"
#include "LeaveOneOut.h"
#include "SelfConsistency.h"
#include "KFold.h"
#include "EvaluationResultContainer.h"
#include "EvaluationResultSort.h"

typedef void (*ExternalCrossValidationDesignCallBack)(int, CDataSet*, CDataSet*, CEvaluationResultContainer*, ClassificationScheme, EVALUATIONINFO*, SELECTIONINFO*);
typedef void (*ExternalCrossValidationClassificationCallBack)(int, CDataSet*, CDataSet*, CEvaluationResultContainer*, ClassificationScheme, EVALUATIONINFO*, SELECTIONINFO*);

class CExternalCrossValidation  
{
public:
	CExternalCrossValidation();
	CExternalCrossValidation(ExternalCrossValidationDesignCallBack pExternalCrossValidationDesignCallBack, ExternalCrossValidationClassificationCallBack pExternalCrossValidationClassificationCallBack);
	virtual ~CExternalCrossValidation();

	void ExternalCrossValidation(CDataSet *pDataSet, int iNumberOfFolds, ClassificationScheme cs, EVALUATIONINFO *pEvaluationInfo, SELECTIONINFO *pSelectionInfo);
	
	ClassificationScheme GetClassificationScheme (void) { return m_cs; }
	EVALUATIONINFO *GetEvaluationInfo (void) { return &m_EvaluationInfo; }
	SELECTIONINFO *GetSelectionInfo (void) { return &m_SelectionInfo; }
	void SetExternalCrossValidationDesignCallBackFunction (ExternalCrossValidationDesignCallBack pExternalCrossValidationDesignCallBack) { m_pExternalCrossValidationDesignCallBack = pExternalCrossValidationDesignCallBack; }
	ExternalCrossValidationDesignCallBack GetExternalCrossValidationDesignCallBackFunction (void) { return m_pExternalCrossValidationDesignCallBack; }
	void SetExternalCrossValidationClassificationCallBackFunction (ExternalCrossValidationClassificationCallBack pExternalCrossValidationClassificationCallBack) { m_pExternalCrossValidationClassificationCallBack = pExternalCrossValidationClassificationCallBack; }
	ExternalCrossValidationClassificationCallBack GetExternalCrossValidationClassificationCallBackFunction (void) { return m_pExternalCrossValidationClassificationCallBack; }

	CEvaluationResultContainer *GetEvaluationResultContainer (void) { return m_EvaluationResultContainer; }

	static void ExternalCrossValidationDesignCB (int iFold, CDataSet *pDesignDataset, CDataSet *pClassificationDataSet, CEvaluationResultContainer* pEvaluationResultContainer, ClassificationScheme cs, EVALUATIONINFO *pEvaluationInfo, SELECTIONINFO *pSelectionInfo);

protected:

	ClassificationScheme m_cs;
	EVALUATIONINFO m_EvaluationInfo;
	SELECTIONINFO m_SelectionInfo;

	CEvaluationResultContainer *m_EvaluationResultContainer;
	ExternalCrossValidationDesignCallBack m_pExternalCrossValidationDesignCallBack;
	ExternalCrossValidationClassificationCallBack m_pExternalCrossValidationClassificationCallBack;

	void ExternalCrossValidationExchaustiveSearch(CDataSet *DesignDataSet, CDataSet *ClassificationDataSet, ClassificationScheme cs, EVALUATIONINFO *pEvaluationInfo, SELECTIONINFO *pSelectionInfo);
	static void ExhaustiveSearchCB (CCombination* pCombination, CDataSet* pDataSet, CEvaluationResultContainer *pEvaluationResultContainer);

};

#endif 
