#if !defined(AFX_ROITOPATTERN_H__3ACF13A6_B247_41C6_9043_96541F277477__INCLUDED_)
#define AFX_ROITOPATTERN_H__3ACF13A6_B247_41C6_9043_96541F277477__INCLUDED_

#include "Pattern.h"
#include "DataMatrix2D.h"
#include "DataCoOccurrenceMatrix2D.h"
#include "DataRunLengthMatrix2D.h"

#include "Feature2DMeanFeature.h"
#include "Feature2DRangeFeature.h"

#include "Feature2DMeanValue.h"
#include "Feature2DStandardDeviation.h"
#include "Feature2DSkewness.h"
#include "Feature2DKurtosis.h"

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

#define NUMBEROFFEATURES_FIRSTORDER			4
#define NUMBEROFFEATURES_COOCCURRENCE_MEAN	11
#define NUMBEROFFEATURES_COOCCURRENCE_RANGE	11
#define NUMBEROFFEATURES_COOCCURRENCE		NUMBEROFFEATURES_COOCCURRENCE_MEAN + NUMBEROFFEATURES_COOCCURRENCE_RANGE
#define NUMBEROFFEATURES_RUNLENGTH_MEAN		5
#define NUMBEROFFEATURES_RUNLENGTH_RANGE	5
#define NUMBEROFFEATURES_RUNLENGTH			NUMBEROFFEATURES_RUNLENGTH_MEAN + NUMBEROFFEATURES_RUNLENGTH_RANGE
#define NUMBEROFFEATURES					NUMBEROFFEATURES_FIRSTORDER + NUMBEROFFEATURES_COOCCURRENCE + NUMBEROFFEATURES_RUNLENGTH

class CROIToPattern  
{
public:
	CROIToPattern();
	virtual ~CROIToPattern();

	CPattern *ROIToPattern8 (CDataMatrix2D *pDataMatrix2D, int iDepth);
	CPattern *ROIToPattern8 (unsigned char *pu8Data, int iWidth, int iHeight, int iDepth);
	static void GetFeatureName (int iFeatureIndex, char *szFeatureName);
	static void GetFeatureShortName (int iFeatureIndex, char *szFeatureShortName);

};

#endif 
