#include "stdafx.h"
#include "KMeans.h"

CKMeans::CKMeans()
{
	
	srand(time(0));
	m_iNumberOfClusters = 0;
	m_iNumberOfDim = 0;
	m_dblCriterion = 0.0f;
	m_iNumberOfIterations = 0;
	m_ict = INITCENTERTYPE_RANDOM;
	m_pClusterDataSet = NULL;
	m_pKMeansCallBack = NULL;

}

CKMeans::CKMeans(int k, CClass *pClass, int iNumberOfIterations, InitCenterType ict, KMeansCallBack pKMeansCallBack)
{
	
	srand(time(0));
	m_iNumberOfClusters = k;
	m_iNumberOfDim = 0;
	m_dblCriterion = 0.0f;
	m_iNumberOfIterations = iNumberOfIterations;
	m_ict = ict;
	m_pClusterDataSet = NULL;

	SetKMeansCallBackFunction(pKMeansCallBack);
	CreateClusters(k, pClass, iNumberOfIterations, ict);

}

CKMeans::~CKMeans()
{

	DeleteClusters();

}

/*
CALLBACK EXAMPLE

void KMeansCB (int iIteration, CDataSet* pDataSet){


}
*/

void CKMeans::CreateClusters(int k, CClass *pClass, int iNumberOfIterations, InitCenterType ict){
	
	CClass *ClusterCenter = NULL;

	if (k > pClass->GetNumberOfPatterns()){
		return;
	}

	m_iNumberOfClusters = k;
	m_iNumberOfDim = pClass->GetNumberOfFeaturesPerPattern();
	m_dblCriterion = 0.0;
	m_ict = ict;
	m_ClusterCenter.CreateClass(m_iNumberOfClusters, m_iNumberOfDim);
	
	GetInitialCenters(pClass, &m_ClusterCenter, ict);
	KMeans(pClass, &m_ClusterCenter, m_dblCriterion);

	if (ict == INITCENTERTYPE_RANDOM){	
		ClusterCenter = new CClass (m_iNumberOfClusters, m_iNumberOfDim);

		unsigned long nCount = 0;
		double dblCriterion = 0.0f;
		do{
			nCount++;
		
			GetInitialCenters(pClass, ClusterCenter, ict);
			KMeans(pClass, ClusterCenter, dblCriterion);
			
			if (m_pKMeansCallBack != NULL){
				m_pKMeansCallBack(nCount, GetDataSet());
			}
			
			if (dblCriterion < m_dblCriterion){
				m_dblCriterion = dblCriterion;
				CClass::CopyClass(&m_ClusterCenter, ClusterCenter);
			}
		}
		while (nCount < iNumberOfIterations);

		delete ClusterCenter;
		ClusterCenter = NULL;
	}

	m_ClusterCenter.DeleteClass();

}

void CKMeans::DeleteClusters (void){

	if (m_pClusterDataSet){
		delete m_pClusterDataSet;
		m_pClusterDataSet = NULL;
	}

}

void CKMeans::GetInitialCenters(CClass *pClass, CClass *pClusterCenter, InitCenterType ict){

	int iCenterCount = 0;
	int i, j;

	switch(ict){
		case INITCENTERTYPE_RANDOM:
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
			
			break;
		case INITCENTERTYPE_MSIA:
			double dblDistance = 0.0f;
			double dblMaxDistance = 0.0f;
			CCentroid *Centroid = new CCentroid();
			CPattern *ClassCentroid = NULL;
			CDistance *PatternDistance = new CDistance ();
			
			ClassCentroid = Centroid->CalculateClassCentroid(pClass);
			
			for (i=0;i<pClass->GetNumberOfPatterns();i++){
				PatternDistance->CalculatePatternsDistance(pClass->GetPattern(i), ClassCentroid);
				if (dblMaxDistance < PatternDistance->GetDistanceValue()){
					dblMaxDistance = PatternDistance->GetDistanceValue();
					CPattern::CopyPattern(pClusterCenter->GetPattern(0), pClass->GetPattern(i));
				}
			}

			double dblThresh = 2.0f * dblMaxDistance;
			int iCenterIndex = 0;
			
			while (iCenterCount < pClusterCenter->GetNumberOfPatterns()){
				for (i=0;i<pClass->GetNumberOfPatterns();i++){
					for (j=0;j<iCenterCount;j++){
						PatternDistance->CalculatePatternsDistance(pClass->GetPattern(i), pClusterCenter->GetPattern(j));
						if (PatternDistance->GetDistanceValue() <= dblThresh){ 
							break;
						}
					}
					if (j == iCenterCount){
						CPattern::CopyPattern(pClusterCenter->GetPattern(iCenterCount), pClass->GetPattern(i));
						iCenterCount++;
						if (iCenterCount == pClusterCenter->GetNumberOfPatterns()){
							break;
						}
					}
				}
				dblThresh *= 0.95f;
			}
			
			delete ClassCentroid;
			ClassCentroid = NULL;
			delete PatternDistance;
			PatternDistance = NULL;
			delete Centroid;
			Centroid = NULL;
			
			break;
	}		
}

