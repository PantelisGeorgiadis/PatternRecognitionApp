#if !defined(AFX_FUZZYCMEANS_H__77BDABCA_9080_4451_9A5F_DC713C4ACC08__INCLUDED_)
#define AFX_FUZZYCMEANS_H__77BDABCA_9080_4451_9A5F_DC713C4ACC08__INCLUDED_

#include "Class.h"
#include "DataMatrix2D.h"
#include "Distance.h"

class CFuzzyCMeans  
{
public:
	CFuzzyCMeans();
	virtual ~CFuzzyCMeans();

	void CreateClusters(int k, CClass *pClass, double dblEpsilon, double m);
	void DeleteClusters (void);

	int GetNumberOfIterations (void) { return m_iNumberOfIterations; }

protected:

	int m_iNumberOfIterations;
	int m_iNumberOfClusters;
	double m_dblEpsilon;
	double m_m;
	double m_dblSquareError;

	CClass *m_V; // Centroids
	CClass *m_U; // U - Matrix (membership);

	void FuzzyCMeans(CClass *pClass);
	double UpdateUMatrix (CClass *pClass);
	void UpdateCentroids (CClass *pClass);
	int IsExampleCentroid(CClass *pClass, int k);
	void GetInitialCenters(CClass *pClass, CClass *pClusterCenter);
	bool EqualPatterns (CPattern *pPattern1, CPattern *pPattern2);

};

#endif 
