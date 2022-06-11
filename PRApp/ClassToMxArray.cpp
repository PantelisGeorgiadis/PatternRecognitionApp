#include "stdafx.h"
#include "ClassToMxArray.h"

#ifdef USE_MATLAB_ENGINE

CClassToMxArray::CClassToMxArray()
{

}

CClassToMxArray::~CClassToMxArray()
{

}

mxArray *CClassToMxArray::ClassToMxArray(CClass *pClass){

	mxArray *Array = NULL;
	Array = mxCreateDoubleMatrix(pClass->GetNumberOfPatterns(), pClass->GetNumberOfFeaturesPerPattern(), mxREAL);
	
	for (int i=0;i<pClass->GetNumberOfPatterns();i++){
		for (int j=0;j<pClass->GetNumberOfFeaturesPerPattern();j++){
			mxGetPr(Array)[(i * pClass->GetNumberOfFeaturesPerPattern()) + j] = pClass->GetPattern(i)->GetFeature(j)->GetFeatureValue();
		}
	}
	
	return Array;

}

CClass *CClassToMxArray::MxArrayToClass(mxArray *Array){

	CClass *pClass = new CClass(mxGetM(Array), mxGetN(Array));
	
	for (int i=0;i<pClass->GetNumberOfPatterns();i++){
		for (int j=0;j<pClass->GetNumberOfFeaturesPerPattern();j++){
			pClass->GetPattern(i)->GetFeature(j)->SetFeatureValue(mxGetPr(Array)[(i * pClass->GetNumberOfFeaturesPerPattern()) + j]);
		}
	}
	
	return pClass;

}

#endif