void CKMeans::KMeans(CClass *pClass, CClass* pClusterCenter, double &dBlCriterion){	

	CPattern *ClassCentroid = NULL;
	bool bKeepRuning = false;
	int iTmpClusterIndex = 0;
	std::deque<unsigned short> nvClusterIndex(pClass->GetNumberOfPatterns());
	int i, j;

	CCentroid *Centroid = new CCentroid();
	CDistance *PatternDistance = new CDistance ();

	if (m_pClusterDataSet){
		delete m_pClusterDataSet;
		m_pClusterDataSet = NULL;
	}
	m_pClusterDataSet = new CDataSet();

	for (i=0;i<m_iNumberOfClusters;i++){
		m_pClusterDataSet->AddClass(pClass->GetNumberOfPatterns(), pClass->GetNumberOfFeaturesPerPattern());
	}

	do{
		bKeepRuning = false;

		for (i=0;i<m_iNumberOfClusters;i++){
			m_pClusterDataSet->GetClass(i)->RemoveAllPatterns();
		}

		for (i=0;i<pClass->GetNumberOfPatterns();i ++){
			if (nvClusterIndex[i] != (iTmpClusterIndex = FindCenterIndex(pClass->GetPattern(i), pClusterCenter))){
				nvClusterIndex[i] = iTmpClusterIndex;
				bKeepRuning = true;
			}
			m_pClusterDataSet->GetClass(iTmpClusterIndex)->AddPattern(pClass->GetPattern(i), i);
		}
		
		for (i=0;i<m_iNumberOfClusters;i++){
			if (m_pClusterDataSet->GetClass(i)->GetNumberOfPatterns() == 0){
				int iRand;
				bool bSetCenter = true;
				do{
					iRand = rand() % pClass->GetNumberOfPatterns();
					for (j=0;j<m_iNumberOfClusters;j++){
						if (EqualPatterns(pClass->GetPattern(iRand), pClusterCenter->GetPattern(j))){
							bSetCenter = false;
						}
					}
				}
				while (!bSetCenter);
				CPattern::CopyPattern(pClusterCenter->GetPattern(i), pClass->GetPattern(iRand));
			}
			else{
				ClassCentroid = Centroid->CalculateClassCentroid(m_pClusterDataSet->GetClass(i));
				CPattern::CopyPattern(pClusterCenter->GetPattern(i), ClassCentroid);
				delete ClassCentroid;
				ClassCentroid = NULL;
			}
		}
	}
	while (bKeepRuning); 

	dBlCriterion = 0.0f;
	for (i=0;i<pClass->GetNumberOfPatterns();i++){
		PatternDistance->CalculatePatternsDistance(pClass->GetPattern(i), pClusterCenter->GetPattern(nvClusterIndex[i]));
		dBlCriterion = dBlCriterion + PatternDistance->GetDistanceValue();
	}

	delete PatternDistance;
	PatternDistance = NULL;
	delete Centroid;
	Centroid = NULL;

}

bool CKMeans::EqualPatterns (CPattern *pPattern1, CPattern *pPattern2){

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

int CKMeans::FindCenterIndex(CPattern *pPattern){

	return FindCenterIndex(pPattern, &m_ClusterCenter);

}

int CKMeans::FindCenterIndex(CPattern *pPattern, CClass *pClusterCenter){

	double dblMinimun = (std::numeric_limits<double>::max)();
	int iIndex = 0;
	
	CDistance *PatternDistance = new CDistance ();
	
	for (int i=0;i<m_iNumberOfClusters;i++){
		PatternDistance->CalculatePatternsDistance(pPattern, pClusterCenter->GetPattern(i));
		if (dblMinimun > PatternDistance->GetDistanceValue()){
			dblMinimun = PatternDistance->GetDistanceValue();
			iIndex = i;
		}
	}

	delete PatternDistance;
	PatternDistance = NULL;

	return iIndex;

}
