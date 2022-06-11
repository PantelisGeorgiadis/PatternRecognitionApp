#include "stdafx.h"
#include "ROIToPattern.h"

char FeatureNameStrings[][50] = {
	"Mean Value",
	"Standard Deviation",
	"Skewness",
	"Kurtosis",
	"Angular Second Moment (Mean)",
	"Contrast (Mean)",
	"Correlation (Mean)",
	"Sum Of Squares (Mean)",
	"Inverse Difference Moment (Mean)",
	"Sum Average (Mean)",
	"Sum Variance (Mean)",
	"Sum Entropy (Mean)",
	"Entropy (Mean)",
	"Difference Variance (Mean)",
	"Difference Entropy (Mean)",
//	"Information Measure Of Correlation 1 (Mean)",
//	"Information Measure Of Correlation 2 (Mean)",
	"Angular Second Moment (Range)",
	"Contrast (Range)",
	"Correlation (Range)",
	"Sum Of Squares (Range)",
	"Inverse Difference Moment (Range)",
	"Sum Average (Range)",
	"Sum Variance (Range)",
	"Sum Entropy (Range)",
	"Entropy (Range)",
	"Difference Variance (Range)",
	"Difference Entropy (Range)",
//	"Information Measure Of Correlation 1 (Range)",
//	"Information Measure Of Correlation 2 (Range)",
	"Short Run Emphasis (Mean)", 
	"Long Run Emphasis (Mean)", 
	"Gray Level Non Uniformity (Mean)",
	"Run Length Non Uniformity (Mean)",
	"Run Percentage (Mean)",
	"Short Run Emphasis (Range)", 
	"Long Run Emphasis (Range)", 
	"Gray Level Non Uniformity (Range)",
	"Run Length Non Uniformity (Range)",
	"Run Percentage (Range)"
};

char FeatureShortNameStrings[][50] = {
	"Mean Value",			// 0
	"Standard Deviation",	// 1
	"Skewness",				// 2
	"Kurtosis",				// 3
	"ASM (Mean)",			// 4
	"CON (Mean)",			// 5
	"COR (Mean)",			// 6
	"SSQ (Mean)",			// 7
	"IDM (Mean)",			// 8
	"SAVE (Mean)",			// 9
	"SVAR (Mean)",			// 10
	"SENT (Mean)",			// 11
	"ENT (Mean)",			// 12
	"DVAR (Mean)",			// 13
	"DENT (Mean)",			// 14
//	"ICM1 (Mean)",
//	"ICM2 (Mean)",
	"ASM (Range)",			// 15
	"CON (Range)",			// 16
	"COR (Range)",			// 17
	"SSQ (Range)",			// 18
	"IDM (Range)",			// 19
	"SAVE (Range)",			// 20
	"SVAR (Range)",			// 21
	"SENT (Range)",			// 22
	"ENT (Range)",			// 23
	"DVAR (Range)",			// 24
	"DENT (Range)",			// 25
//	"ICM1 (Range)",
//	"ICM2 (Range)",
	"SRE (Mean)",			// 26
	"LRE (Mean)",			// 27
	"GLNU (Mean)",			// 28
	"RLNU (Mean)",			// 29
	"RP (Mean)",			// 30
	"SRE (Range)",			// 31
	"LRE (Range)",			// 32
	"GLNU (Range)",			// 33
	"RLNU (Range)",			// 34
	"RP (Range)"			// 35
};



CROIToPattern::CROIToPattern()
{

}

CROIToPattern::~CROIToPattern()
{

}

CPattern *CROIToPattern::ROIToPattern8 (CDataMatrix2D *pDataMatrix2D, int iDepth){

	CPattern *Pattern = NULL;
	unsigned char *pu8Data = new unsigned char [pDataMatrix2D->GetNumberOfRows() * pDataMatrix2D->GetNumberOfColumns()];

	for (int i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		for (int j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			pu8Data[(i * pDataMatrix2D->GetNumberOfColumns()) + j] = (unsigned char)(pDataMatrix2D->GetMatrixValue(i, j));
		}
	}

	Pattern = ROIToPattern8(pu8Data, pDataMatrix2D->GetNumberOfColumns(), pDataMatrix2D->GetNumberOfRows(), iDepth);
	
	delete [] pu8Data;
	pu8Data = NULL;

	return Pattern;

}

