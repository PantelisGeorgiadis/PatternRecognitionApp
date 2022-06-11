#if !defined(AFX_PROBABILISTICNEURALNETWORK_H__1411D9FA_87EF_4076_90AA_608C1955DEC6__INCLUDED_)
#define AFX_PROBABILISTICNEURALNETWORK_H__1411D9FA_87EF_4076_90AA_608C1955DEC6__INCLUDED_

#include <limits>
#include "Classifier.h"
#include "DiscriminantFunction.h"
#include "DataSet.h"
#include "Distance.h"

class CProbabilisticNeuralNetwork : public CClassifier
{
public:
	CProbabilisticNeuralNetwork();
	virtual ~CProbabilisticNeuralNetwork();

	void ClassifyGaussian (CDataSet *pDataSet, CPattern *pUnknownPattern, double dblSmoothingParameter);
	void ClassifyExponential (CDataSet *pDataSet, CPattern *pUnknownPattern, double dblSmoothingParameter);
	void ClassifyReciprocal (CDataSet *pDataSet, CPattern *pUnknownPattern, double dblSmoothingParameter);

	void ClassifyGaussian (CDataSet *pDataSet, CDataSet *pUnknownPatterns, double dblSmoothingParameter);
	void ClassifyExponential (CDataSet *pDataSet, CDataSet *pUnknownPatterns, double dblSmoothingParameter);
	void ClassifyReciprocal (CDataSet *pDataSet, CDataSet *pUnknownPatterns, double dblSmoothingParameter);

};

class CProbabilisticNeuralNetworkClassifierDiscriminantFunction : public CDiscriminantFunction
{
public:
	CProbabilisticNeuralNetworkClassifierDiscriminantFunction() {};
	~CProbabilisticNeuralNetworkClassifierDiscriminantFunction() {};

	void CalculateClassDiscriminantFunctionProbabilisticNeuralNetworkGaussian (CClass *pClass, CPattern *pDistanceFromPattern, double dblSmoothingParameter);
	void CalculateClassDiscriminantFunctionProbabilisticNeuralNetworkExponential (CClass *pClass, CPattern *pDistanceFromPattern, double dblSmoothingParameter);
	void CalculateClassDiscriminantFunctionProbabilisticNeuralNetworkReciprocal (CClass *pClass, CPattern *pDistanceFromPattern, double dblSmoothingParameter);
	
};

#endif 
