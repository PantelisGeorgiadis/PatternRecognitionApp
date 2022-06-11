#if !defined(AFX_VOITOPATTERN_H__18CC479C_CF59_42EA_B9CE_BF3A571EA360__INCLUDED_)
#define AFX_VOITOPATTERN_H__18CC479C_CF59_42EA_B9CE_BF3A571EA360__INCLUDED_

#include "Pattern.h"
#include "DataMatrix3D.h"
#include "DataCoOccurrenceMatrix3D.h"
#include "DataRunLengthMatrix3D.h"

#include "Feature3DMeanFeature.h"
#include "Feature3DRangeFeature.h"

#include "Feature3DMeanValue.h"
#include "Feature3DStandardDeviation.h"
#include "Feature3DSkewness.h"
#include "Feature3DKurtosis.h"

#include "Feature2DAngularSecondMoment.h"
#include "Feature2DContrast.h"
#include "Feature2DInverseDifferenceMoment.h"
#include "Feature2DEntropy.h"
#include "Feature2DSumOfSquares.h"
#include "Feature2DSumAverage.h"
#include "Feature2DSumEntropy.h"
#include "Feature2DSumVariance.h"
#include "Feature2DDifferenceEntropy.h"
#include "Feature2DDifferenceVariance.h"
#include "Feature2DCorrelation.h"

#include "Feature2DShortRunEmphasis.h"
#include "Feature2DLongRunEmphasis.h"
#include "Feature2DGrayLevelNonUniformity.h"
#include "Feature2DRunLengthNonUniformity.h"
#include "Feature2DRunPercentage.h"

class CVOIToPattern  
{
public:
	CVOIToPattern();
	virtual ~CVOIToPattern();

	CPattern *VOIToPattern8 (CDataMatrix3D *pDataMatrix3D, int iDepth);

};

#endif 
