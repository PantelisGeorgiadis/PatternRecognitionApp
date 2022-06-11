#include "stdafx.h"
#include "MinimumDistanceClassifier.h"

CMinimumDistanceClassifier::CMinimumDistanceClassifier()
{

}

CMinimumDistanceClassifier::~CMinimumDistanceClassifier()
{

}

void CMinimumDistanceClassifier::Classify (CDataSet *pDataSet, CPattern *pUnknownPattern){

	int iClassIndexRet = 0;
	int i, j;
	int iMaxDiscriminantFunctionClassIndex = 0;
	double dblMaxDiscriminantFunctionValue = (std::numeric_limits<double>::max)();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		if (pDataSet->GetClass(0)->GetNumberOfFeaturesPerPattern() !=  pDataSet->GetClass(i)->GetNumberOfFeaturesPerPattern()){
			return;
		}
	}

	CMeanValue *FeaturesMeanValues = new CMeanValue[pDataSet->GetClass(0)->GetNumberOfFeaturesPerPattern()];
	CMinimumDistanceClassifierDiscriminantFunction *DiscriminantFunction = new CMinimumDistanceClassifierDiscriminantFunction[pDataSet->GetNumberOfClasses()];

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(0)->GetNumberOfFeaturesPerPattern();j++){
			FeaturesMeanValues[j].CalculateFeaturesMeanValue (pDataSet->GetClass(i), j);
		}
		DiscriminantFunction[i].CalculateClassDiscriminantFunctionMinimumDistance(FeaturesMeanValues, pUnknownPattern);
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
	delete [] FeaturesMeanValues;
	FeaturesMeanValues = NULL;

	SetClassifierOutput(iClassIndexRet);

}

void CMinimumDistanceClassifier::Classify (CDataSet *pDataSet, CDataSet *pUnknownPatterns){

	for (int i=0;i<pUnknownPatterns->GetNumberOfClasses();i++){
		for (int j=0;j<pUnknownPatterns->GetClass(i)->GetNumberOfPatterns();j++){
			Classify(pDataSet, pUnknownPatterns->GetClass(i)->GetPattern(j));
			pUnknownPatterns->GetTruthTable()->SetTruthTableValue(i, GetClassifierOutput(), pUnknownPatterns->GetTruthTable()->GetTruthTableValue(i, GetClassifierOutput()) + 1);
		}
	}

}

void CMinimumDistanceClassifierDiscriminantFunction::CalculateClassDiscriminantFunctionMinimumDistance (CMeanValue *pFeaturesMeanValue, CPattern *pPattern){

	int i;
	double dblRet = 0.0f;

	for (i=0;i<pPattern->GetNumberOfFeatures();i++){	
		dblRet = dblRet + (pFeaturesMeanValue[i].GetMeanValue() * pPattern->GetFeature(i)->GetFeatureValue() - 0.5f * pow(pFeaturesMeanValue[i].GetMeanValue(), 2));
	}

	SetDiscriminantFunctionValue(dblRet);

}
