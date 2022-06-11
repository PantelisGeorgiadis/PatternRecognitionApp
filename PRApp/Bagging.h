#if !defined(AFX_BAGGING_H__21389521_7589_4CD1_9C4C_0194F207EFBC__INCLUDED_)
#define AFX_BAGGING_H__21389521_7589_4CD1_9C4C_0194F207EFBC__INCLUDED_

#include <time.h>
#include "DataSet.h"
#include "MersenneTwister.h"

class CBagging  
{
public:
	CBagging();
	virtual ~CBagging();

	CDataSet *BaggDataSet (CDataSet *pDataSet, int iNumberOfReplicates);

};

#endif 
