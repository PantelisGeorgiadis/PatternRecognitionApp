#if !defined(AFX_KNEARESTNEIGHBORCLASSIFIER_H__87695C22_129F_45D9_B242_28146BED9DA5__INCLUDED_)
#define AFX_KNEARESTNEIGHBORCLASSIFIER_H__87695C22_129F_45D9_B242_28146BED9DA5__INCLUDED_

#include "Classifier.h"
#include "DataSet.h"
#include "Distance.h"
#include "DistanceSort.h"

class CKNearestNeighborClassifier : public CClassifier
{
public:
	CKNearestNeighborClassifier();
	virtual ~CKNearestNeighborClassifier();

	void ClassifyAverage (CDataSet *pDataSet, CPattern *pUnknownPattern, int k);
	void ClassifyMajorityVote (CDataSet *pDataSet, CPattern *pUnknownPattern, int k);

	void ClassifyAverage (CDataSet *pDataSet, CDataSet *pUnknownPatterns, int k);
	void ClassifyMajorityVote (CDataSet *pDataSet, CDataSet *pUnknownPattern, int k);

};

#endif 
