#if !defined(AFX_SHUFFLEDATASET_H__57D4EE94_E4B9_4630_9CE6_9C3862680160__INCLUDED_)
#define AFX_SHUFFLEDATASET_H__57D4EE94_E4B9_4630_9CE6_9C3862680160__INCLUDED_

#include <time.h>
#include <cmath>
#include "DataSet.h"
#include "MersenneTwister.h"

class CShuffleDataSet  
{
public:
	CShuffleDataSet();
	virtual ~CShuffleDataSet();

	CDataSet *ShuffleDataSet (CDataSet *pDataSet, int iShuffleIterations);
	CClass *ShuffleClass (CClass *pClass, int iShuffleIterations);

protected:

	void CopyPattern (CPattern *pPatternDest, CPattern *pPatternSrc);

};

#endif 
