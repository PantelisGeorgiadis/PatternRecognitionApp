#include "stdafx.h"
#include "ProbabilisticNeuralNetwork.h"

CProbabilisticNeuralNetwork::CProbabilisticNeuralNetwork()
{

}

CProbabilisticNeuralNetwork::~CProbabilisticNeuralNetwork()
{

}

void CProbabilisticNeuralNetwork::ClassifyGaussian (CDataSet *pDataSet, CPattern *pUnknownPattern, double dblSmoothingParameter){

	int iClassIndexRet = 0;
	int i;
	int iMaxDiscriminantFunctionClassIndex = 0;
	double dblMaxDiscriminantFunctionValue = (std::numeric_limits<double>::max)();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		if (pDataSet->GetClass(0)->GetNumberOfFeaturesPerPattern() !=  pDataSet->GetClass(i)->GetNumberOfFeaturesPerPattern()){
			return;
		}
	}

	CProbabilisticNeuralNetworkClassifierDiscriminantFunction *DiscriminantFunction = new CProbabilisticNeuralNetworkClassifierDiscriminantFunction[pDataSet->GetNumberOfClasses()];

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		DiscriminantFunction[i].CalculateClassDiscriminantFunctionProbabilisticNeuralNetworkGaussian(pDataSet->GetClass(i), pUnknownPattern, dblSmoothingParameter);
	}

	dblMaxDiscriminantFunctionValue = DiscriminantFunction[0].GetDiscriminantFunctionValue();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		if (DiscriminantFunction[i].GetDiscriminantFunctionValue() > dblMaxDiscriminantFunctionValue){
			dblMaxDiscriminantFunctionValue = DiscriminantFunction[i].GetDiscriminantFunctionValue();
			iMaxDiscriminantFunctionClassIndex = i;
		}
	}

	iClassIndexRet = iMaxDiscriminantFunctionClassIndex;

	delete [] DiscriminantFunction;
	DiscriminantFunction = NULL;

	SetClassifierOutput(iClassIndexRet);

}

void CProbabilisticNeuralNetwork::ClassifyExponential (CDataSet *pDataSet, CPattern *pUnknownPattern, double dblSmoothingParameter){

	int iClassIndexRet = 0;
	int i;
	int iMaxDiscriminantFunctionClassIndex = 0;
	double dblMaxDiscriminantFunctionValue = (std::numeric_limits<double>::max)();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		if (pDataSet->GetClass(0)->GetNumberOfFeaturesPerPattern() !=  pDataSet->GetClass(i)->GetNumberOfFeaturesPerPattern()){
			return;
		}
	}

	CProbabilisticNeuralNetworkClassifierDiscriminantFunction *DiscriminantFunction = new CProbabilisticNeuralNetworkClassifierDiscriminantFunction[pDataSet->GetNumberOfClasses()];

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		DiscriminantFunction[i].CalculateClassDiscriminantFunctionProbabilisticNeuralNetworkExponential(pDataSet->GetClass(i), pUnknownPattern, dblSmoothingParameter);
	}

	dblMaxDiscriminantFunctionValue = DiscriminantFunction[0].GetDiscriminantFunctionValue();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		if (DiscriminantFunction[i].GetDiscriminantFunctionValue() > dblMaxDiscriminantFunctionValue){
			dblMaxDiscriminantFunctionValue = DiscriminantFunction[i].GetDiscriminantFunctionValue();
			iMaxDiscriminantFunctionClassIndex = i;
		}
	}

	iClassIndexRet = iMaxDiscriminantFunctionClassIndex;

	delete [] DiscriminantFunction;
	DiscriminantFunction = NULL;

	SetClassifierOutput(iClassIndexRet);

}

void CProbabilisticNeuralNetwork::ClassifyReciprocal (CDataSet *pDataSet, CPattern *pUnknownPattern, double dblSmoothingParameter){

	int iClassIndexRet = 0;
	int i;
	int iMaxDiscriminantFunctionClassIndex = 0;
	double dblMaxDiscriminantFunctionValue = (std::numeric_limits<double>::max)();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		if (pDataSet->GetClass(0)->GetNumberOfFeaturesPerPattern() !=  pDataSet->GetClass(i)->GetNumberOfFeaturesPerPattern()){
			return;
		}
	}

	CProbabilisticNeuralNetworkClassifierDiscriminantFunction *DiscriminantFunction = new CProbabilisticNeuralNetworkClassifierDiscriminantFunction[pDataSet->GetNumberOfClasses()];

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		DiscriminantFunction[i].CalculateClassDiscriminantFunctionProbabilisticNeuralNetworkReciprocal(pDataSet->GetClass(i), pUnknownPattern, dblSmoothingParameter);
	}

	dblMaxDiscriminantFunctionValue = DiscriminantFunction[0].GetDiscriminantFunctionValue();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		if (DiscriminantFunction[i].GetDiscriminantFunctionValue() > dblMaxDiscriminantFunctionValue){
			dblMaxDiscriminantFunctionValue = DiscriminantFunction[i].GetDiscriminantFunctionValue();
			iMaxDiscriminantFunctionClassIndex = i;
		}
	}

	iClassIndexRet = iMaxDiscriminantFunctionClassIndex;

	delete [] DiscriminantFunction;
	DiscriminantFunction = NULL;

	SetClassifierOutput(iClassIndexRet);

}

