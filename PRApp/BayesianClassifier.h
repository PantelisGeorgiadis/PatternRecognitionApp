#if !defined(AFX_BAYESIANCLASSIFIER_H__7FCFE603_A7D3_4193_86C3_F8D1E3047A6D__INCLUDED_)
#define AFX_BAYESIANCLASSIFIER_H__7FCFE603_A7D3_4193_86C3_F8D1E3047A6D__INCLUDED_

#include <limits>
#include <cmath>
#include "Classifier.h"
#include "DiscriminantFunction.h"
#include "DataSet.h"
#include "DataMatrix2D.h"
#include "MeanValue.h"
#include "Centroid.h"
#include "Determinant.h"

class CBayesianClassifier : public CClassifier
{
public:
	CBayesianClassifier();
	virtual ~CBayesianClassifier();

	void Classify (CDataSet *pDataSet, CPattern *pUnknownPattern);
	void ClassifyQuadratic (CDataSet *pDataSet, CPattern *pUnknownPattern);
	
	void Classify (CDataSet *pDataSet, CDataSet *pUnknownPatterns);
	void ClassifyQuadratic (CDataSet *pDataSet, CDataSet *pUnknownPatterns);


protected:

	CDataMatrix2D *CalculateClassCovarianceMatrix (CClass *pClass);
	CDataMatrix2D *PatternToDataMatrixTransposeMultiplication (CPattern *pPattern);

};

class CBayesianClassifierDiscriminantFunction : public CDiscriminantFunction
{
public:
	CBayesianClassifierDiscriminantFunction() {};
	~CBayesianClassifierDiscriminantFunction() {};

	void CalculateClassDiscriminantFunctionBayesian (CClass *pClass, CPattern *pPattern, CDataMatrix2D *ClassesCovarianceMatrix, int iNumberOfClasses);
	void CalculateClassDiscriminantFunctionBayesianQuadratic (CClass *pClass, CPattern *pPattern, CDataMatrix2D *ClassCovarianceMatrix, double dblClassProbability);
	
};

#endif 
