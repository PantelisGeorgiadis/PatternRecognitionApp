#if !defined(AFX_ENSEMBLE_H__D03A953B_C0A3_474E_A0C9_477582F83A32__INCLUDED_)
#define AFX_ENSEMBLE_H__D03A953B_C0A3_474E_A0C9_477582F83A32__INCLUDED_

#include "DataSet.h"
#include "MinimumDistanceClassifier.h"
#include "KNearestNeighborClassifier.h"
#include "ProbabilisticNeuralNetwork.h"
#include "BayesianClassifier.h"
#include "LeastSquaresMinimumDistanceClassifier.h"

enum EnsembleClassificationRule {CLASSIFICATIONRULE_MAJORITYVOTE, CLASSIFICATIONRULE_AVERAGE};

typedef struct _tagENSEMBLEINFO
{

	ClassificationScheme cs;


}ENSEMBLEINFO, *PENSEMBLEINFO;

class CEnsemble  
{
public:
	CEnsemble();
	virtual ~CEnsemble();

	void CombineClassifiers (CDataSet *pDataSet, ENSEMBLEINFO *pEnsembleInfo, int iEnsembleInfoSize, EVALUATIONINFO *pEvaluationInfo, EnsembleClassificationRule ecr = CLASSIFICATIONRULE_MAJORITYVOTE);

protected:

	int MajorityVoteRule (int *iClassifierOutputs, int iNumberOfClassifiers, int iNumberOfClasses);
	int AverageRule (int *iClassifierOutputs, int iNumberOfClassifiers, int iNumberOfClasses);

};

#endif 
