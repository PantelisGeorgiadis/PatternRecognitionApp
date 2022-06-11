#include "stdafx.h"
#include "FuzzyCMeans.h"
#include "Trace.h"

CFuzzyCMeans::CFuzzyCMeans()
{
	srand(2000);
	m_iNumberOfIterations = 0;
	m_iNumberOfClusters = 0;
	m_dblEpsilon = 0.0f;
	m_m = 0.0f;
	m_dblSquareError = 0.0;
	m_V = NULL;
	m_U = NULL;

}

CFuzzyCMeans::~CFuzzyCMeans()
{

	DeleteClusters();

}

void CFuzzyCMeans::CreateClusters(int k, CClass *pClass, double dblEpsilon, double m){

	m_iNumberOfClusters = k;
	m_dblEpsilon = dblEpsilon;
	m_m = m;

	m_V = new CClass(m_iNumberOfClusters, pClass->GetNumberOfFeaturesPerPattern());
	m_U = new CClass(pClass->GetNumberOfPatterns(), m_iNumberOfClusters);

	for (int i=0;i<m_iNumberOfClusters;i++){
		for (int j=0;j<pClass->GetNumberOfFeaturesPerPattern();j++){
			m_V->GetPattern(i)->GetFeature(j)->SetFeatureValue(rand()*4096);
		}
	}
	//GetInitialCenters(pClass, m_V);
	UpdateUMatrix(pClass);

	FuzzyCMeans(pClass);

}

void CFuzzyCMeans::DeleteClusters (void){

	if (m_V){
		delete m_V;
		m_V = NULL;
	}

	if (m_U){
		delete m_U;
		m_U = NULL;
	}

}

void CFuzzyCMeans::FuzzyCMeans(CClass *pClass){

	m_dblSquareError = (2.0f * m_dblEpsilon);
	
	while (m_dblSquareError > m_dblEpsilon){
		m_iNumberOfIterations++;
		UpdateCentroids(pClass);
		m_dblSquareError = UpdateUMatrix(pClass);
	}

	UpdateCentroids(pClass);

	CTrace::PrintClassToConsole(m_U, "U - Matrix");
	CTrace::PrintClassToConsole(m_V, "Centroids");

}

double CFuzzyCMeans::UpdateUMatrix (CClass *pClass){

	int i, j, k;
	int iExampleCentroidIndex = 0;
	double dblSum = 0.0f;
	double dblki = 0.0f, dblkj = 0.0f;
	double dblNewUValue = 0.0f;
	double dblSquareDifference = 0.0f;

	CDistance *Distance = new CDistance();

	for (k=0;k<pClass->GetNumberOfPatterns();k++){
		if ((iExampleCentroidIndex = IsExampleCentroid(pClass, k)) != -1){
			for (i=0;i<m_iNumberOfClusters;i++){
				if (i == iExampleCentroidIndex){
					m_U->GetPattern(k)->GetFeature(i)->SetFeatureValue(1.0f);
				}
				else{
					m_U->GetPattern(k)->GetFeature(i)->SetFeatureValue(0.0f);
				}
			}
			continue;
		}

		for (i=0;i<m_iNumberOfClusters;i++){
			dblSum = 0.0f;
			for (j=0;j<m_iNumberOfClusters;j++){
				Distance->CalculatePatternsDistance(pClass->GetPattern(k), m_V->GetPattern(i));
				dblki = Distance->GetDistanceValue();
				Distance->CalculatePatternsDistance(pClass->GetPattern(k), m_V->GetPattern(j));
				dblkj = Distance->GetDistanceValue();
				dblSum += pow((dblki / dblkj), (2.0f / (m_m - 1)));
			}
			dblNewUValue = (double)(1.0f / dblSum);
			dblSquareDifference += pow((m_U->GetPattern(k)->GetFeature(i)->GetFeatureValue() - dblNewUValue), 2);
			m_U->GetPattern(k)->GetFeature(i)->SetFeatureValue(dblNewUValue);
		}
	}

	delete Distance;
	Distance = NULL;

	return dblSquareDifference;

}

// Given a membership matrix U, recalculate the cluster centroids as the
// "weighted" mean of each contributing example from the dataset. Each
// example contributes by an amount proportional to the membership value.

void CFuzzyCMeans::UpdateCentroids (CClass *pClass){

	int i, j, k;
	
	double *dblNumerator = new double[pClass->GetNumberOfFeaturesPerPattern()];
	double *dblDenominator = new double[pClass->GetNumberOfFeaturesPerPattern()];

	for (i=0;i<m_iNumberOfClusters;i++){
		for (j=0;j<pClass->GetNumberOfFeaturesPerPattern();j++){
		  dblNumerator[j] = 0.0f;
		  dblDenominator[j] = 0.0f;
		}

		for (k=0;k<pClass->GetNumberOfPatterns();k++){
			for (j=0;j<pClass->GetNumberOfFeaturesPerPattern();j++){ 
				dblNumerator[j] += pow(m_U->GetPattern(k)->GetFeature(i)->GetFeatureValue(), m_m) * pClass->GetPattern(k)->GetFeature(j)->GetFeatureValue();
			}
		}
    
		for (k=0;k<pClass->GetNumberOfPatterns();k++){
			for (j=0;j<pClass->GetNumberOfFeaturesPerPattern();j++){ 
				dblDenominator[j] += pow(m_U->GetPattern(k)->GetFeature(i)->GetFeatureValue(), m_m);
			}
		}
    
		for (j=0;j<pClass->GetNumberOfFeaturesPerPattern();j++){ 
			m_V->GetPattern(i)->GetFeature(j)->SetFeatureValue((dblNumerator[j] / dblDenominator[j]));
		}

	}

	delete [] dblNumerator;
	dblNumerator = NULL;
	delete [] dblDenominator;
	dblDenominator = NULL;

}

int CFuzzyCMeans::IsExampleCentroid(CClass *pClass, int k){
	
	int i, j;
	
	for (i=0;i<m_iNumberOfClusters;i++){
		for (j=0;j<pClass->GetNumberOfFeaturesPerPattern();j++){
			if (pClass->GetPattern(k)->GetFeature(j)->GetFeatureValue() != m_V->GetPattern(i)->GetFeature(j)->GetFeatureValue()){
				break;
			}
		}
		if (j == pClass->GetNumberOfFeaturesPerPattern()){  
			return i;
		}
	}

	return -1;

}

void CFuzzyCMeans::GetInitialCenters(CClass *pClass, CClass *pClusterCenter){

	int iCenterCount = 0;
	int i;

	do{
		bool bSetCenter = true;
		int iRand = rand() % pClass->GetNumberOfPatterns();
		for (i=0;i<iCenterCount;i++){
			if (EqualPatterns(pClass->GetPattern(iRand), pClusterCenter->GetPattern(i))){
				bSetCenter = false;
			}
		}
		if (bSetCenter){
			CPattern::CopyPattern(pClusterCenter->GetPattern(i), pClass->GetPattern(iRand));
			iCenterCount++;
		}
	}
	while (iCenterCount < pClusterCenter->GetNumberOfPatterns());
		
}

bool CFuzzyCMeans::EqualPatterns (CPattern *pPattern1, CPattern *pPattern2){

	if (pPattern1->GetNumberOfFeatures() != pPattern2->GetNumberOfFeatures()){
		return false;
	}
	
	for (int i=0;i<pPattern1->GetNumberOfFeatures();i++){
		if (pPattern1->GetFeature(i)->GetFeatureValue() != pPattern2->GetFeature(i)->GetFeatureValue()){
			return false;
		}
	}

	return true;

}

