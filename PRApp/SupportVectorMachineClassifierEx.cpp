#include "stdafx.h"
#include "SupportVectorMachineClassifierEx.h"

CSupportVectorMachineClassifierEx::CSupportVectorMachineClassifierEx()
{

	m_svmi.svmkt = SVMKERNELTYPE_LINEAR;
	m_svmi.dblGaussianSigma = 0.0f;
	m_svmi.iPolynomialDegree = 0;
	m_svmi.dblSigmoidC = 0.0f;
	m_svmi.dblSigmoidV = 1.0f;
	m_svmi.dblGammaEx = 0.0f;
	m_svmi.dblCoef0Ex = 0.0f;
	m_svmi.dblTolerance = 0.001;
	m_svmi.dblC = 1.0f; 
	m_svmi.dblCostEx = 0.0f;

}

CSupportVectorMachineClassifierEx::CSupportVectorMachineClassifierEx(SVMINFO *svmi)
{

	SetSupportVectorMachineInfo(svmi);

}

CSupportVectorMachineClassifierEx::~CSupportVectorMachineClassifierEx()
{

}

void CSupportVectorMachineClassifierEx::SetSupportVectorMachineInfo (SVMINFO *svmi){

	m_svmi.svmkt = svmi->svmkt;
	m_svmi.dblGaussianSigma = svmi->dblGaussianSigma;
	m_svmi.iPolynomialDegree = svmi->iPolynomialDegree;
	m_svmi.dblSigmoidC = svmi->dblSigmoidC;
	m_svmi.dblSigmoidV = svmi->dblSigmoidV;
	m_svmi.dblGammaEx = svmi->dblGammaEx;
	m_svmi.dblCoef0Ex = svmi->dblCoef0Ex;
	m_svmi.dblTolerance = svmi->dblTolerance;
	m_svmi.dblC = svmi->dblC;
	m_svmi.dblCostEx = svmi->dblCostEx;

}

void CSupportVectorMachineClassifierEx::LabelDataSet (CDataSet *pDataSet){

	for (int i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (int j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			pDataSet->GetClass(i)->GetPattern(j)->SetReservedValue(i + 1);
		}
	}

}

void CSupportVectorMachineClassifierEx::Classify (CDataSet *pDataSet, CPattern *pUnknownPattern){

	int i, j;
	int iPatternSum = 0;
	SVMPARAMETER svmparam;

	svmparam.iSVMType = C_SVC;
	
	switch (m_svmi.svmkt){
		case SVMKERNELTYPE_LINEAR:
			svmparam.iKernelType = LINEAR;
			break;
		case SVMKERNELTYPE_POLYNOMIAL:
			svmparam.iKernelType = POLY;
			break;
		case SVMKERNELTYPE_RBF:
			svmparam.iKernelType = RBF;
			break;
		case SVMKERNELTYPE_SIGMOID:
			svmparam.iKernelType = SIGMOID;
			break;
	}
	
	svmparam.iDegree = m_svmi.iPolynomialDegree;
	svmparam.dblGamma = m_svmi.dblGammaEx;
	svmparam.dblCoef0 = m_svmi.dblCoef0Ex;
	svmparam.dblC = m_svmi.dblCostEx;				// Cost (100)
	svmparam.dblEps = m_svmi.dblTolerance;			// Epsilon (1e-3)
	svmparam.dblNU = 0.5;
	svmparam.dblCacheSize = 100;
	svmparam.dblp = 0.1;
	svmparam.iShrinking = 1;
	svmparam.iProbability = 0;
	svmparam.iNRWeight = 0;
	svmparam.iWeightLabel = NULL;
	svmparam.dblWeight = NULL;

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			iPatternSum++;
		}
	}

	SVMPROBLEM svmproblem;
	svmproblem.l = iPatternSum;
	svmproblem.y = new double[svmproblem.l];

	CClass *pCombinedClass = pDataSet->MergeDataSet();
	int iNumberOfFeatures = pCombinedClass->GetNumberOfFeaturesPerPattern();
	int iIterationHelper = iNumberOfFeatures + 1;
	int iIndexHelper = 0;

	SVMNODE *pTrainingNodes = new SVMNODE[iIterationHelper * svmproblem.l];
	svmproblem.x = new SVMNODE * [svmproblem.l];

	for (i=0;i<pCombinedClass->GetNumberOfPatterns();i++){
		iIndexHelper = 0;
		for (j=0;j<pCombinedClass->GetPattern(i)->GetNumberOfFeatures();j++){
			iIndexHelper++;
			pTrainingNodes[(iIterationHelper * i) + j].iIndex = iIndexHelper;
			pTrainingNodes[(iIterationHelper * i) + j].dblValue = pCombinedClass->GetPattern(i)->GetFeature(j)->GetFeatureValue();
		}
		pTrainingNodes[(iIterationHelper * i) + j].iIndex = -1;
		svmproblem.x[i] = &pTrainingNodes[iIterationHelper * i];
		svmproblem.y[i] = pCombinedClass->GetPattern(i)->GetReservedValue();
	}

	SVMMODEL *svmmodel = svm_train(&svmproblem, &svmparam);

	SVMNODE *pUnknownNode = new SVMNODE[iIterationHelper];
	iIndexHelper = 0;
	for (i=0;i<pUnknownPattern->GetNumberOfFeatures();i++){
		iIndexHelper++;
		pUnknownNode[i].iIndex = iIndexHelper;
		pUnknownNode[i].dblValue = pUnknownPattern->GetFeature(i)->GetFeatureValue();
	}
	pUnknownNode[i].iIndex = -1;

	double dblLabel = svm_predict(svmmodel, pUnknownNode);

	svm_destroy_model(svmmodel);

	delete [] pUnknownNode;
	pUnknownNode = NULL;
	delete [] pTrainingNodes;
	pTrainingNodes = NULL;
	delete pCombinedClass;
	pCombinedClass = NULL;
	delete [] svmproblem.x;
	svmproblem.x = NULL;
	delete [] svmproblem.y;
	svmproblem.y = NULL;

	SetClassifierOutput((int)(dblLabel));

}

void CSupportVectorMachineClassifierEx::Classify (CDataSet *pDataSet, CDataSet *pUnknownPatterns){

	for (int i=0;i<pUnknownPatterns->GetNumberOfClasses();i++){
		for (int j=0;j<pUnknownPatterns->GetClass(i)->GetNumberOfPatterns();j++){
			Classify(pDataSet, pUnknownPatterns->GetClass(i)->GetPattern(j));
			pUnknownPatterns->GetTruthTable()->SetTruthTableValue(i, (GetClassifierOutput() - 1), pUnknownPatterns->GetTruthTable()->GetTruthTableValue(i, (GetClassifierOutput() - 1)) + 1);
		}
	}

}