CPattern *CROIToPattern::ROIToPattern8 (unsigned char *pu8Data, int iWidth, int iHeight, int iDepth){

	CFeature *Feature = new CFeature();
	CPattern *Pattern = new CPattern(1);
	Pattern->RemoveAllFeatures();
	CDataMatrix2D *ROIDataMatrix = new CDataMatrix2D(iHeight, iWidth);

	CFeature2DMeanFeature *MeanFeature = new CFeature2DMeanFeature();
	CFeature2DRangeFeature *RangeFeature = new CFeature2DRangeFeature();

	for (int i=0;i<ROIDataMatrix->GetNumberOfRows();i++){
		for (int j=0;j<ROIDataMatrix->GetNumberOfColumns();j++){
			ROIDataMatrix->SetMatrixValue(i, j, *((unsigned char*)pu8Data + i * ROIDataMatrix->GetNumberOfColumns() + j));
		}
	}

	// First-Order Statistical Features
	CFeature2DMeanValue *MeanValue = new CFeature2DMeanValue();
	MeanValue->CalculateMeanValue(ROIDataMatrix);

	CFeature2DStandardDeviation *StandardDeviation = new CFeature2DStandardDeviation();
	StandardDeviation->CalculateStandardDeviation(ROIDataMatrix);

	CFeature2DSkewness *Skewness = new CFeature2DSkewness();
	Skewness->CalculateSkewness(ROIDataMatrix);
	
	CFeature2DKurtosis *Kurtosis = new CFeature2DKurtosis();
	Kurtosis->CalculateKurtosis(ROIDataMatrix);
	
	// Co-occurrence based features
	CDataMatrix2D *ROICoOccurrenceMatrix0 = NULL;
	CDataMatrix2D *ROICoOccurrenceMatrix45 = NULL;
	CDataMatrix2D *ROICoOccurrenceMatrix90 = NULL;
	CDataMatrix2D *ROICoOccurrenceMatrix135 = NULL;

	CDataMatrix2D *ROICoOccurrenceMatrixNormalized0 = NULL;
	CDataMatrix2D *ROICoOccurrenceMatrixNormalized45 = NULL;
	CDataMatrix2D *ROICoOccurrenceMatrixNormalized90 = NULL;
	CDataMatrix2D *ROICoOccurrenceMatrixNormalized135 = NULL;

	CDataMatrix2D *ROIDataMatrix0 = NULL;
	CDataMatrix2D *ROIDataMatrix45 = NULL;
	CDataMatrix2D *ROIDataMatrix90 = NULL;
	CDataMatrix2D *ROIDataMatrix135 = NULL;

	ROIDataMatrix0 = ROIDataMatrix->RotateMatrix(DEGREES_0);
	ROIDataMatrix45 = ROIDataMatrix->RotateMatrix(DEGREES_45);
	ROIDataMatrix90 = ROIDataMatrix->RotateMatrix(DEGREES_90);
	ROIDataMatrix135 = ROIDataMatrix->RotateMatrix(DEGREES_135);

	CDataCoOccurrenceMatrix2D *CoOccurrenceMatrix0 = new CDataCoOccurrenceMatrix2D(ROIDataMatrix0, iDepth, DEGREES_0);
	ROICoOccurrenceMatrix0 = CoOccurrenceMatrix0->CopyCoOccurrenceDataMatrixToDataMatrix2D();
	ROICoOccurrenceMatrixNormalized0 = ROICoOccurrenceMatrix0->NormalizeSum();
	
	CDataCoOccurrenceMatrix2D *CoOccurrenceMatrix45 = new CDataCoOccurrenceMatrix2D(ROIDataMatrix45, iDepth, DEGREES_45);
	ROICoOccurrenceMatrix45 = CoOccurrenceMatrix45->CopyCoOccurrenceDataMatrixToDataMatrix2D();
	ROICoOccurrenceMatrixNormalized45 = ROICoOccurrenceMatrix45->NormalizeSum();
	
	CDataCoOccurrenceMatrix2D *CoOccurrenceMatrix90 = new CDataCoOccurrenceMatrix2D(ROIDataMatrix90, iDepth, DEGREES_90);
	ROICoOccurrenceMatrix90 = CoOccurrenceMatrix90->CopyCoOccurrenceDataMatrixToDataMatrix2D();
	ROICoOccurrenceMatrixNormalized90 = ROICoOccurrenceMatrix90->NormalizeSum();

	CDataCoOccurrenceMatrix2D *CoOccurrenceMatrix135 = new CDataCoOccurrenceMatrix2D(ROIDataMatrix135, iDepth, DEGREES_135);
	ROICoOccurrenceMatrix135 = CoOccurrenceMatrix135->CopyCoOccurrenceDataMatrixToDataMatrix2D();
	ROICoOccurrenceMatrixNormalized135 = ROICoOccurrenceMatrix135->NormalizeSum();


	CFeature2DAngularSecondMoment *AngularSecondMoment0 = new CFeature2DAngularSecondMoment();
	AngularSecondMoment0->CalculateAngularSecondMoment(ROICoOccurrenceMatrixNormalized0);
	CFeature2DAngularSecondMoment *AngularSecondMoment45 = new CFeature2DAngularSecondMoment();
	AngularSecondMoment45->CalculateAngularSecondMoment(ROICoOccurrenceMatrixNormalized45);
	CFeature2DAngularSecondMoment *AngularSecondMoment90 = new CFeature2DAngularSecondMoment();
	AngularSecondMoment90->CalculateAngularSecondMoment(ROICoOccurrenceMatrixNormalized90);
	CFeature2DAngularSecondMoment *AngularSecondMoment135 = new CFeature2DAngularSecondMoment();
	AngularSecondMoment135->CalculateAngularSecondMoment(ROICoOccurrenceMatrixNormalized135);

	CFeature2DContrast *Contrast0 = new CFeature2DContrast();
	Contrast0->CalculateContrast(ROICoOccurrenceMatrixNormalized0);
	CFeature2DContrast *Contrast45 = new CFeature2DContrast();
	Contrast45->CalculateContrast(ROICoOccurrenceMatrixNormalized45);
	CFeature2DContrast *Contrast90 = new CFeature2DContrast();
	Contrast90->CalculateContrast(ROICoOccurrenceMatrixNormalized90);
	CFeature2DContrast *Contrast135 = new CFeature2DContrast();
	Contrast135->CalculateContrast(ROICoOccurrenceMatrixNormalized135);

	CFeature2DCorrelation *Correlation0 = new CFeature2DCorrelation();
	Correlation0->CalculateCorrelation(ROICoOccurrenceMatrixNormalized0);
	CFeature2DCorrelation *Correlation45 = new CFeature2DCorrelation();
	Correlation45->CalculateCorrelation(ROICoOccurrenceMatrixNormalized45);
	CFeature2DCorrelation *Correlation90 = new CFeature2DCorrelation();
	Correlation90->CalculateCorrelation(ROICoOccurrenceMatrixNormalized90);
	CFeature2DCorrelation *Correlation135 = new CFeature2DCorrelation();
	Correlation135->CalculateCorrelation(ROICoOccurrenceMatrixNormalized135);

	CFeature2DSumOfSquares *SumOfSquares0 = new CFeature2DSumOfSquares();
	SumOfSquares0->CalculateSumOfSquares(ROICoOccurrenceMatrixNormalized0);
	CFeature2DSumOfSquares *SumOfSquares45 = new CFeature2DSumOfSquares();
	SumOfSquares45->CalculateSumOfSquares(ROICoOccurrenceMatrixNormalized45);
	CFeature2DSumOfSquares *SumOfSquares90 = new CFeature2DSumOfSquares();
	SumOfSquares90->CalculateSumOfSquares(ROICoOccurrenceMatrixNormalized90);
	CFeature2DSumOfSquares *SumOfSquares135 = new CFeature2DSumOfSquares();
	SumOfSquares135->CalculateSumOfSquares(ROICoOccurrenceMatrixNormalized135);

	CFeature2DInverseDifferenceMoment *InverseDifferenceMoment0 = new CFeature2DInverseDifferenceMoment();
	InverseDifferenceMoment0->CalculateInverseDifferenceMoment(ROICoOccurrenceMatrixNormalized0);
	CFeature2DInverseDifferenceMoment *InverseDifferenceMoment45 = new CFeature2DInverseDifferenceMoment();
	InverseDifferenceMoment45->CalculateInverseDifferenceMoment(ROICoOccurrenceMatrixNormalized45);
	CFeature2DInverseDifferenceMoment *InverseDifferenceMoment90 = new CFeature2DInverseDifferenceMoment();
	InverseDifferenceMoment90->CalculateInverseDifferenceMoment(ROICoOccurrenceMatrixNormalized90);
	CFeature2DInverseDifferenceMoment *InverseDifferenceMoment135 = new CFeature2DInverseDifferenceMoment();
	InverseDifferenceMoment135->CalculateInverseDifferenceMoment(ROICoOccurrenceMatrixNormalized135);

	CFeature2DSumAverage *SumAverage0 = new CFeature2DSumAverage();
	SumAverage0->CalculateSumAverage(ROICoOccurrenceMatrixNormalized0);
	CFeature2DSumAverage *SumAverage45 = new CFeature2DSumAverage();
	SumAverage45->CalculateSumAverage(ROICoOccurrenceMatrixNormalized45);
	CFeature2DSumAverage *SumAverage90 = new CFeature2DSumAverage();
	SumAverage90->CalculateSumAverage(ROICoOccurrenceMatrixNormalized90);
	CFeature2DSumAverage *SumAverage135 = new CFeature2DSumAverage();
	SumAverage135->CalculateSumAverage(ROICoOccurrenceMatrixNormalized135);

	CFeature2DSumVariance *SumVariance0 = new CFeature2DSumVariance();
	SumVariance0->CalculateSumVariance(ROICoOccurrenceMatrixNormalized0);
	CFeature2DSumVariance *SumVariance45 = new CFeature2DSumVariance();
	SumVariance45->CalculateSumVariance(ROICoOccurrenceMatrixNormalized45);
	CFeature2DSumVariance *SumVariance90 = new CFeature2DSumVariance();
	SumVariance90->CalculateSumVariance(ROICoOccurrenceMatrixNormalized90);
	CFeature2DSumVariance *SumVariance135 = new CFeature2DSumVariance();
	SumVariance135->CalculateSumVariance(ROICoOccurrenceMatrixNormalized135);

	CFeature2DSumEntropy *SumEntropy0 = new CFeature2DSumEntropy();
	SumEntropy0->CalculateSumEntropy(ROICoOccurrenceMatrixNormalized0);
	CFeature2DSumEntropy *SumEntropy45 = new CFeature2DSumEntropy();
	SumEntropy45->CalculateSumEntropy(ROICoOccurrenceMatrixNormalized45);
	CFeature2DSumEntropy *SumEntropy90 = new CFeature2DSumEntropy();
	SumEntropy90->CalculateSumEntropy(ROICoOccurrenceMatrixNormalized90);
	CFeature2DSumEntropy *SumEntropy135 = new CFeature2DSumEntropy();
	SumEntropy135->CalculateSumEntropy(ROICoOccurrenceMatrixNormalized135);

	CFeature2DEntropy *Entropy0 = new CFeature2DEntropy();
	Entropy0->CalculateEntropy(ROICoOccurrenceMatrixNormalized0);
	CFeature2DEntropy *Entropy45 = new CFeature2DEntropy();
	Entropy45->CalculateEntropy(ROICoOccurrenceMatrixNormalized45);
	CFeature2DEntropy *Entropy90 = new CFeature2DEntropy();
	Entropy90->CalculateEntropy(ROICoOccurrenceMatrixNormalized90);
	CFeature2DEntropy *Entropy135 = new CFeature2DEntropy();
	Entropy135->CalculateEntropy(ROICoOccurrenceMatrixNormalized135);

	CFeature2DDifferenceVariance *DifferenceVariance0 = new CFeature2DDifferenceVariance();
	DifferenceVariance0->CalculateDifferenceVariance(ROICoOccurrenceMatrixNormalized0);
	CFeature2DDifferenceVariance *DifferenceVariance45 = new CFeature2DDifferenceVariance();
	DifferenceVariance45->CalculateDifferenceVariance(ROICoOccurrenceMatrixNormalized45);
	CFeature2DDifferenceVariance *DifferenceVariance90 = new CFeature2DDifferenceVariance();
	DifferenceVariance90->CalculateDifferenceVariance(ROICoOccurrenceMatrixNormalized90);
	CFeature2DDifferenceVariance *DifferenceVariance135 = new CFeature2DDifferenceVariance();
	DifferenceVariance135->CalculateDifferenceVariance(ROICoOccurrenceMatrixNormalized135);

	CFeature2DDifferenceEntropy *DifferenceEntropy0 = new CFeature2DDifferenceEntropy();
	DifferenceEntropy0->CalculateDifferenceEntropy(ROICoOccurrenceMatrixNormalized0);
	CFeature2DDifferenceEntropy *DifferenceEntropy45 = new CFeature2DDifferenceEntropy();
	DifferenceEntropy45->CalculateDifferenceEntropy(ROICoOccurrenceMatrixNormalized45);
	CFeature2DDifferenceEntropy *DifferenceEntropy90 = new CFeature2DDifferenceEntropy();
	DifferenceEntropy90->CalculateDifferenceEntropy(ROICoOccurrenceMatrixNormalized90);
	CFeature2DDifferenceEntropy *DifferenceEntropy135 = new CFeature2DDifferenceEntropy();
	DifferenceEntropy135->CalculateDifferenceEntropy(ROICoOccurrenceMatrixNormalized135);

	// Run length matrix based features
	CDataMatrix2D *ROIRunLengthMatrix0 = NULL;
	CDataMatrix2D *ROIRunLengthMatrix45 = NULL;
	CDataMatrix2D *ROIRunLengthMatrix90 = NULL;
	CDataMatrix2D *ROIRunLengthMatrix135 = NULL;

	CDataRunLengthMatrix2D *RunLengthMatrix0 = new CDataRunLengthMatrix2D(ROIDataMatrix0, iDepth, DEGREES_0);
	ROIRunLengthMatrix0 = RunLengthMatrix0->CopyRunLengthDataMatrixToDataMatrix2D();
		
	CDataRunLengthMatrix2D *RunLengthMatrix45 = new CDataRunLengthMatrix2D(ROIDataMatrix45, iDepth, DEGREES_45);
	ROIRunLengthMatrix45 = RunLengthMatrix45->CopyRunLengthDataMatrixToDataMatrix2D();
	
	CDataRunLengthMatrix2D *RunLengthMatrix90 = new CDataRunLengthMatrix2D(ROIDataMatrix90, iDepth, DEGREES_90);
	ROIRunLengthMatrix90 = RunLengthMatrix90->CopyRunLengthDataMatrixToDataMatrix2D();
	
	CDataRunLengthMatrix2D *RunLengthMatrix135 = new CDataRunLengthMatrix2D(ROIDataMatrix135, iDepth, DEGREES_135);
	ROIRunLengthMatrix135 = RunLengthMatrix135->CopyRunLengthDataMatrixToDataMatrix2D();
	
	CFeature2DShortRunEmphasis *ShortRunEmphasis0= new CFeature2DShortRunEmphasis();
	ShortRunEmphasis0->CalculateShortRunEmphasis(ROIRunLengthMatrix0);
	CFeature2DShortRunEmphasis *ShortRunEmphasis45= new CFeature2DShortRunEmphasis();
	ShortRunEmphasis45->CalculateShortRunEmphasis(ROIRunLengthMatrix45);
	CFeature2DShortRunEmphasis *ShortRunEmphasis90= new CFeature2DShortRunEmphasis();
	ShortRunEmphasis90->CalculateShortRunEmphasis(ROIRunLengthMatrix90);
	CFeature2DShortRunEmphasis *ShortRunEmphasis135= new CFeature2DShortRunEmphasis();
	ShortRunEmphasis135->CalculateShortRunEmphasis(ROIRunLengthMatrix135);

	CFeature2DLongRunEmphasis *LongRunEmphasis0 = new CFeature2DLongRunEmphasis();
	LongRunEmphasis0->CalculateLongRunEmphasis(ROIRunLengthMatrix0);
	CFeature2DLongRunEmphasis *LongRunEmphasis45 = new CFeature2DLongRunEmphasis();
	LongRunEmphasis45->CalculateLongRunEmphasis(ROIRunLengthMatrix45);
	CFeature2DLongRunEmphasis *LongRunEmphasis90 = new CFeature2DLongRunEmphasis();
	LongRunEmphasis90->CalculateLongRunEmphasis(ROIRunLengthMatrix90);
	CFeature2DLongRunEmphasis *LongRunEmphasis135 = new CFeature2DLongRunEmphasis();
	LongRunEmphasis135->CalculateLongRunEmphasis(ROIRunLengthMatrix135);

	CFeature2DGrayLevelNonUniformity *GrayLevelNonUniformity0 = new CFeature2DGrayLevelNonUniformity();
	GrayLevelNonUniformity0->CalculateGrayLevelNonUniformity(ROIRunLengthMatrix0);
	CFeature2DGrayLevelNonUniformity *GrayLevelNonUniformity45 = new CFeature2DGrayLevelNonUniformity();
	GrayLevelNonUniformity45->CalculateGrayLevelNonUniformity(ROIRunLengthMatrix45);
	CFeature2DGrayLevelNonUniformity *GrayLevelNonUniformity90 = new CFeature2DGrayLevelNonUniformity();
	GrayLevelNonUniformity90->CalculateGrayLevelNonUniformity(ROIRunLengthMatrix90);
	CFeature2DGrayLevelNonUniformity *GrayLevelNonUniformity135 = new CFeature2DGrayLevelNonUniformity();
	GrayLevelNonUniformity135->CalculateGrayLevelNonUniformity(ROIRunLengthMatrix135);

	CFeature2DRunLengthNonUniformity *RunLengthNonUniformity0 = new CFeature2DRunLengthNonUniformity();
	RunLengthNonUniformity0->CalculateRunLengthNonUniformity(ROIRunLengthMatrix0);
	CFeature2DRunLengthNonUniformity *RunLengthNonUniformity45 = new CFeature2DRunLengthNonUniformity();
	RunLengthNonUniformity45->CalculateRunLengthNonUniformity(ROIRunLengthMatrix45);
	CFeature2DRunLengthNonUniformity *RunLengthNonUniformity90 = new CFeature2DRunLengthNonUniformity();
	RunLengthNonUniformity90->CalculateRunLengthNonUniformity(ROIRunLengthMatrix90);
	CFeature2DRunLengthNonUniformity *RunLengthNonUniformity135 = new CFeature2DRunLengthNonUniformity();
	RunLengthNonUniformity135->CalculateRunLengthNonUniformity(ROIRunLengthMatrix135);

	CFeature2DRunPercentage *RunPercentage0 = new CFeature2DRunPercentage();
	RunPercentage0->CalculateRunPercentage(ROIRunLengthMatrix0, iWidth, iHeight);
	CFeature2DRunPercentage *RunPercentage45 = new CFeature2DRunPercentage();
	RunPercentage45->CalculateRunPercentage(ROIRunLengthMatrix45, iWidth, iHeight);
	CFeature2DRunPercentage *RunPercentage90 = new CFeature2DRunPercentage();
	RunPercentage90->CalculateRunPercentage(ROIRunLengthMatrix90, iWidth, iHeight);
	CFeature2DRunPercentage *RunPercentage135 = new CFeature2DRunPercentage();
	RunPercentage135->CalculateRunPercentage(ROIRunLengthMatrix135, iWidth, iHeight);


	Feature->SetFeatureValue(MeanValue->GetMeanValue());
	Pattern->AddFeature(Feature);

	Feature->SetFeatureValue(StandardDeviation->GetStandardDeviation());
	Pattern->AddFeature(Feature);

	Feature->SetFeatureValue(Skewness->GetSkewness());
 	Pattern->AddFeature(Feature);

	Feature->SetFeatureValue(Kurtosis->GetKurtosis());
	Pattern->AddFeature(Feature);

	// Mean Features (Co-Occurrence)
	MeanFeature->CalculateMeanFeatureValue(AngularSecondMoment0->GetAngularSecondMoment(), AngularSecondMoment45->GetAngularSecondMoment(), AngularSecondMoment90->GetAngularSecondMoment(), AngularSecondMoment135->GetAngularSecondMoment());
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(Contrast0->GetContrast(), Contrast45->GetContrast(), Contrast90->GetContrast(), Contrast135->GetContrast());
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(Correlation0->GetCorrelation(), Correlation45->GetCorrelation(), Correlation90->GetCorrelation(), Correlation135->GetCorrelation());
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(SumOfSquares0->GetSumOfSquares(), SumOfSquares45->GetSumOfSquares(), SumOfSquares90->GetSumOfSquares(), SumOfSquares135->GetSumOfSquares());
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);
	
	MeanFeature->CalculateMeanFeatureValue(InverseDifferenceMoment0->GetInverseDifferenceMoment(), InverseDifferenceMoment45->GetInverseDifferenceMoment(), InverseDifferenceMoment90->GetInverseDifferenceMoment(), InverseDifferenceMoment135->GetInverseDifferenceMoment());
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(SumAverage0->GetSumAverage(), SumAverage45->GetSumAverage(), SumAverage90->GetSumAverage(), SumAverage135->GetSumAverage());
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(SumVariance0->GetSumVariance(), SumVariance45->GetSumVariance(), SumVariance90->GetSumVariance(), SumVariance135->GetSumVariance());
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(SumEntropy0->GetSumEntropy(), SumEntropy45->GetSumEntropy(), SumEntropy90->GetSumEntropy(), SumEntropy135->GetSumEntropy());
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(Entropy0->GetEntropy(), Entropy45->GetEntropy(), Entropy90->GetEntropy(), Entropy135->GetEntropy());
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(DifferenceVariance0->GetDifferenceVariance(), DifferenceVariance45->GetDifferenceVariance(), DifferenceVariance90->GetDifferenceVariance(), DifferenceVariance135->GetDifferenceVariance());
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(DifferenceEntropy0->GetDifferenceEntropy(), DifferenceEntropy45->GetDifferenceEntropy(), DifferenceEntropy90->GetDifferenceEntropy(), DifferenceEntropy135->GetDifferenceEntropy());
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	// Range Features (Co-Occurrence)
	RangeFeature->CalculateRangeFeatureValue(AngularSecondMoment0->GetAngularSecondMoment(), AngularSecondMoment45->GetAngularSecondMoment(), AngularSecondMoment90->GetAngularSecondMoment(), AngularSecondMoment135->GetAngularSecondMoment());
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(Contrast0->GetContrast(), Contrast45->GetContrast(), Contrast90->GetContrast(), Contrast135->GetContrast());
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(Correlation0->GetCorrelation(), Correlation45->GetCorrelation(), Correlation90->GetCorrelation(), Correlation135->GetCorrelation());
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(SumOfSquares0->GetSumOfSquares(), SumOfSquares45->GetSumOfSquares(), SumOfSquares90->GetSumOfSquares(), SumOfSquares135->GetSumOfSquares());
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);
	
	RangeFeature->CalculateRangeFeatureValue(InverseDifferenceMoment0->GetInverseDifferenceMoment(), InverseDifferenceMoment45->GetInverseDifferenceMoment(), InverseDifferenceMoment90->GetInverseDifferenceMoment(), InverseDifferenceMoment135->GetInverseDifferenceMoment());
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(SumAverage0->GetSumAverage(), SumAverage45->GetSumAverage(), SumAverage90->GetSumAverage(), SumAverage135->GetSumAverage());
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(SumVariance0->GetSumVariance(), SumVariance45->GetSumVariance(), SumVariance90->GetSumVariance(), SumVariance135->GetSumVariance());
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(SumEntropy0->GetSumEntropy(), SumEntropy45->GetSumEntropy(), SumEntropy90->GetSumEntropy(), SumEntropy135->GetSumEntropy());
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(Entropy0->GetEntropy(), Entropy45->GetEntropy(), Entropy90->GetEntropy(), Entropy135->GetEntropy());
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(DifferenceVariance0->GetDifferenceVariance(), DifferenceVariance45->GetDifferenceVariance(), DifferenceVariance90->GetDifferenceVariance(), DifferenceVariance135->GetDifferenceVariance());
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(DifferenceEntropy0->GetDifferenceEntropy(), DifferenceEntropy45->GetDifferenceEntropy(), DifferenceEntropy90->GetDifferenceEntropy(), DifferenceEntropy135->GetDifferenceEntropy());
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	// Mean Features (Run Length)
	MeanFeature->CalculateMeanFeatureValue(ShortRunEmphasis0->GetShortRunEmphasis(), ShortRunEmphasis45->GetShortRunEmphasis(), ShortRunEmphasis90->GetShortRunEmphasis(), ShortRunEmphasis135->GetShortRunEmphasis());
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(LongRunEmphasis0->GetLongRunEmphasis(), LongRunEmphasis45->GetLongRunEmphasis(), LongRunEmphasis90->GetLongRunEmphasis(), LongRunEmphasis135->GetLongRunEmphasis());
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(GrayLevelNonUniformity0->GetGrayLevelNonUniformity(), GrayLevelNonUniformity45->GetGrayLevelNonUniformity(), GrayLevelNonUniformity90->GetGrayLevelNonUniformity(), GrayLevelNonUniformity135->GetGrayLevelNonUniformity());
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(RunLengthNonUniformity0->GetRunLengthNonUniformity(), RunLengthNonUniformity45->GetRunLengthNonUniformity(), RunLengthNonUniformity90->GetRunLengthNonUniformity(), RunLengthNonUniformity135->GetRunLengthNonUniformity());
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(RunPercentage0->GetRunPercentage(), RunPercentage45->GetRunPercentage(), RunPercentage90->GetRunPercentage(), RunPercentage135->GetRunPercentage());
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	// Range Features (Run Length)
	RangeFeature->CalculateRangeFeatureValue(ShortRunEmphasis0->GetShortRunEmphasis(), ShortRunEmphasis45->GetShortRunEmphasis(), ShortRunEmphasis90->GetShortRunEmphasis(), ShortRunEmphasis135->GetShortRunEmphasis());
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(LongRunEmphasis0->GetLongRunEmphasis(), LongRunEmphasis45->GetLongRunEmphasis(), LongRunEmphasis90->GetLongRunEmphasis(), LongRunEmphasis135->GetLongRunEmphasis());
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(GrayLevelNonUniformity0->GetGrayLevelNonUniformity(), GrayLevelNonUniformity45->GetGrayLevelNonUniformity(), GrayLevelNonUniformity90->GetGrayLevelNonUniformity(), GrayLevelNonUniformity135->GetGrayLevelNonUniformity());
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(RunLengthNonUniformity0->GetRunLengthNonUniformity(), RunLengthNonUniformity45->GetRunLengthNonUniformity(), RunLengthNonUniformity90->GetRunLengthNonUniformity(), RunLengthNonUniformity135->GetRunLengthNonUniformity());
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(RunPercentage0->GetRunPercentage(), RunPercentage45->GetRunPercentage(), RunPercentage90->GetRunPercentage(), RunPercentage135->GetRunPercentage());
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	delete RunPercentage0;
	RunPercentage0 = NULL;
	delete RunPercentage45;
	RunPercentage45 = NULL;
	delete RunPercentage90;
	RunPercentage90 = NULL;
	delete RunPercentage135;
	RunPercentage135 = NULL;

	delete RunLengthNonUniformity0;
	RunLengthNonUniformity0 = NULL;
	delete RunLengthNonUniformity45;
	RunLengthNonUniformity45 = NULL;
	delete RunLengthNonUniformity90;
	RunLengthNonUniformity90 = NULL;
	delete RunLengthNonUniformity135;
	RunLengthNonUniformity135 = NULL;

	delete GrayLevelNonUniformity0;
	GrayLevelNonUniformity0 = NULL;
	delete GrayLevelNonUniformity45;
	GrayLevelNonUniformity45 = NULL;
	delete GrayLevelNonUniformity90;
	GrayLevelNonUniformity90 = NULL;
	delete GrayLevelNonUniformity135;
	GrayLevelNonUniformity135 = NULL;

	delete LongRunEmphasis0;
	LongRunEmphasis0 = NULL;
	delete LongRunEmphasis45;
	LongRunEmphasis45 = NULL;
	delete LongRunEmphasis90;
	LongRunEmphasis90 = NULL;
	delete LongRunEmphasis135;
	LongRunEmphasis135 = NULL;

	delete ShortRunEmphasis0;
	ShortRunEmphasis0 = NULL;
	delete ShortRunEmphasis45;
	ShortRunEmphasis45 = NULL;
	delete ShortRunEmphasis90;
	ShortRunEmphasis90 = NULL;
	delete ShortRunEmphasis135;
	ShortRunEmphasis135 = NULL;

	delete Correlation0;
	Correlation0 = NULL;
	delete Correlation45;
	Correlation45 = NULL;
	delete Correlation90;
	Correlation90 = NULL;
	delete Correlation135;
	Correlation135 = NULL;

	delete DifferenceVariance0;
	DifferenceVariance0 = NULL;
	delete DifferenceVariance45;
	DifferenceVariance45 = NULL;
	delete DifferenceVariance90;
	DifferenceVariance90 = NULL;
	delete DifferenceVariance135;
	DifferenceVariance135 = NULL;

	delete DifferenceEntropy0;
	DifferenceEntropy0 = NULL;
	delete DifferenceEntropy45;
	DifferenceEntropy45 = NULL;
	delete DifferenceEntropy90;
	DifferenceEntropy90 = NULL;
	delete DifferenceEntropy135;
	DifferenceEntropy135 = NULL;

	delete SumVariance0;
	SumVariance0 = NULL;
	delete SumVariance45;
	SumVariance45 = NULL;
	delete SumVariance90;
	SumVariance90 = NULL;
	delete SumVariance135;
	SumVariance135 = NULL;

	delete SumEntropy0;
	SumEntropy0 = NULL;
	delete SumEntropy45;
	SumEntropy45 = NULL;
	delete SumEntropy90;
	SumEntropy90 = NULL;
	delete SumEntropy135;
	SumEntropy135 = NULL;

	delete SumAverage0;
	SumAverage0 = NULL;
	delete SumAverage45;
	SumAverage45 = NULL;
	delete SumAverage90;
	SumAverage90 = NULL;
	delete SumAverage135;
	SumAverage135 = NULL;

	delete SumOfSquares0;
	SumOfSquares0 = NULL;
	delete SumOfSquares45;
	SumOfSquares45 = NULL;
	delete SumOfSquares90;
	SumOfSquares90 = NULL;
	delete SumOfSquares135;
	SumOfSquares135 = NULL;

	delete Entropy0;
	Entropy0 = NULL;
	delete Entropy45;
	Entropy45 = NULL;
	delete Entropy90;
	Entropy90 = NULL;
	delete Entropy135;
	Entropy135 = NULL;

	delete InverseDifferenceMoment0;
	InverseDifferenceMoment0 = NULL;
	delete InverseDifferenceMoment45;
	InverseDifferenceMoment45 = NULL;
	delete InverseDifferenceMoment90;
	InverseDifferenceMoment90 = NULL;
	delete InverseDifferenceMoment135;
	InverseDifferenceMoment135 = NULL;

	delete Contrast0;
	Contrast0 = NULL;
	delete Contrast45;
	Contrast45 = NULL;
	delete Contrast90;
	Contrast90 = NULL;
	delete Contrast135;
	Contrast135 = NULL;

	delete AngularSecondMoment0;
	AngularSecondMoment0 = NULL;
	delete AngularSecondMoment45;
	AngularSecondMoment45 = NULL;
	delete AngularSecondMoment90;
	AngularSecondMoment90 = NULL;
	delete AngularSecondMoment135;
	AngularSecondMoment135 = NULL;

	delete ROIRunLengthMatrix0;
	ROIRunLengthMatrix0 = NULL;
	delete ROIRunLengthMatrix45;
	ROIRunLengthMatrix45 = NULL;
	delete ROIRunLengthMatrix90;
	ROIRunLengthMatrix90 = NULL;
	delete ROIRunLengthMatrix135;
	ROIRunLengthMatrix135 = NULL;

	delete RunLengthMatrix0;
	RunLengthMatrix0 = NULL;
	delete RunLengthMatrix45;
	RunLengthMatrix45 = NULL;
	delete RunLengthMatrix90;
	RunLengthMatrix90 = NULL;
	delete RunLengthMatrix135;
	RunLengthMatrix135 = NULL;

	delete ROICoOccurrenceMatrixNormalized0;
	ROICoOccurrenceMatrixNormalized0 = NULL;
	delete ROICoOccurrenceMatrixNormalized45;
	ROICoOccurrenceMatrixNormalized45 = NULL;
	delete ROICoOccurrenceMatrixNormalized90;
	ROICoOccurrenceMatrixNormalized90 = NULL;
	delete ROICoOccurrenceMatrixNormalized135;
	ROICoOccurrenceMatrixNormalized135 = NULL;

	delete ROICoOccurrenceMatrix0;
	ROICoOccurrenceMatrix0 = NULL;
	delete ROICoOccurrenceMatrix45;
	ROICoOccurrenceMatrix45 = NULL;
	delete ROICoOccurrenceMatrix90;
	ROICoOccurrenceMatrix90 = NULL;
	delete ROICoOccurrenceMatrix135;
	ROICoOccurrenceMatrix135 = NULL;

	delete CoOccurrenceMatrix0;
	CoOccurrenceMatrix0 = NULL;
	delete CoOccurrenceMatrix45;
	CoOccurrenceMatrix45 = NULL;
	delete CoOccurrenceMatrix90;
	CoOccurrenceMatrix90 = NULL;
	delete CoOccurrenceMatrix135;
	CoOccurrenceMatrix135 = NULL;

	delete ROIDataMatrix0;
	ROIDataMatrix0 = NULL;
	delete ROIDataMatrix45;
	ROIDataMatrix45 = NULL;
	delete ROIDataMatrix90;
	ROIDataMatrix90 = NULL;
	delete ROIDataMatrix135;
	ROIDataMatrix135 = NULL;

	delete Kurtosis;
	Kurtosis = NULL;

	delete Skewness;
	Skewness = NULL;

	delete StandardDeviation;
	StandardDeviation = NULL;
	
	delete MeanValue;
	MeanValue = NULL;

	delete RangeFeature;
	RangeFeature = NULL;

	delete MeanFeature;
	MeanFeature = NULL;
	
	delete ROIDataMatrix;
	ROIDataMatrix = NULL;

	delete Feature;
	Feature = NULL;

	return Pattern;

}

void CROIToPattern::GetFeatureName (int iFeatureIndex, char *szFeatureName){

	if (szFeatureName){
		strcpy(szFeatureName, FeatureNameStrings[iFeatureIndex]);
	}

}

void CROIToPattern::GetFeatureShortName (int iFeatureIndex, char *szFeatureShortName){

	if (szFeatureShortName){
		strcpy(szFeatureShortName, FeatureShortNameStrings[iFeatureIndex]);
	}

}
