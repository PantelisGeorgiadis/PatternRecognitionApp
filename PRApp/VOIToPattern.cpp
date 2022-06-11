#include "stdafx.h"
#include "VOIToPattern.h"

CVOIToPattern::CVOIToPattern()
{

}

CVOIToPattern::~CVOIToPattern()
{

}

CPattern *CVOIToPattern::VOIToPattern8 (CDataMatrix3D *pDataMatrix3D, int iDepth){

	CFeature *Feature = new CFeature();
	CPattern *Pattern = new CPattern(1);
	Pattern->RemoveAllFeatures();

	CFeature3DMeanFeature *MeanFeature = new CFeature3DMeanFeature();
	CFeature3DRangeFeature *RangeFeature = new CFeature3DRangeFeature();


	// First-Order Statistical Features
	CFeature3DMeanValue *MeanValue = new CFeature3DMeanValue();
	MeanValue->CalculateMeanValue(pDataMatrix3D);

	CFeature3DStandardDeviation *StandardDeviation = new CFeature3DStandardDeviation();
	StandardDeviation->CalculateStandardDeviation(pDataMatrix3D);

	CFeature3DSkewness *Skewness = new CFeature3DSkewness();
	Skewness->CalculateSkewness(pDataMatrix3D);
	
	CFeature3DKurtosis *Kurtosis = new CFeature3DKurtosis();
	Kurtosis->CalculateKurtosis(pDataMatrix3D);

	
	// Co-occurrence based features
	CDataMatrix2D *VOICoOccurrenceMatrix0 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrix1 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrix2 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrix3 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrix4 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrix5 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrix6 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrix7 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrix8 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrix9 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrix10 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrix11 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrix12 = NULL;

	CDataMatrix2D *VOICoOccurrenceMatrixNormalized0 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrixNormalized1 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrixNormalized2 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrixNormalized3 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrixNormalized4 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrixNormalized5 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrixNormalized6 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrixNormalized7 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrixNormalized8 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrixNormalized9 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrixNormalized10 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrixNormalized11 = NULL;
	CDataMatrix2D *VOICoOccurrenceMatrixNormalized12 = NULL;

	CDataCoOccurrenceMatrix3D *CoOccurrenceMatrixes = new CDataCoOccurrenceMatrix3D();
	CoOccurrenceMatrixes->FillDataCoOccurrenceMatrixes(pDataMatrix3D, iDepth);

	VOICoOccurrenceMatrix0 = CoOccurrenceMatrixes->GetDataCoOccurrenceMatrix(0);
	VOICoOccurrenceMatrix1 = CoOccurrenceMatrixes->GetDataCoOccurrenceMatrix(1);
	VOICoOccurrenceMatrix2 = CoOccurrenceMatrixes->GetDataCoOccurrenceMatrix(2);
	VOICoOccurrenceMatrix3 = CoOccurrenceMatrixes->GetDataCoOccurrenceMatrix(3);
	VOICoOccurrenceMatrix4 = CoOccurrenceMatrixes->GetDataCoOccurrenceMatrix(4);
	VOICoOccurrenceMatrix5 = CoOccurrenceMatrixes->GetDataCoOccurrenceMatrix(5);
	VOICoOccurrenceMatrix6 = CoOccurrenceMatrixes->GetDataCoOccurrenceMatrix(6);
	VOICoOccurrenceMatrix7 = CoOccurrenceMatrixes->GetDataCoOccurrenceMatrix(7);
	VOICoOccurrenceMatrix8 = CoOccurrenceMatrixes->GetDataCoOccurrenceMatrix(8);
	VOICoOccurrenceMatrix9 = CoOccurrenceMatrixes->GetDataCoOccurrenceMatrix(9);
	VOICoOccurrenceMatrix10 = CoOccurrenceMatrixes->GetDataCoOccurrenceMatrix(10);
	VOICoOccurrenceMatrix11 = CoOccurrenceMatrixes->GetDataCoOccurrenceMatrix(11);
	VOICoOccurrenceMatrix12 = CoOccurrenceMatrixes->GetDataCoOccurrenceMatrix(12);

	VOICoOccurrenceMatrixNormalized0 = VOICoOccurrenceMatrix0->NormalizeSum();
	VOICoOccurrenceMatrixNormalized1 = VOICoOccurrenceMatrix1->NormalizeSum();
	VOICoOccurrenceMatrixNormalized2 = VOICoOccurrenceMatrix2->NormalizeSum();
	VOICoOccurrenceMatrixNormalized3 = VOICoOccurrenceMatrix3->NormalizeSum();
	VOICoOccurrenceMatrixNormalized4 = VOICoOccurrenceMatrix4->NormalizeSum();
	VOICoOccurrenceMatrixNormalized5 = VOICoOccurrenceMatrix5->NormalizeSum();
	VOICoOccurrenceMatrixNormalized6 = VOICoOccurrenceMatrix6->NormalizeSum();
	VOICoOccurrenceMatrixNormalized7 = VOICoOccurrenceMatrix7->NormalizeSum();
	VOICoOccurrenceMatrixNormalized8 = VOICoOccurrenceMatrix8->NormalizeSum();
	VOICoOccurrenceMatrixNormalized9 = VOICoOccurrenceMatrix9->NormalizeSum();
	VOICoOccurrenceMatrixNormalized10 = VOICoOccurrenceMatrix10->NormalizeSum();
	VOICoOccurrenceMatrixNormalized11 = VOICoOccurrenceMatrix11->NormalizeSum();
	VOICoOccurrenceMatrixNormalized12 = VOICoOccurrenceMatrix12->NormalizeSum();

	CFeature2DAngularSecondMoment *AngularSecondMoment0 = new CFeature2DAngularSecondMoment();
	AngularSecondMoment0->CalculateAngularSecondMoment(VOICoOccurrenceMatrixNormalized0);
	CFeature2DAngularSecondMoment *AngularSecondMoment1 = new CFeature2DAngularSecondMoment();
	AngularSecondMoment1->CalculateAngularSecondMoment(VOICoOccurrenceMatrixNormalized1);
	CFeature2DAngularSecondMoment *AngularSecondMoment2 = new CFeature2DAngularSecondMoment();
	AngularSecondMoment2->CalculateAngularSecondMoment(VOICoOccurrenceMatrixNormalized2);
	CFeature2DAngularSecondMoment *AngularSecondMoment3 = new CFeature2DAngularSecondMoment();
	AngularSecondMoment3->CalculateAngularSecondMoment(VOICoOccurrenceMatrixNormalized3);
	CFeature2DAngularSecondMoment *AngularSecondMoment4 = new CFeature2DAngularSecondMoment();
	AngularSecondMoment4->CalculateAngularSecondMoment(VOICoOccurrenceMatrixNormalized4);
	CFeature2DAngularSecondMoment *AngularSecondMoment5 = new CFeature2DAngularSecondMoment();
	AngularSecondMoment5->CalculateAngularSecondMoment(VOICoOccurrenceMatrixNormalized5);
	CFeature2DAngularSecondMoment *AngularSecondMoment6 = new CFeature2DAngularSecondMoment();
	AngularSecondMoment6->CalculateAngularSecondMoment(VOICoOccurrenceMatrixNormalized6);
	CFeature2DAngularSecondMoment *AngularSecondMoment7 = new CFeature2DAngularSecondMoment();
	AngularSecondMoment7->CalculateAngularSecondMoment(VOICoOccurrenceMatrixNormalized7);
	CFeature2DAngularSecondMoment *AngularSecondMoment8 = new CFeature2DAngularSecondMoment();
	AngularSecondMoment8->CalculateAngularSecondMoment(VOICoOccurrenceMatrixNormalized8);
	CFeature2DAngularSecondMoment *AngularSecondMoment9 = new CFeature2DAngularSecondMoment();
	AngularSecondMoment9->CalculateAngularSecondMoment(VOICoOccurrenceMatrixNormalized9);
	CFeature2DAngularSecondMoment *AngularSecondMoment10 = new CFeature2DAngularSecondMoment();
	AngularSecondMoment10->CalculateAngularSecondMoment(VOICoOccurrenceMatrixNormalized10);
	CFeature2DAngularSecondMoment *AngularSecondMoment11 = new CFeature2DAngularSecondMoment();
	AngularSecondMoment11->CalculateAngularSecondMoment(VOICoOccurrenceMatrixNormalized11);
	CFeature2DAngularSecondMoment *AngularSecondMoment12 = new CFeature2DAngularSecondMoment();
	AngularSecondMoment12->CalculateAngularSecondMoment(VOICoOccurrenceMatrixNormalized12);

	CFeature2DContrast *Contrast0 = new CFeature2DContrast();
	Contrast0->CalculateContrast(VOICoOccurrenceMatrixNormalized0);
	CFeature2DContrast *Contrast1 = new CFeature2DContrast();
	Contrast1->CalculateContrast(VOICoOccurrenceMatrixNormalized1);
	CFeature2DContrast *Contrast2 = new CFeature2DContrast();
	Contrast2->CalculateContrast(VOICoOccurrenceMatrixNormalized2);
	CFeature2DContrast *Contrast3 = new CFeature2DContrast();
	Contrast3->CalculateContrast(VOICoOccurrenceMatrixNormalized3);
	CFeature2DContrast *Contrast4 = new CFeature2DContrast();
	Contrast4->CalculateContrast(VOICoOccurrenceMatrixNormalized4);
	CFeature2DContrast *Contrast5 = new CFeature2DContrast();
	Contrast5->CalculateContrast(VOICoOccurrenceMatrixNormalized5);
	CFeature2DContrast *Contrast6 = new CFeature2DContrast();
	Contrast6->CalculateContrast(VOICoOccurrenceMatrixNormalized6);
	CFeature2DContrast *Contrast7 = new CFeature2DContrast();
	Contrast7->CalculateContrast(VOICoOccurrenceMatrixNormalized7);
	CFeature2DContrast *Contrast8 = new CFeature2DContrast();
	Contrast8->CalculateContrast(VOICoOccurrenceMatrixNormalized8);
	CFeature2DContrast *Contrast9 = new CFeature2DContrast();
	Contrast9->CalculateContrast(VOICoOccurrenceMatrixNormalized9);
	CFeature2DContrast *Contrast10 = new CFeature2DContrast();
	Contrast10->CalculateContrast(VOICoOccurrenceMatrixNormalized10);
	CFeature2DContrast *Contrast11 = new CFeature2DContrast();
	Contrast11->CalculateContrast(VOICoOccurrenceMatrixNormalized11);
	CFeature2DContrast *Contrast12 = new CFeature2DContrast();
	Contrast12->CalculateContrast(VOICoOccurrenceMatrixNormalized12);

	CFeature2DCorrelation *Correlation0 = new CFeature2DCorrelation();
	Correlation0->CalculateCorrelation(VOICoOccurrenceMatrixNormalized0);
	CFeature2DCorrelation *Correlation1 = new CFeature2DCorrelation();
	Correlation1->CalculateCorrelation(VOICoOccurrenceMatrixNormalized1);
	CFeature2DCorrelation *Correlation2 = new CFeature2DCorrelation();
	Correlation2->CalculateCorrelation(VOICoOccurrenceMatrixNormalized2);
	CFeature2DCorrelation *Correlation3 = new CFeature2DCorrelation();
	Correlation3->CalculateCorrelation(VOICoOccurrenceMatrixNormalized3);
	CFeature2DCorrelation *Correlation4 = new CFeature2DCorrelation();
	Correlation4->CalculateCorrelation(VOICoOccurrenceMatrixNormalized4);
	CFeature2DCorrelation *Correlation5 = new CFeature2DCorrelation();
	Correlation5->CalculateCorrelation(VOICoOccurrenceMatrixNormalized5);
	CFeature2DCorrelation *Correlation6 = new CFeature2DCorrelation();
	Correlation6->CalculateCorrelation(VOICoOccurrenceMatrixNormalized6);
	CFeature2DCorrelation *Correlation7 = new CFeature2DCorrelation();
	Correlation7->CalculateCorrelation(VOICoOccurrenceMatrixNormalized7);
	CFeature2DCorrelation *Correlation8 = new CFeature2DCorrelation();
	Correlation8->CalculateCorrelation(VOICoOccurrenceMatrixNormalized8);
	CFeature2DCorrelation *Correlation9 = new CFeature2DCorrelation();
	Correlation9->CalculateCorrelation(VOICoOccurrenceMatrixNormalized9);
	CFeature2DCorrelation *Correlation10 = new CFeature2DCorrelation();
	Correlation10->CalculateCorrelation(VOICoOccurrenceMatrixNormalized10);
	CFeature2DCorrelation *Correlation11 = new CFeature2DCorrelation();
	Correlation11->CalculateCorrelation(VOICoOccurrenceMatrixNormalized11);
	CFeature2DCorrelation *Correlation12 = new CFeature2DCorrelation();
	Correlation12->CalculateCorrelation(VOICoOccurrenceMatrixNormalized12);

	CFeature2DSumOfSquares *SumOfSquares0 = new CFeature2DSumOfSquares();
	SumOfSquares0->CalculateSumOfSquares(VOICoOccurrenceMatrixNormalized0);
	CFeature2DSumOfSquares *SumOfSquares1 = new CFeature2DSumOfSquares();
	SumOfSquares1->CalculateSumOfSquares(VOICoOccurrenceMatrixNormalized1);
	CFeature2DSumOfSquares *SumOfSquares2 = new CFeature2DSumOfSquares();
	SumOfSquares2->CalculateSumOfSquares(VOICoOccurrenceMatrixNormalized2);
	CFeature2DSumOfSquares *SumOfSquares3 = new CFeature2DSumOfSquares();
	SumOfSquares3->CalculateSumOfSquares(VOICoOccurrenceMatrixNormalized3);
	CFeature2DSumOfSquares *SumOfSquares4 = new CFeature2DSumOfSquares();
	SumOfSquares4->CalculateSumOfSquares(VOICoOccurrenceMatrixNormalized4);
	CFeature2DSumOfSquares *SumOfSquares5 = new CFeature2DSumOfSquares();
	SumOfSquares5->CalculateSumOfSquares(VOICoOccurrenceMatrixNormalized5);
	CFeature2DSumOfSquares *SumOfSquares6 = new CFeature2DSumOfSquares();
	SumOfSquares6->CalculateSumOfSquares(VOICoOccurrenceMatrixNormalized6);
	CFeature2DSumOfSquares *SumOfSquares7 = new CFeature2DSumOfSquares();
	SumOfSquares7->CalculateSumOfSquares(VOICoOccurrenceMatrixNormalized7);
	CFeature2DSumOfSquares *SumOfSquares8 = new CFeature2DSumOfSquares();
	SumOfSquares8->CalculateSumOfSquares(VOICoOccurrenceMatrixNormalized8);
	CFeature2DSumOfSquares *SumOfSquares9 = new CFeature2DSumOfSquares();
	SumOfSquares9->CalculateSumOfSquares(VOICoOccurrenceMatrixNormalized9);
	CFeature2DSumOfSquares *SumOfSquares10 = new CFeature2DSumOfSquares();
	SumOfSquares10->CalculateSumOfSquares(VOICoOccurrenceMatrixNormalized10);
	CFeature2DSumOfSquares *SumOfSquares11 = new CFeature2DSumOfSquares();
	SumOfSquares11->CalculateSumOfSquares(VOICoOccurrenceMatrixNormalized11);
	CFeature2DSumOfSquares *SumOfSquares12 = new CFeature2DSumOfSquares();
	SumOfSquares12->CalculateSumOfSquares(VOICoOccurrenceMatrixNormalized12);

	CFeature2DInverseDifferenceMoment *InverseDifferenceMoment0 = new CFeature2DInverseDifferenceMoment();
	InverseDifferenceMoment0->CalculateInverseDifferenceMoment(VOICoOccurrenceMatrixNormalized0);
	CFeature2DInverseDifferenceMoment *InverseDifferenceMoment1 = new CFeature2DInverseDifferenceMoment();
	InverseDifferenceMoment1->CalculateInverseDifferenceMoment(VOICoOccurrenceMatrixNormalized1);
	CFeature2DInverseDifferenceMoment *InverseDifferenceMoment2 = new CFeature2DInverseDifferenceMoment();
	InverseDifferenceMoment2->CalculateInverseDifferenceMoment(VOICoOccurrenceMatrixNormalized2);
	CFeature2DInverseDifferenceMoment *InverseDifferenceMoment3 = new CFeature2DInverseDifferenceMoment();
	InverseDifferenceMoment3->CalculateInverseDifferenceMoment(VOICoOccurrenceMatrixNormalized3);
	CFeature2DInverseDifferenceMoment *InverseDifferenceMoment4 = new CFeature2DInverseDifferenceMoment();
	InverseDifferenceMoment4->CalculateInverseDifferenceMoment(VOICoOccurrenceMatrixNormalized4);
	CFeature2DInverseDifferenceMoment *InverseDifferenceMoment5 = new CFeature2DInverseDifferenceMoment();
	InverseDifferenceMoment5->CalculateInverseDifferenceMoment(VOICoOccurrenceMatrixNormalized5);
	CFeature2DInverseDifferenceMoment *InverseDifferenceMoment6 = new CFeature2DInverseDifferenceMoment();
	InverseDifferenceMoment6->CalculateInverseDifferenceMoment(VOICoOccurrenceMatrixNormalized6);
	CFeature2DInverseDifferenceMoment *InverseDifferenceMoment7 = new CFeature2DInverseDifferenceMoment();
	InverseDifferenceMoment7->CalculateInverseDifferenceMoment(VOICoOccurrenceMatrixNormalized7);
	CFeature2DInverseDifferenceMoment *InverseDifferenceMoment8 = new CFeature2DInverseDifferenceMoment();
	InverseDifferenceMoment8->CalculateInverseDifferenceMoment(VOICoOccurrenceMatrixNormalized8);
	CFeature2DInverseDifferenceMoment *InverseDifferenceMoment9 = new CFeature2DInverseDifferenceMoment();
	InverseDifferenceMoment9->CalculateInverseDifferenceMoment(VOICoOccurrenceMatrixNormalized9);
	CFeature2DInverseDifferenceMoment *InverseDifferenceMoment10 = new CFeature2DInverseDifferenceMoment();
	InverseDifferenceMoment10->CalculateInverseDifferenceMoment(VOICoOccurrenceMatrixNormalized10);
	CFeature2DInverseDifferenceMoment *InverseDifferenceMoment11 = new CFeature2DInverseDifferenceMoment();
	InverseDifferenceMoment11->CalculateInverseDifferenceMoment(VOICoOccurrenceMatrixNormalized11);
	CFeature2DInverseDifferenceMoment *InverseDifferenceMoment12 = new CFeature2DInverseDifferenceMoment();
	InverseDifferenceMoment12->CalculateInverseDifferenceMoment(VOICoOccurrenceMatrixNormalized12);

	CFeature2DSumAverage *SumAverage0 = new CFeature2DSumAverage();
	SumAverage0->CalculateSumAverage(VOICoOccurrenceMatrixNormalized0);
	CFeature2DSumAverage *SumAverage1 = new CFeature2DSumAverage();
	SumAverage1->CalculateSumAverage(VOICoOccurrenceMatrixNormalized1);
	CFeature2DSumAverage *SumAverage2 = new CFeature2DSumAverage();
	SumAverage2->CalculateSumAverage(VOICoOccurrenceMatrixNormalized2);
	CFeature2DSumAverage *SumAverage3 = new CFeature2DSumAverage();
	SumAverage3->CalculateSumAverage(VOICoOccurrenceMatrixNormalized3);
	CFeature2DSumAverage *SumAverage4 = new CFeature2DSumAverage();
	SumAverage4->CalculateSumAverage(VOICoOccurrenceMatrixNormalized4);
	CFeature2DSumAverage *SumAverage5 = new CFeature2DSumAverage();
	SumAverage5->CalculateSumAverage(VOICoOccurrenceMatrixNormalized5);
	CFeature2DSumAverage *SumAverage6 = new CFeature2DSumAverage();
	SumAverage6->CalculateSumAverage(VOICoOccurrenceMatrixNormalized6);
	CFeature2DSumAverage *SumAverage7 = new CFeature2DSumAverage();
	SumAverage7->CalculateSumAverage(VOICoOccurrenceMatrixNormalized7);
	CFeature2DSumAverage *SumAverage8 = new CFeature2DSumAverage();
	SumAverage8->CalculateSumAverage(VOICoOccurrenceMatrixNormalized8);
	CFeature2DSumAverage *SumAverage9 = new CFeature2DSumAverage();
	SumAverage9->CalculateSumAverage(VOICoOccurrenceMatrixNormalized9);
	CFeature2DSumAverage *SumAverage10 = new CFeature2DSumAverage();
	SumAverage10->CalculateSumAverage(VOICoOccurrenceMatrixNormalized10);
	CFeature2DSumAverage *SumAverage11 = new CFeature2DSumAverage();
	SumAverage11->CalculateSumAverage(VOICoOccurrenceMatrixNormalized11);
	CFeature2DSumAverage *SumAverage12 = new CFeature2DSumAverage();
	SumAverage12->CalculateSumAverage(VOICoOccurrenceMatrixNormalized12);

	CFeature2DSumVariance *SumVariance0 = new CFeature2DSumVariance();
	SumVariance0->CalculateSumVariance(VOICoOccurrenceMatrixNormalized0);
	CFeature2DSumVariance *SumVariance1 = new CFeature2DSumVariance();
	SumVariance1->CalculateSumVariance(VOICoOccurrenceMatrixNormalized1);
	CFeature2DSumVariance *SumVariance2 = new CFeature2DSumVariance();
	SumVariance2->CalculateSumVariance(VOICoOccurrenceMatrixNormalized2);
	CFeature2DSumVariance *SumVariance3 = new CFeature2DSumVariance();
	SumVariance3->CalculateSumVariance(VOICoOccurrenceMatrixNormalized3);
	CFeature2DSumVariance *SumVariance4 = new CFeature2DSumVariance();
	SumVariance4->CalculateSumVariance(VOICoOccurrenceMatrixNormalized4);
	CFeature2DSumVariance *SumVariance5 = new CFeature2DSumVariance();
	SumVariance5->CalculateSumVariance(VOICoOccurrenceMatrixNormalized5);
	CFeature2DSumVariance *SumVariance6 = new CFeature2DSumVariance();
	SumVariance6->CalculateSumVariance(VOICoOccurrenceMatrixNormalized6);
	CFeature2DSumVariance *SumVariance7 = new CFeature2DSumVariance();
	SumVariance7->CalculateSumVariance(VOICoOccurrenceMatrixNormalized7);
	CFeature2DSumVariance *SumVariance8 = new CFeature2DSumVariance();
	SumVariance8->CalculateSumVariance(VOICoOccurrenceMatrixNormalized8);
	CFeature2DSumVariance *SumVariance9 = new CFeature2DSumVariance();
	SumVariance9->CalculateSumVariance(VOICoOccurrenceMatrixNormalized9);
	CFeature2DSumVariance *SumVariance10 = new CFeature2DSumVariance();
	SumVariance10->CalculateSumVariance(VOICoOccurrenceMatrixNormalized10);
	CFeature2DSumVariance *SumVariance11 = new CFeature2DSumVariance();
	SumVariance11->CalculateSumVariance(VOICoOccurrenceMatrixNormalized11);
	CFeature2DSumVariance *SumVariance12 = new CFeature2DSumVariance();
	SumVariance12->CalculateSumVariance(VOICoOccurrenceMatrixNormalized12);

	CFeature2DSumEntropy *SumEntropy0 = new CFeature2DSumEntropy();
	SumEntropy0->CalculateSumEntropy(VOICoOccurrenceMatrixNormalized0);
	CFeature2DSumEntropy *SumEntropy1 = new CFeature2DSumEntropy();
	SumEntropy1->CalculateSumEntropy(VOICoOccurrenceMatrixNormalized1);
	CFeature2DSumEntropy *SumEntropy2 = new CFeature2DSumEntropy();
	SumEntropy2->CalculateSumEntropy(VOICoOccurrenceMatrixNormalized2);
	CFeature2DSumEntropy *SumEntropy3 = new CFeature2DSumEntropy();
	SumEntropy3->CalculateSumEntropy(VOICoOccurrenceMatrixNormalized3);
	CFeature2DSumEntropy *SumEntropy4 = new CFeature2DSumEntropy();
	SumEntropy4->CalculateSumEntropy(VOICoOccurrenceMatrixNormalized4);
	CFeature2DSumEntropy *SumEntropy5 = new CFeature2DSumEntropy();
	SumEntropy5->CalculateSumEntropy(VOICoOccurrenceMatrixNormalized5);
	CFeature2DSumEntropy *SumEntropy6 = new CFeature2DSumEntropy();
	SumEntropy6->CalculateSumEntropy(VOICoOccurrenceMatrixNormalized6);
	CFeature2DSumEntropy *SumEntropy7 = new CFeature2DSumEntropy();
	SumEntropy7->CalculateSumEntropy(VOICoOccurrenceMatrixNormalized7);
	CFeature2DSumEntropy *SumEntropy8 = new CFeature2DSumEntropy();
	SumEntropy8->CalculateSumEntropy(VOICoOccurrenceMatrixNormalized8);
	CFeature2DSumEntropy *SumEntropy9 = new CFeature2DSumEntropy();
	SumEntropy9->CalculateSumEntropy(VOICoOccurrenceMatrixNormalized9);
	CFeature2DSumEntropy *SumEntropy10 = new CFeature2DSumEntropy();
	SumEntropy10->CalculateSumEntropy(VOICoOccurrenceMatrixNormalized10);
	CFeature2DSumEntropy *SumEntropy11 = new CFeature2DSumEntropy();
	SumEntropy11->CalculateSumEntropy(VOICoOccurrenceMatrixNormalized11);
	CFeature2DSumEntropy *SumEntropy12 = new CFeature2DSumEntropy();
	SumEntropy12->CalculateSumEntropy(VOICoOccurrenceMatrixNormalized12);

	CFeature2DEntropy *Entropy0 = new CFeature2DEntropy();
	Entropy0->CalculateEntropy(VOICoOccurrenceMatrixNormalized0);
	CFeature2DEntropy *Entropy1 = new CFeature2DEntropy();
	Entropy1->CalculateEntropy(VOICoOccurrenceMatrixNormalized1);
	CFeature2DEntropy *Entropy2 = new CFeature2DEntropy();
	Entropy2->CalculateEntropy(VOICoOccurrenceMatrixNormalized2);
	CFeature2DEntropy *Entropy3 = new CFeature2DEntropy();
	Entropy3->CalculateEntropy(VOICoOccurrenceMatrixNormalized3);
	CFeature2DEntropy *Entropy4 = new CFeature2DEntropy();
	Entropy4->CalculateEntropy(VOICoOccurrenceMatrixNormalized4);
	CFeature2DEntropy *Entropy5 = new CFeature2DEntropy();
	Entropy5->CalculateEntropy(VOICoOccurrenceMatrixNormalized5);
	CFeature2DEntropy *Entropy6 = new CFeature2DEntropy();
	Entropy6->CalculateEntropy(VOICoOccurrenceMatrixNormalized6);
	CFeature2DEntropy *Entropy7 = new CFeature2DEntropy();
	Entropy7->CalculateEntropy(VOICoOccurrenceMatrixNormalized7);
	CFeature2DEntropy *Entropy8 = new CFeature2DEntropy();
	Entropy8->CalculateEntropy(VOICoOccurrenceMatrixNormalized8);
	CFeature2DEntropy *Entropy9 = new CFeature2DEntropy();
	Entropy9->CalculateEntropy(VOICoOccurrenceMatrixNormalized9);
	CFeature2DEntropy *Entropy10 = new CFeature2DEntropy();
	Entropy10->CalculateEntropy(VOICoOccurrenceMatrixNormalized10);
	CFeature2DEntropy *Entropy11 = new CFeature2DEntropy();
	Entropy11->CalculateEntropy(VOICoOccurrenceMatrixNormalized11);
	CFeature2DEntropy *Entropy12 = new CFeature2DEntropy();
	Entropy12->CalculateEntropy(VOICoOccurrenceMatrixNormalized12);

	CFeature2DDifferenceVariance *DifferenceVariance0 = new CFeature2DDifferenceVariance();
	DifferenceVariance0->CalculateDifferenceVariance(VOICoOccurrenceMatrixNormalized0);
	CFeature2DDifferenceVariance *DifferenceVariance1 = new CFeature2DDifferenceVariance();
	DifferenceVariance1->CalculateDifferenceVariance(VOICoOccurrenceMatrixNormalized1);
	CFeature2DDifferenceVariance *DifferenceVariance2 = new CFeature2DDifferenceVariance();
	DifferenceVariance2->CalculateDifferenceVariance(VOICoOccurrenceMatrixNormalized2);
	CFeature2DDifferenceVariance *DifferenceVariance3 = new CFeature2DDifferenceVariance();
	DifferenceVariance3->CalculateDifferenceVariance(VOICoOccurrenceMatrixNormalized3);
	CFeature2DDifferenceVariance *DifferenceVariance4 = new CFeature2DDifferenceVariance();
	DifferenceVariance4->CalculateDifferenceVariance(VOICoOccurrenceMatrixNormalized4);
	CFeature2DDifferenceVariance *DifferenceVariance5 = new CFeature2DDifferenceVariance();
	DifferenceVariance5->CalculateDifferenceVariance(VOICoOccurrenceMatrixNormalized5);
	CFeature2DDifferenceVariance *DifferenceVariance6 = new CFeature2DDifferenceVariance();
	DifferenceVariance6->CalculateDifferenceVariance(VOICoOccurrenceMatrixNormalized6);
	CFeature2DDifferenceVariance *DifferenceVariance7 = new CFeature2DDifferenceVariance();
	DifferenceVariance7->CalculateDifferenceVariance(VOICoOccurrenceMatrixNormalized7);
	CFeature2DDifferenceVariance *DifferenceVariance8 = new CFeature2DDifferenceVariance();
	DifferenceVariance8->CalculateDifferenceVariance(VOICoOccurrenceMatrixNormalized8);
	CFeature2DDifferenceVariance *DifferenceVariance9 = new CFeature2DDifferenceVariance();
	DifferenceVariance9->CalculateDifferenceVariance(VOICoOccurrenceMatrixNormalized9);
	CFeature2DDifferenceVariance *DifferenceVariance10 = new CFeature2DDifferenceVariance();
	DifferenceVariance10->CalculateDifferenceVariance(VOICoOccurrenceMatrixNormalized10);
	CFeature2DDifferenceVariance *DifferenceVariance11 = new CFeature2DDifferenceVariance();
	DifferenceVariance11->CalculateDifferenceVariance(VOICoOccurrenceMatrixNormalized11);
	CFeature2DDifferenceVariance *DifferenceVariance12 = new CFeature2DDifferenceVariance();
	DifferenceVariance12->CalculateDifferenceVariance(VOICoOccurrenceMatrixNormalized12);

	CFeature2DDifferenceEntropy *DifferenceEntropy0 = new CFeature2DDifferenceEntropy();
	DifferenceEntropy0->CalculateDifferenceEntropy(VOICoOccurrenceMatrixNormalized0);
	CFeature2DDifferenceEntropy *DifferenceEntropy1 = new CFeature2DDifferenceEntropy();
	DifferenceEntropy1->CalculateDifferenceEntropy(VOICoOccurrenceMatrixNormalized1);
	CFeature2DDifferenceEntropy *DifferenceEntropy2 = new CFeature2DDifferenceEntropy();
	DifferenceEntropy2->CalculateDifferenceEntropy(VOICoOccurrenceMatrixNormalized2);
	CFeature2DDifferenceEntropy *DifferenceEntropy3 = new CFeature2DDifferenceEntropy();
	DifferenceEntropy3->CalculateDifferenceEntropy(VOICoOccurrenceMatrixNormalized3);
	CFeature2DDifferenceEntropy *DifferenceEntropy4 = new CFeature2DDifferenceEntropy();
	DifferenceEntropy4->CalculateDifferenceEntropy(VOICoOccurrenceMatrixNormalized4);
	CFeature2DDifferenceEntropy *DifferenceEntropy5 = new CFeature2DDifferenceEntropy();
	DifferenceEntropy5->CalculateDifferenceEntropy(VOICoOccurrenceMatrixNormalized5);
	CFeature2DDifferenceEntropy *DifferenceEntropy6 = new CFeature2DDifferenceEntropy();
	DifferenceEntropy6->CalculateDifferenceEntropy(VOICoOccurrenceMatrixNormalized6);
	CFeature2DDifferenceEntropy *DifferenceEntropy7 = new CFeature2DDifferenceEntropy();
	DifferenceEntropy7->CalculateDifferenceEntropy(VOICoOccurrenceMatrixNormalized7);
	CFeature2DDifferenceEntropy *DifferenceEntropy8 = new CFeature2DDifferenceEntropy();
	DifferenceEntropy8->CalculateDifferenceEntropy(VOICoOccurrenceMatrixNormalized8);
	CFeature2DDifferenceEntropy *DifferenceEntropy9 = new CFeature2DDifferenceEntropy();
	DifferenceEntropy9->CalculateDifferenceEntropy(VOICoOccurrenceMatrixNormalized9);
	CFeature2DDifferenceEntropy *DifferenceEntropy10 = new CFeature2DDifferenceEntropy();
	DifferenceEntropy10->CalculateDifferenceEntropy(VOICoOccurrenceMatrixNormalized10);
	CFeature2DDifferenceEntropy *DifferenceEntropy11 = new CFeature2DDifferenceEntropy();
	DifferenceEntropy11->CalculateDifferenceEntropy(VOICoOccurrenceMatrixNormalized11);
	CFeature2DDifferenceEntropy *DifferenceEntropy12 = new CFeature2DDifferenceEntropy();
	DifferenceEntropy12->CalculateDifferenceEntropy(VOICoOccurrenceMatrixNormalized12);


	// Run length matrix based features







	


	Feature->SetFeatureValue(MeanValue->GetMeanValue());
	Pattern->AddFeature(Feature);

	Feature->SetFeatureValue(StandardDeviation->GetStandardDeviation());
	Pattern->AddFeature(Feature);

	Feature->SetFeatureValue(Skewness->GetSkewness());
 	Pattern->AddFeature(Feature);

	Feature->SetFeatureValue(Kurtosis->GetKurtosis());
	Pattern->AddFeature(Feature);

	// Mean Features (Co-Occurrence)
	MeanFeature->CalculateMeanFeatureValue(AngularSecondMoment0->GetAngularSecondMoment(),
										   AngularSecondMoment1->GetAngularSecondMoment(),
										   AngularSecondMoment2->GetAngularSecondMoment(),
										   AngularSecondMoment3->GetAngularSecondMoment(),
										   AngularSecondMoment4->GetAngularSecondMoment(),
										   AngularSecondMoment5->GetAngularSecondMoment(),
										   AngularSecondMoment6->GetAngularSecondMoment(),
										   AngularSecondMoment7->GetAngularSecondMoment(),
										   AngularSecondMoment8->GetAngularSecondMoment(),
										   AngularSecondMoment9->GetAngularSecondMoment(),
										   AngularSecondMoment10->GetAngularSecondMoment(),
										   AngularSecondMoment11->GetAngularSecondMoment(),
										   AngularSecondMoment12->GetAngularSecondMoment()
										  );
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(Contrast0->GetContrast(),
										   Contrast1->GetContrast(),
										   Contrast2->GetContrast(),
										   Contrast3->GetContrast(),
										   Contrast4->GetContrast(),
										   Contrast5->GetContrast(),
										   Contrast6->GetContrast(),
										   Contrast7->GetContrast(),
										   Contrast8->GetContrast(),
										   Contrast9->GetContrast(),
										   Contrast10->GetContrast(),
										   Contrast11->GetContrast(),
										   Contrast12->GetContrast()
										  );
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(Correlation0->GetCorrelation(),
										   Correlation1->GetCorrelation(),
										   Correlation2->GetCorrelation(),
										   Correlation3->GetCorrelation(),
										   Correlation4->GetCorrelation(),
										   Correlation5->GetCorrelation(),
										   Correlation6->GetCorrelation(),
										   Correlation7->GetCorrelation(),
										   Correlation8->GetCorrelation(),
										   Correlation9->GetCorrelation(),
										   Correlation10->GetCorrelation(),
										   Correlation11->GetCorrelation(),
										   Correlation12->GetCorrelation()
										  );
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(SumOfSquares0->GetSumOfSquares(),
										   SumOfSquares1->GetSumOfSquares(),
										   SumOfSquares2->GetSumOfSquares(),
										   SumOfSquares3->GetSumOfSquares(),
										   SumOfSquares4->GetSumOfSquares(),
										   SumOfSquares5->GetSumOfSquares(),
										   SumOfSquares6->GetSumOfSquares(),
										   SumOfSquares7->GetSumOfSquares(),
										   SumOfSquares8->GetSumOfSquares(),
										   SumOfSquares9->GetSumOfSquares(),
										   SumOfSquares10->GetSumOfSquares(),
										   SumOfSquares11->GetSumOfSquares(),
										   SumOfSquares12->GetSumOfSquares()
										  );
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(InverseDifferenceMoment0->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment1->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment2->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment3->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment4->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment5->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment6->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment7->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment8->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment9->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment10->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment11->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment12->GetInverseDifferenceMoment()
										  );
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(SumAverage0->GetSumAverage(),
										   SumAverage1->GetSumAverage(),
										   SumAverage2->GetSumAverage(),
										   SumAverage3->GetSumAverage(),
										   SumAverage4->GetSumAverage(),
										   SumAverage5->GetSumAverage(),
										   SumAverage6->GetSumAverage(),
										   SumAverage7->GetSumAverage(),
										   SumAverage8->GetSumAverage(),
										   SumAverage9->GetSumAverage(),
										   SumAverage10->GetSumAverage(),
										   SumAverage11->GetSumAverage(),
										   SumAverage12->GetSumAverage()
										  );
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(SumVariance0->GetSumVariance(),
										   SumVariance1->GetSumVariance(),
										   SumVariance2->GetSumVariance(),
										   SumVariance3->GetSumVariance(),
										   SumVariance4->GetSumVariance(),
										   SumVariance5->GetSumVariance(),
										   SumVariance6->GetSumVariance(),
										   SumVariance7->GetSumVariance(),
										   SumVariance8->GetSumVariance(),
										   SumVariance9->GetSumVariance(),
										   SumVariance10->GetSumVariance(),
										   SumVariance11->GetSumVariance(),
										   SumVariance12->GetSumVariance()
										  );
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(SumEntropy0->GetSumEntropy(),
										   SumEntropy1->GetSumEntropy(),
										   SumEntropy2->GetSumEntropy(),
										   SumEntropy3->GetSumEntropy(),
										   SumEntropy4->GetSumEntropy(),
										   SumEntropy5->GetSumEntropy(),
										   SumEntropy6->GetSumEntropy(),
										   SumEntropy7->GetSumEntropy(),
										   SumEntropy8->GetSumEntropy(),
										   SumEntropy9->GetSumEntropy(),
										   SumEntropy10->GetSumEntropy(),
										   SumEntropy11->GetSumEntropy(),
										   SumEntropy12->GetSumEntropy()
										  );
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(Entropy0->GetEntropy(),
										   Entropy1->GetEntropy(),
										   Entropy2->GetEntropy(),
										   Entropy3->GetEntropy(),
										   Entropy4->GetEntropy(),
										   Entropy5->GetEntropy(),
										   Entropy6->GetEntropy(),
										   Entropy7->GetEntropy(),
										   Entropy8->GetEntropy(),
										   Entropy9->GetEntropy(),
										   Entropy10->GetEntropy(),
										   Entropy11->GetEntropy(),
										   Entropy12->GetEntropy()
										  );
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(DifferenceVariance0->GetDifferenceVariance(),
										   DifferenceVariance1->GetDifferenceVariance(),
										   DifferenceVariance2->GetDifferenceVariance(),
										   DifferenceVariance3->GetDifferenceVariance(),
										   DifferenceVariance4->GetDifferenceVariance(),
										   DifferenceVariance5->GetDifferenceVariance(),
										   DifferenceVariance6->GetDifferenceVariance(),
										   DifferenceVariance7->GetDifferenceVariance(),
										   DifferenceVariance8->GetDifferenceVariance(),
										   DifferenceVariance9->GetDifferenceVariance(),
										   DifferenceVariance10->GetDifferenceVariance(),
										   DifferenceVariance11->GetDifferenceVariance(),
										   DifferenceVariance12->GetDifferenceVariance()
										  );
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	MeanFeature->CalculateMeanFeatureValue(DifferenceEntropy0->GetDifferenceEntropy(),
										   DifferenceEntropy1->GetDifferenceEntropy(),
										   DifferenceEntropy2->GetDifferenceEntropy(),
										   DifferenceEntropy3->GetDifferenceEntropy(),
										   DifferenceEntropy4->GetDifferenceEntropy(),
										   DifferenceEntropy5->GetDifferenceEntropy(),
										   DifferenceEntropy6->GetDifferenceEntropy(),
										   DifferenceEntropy7->GetDifferenceEntropy(),
										   DifferenceEntropy8->GetDifferenceEntropy(),
										   DifferenceEntropy9->GetDifferenceEntropy(),
										   DifferenceEntropy10->GetDifferenceEntropy(),
										   DifferenceEntropy11->GetDifferenceEntropy(),
										   DifferenceEntropy12->GetDifferenceEntropy()
										  );
	Feature->SetFeatureValue(MeanFeature->GetMeanFeatureValue());
	Pattern->AddFeature(Feature);

	// Range Features (Co-Occurrence)
	RangeFeature->CalculateRangeFeatureValue(AngularSecondMoment0->GetAngularSecondMoment(),
										   AngularSecondMoment1->GetAngularSecondMoment(),
										   AngularSecondMoment2->GetAngularSecondMoment(),
										   AngularSecondMoment3->GetAngularSecondMoment(),
										   AngularSecondMoment4->GetAngularSecondMoment(),
										   AngularSecondMoment5->GetAngularSecondMoment(),
										   AngularSecondMoment6->GetAngularSecondMoment(),
										   AngularSecondMoment7->GetAngularSecondMoment(),
										   AngularSecondMoment8->GetAngularSecondMoment(),
										   AngularSecondMoment9->GetAngularSecondMoment(),
										   AngularSecondMoment10->GetAngularSecondMoment(),
										   AngularSecondMoment11->GetAngularSecondMoment(),
										   AngularSecondMoment12->GetAngularSecondMoment()
										  );
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(Contrast0->GetContrast(),
										   Contrast1->GetContrast(),
										   Contrast2->GetContrast(),
										   Contrast3->GetContrast(),
										   Contrast4->GetContrast(),
										   Contrast5->GetContrast(),
										   Contrast6->GetContrast(),
										   Contrast7->GetContrast(),
										   Contrast8->GetContrast(),
										   Contrast9->GetContrast(),
										   Contrast10->GetContrast(),
										   Contrast11->GetContrast(),
										   Contrast12->GetContrast()
										  );
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(Correlation0->GetCorrelation(),
										   Correlation1->GetCorrelation(),
										   Correlation2->GetCorrelation(),
										   Correlation3->GetCorrelation(),
										   Correlation4->GetCorrelation(),
										   Correlation5->GetCorrelation(),
										   Correlation6->GetCorrelation(),
										   Correlation7->GetCorrelation(),
										   Correlation8->GetCorrelation(),
										   Correlation9->GetCorrelation(),
										   Correlation10->GetCorrelation(),
										   Correlation11->GetCorrelation(),
										   Correlation12->GetCorrelation()
										  );
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(SumOfSquares0->GetSumOfSquares(),
										   SumOfSquares1->GetSumOfSquares(),
										   SumOfSquares2->GetSumOfSquares(),
										   SumOfSquares3->GetSumOfSquares(),
										   SumOfSquares4->GetSumOfSquares(),
										   SumOfSquares5->GetSumOfSquares(),
										   SumOfSquares6->GetSumOfSquares(),
										   SumOfSquares7->GetSumOfSquares(),
										   SumOfSquares8->GetSumOfSquares(),
										   SumOfSquares9->GetSumOfSquares(),
										   SumOfSquares10->GetSumOfSquares(),
										   SumOfSquares11->GetSumOfSquares(),
										   SumOfSquares12->GetSumOfSquares()
										  );
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(InverseDifferenceMoment0->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment1->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment2->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment3->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment4->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment5->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment6->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment7->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment8->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment9->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment10->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment11->GetInverseDifferenceMoment(),
										   InverseDifferenceMoment12->GetInverseDifferenceMoment()
										  );
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(SumAverage0->GetSumAverage(),
										   SumAverage1->GetSumAverage(),
										   SumAverage2->GetSumAverage(),
										   SumAverage3->GetSumAverage(),
										   SumAverage4->GetSumAverage(),
										   SumAverage5->GetSumAverage(),
										   SumAverage6->GetSumAverage(),
										   SumAverage7->GetSumAverage(),
										   SumAverage8->GetSumAverage(),
										   SumAverage9->GetSumAverage(),
										   SumAverage10->GetSumAverage(),
										   SumAverage11->GetSumAverage(),
										   SumAverage12->GetSumAverage()
										  );
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(SumVariance0->GetSumVariance(),
										   SumVariance1->GetSumVariance(),
										   SumVariance2->GetSumVariance(),
										   SumVariance3->GetSumVariance(),
										   SumVariance4->GetSumVariance(),
										   SumVariance5->GetSumVariance(),
										   SumVariance6->GetSumVariance(),
										   SumVariance7->GetSumVariance(),
										   SumVariance8->GetSumVariance(),
										   SumVariance9->GetSumVariance(),
										   SumVariance10->GetSumVariance(),
										   SumVariance11->GetSumVariance(),
										   SumVariance12->GetSumVariance()
										  );
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(SumEntropy0->GetSumEntropy(),
										   SumEntropy1->GetSumEntropy(),
										   SumEntropy2->GetSumEntropy(),
										   SumEntropy3->GetSumEntropy(),
										   SumEntropy4->GetSumEntropy(),
										   SumEntropy5->GetSumEntropy(),
										   SumEntropy6->GetSumEntropy(),
										   SumEntropy7->GetSumEntropy(),
										   SumEntropy8->GetSumEntropy(),
										   SumEntropy9->GetSumEntropy(),
										   SumEntropy10->GetSumEntropy(),
										   SumEntropy11->GetSumEntropy(),
										   SumEntropy12->GetSumEntropy()
										  );
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(Entropy0->GetEntropy(),
										   Entropy1->GetEntropy(),
										   Entropy2->GetEntropy(),
										   Entropy3->GetEntropy(),
										   Entropy4->GetEntropy(),
										   Entropy5->GetEntropy(),
										   Entropy6->GetEntropy(),
										   Entropy7->GetEntropy(),
										   Entropy8->GetEntropy(),
										   Entropy9->GetEntropy(),
										   Entropy10->GetEntropy(),
										   Entropy11->GetEntropy(),
										   Entropy12->GetEntropy()
										  );
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(DifferenceVariance0->GetDifferenceVariance(),
										   DifferenceVariance1->GetDifferenceVariance(),
										   DifferenceVariance2->GetDifferenceVariance(),
										   DifferenceVariance3->GetDifferenceVariance(),
										   DifferenceVariance4->GetDifferenceVariance(),
										   DifferenceVariance5->GetDifferenceVariance(),
										   DifferenceVariance6->GetDifferenceVariance(),
										   DifferenceVariance7->GetDifferenceVariance(),
										   DifferenceVariance8->GetDifferenceVariance(),
										   DifferenceVariance9->GetDifferenceVariance(),
										   DifferenceVariance10->GetDifferenceVariance(),
										   DifferenceVariance11->GetDifferenceVariance(),
										   DifferenceVariance12->GetDifferenceVariance()
										  );
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	RangeFeature->CalculateRangeFeatureValue(DifferenceEntropy0->GetDifferenceEntropy(),
										   DifferenceEntropy1->GetDifferenceEntropy(),
										   DifferenceEntropy2->GetDifferenceEntropy(),
										   DifferenceEntropy3->GetDifferenceEntropy(),
										   DifferenceEntropy4->GetDifferenceEntropy(),
										   DifferenceEntropy5->GetDifferenceEntropy(),
										   DifferenceEntropy6->GetDifferenceEntropy(),
										   DifferenceEntropy7->GetDifferenceEntropy(),
										   DifferenceEntropy8->GetDifferenceEntropy(),
										   DifferenceEntropy9->GetDifferenceEntropy(),
										   DifferenceEntropy10->GetDifferenceEntropy(),
										   DifferenceEntropy11->GetDifferenceEntropy(),
										   DifferenceEntropy12->GetDifferenceEntropy()
										  );
	Feature->SetFeatureValue(RangeFeature->GetRangeFeatureValue());
	Pattern->AddFeature(Feature);

	// Mean Features (Run Length)

	// Range Features (Run Length)


	

	delete DifferenceEntropy0;
	DifferenceEntropy0 = NULL;
	delete DifferenceEntropy1;
	DifferenceEntropy1 = NULL;
	delete DifferenceEntropy2;
	DifferenceEntropy2 = NULL;
	delete DifferenceEntropy3;
	DifferenceEntropy3 = NULL;
	delete DifferenceEntropy4;
	DifferenceEntropy4 = NULL;
	delete DifferenceEntropy5;
	DifferenceEntropy5 = NULL;
	delete DifferenceEntropy6;
	DifferenceEntropy6 = NULL;
	delete DifferenceEntropy7;
	DifferenceEntropy7 = NULL;
	delete DifferenceEntropy8;
	DifferenceEntropy8 = NULL;
	delete DifferenceEntropy9;
	DifferenceEntropy9 = NULL;
	delete DifferenceEntropy10;
	DifferenceEntropy10 = NULL;
	delete DifferenceEntropy11;
	DifferenceEntropy11 = NULL;
	delete DifferenceEntropy12;
	DifferenceEntropy12 = NULL;

	delete DifferenceVariance0;
	DifferenceVariance0 = NULL;
	delete DifferenceVariance1;
	DifferenceVariance1 = NULL;
	delete DifferenceVariance2;
	DifferenceVariance2 = NULL;
	delete DifferenceVariance3;
	DifferenceVariance3 = NULL;
	delete DifferenceVariance4;
	DifferenceVariance4 = NULL;
	delete DifferenceVariance5;
	DifferenceVariance5 = NULL;
	delete DifferenceVariance6;
	DifferenceVariance6 = NULL;
	delete DifferenceVariance7;
	DifferenceVariance7 = NULL;
	delete DifferenceVariance8;
	DifferenceVariance8 = NULL;
	delete DifferenceVariance9;
	DifferenceVariance9 = NULL;
	delete DifferenceVariance10;
	DifferenceVariance10 = NULL;
	delete DifferenceVariance11;
	DifferenceVariance11 = NULL;
	delete DifferenceVariance12;
	DifferenceVariance12 = NULL;

	delete Entropy0;
	Entropy0 = NULL;
	delete Entropy1;
	Entropy1 = NULL;
	delete Entropy2;
	Entropy2 = NULL;
	delete Entropy3;
	Entropy3 = NULL;
	delete Entropy4;
	Entropy4 = NULL;
	delete Entropy5;
	Entropy5 = NULL;
	delete Entropy6;
	Entropy6 = NULL;
	delete Entropy7;
	Entropy7 = NULL;
	delete Entropy8;
	Entropy8 = NULL;
	delete Entropy9;
	Entropy9 = NULL;
	delete Entropy10;
	Entropy10 = NULL;
	delete Entropy11;
	Entropy11 = NULL;
	delete Entropy12;
	Entropy12 = NULL;

	delete SumEntropy0;
	SumEntropy0 = NULL;
	delete SumEntropy1;
	SumEntropy1 = NULL;
	delete SumEntropy2;
	SumEntropy2 = NULL;
	delete SumEntropy3;
	SumEntropy3 = NULL;
	delete SumEntropy4;
	SumEntropy4 = NULL;
	delete SumEntropy5;
	SumEntropy5 = NULL;
	delete SumEntropy6;
	SumEntropy6 = NULL;
	delete SumEntropy7;
	SumEntropy7 = NULL;
	delete SumEntropy8;
	SumEntropy8 = NULL;
	delete SumEntropy9;
	SumEntropy9 = NULL;
	delete SumEntropy10;
	SumEntropy10 = NULL;
	delete SumEntropy11;
	SumEntropy11 = NULL;
	delete SumEntropy12;
	SumEntropy12 = NULL;

	delete SumVariance0;
	SumVariance0 = NULL;
	delete SumVariance1;
	SumVariance1 = NULL;
	delete SumVariance2;
	SumVariance2 = NULL;
	delete SumVariance3;
	SumVariance3 = NULL;
	delete SumVariance4;
	SumVariance4 = NULL;
	delete SumVariance5;
	SumVariance5 = NULL;
	delete SumVariance6;
	SumVariance6 = NULL;
	delete SumVariance7;
	SumVariance7 = NULL;
	delete SumVariance8;
	SumVariance8 = NULL;
	delete SumVariance9;
	SumVariance9 = NULL;
	delete SumVariance10;
	SumVariance10 = NULL;
	delete SumVariance11;
	SumVariance11 = NULL;
	delete SumVariance12;
	SumVariance12 = NULL;

	delete SumAverage0;
	SumAverage0 = NULL;
	delete SumAverage1;
	SumAverage1 = NULL;
	delete SumAverage2;
	SumAverage2 = NULL;
	delete SumAverage3;
	SumAverage3 = NULL;
	delete SumAverage4;
	SumAverage4 = NULL;
	delete SumAverage5;
	SumAverage5 = NULL;
	delete SumAverage6;
	SumAverage6 = NULL;
	delete SumAverage7;
	SumAverage7 = NULL;
	delete SumAverage8;
	SumAverage8 = NULL;
	delete SumAverage9;
	SumAverage9 = NULL;
	delete SumAverage10;
	SumAverage10 = NULL;
	delete SumAverage11;
	SumAverage11 = NULL;
	delete SumAverage12;
	SumAverage12 = NULL;

	delete InverseDifferenceMoment0;
	InverseDifferenceMoment0 = NULL;
	delete InverseDifferenceMoment1;
	InverseDifferenceMoment1 = NULL;
	delete InverseDifferenceMoment2;
	InverseDifferenceMoment2 = NULL;
	delete InverseDifferenceMoment3;
	InverseDifferenceMoment3 = NULL;
	delete InverseDifferenceMoment4;
	InverseDifferenceMoment4 = NULL;
	delete InverseDifferenceMoment5;
	InverseDifferenceMoment5 = NULL;
	delete InverseDifferenceMoment6;
	InverseDifferenceMoment6 = NULL;
	delete InverseDifferenceMoment7;
	InverseDifferenceMoment7 = NULL;
	delete InverseDifferenceMoment8;
	InverseDifferenceMoment8 = NULL;
	delete InverseDifferenceMoment9;
	InverseDifferenceMoment9 = NULL;
	delete InverseDifferenceMoment10;
	InverseDifferenceMoment10 = NULL;
	delete InverseDifferenceMoment11;
	InverseDifferenceMoment11 = NULL;
	delete InverseDifferenceMoment12;
	InverseDifferenceMoment12 = NULL;

	delete SumOfSquares0;
	SumOfSquares0 = NULL;
	delete SumOfSquares1;
	SumOfSquares1 = NULL;
	delete SumOfSquares2;
	SumOfSquares2 = NULL;
	delete SumOfSquares3;
	SumOfSquares3 = NULL;
	delete SumOfSquares4;
	SumOfSquares4 = NULL;
	delete SumOfSquares5;
	SumOfSquares5 = NULL;
	delete SumOfSquares6;
	SumOfSquares6 = NULL;
	delete SumOfSquares7;
	SumOfSquares7 = NULL;
	delete SumOfSquares8;
	SumOfSquares8 = NULL;
	delete SumOfSquares9;
	SumOfSquares9 = NULL;
	delete SumOfSquares10;
	SumOfSquares10 = NULL;
	delete SumOfSquares11;
	SumOfSquares11 = NULL;
	delete SumOfSquares12;
	SumOfSquares12 = NULL;

	delete Correlation0;
	Correlation0 = NULL;
	delete Correlation1;
	Correlation1 = NULL;
	delete Correlation2;
	Correlation2 = NULL;
	delete Correlation3;
	Correlation3 = NULL;
	delete Correlation4;
	Correlation4 = NULL;
	delete Correlation5;
	Correlation5 = NULL;
	delete Correlation6;
	Correlation6 = NULL;
	delete Correlation7;
	Correlation7 = NULL;
	delete Correlation8;
	Correlation8 = NULL;
	delete Correlation9;
	Correlation9 = NULL;
	delete Correlation10;
	Correlation10 = NULL;
	delete Correlation11;
	Correlation11 = NULL;
	delete Correlation12;
	Correlation12 = NULL;

	delete Contrast0;
	Contrast0 = NULL;
	delete Contrast1;
	Contrast1 = NULL;
	delete Contrast2;
	Contrast2 = NULL;
	delete Contrast3;
	Contrast3 = NULL;
	delete Contrast4;
	Contrast4 = NULL;
	delete Contrast5;
	Contrast5 = NULL;
	delete Contrast6;
	Contrast6 = NULL;
	delete Contrast7;
	Contrast7 = NULL;
	delete Contrast8;
	Contrast8 = NULL;
	delete Contrast9;
	Contrast9 = NULL;
	delete Contrast10;
	Contrast10 = NULL;
	delete Contrast11;
	Contrast11 = NULL;
	delete Contrast12;
	Contrast12 = NULL;

	delete AngularSecondMoment0;
	AngularSecondMoment0 = NULL;
	delete AngularSecondMoment1;
	AngularSecondMoment1 = NULL;
	delete AngularSecondMoment2;
	AngularSecondMoment2 = NULL;
	delete AngularSecondMoment3;
	AngularSecondMoment3 = NULL;
	delete AngularSecondMoment4;
	AngularSecondMoment4 = NULL;
	delete AngularSecondMoment5;
	AngularSecondMoment5 = NULL;
	delete AngularSecondMoment6;
	AngularSecondMoment6 = NULL;
	delete AngularSecondMoment7;
	AngularSecondMoment7 = NULL;
	delete AngularSecondMoment8;
	AngularSecondMoment8 = NULL;
	delete AngularSecondMoment9;
	AngularSecondMoment9 = NULL;
	delete AngularSecondMoment10;
	AngularSecondMoment10 = NULL;
	delete AngularSecondMoment11;
	AngularSecondMoment11 = NULL;
	delete AngularSecondMoment12;
	AngularSecondMoment12 = NULL;

	delete CoOccurrenceMatrixes;
	CoOccurrenceMatrixes = NULL;

	delete VOICoOccurrenceMatrixNormalized0;
	VOICoOccurrenceMatrixNormalized0 = NULL;
	delete VOICoOccurrenceMatrixNormalized1;
	VOICoOccurrenceMatrixNormalized1 = NULL;
	delete VOICoOccurrenceMatrixNormalized2;
	VOICoOccurrenceMatrixNormalized2 = NULL;
	delete VOICoOccurrenceMatrixNormalized3;
	VOICoOccurrenceMatrixNormalized3 = NULL;
	delete VOICoOccurrenceMatrixNormalized4;
	VOICoOccurrenceMatrixNormalized4 = NULL;
	delete VOICoOccurrenceMatrixNormalized5;
	VOICoOccurrenceMatrixNormalized5 = NULL;
	delete VOICoOccurrenceMatrixNormalized6;
	VOICoOccurrenceMatrixNormalized6 = NULL;
	delete VOICoOccurrenceMatrixNormalized7;
	VOICoOccurrenceMatrixNormalized7 = NULL;
	delete VOICoOccurrenceMatrixNormalized8;
	VOICoOccurrenceMatrixNormalized8 = NULL;
	delete VOICoOccurrenceMatrixNormalized9;
	VOICoOccurrenceMatrixNormalized9 = NULL;
	delete VOICoOccurrenceMatrixNormalized10;
	VOICoOccurrenceMatrixNormalized10 = NULL;
	delete VOICoOccurrenceMatrixNormalized11;
	VOICoOccurrenceMatrixNormalized11 = NULL;
	delete VOICoOccurrenceMatrixNormalized12;
	VOICoOccurrenceMatrixNormalized12 = NULL;

	delete VOICoOccurrenceMatrix0;
	VOICoOccurrenceMatrix0 = NULL;
	delete VOICoOccurrenceMatrix1;
	VOICoOccurrenceMatrix1 = NULL;
	delete VOICoOccurrenceMatrix2;
	VOICoOccurrenceMatrix2 = NULL;
	delete VOICoOccurrenceMatrix3;
	VOICoOccurrenceMatrix3 = NULL;
	delete VOICoOccurrenceMatrix4;
	VOICoOccurrenceMatrix4 = NULL;
	delete VOICoOccurrenceMatrix5;
	VOICoOccurrenceMatrix5 = NULL;
	delete VOICoOccurrenceMatrix6;
	VOICoOccurrenceMatrix6 = NULL;
	delete VOICoOccurrenceMatrix7;
	VOICoOccurrenceMatrix7 = NULL;
	delete VOICoOccurrenceMatrix8;
	VOICoOccurrenceMatrix8 = NULL;
	delete VOICoOccurrenceMatrix9;
	VOICoOccurrenceMatrix9 = NULL;
	delete VOICoOccurrenceMatrix10;
	VOICoOccurrenceMatrix10 = NULL;
	delete VOICoOccurrenceMatrix11;
	VOICoOccurrenceMatrix11 = NULL;
	delete VOICoOccurrenceMatrix12;
	VOICoOccurrenceMatrix12 = NULL;
	
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
	
	delete Feature;
	Feature = NULL;

	return Pattern;

}
