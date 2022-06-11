#if !defined(AFX_MINIMUMDISTANCECLASSIFIER_H__92C1DBDD_CD0C_44CA_A018_1FA4349AA805__INCLUDED_)
#define AFX_MINIMUMDISTANCECLASSIFIER_H__92C1DBDD_CD0C_44CA_A018_1FA4349AA805__INCLUDED_

#include <limits>
#include "Classifier.h"
#include "DiscriminantFunction.h"
#include "DataSet.h"
#include "MeanValue.h"

class CMinimumDistanceClassifier : public CClassifier
{
public:
	CMinimumDistanceClassifier();
	virtual ~CMinimumDistanceClassifier();

	void Classify (CDataSet *pDataSet, CPattern *pUnknownPattern);
	
	void Classify (CDataSet *pDataSet, CDataSet *pUnknownPatterns);

};

class CMinimumDistanceClassifierDiscriminantFunction : public CDiscriminantFunction
{
public:
	CMinimumDistanceClassifierDiscriminantFunction() {};
	~CMinimumDistanceClassifierDiscriminantFunction() {};

	void CalculateClassDiscriminantFunctionMinimumDistance (CMeanValue *pFeaturesMeanValue, CPattern *pPattern);

};

#endif 