void CProbabilisticNeuralNetwork::ClassifyGaussian (CDataSet *pDataSet, CDataSet *pUnknownPatterns, double dblSmoothingParameter){

	for (int i=0;i<pUnknownPatterns->GetNumberOfClasses();i++){
		for (int j=0;j<pUnknownPatterns->GetClass(i)->GetNumberOfPatterns();j++){
			ClassifyGaussian(pDataSet, pUnknownPatterns->GetClass(i)->GetPattern(j), dblSmoothingParameter);
			pUnknownPatterns->GetTruthTable()->SetTruthTableValue(i, GetClassifierOutput(), pUnknownPatterns->GetTruthTable()->GetTruthTableValue(i, GetClassifierOutput()) + 1);
		}
	}

}


void CProbabilisticNeuralNetwork::ClassifyExponential (CDataSet *pDataSet, CDataSet *pUnknownPatterns, double dblSmoothingParameter){

	for (int i=0;i<pUnknownPatterns->GetNumberOfClasses();i++){
		for (int j=0;j<pUnknownPatterns->GetClass(i)->GetNumberOfPatterns();j++){
			ClassifyExponential(pDataSet, pUnknownPatterns->GetClass(i)->GetPattern(j), dblSmoothingParameter);
			pUnknownPatterns->GetTruthTable()->SetTruthTableValue(i, GetClassifierOutput(), pUnknownPatterns->GetTruthTable()->GetTruthTableValue(i, GetClassifierOutput()) + 1);
		}
	}

}

void CProbabilisticNeuralNetwork::ClassifyReciprocal (CDataSet *pDataSet, CDataSet *pUnknownPatterns, double dblSmoothingParameter){

	for (int i=0;i<pUnknownPatterns->GetNumberOfClasses();i++){
		for (int j=0;j<pUnknownPatterns->GetClass(i)->GetNumberOfPatterns();j++){
			ClassifyReciprocal(pDataSet, pUnknownPatterns->GetClass(i)->GetPattern(j), dblSmoothingParameter);
			pUnknownPatterns->GetTruthTable()->SetTruthTableValue(i, GetClassifierOutput(), pUnknownPatterns->GetTruthTable()->GetTruthTableValue(i, GetClassifierOutput()) + 1);
		}
	}

}

void CProbabilisticNeuralNetworkClassifierDiscriminantFunction::CalculateClassDiscriminantFunctionProbabilisticNeuralNetworkGaussian (CClass *pClass, CPattern *pDistanceFromPattern, double dblSmoothingParameter){

	double dblMultiplier = 0.0f;
	double dblSum = 0.0f;

	CSquaredDistance *PatternSquaredDistance = new CSquaredDistance();

	dblMultiplier = 1.0f / ((pow(2.0f * PI, (pClass->GetNumberOfFeaturesPerPattern() / 2))) * (pow(dblSmoothingParameter, pClass->GetNumberOfFeaturesPerPattern())) * (pClass->GetNumberOfPatterns()));
	
	for (int i=0;i<pClass->GetNumberOfPatterns();i++){
		PatternSquaredDistance->CalculatePatternsSquaredDistance(pDistanceFromPattern, -1, pClass->GetPattern(i), -1);
		dblSum = dblSum + exp(-(PatternSquaredDistance->GetSquaredDistanceValue()) / (2.0f * pow(dblSmoothingParameter, 2)));
	}

	delete PatternSquaredDistance;
	PatternSquaredDistance = NULL;

	SetDiscriminantFunctionValue(dblMultiplier * dblSum);

}

void CProbabilisticNeuralNetworkClassifierDiscriminantFunction::CalculateClassDiscriminantFunctionProbabilisticNeuralNetworkExponential (CClass *pClass, CPattern *pDistanceFromPattern, double dblSmoothingParameter){

	double dblMultiplier = 0.0f;
	double dblSum = 0.0f;

	CDistance *PatternDistance = new CDistance();

	dblMultiplier = 1.0f / ((pow(2.0f * PI, (pClass->GetNumberOfFeaturesPerPattern() / 2))) * (pow(dblSmoothingParameter, pClass->GetNumberOfFeaturesPerPattern())) * (pClass->GetNumberOfPatterns()));
	
	for (int i=0;i<pClass->GetNumberOfPatterns();i++){
		PatternDistance->CalculatePatternsDistance(pDistanceFromPattern, pClass->GetPattern(i));
		dblSum = dblSum + exp(-(PatternDistance->GetDistanceValue()) / dblSmoothingParameter);
	}

	delete PatternDistance;
	PatternDistance = NULL;

	SetDiscriminantFunctionValue(dblMultiplier * dblSum);

}

void CProbabilisticNeuralNetworkClassifierDiscriminantFunction::CalculateClassDiscriminantFunctionProbabilisticNeuralNetworkReciprocal (CClass *pClass, CPattern *pDistanceFromPattern, double dblSmoothingParameter){

	double dblMultiplier = 0.0f;
	double dblSum = 0.0f;

	CSquaredDistance *PatternSquaredDistance = new CSquaredDistance();

	dblMultiplier = 1.0f / ((pow(2.0f * PI, (pClass->GetNumberOfFeaturesPerPattern() / 2))) * (pow(dblSmoothingParameter, pClass->GetNumberOfFeaturesPerPattern())) * (pClass->GetNumberOfPatterns()));
	
	for (int i=0;i<pClass->GetNumberOfPatterns();i++){
		PatternSquaredDistance->CalculatePatternsSquaredDistance(pDistanceFromPattern, -1, pClass->GetPattern(i), -1);
		dblSum = dblSum + (1.0f / (1.0f + (PatternSquaredDistance->GetSquaredDistanceValue() / pow(dblSmoothingParameter, 2))));
	}

	delete PatternSquaredDistance;
	PatternSquaredDistance = NULL;

	SetDiscriminantFunctionValue(dblMultiplier * dblSum);

}
