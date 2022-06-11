#if !defined(AFX_LEASTSQUARESMAPPING_H__103AFED0_1472_4975_A511_F62AFEF11381__INCLUDED_)
#define AFX_LEASTSQUARESMAPPING_H__103AFED0_1472_4975_A511_F62AFEF11381__INCLUDED_

#include <cmath>
#include "DataSet.h"
#include "ExhaustiveSearch.h"
#include "ClassToDataMatrix.h"

#ifdef USE_MATLAB_ENGINE
#include "MatlabEngine.h"
#include "DataMatrixToMxArray.h"
#include "ClassToMxArray.h"
//#define USE_MATLAB_INVERSE
#endif

class CLeastSquaresMapping : public CExhaustiveSearch
{
public:
	CLeastSquaresMapping();
	virtual ~CLeastSquaresMapping();

	CDataSet *LeastSquaresMapping (CDataSet *pDataSet, int iOrder, CPattern *pClusteringPoints, int iClusteringPointsSize);

protected:

#ifdef USE_MATLAB_INVERSE
	CMatlabEngine *m_MatlabEngine;
#endif

	CPattern *CalculateFeatures (CPattern *pPattern);
	void MapPattern (CPattern *pPattern, CPattern *pMappedPattern, int iOrder);
	CDataMatrix2D *PatternToDataMatrixTransposeMultiplication (CPattern *pClassClusteringPoint, CPattern *pPattern);
	CDataMatrix2D *AugmentedPatternToDataMatrixTransposeMultiplication (CPattern *pAugmentedPattern);

};

#endif
