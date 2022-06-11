#if !defined(AFX_KMEANS_H__8B1A04F3_80D5_4F91_BD51_18D01239739D__INCLUDED_)
#define AFX_KMEANS_H__8B1A04F3_80D5_4F91_BD51_18D01239739D__INCLUDED_

#include <time.h>
#include <limits>
#include <deque>
#include "DataSet.h"
#include "Distance.h"
#include "Centroid.h"

enum InitCenterType {INITCENTERTYPE_RANDOM, INITCENTERTYPE_MSIA};

typedef void (*KMeansCallBack)(int, CDataSet*);

class CKMeans  
{
public:
	CKMeans();
	CKMeans(int k, CClass *pClass, int iNumberOfIterations, InitCenterType ict = INITCENTERTYPE_RANDOM, KMeansCallBack pKMeansCallBack = NULL);
	virtual ~CKMeans();

	void CreateClusters(int k, CClass *pClass, int iNumberOfIterations, InitCenterType ict = INITCENTERTYPE_RANDOM);
	void DeleteClusters (void);
	void GetInitialCenters(CClass *pClass, CClass *pClusterCenter, InitCenterType ict = INITCENTERTYPE_RANDOM);
	void KMeans(CClass *pClass, CClass* pClusterCenter, double &dBlCriterion);
	CDataSet *GetDataSet (void) { return m_pClusterDataSet; }
	void SetKMeansCallBackFunction (KMeansCallBack pKMeansCallBack) { m_pKMeansCallBack = pKMeansCallBack; }

protected:

	double			m_dblCriterion;		
	CClass			m_ClusterCenter;
	CDataSet		*m_pClusterDataSet;
	int				m_iNumberOfClusters;		
	int				m_iNumberOfDim;	
	int				m_iNumberOfIterations;
	InitCenterType	m_ict;	
	KMeansCallBack	m_pKMeansCallBack;

	bool EqualPatterns (CPattern *pPattern1, CPattern *pPattern2);
	int FindCenterIndex(CPattern *pPattern);
	int FindCenterIndex(CPattern *pPattern, CClass *pClusterCenter);

};

#endif 
