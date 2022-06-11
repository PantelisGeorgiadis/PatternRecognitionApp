#if !defined(AFX_CENTROID_H__27D2C6C4_41A4_4C0F_A9B2_961CD0292280__INCLUDED_)
#define AFX_CENTROID_H__27D2C6C4_41A4_4C0F_A9B2_961CD0292280__INCLUDED_

#include "Class.h"
#include "MeanValue.h"

enum CentroidType  {CENTROID_MEAN};

class CCentroid  
{
public:
	CCentroid();
	virtual ~CCentroid();

	CPattern *CalculateClassCentroid (CClass *pClass, CentroidType ct = CENTROID_MEAN);

};

#endif 
