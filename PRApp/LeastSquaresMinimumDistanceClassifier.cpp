#include "stdafx.h"
#include "LeastSquaresMinimumDistanceClassifier.h"

CLeastSquaresMinimumDistanceClassifier::CLeastSquaresMinimumDistanceClassifier()
{

	m_TransformationCoefficientsMatrix = NULL;
	m_iOrder = 0;

}

CLeastSquaresMinimumDistanceClassifier::CLeastSquaresMinimumDistanceClassifier(CDataSet *pDataSet, int iOrder, CPattern *pClusteringPoints, int iClusteringPointsSize)
{

	InitializeClassifier(pDataSet, iOrder, pClusteringPoints, iClusteringPointsSize);

}

CLeastSquaresMinimumDistanceClassifier::~CLeastSquaresMinimumDistanceClassifier()
{

	DeleteTransformationCoefficientsMatrix();

}

void CLeastSquaresMinimumDistanceClassifier::InitializeClassifier (CDataSet *pDataSet, int iOrder, CPattern *pClusteringPoints, int iClusteringPointsSize){

	m_iOrder = iOrder;
	m_TransformationCoefficientsMatrix = LeastSquaresMapping(pDataSet, iOrder, pClusteringPoints, iClusteringPointsSize);
	
}

void CLeastSquaresMinimumDistanceClassifier::DeleteTransformationCoefficientsMatrix (void){

	if (m_TransformationCoefficientsMatrix != NULL){
		delete m_TransformationCoefficientsMatrix;
		m_TransformationCoefficientsMatrix = NULL;
	}

}

void CLeastSquaresMinimumDistanceClassifier::Classify (CDataSet *pDataSet, CPattern *pUnknownPattern){

	int iClassIndexRet = 0;
	int i;
	int iMaxDiscriminantFunctionClassIndex = 0;
	double dblMaxDiscriminantFunctionValue = (std::numeric_limits<double>::max)();

	CLeastSquaresMinimumDistanceClassifierDiscriminantFunction *DiscriminantFunction = new CLeastSquaresMinimumDistanceClassifierDiscriminantFunction[pDataSet->GetNumberOfClasses()];
	CPattern *UnknownPatternMapped = new CPattern(1);
	CDataMatrix2D *TransformationCoefficientsMatrix = NULL;

	MapPattern(pUnknownPattern, UnknownPatternMapped, m_iOrder); 
	
	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		DiscriminantFunction[i].CalculateClassDiscriminantFunctionLeastSquareMinimumDistance(i, UnknownPatternMapped, m_TransformationCoefficientsMatrix);
	}

	dblMaxDiscriminantFunctionValue = DiscriminantFunction[0].GetDiscriminantFunctionValue();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		if (DiscriminantFunction[i].GetDiscriminantFunctionValue() > dblMaxDiscriminantFunctionValue){
			dblMaxDiscriminantFunctionValue = DiscriminantFunction[i].GetDiscriminantFunctionValue();
			iMaxDiscriminantFunctionClassIndex = i;
		}
	}

	iClassIndexRet = iMaxDiscriminantFunctionClassIndex;

	delete TransformationCoefficientsMatrix;
	TransformationCoefficientsMatrix = NULL;
	delete UnknownPatternMapped;
	UnknownPatternMapped = NULL;
	delete [] DiscriminantFunction;
	DiscriminantFunction = NULL;


	SetClassifierOutput(iClassIndexRet);

}

void CLeastSquaresMinimumDistanceClassifier::Classify (CDataSet *pDataSet, CDataSet *pUnknownPatterns){

	for (int i=0;i<pUnknownPatterns->GetNumberOfClasses();i++){
		for (int j=0;j<pUnknownPatterns->GetClass(i)->GetNumberOfPatterns();j++){
			Classify(pDataSet, pUnknownPatterns->GetClass(i)->GetPattern(j));
			pUnknownPatterns->GetTruthTable()->SetTruthTableValue(i, GetClassifierOutput(), pUnknownPatterns->GetTruthTable()->GetTruthTableValue(i, GetClassifierOutput()) + 1);
		}
	}

}

CDataMatrix2D *CLeastSquaresMinimumDistanceClassifier::LeastSquaresMapping (CDataSet *pDataSet, int iOrder, CPattern *pClusteringPoints, int iClusteringPointsSize){

	int i, j;
	int iNumberOfMappedFeatures = 0;
	CDataSet *AugmentedDataSet = new CDataSet();
	double *dblClassProbability = new double [pDataSet->GetNumberOfClasses()];
	CDataMatrix2D *MatrixTransposeMultiplicationTmp = NULL;
	CDataMatrix2D *AugmentedMatrixTransposeMultiplicationTmp = NULL;
	CDataMatrix2D *SumAugmentedMatrixTransposeMultiplicationInversed = NULL;
	CDataMatrix2D *TransformationCoefficientsMatrix = NULL;

// 	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
// 		if (pDataSet->GetClass(i)->GetNumberOfPatterns() > iOrder){
// 			return NULL;
// 		}
// 	}

	if (pDataSet->GetNumberOfClasses() != iClusteringPointsSize){
		return NULL;
	}
	
	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		dblClassProbability[i] = (1.0f / (pDataSet->GetClass(i)->GetNumberOfPatterns() * pDataSet->GetNumberOfClasses()));
	}

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		AugmentedDataSet->AddClass(pDataSet->GetClass(i)->GetNumberOfPatterns(), 1);
	}

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			MapPattern(pDataSet->GetClass(i)->GetPattern(j), AugmentedDataSet->GetClass(i)->GetPattern(j), iOrder);
		}
	}

	CDataMatrix2D *SumMatrixTransposeMultiplicationClass = new CDataMatrix2D(pClusteringPoints[0].GetNumberOfFeatures(), AugmentedDataSet->GetClass(0)->GetNumberOfFeaturesPerPattern());
	CDataMatrix2D *SumMatrixTransposeMultiplication = new CDataMatrix2D(pClusteringPoints[0].GetNumberOfFeatures(), AugmentedDataSet->GetClass(0)->GetNumberOfFeaturesPerPattern());

	for (i=0;i<AugmentedDataSet->GetNumberOfClasses();i++){
		SumMatrixTransposeMultiplicationClass->Zeros();
		for (j=0;j<AugmentedDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			MatrixTransposeMultiplicationTmp = PatternToDataMatrixTransposeMultiplication(&pClusteringPoints[i], AugmentedDataSet->GetClass(i)->GetPattern(j));
			SumMatrixTransposeMultiplicationClass->AddToDataMatrix(MatrixTransposeMultiplicationTmp);
			delete MatrixTransposeMultiplicationTmp;
			MatrixTransposeMultiplicationTmp = NULL;
		}
		SumMatrixTransposeMultiplicationClass->MultiplyScalarToMatrix(dblClassProbability[i]);
		SumMatrixTransposeMultiplication->AddToDataMatrix(SumMatrixTransposeMultiplicationClass);
	}
	
	CDataMatrix2D *SumAugmentedMatrixTransposeMultiplicationClass = new CDataMatrix2D(AugmentedDataSet->GetClass(0)->GetNumberOfFeaturesPerPattern(), AugmentedDataSet->GetClass(0)->GetNumberOfFeaturesPerPattern());
	CDataMatrix2D *SumAugmentedMatrixTransposeMultiplication = new CDataMatrix2D(AugmentedDataSet->GetClass(0)->GetNumberOfFeaturesPerPattern(), AugmentedDataSet->GetClass(0)->GetNumberOfFeaturesPerPattern());

	for (i=0;i<AugmentedDataSet->GetNumberOfClasses();i++){
		SumAugmentedMatrixTransposeMultiplicationClass->Zeros();
		for (j=0;j<AugmentedDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			AugmentedMatrixTransposeMultiplicationTmp = AugmentedPatternToDataMatrixTransposeMultiplication(AugmentedDataSet->GetClass(i)->GetPattern(j));
			SumAugmentedMatrixTransposeMultiplicationClass->AddToDataMatrix(AugmentedMatrixTransposeMultiplicationTmp);
			delete AugmentedMatrixTransposeMultiplicationTmp;
			AugmentedMatrixTransposeMultiplicationTmp = NULL;
		}
		SumAugmentedMatrixTransposeMultiplicationClass->MultiplyScalarToMatrix(dblClassProbability[i]);
		SumAugmentedMatrixTransposeMultiplication->AddToDataMatrix(SumAugmentedMatrixTransposeMultiplicationClass);
	}
	
	SumAugmentedMatrixTransposeMultiplicationInversed = SumAugmentedMatrixTransposeMultiplication->InverseMatrix();

	TransformationCoefficientsMatrix = SumMatrixTransposeMultiplication->Multiply(SumAugmentedMatrixTransposeMultiplicationInversed);

	delete SumAugmentedMatrixTransposeMultiplicationInversed;
	SumAugmentedMatrixTransposeMultiplicationInversed = NULL;
	delete SumAugmentedMatrixTransposeMultiplication;
	SumAugmentedMatrixTransposeMultiplication = NULL;
	delete SumAugmentedMatrixTransposeMultiplicationClass;
	SumAugmentedMatrixTransposeMultiplicationClass = NULL;
	delete SumMatrixTransposeMultiplication;
	SumMatrixTransposeMultiplication = NULL;
	delete SumMatrixTransposeMultiplicationClass;
	SumMatrixTransposeMultiplicationClass = NULL;
	delete [] dblClassProbability;
	dblClassProbability = NULL;
	delete AugmentedDataSet;
	AugmentedDataSet = NULL;

	return TransformationCoefficientsMatrix;

}

void CLeastSquaresMinimumDistanceClassifier::MapPattern (CPattern *pPattern, CPattern *pMappedPattern, int iOrder){

	int i, j, k, l, m;

	CExhaustiveSearch *ExhaustiveSearch = new CExhaustiveSearch();
	CPattern *CombinationPattern = NULL;
	CPattern *TmpPattern = NULL;
	CPattern *TmpPattern2 = NULL;
	CFeature *AugmentationFeature = new CFeature();
	AugmentationFeature->SetFeatureValue(-1.0f);

	pMappedPattern->RemoveAllFeatures();
	
	if (iOrder == 1){
		for (i=0;i<pPattern->GetNumberOfFeatures();i++){
			pMappedPattern->AddFeature(pPattern->GetFeature(i));
		}
	}
	else{
		for (i=0;i<pPattern->GetNumberOfFeatures();i++){
			ExhaustiveSearch->CreateCombinations(pPattern->GetNumberOfFeatures(), (i + 1));
				for (k=0;k<(iOrder - ExhaustiveSearch->GetCombination(0)->GetCombinationVectorSize() + 1);k++){
					for (j=0;j<ExhaustiveSearch->GetNumberOfCombinations();j++){
						if (k == 0){
							CombinationPattern = pPattern->CopyPatternFromCombination(ExhaustiveSearch->GetCombination(j));
							TmpPattern = CalculateFeatures(CombinationPattern);
							for (m=0;m<TmpPattern->GetNumberOfFeatures();m++){
								pMappedPattern->AddFeature(TmpPattern->GetFeature(m));
							}
							delete TmpPattern;
							TmpPattern = NULL;
							delete CombinationPattern;
							CombinationPattern = NULL;
						}
						else{
							for (l=0;l<ExhaustiveSearch->GetCombination(0)->GetCombinationVectorSize();l++){
								CombinationPattern = pPattern->CopyPatternFromCombination(ExhaustiveSearch->GetCombination(j));
								TmpPattern = CombinationPattern->CopyPattern();
								TmpPattern->GetFeature(l)->SetFeatureValue(pow(CombinationPattern->GetFeature(l)->GetFeatureValue(), (k + 1)));
								TmpPattern2 = CalculateFeatures(TmpPattern);
								for (m=0;m<TmpPattern2->GetNumberOfFeatures();m++){
									pMappedPattern->AddFeature(TmpPattern2->GetFeature(m));
								}
								delete TmpPattern2;
								TmpPattern2 = NULL;
								delete TmpPattern;
								TmpPattern = NULL;
								delete CombinationPattern;
								CombinationPattern = NULL;
							}
						}
					}
				}
			ExhaustiveSearch->DeleteCombinations();
		}
	}

	pMappedPattern->AddFeature(AugmentationFeature);

	delete AugmentationFeature;
	AugmentationFeature = NULL;
	delete ExhaustiveSearch;
	ExhaustiveSearch = NULL;

}

CPattern *CLeastSquaresMinimumDistanceClassifier::CalculateFeatures (CPattern *pPattern){

	int i;
	
	CPattern *CalculatedPattern = new CPattern(1);
	for (i=0;i<CalculatedPattern->GetNumberOfFeatures();i++){
		CalculatedPattern->GetFeature(i)->SetFeatureValue(1.0f);
	}

	for (i=0;i<pPattern->GetNumberOfFeatures();i++){
		CalculatedPattern->GetFeature(0)->SetFeatureValue((CalculatedPattern->GetFeature(0)->GetFeatureValue() * pPattern->GetFeature(i)->GetFeatureValue()));
	}

	return CalculatedPattern;

}

CDataMatrix2D *CLeastSquaresMinimumDistanceClassifier::PatternToDataMatrixTransposeMultiplication (CPattern *pClassClusteringPoint, CPattern *pPattern){

	CDataMatrix2D *DataMatrixTransposeMultiplication = NULL;
	CDataMatrix2D *ClassClusteringPointMatrix = NULL;
	CDataMatrix2D *ClassClusteringPointMatrixTransposed = NULL;
	CDataMatrix2D *PatternMatrix = NULL;

	CClassToDataMatrix *ClassToDataMatrix = new CClassToDataMatrix();

	ClassClusteringPointMatrix = ClassToDataMatrix->PatternToDataMatrix2D(pClassClusteringPoint);
	ClassClusteringPointMatrixTransposed = ClassClusteringPointMatrix->TransposeMatrix();

	PatternMatrix = ClassToDataMatrix->PatternToDataMatrix2D(pPattern);

	DataMatrixTransposeMultiplication = ClassClusteringPointMatrixTransposed->Multiply(PatternMatrix);

	delete ClassToDataMatrix;
	ClassToDataMatrix = NULL;
	delete PatternMatrix;
	PatternMatrix = NULL;
	delete ClassClusteringPointMatrixTransposed;
	ClassClusteringPointMatrixTransposed = NULL;
	delete ClassClusteringPointMatrix;
	ClassClusteringPointMatrix = NULL;
	
	return DataMatrixTransposeMultiplication;

}

CDataMatrix2D *CLeastSquaresMinimumDistanceClassifier::AugmentedPatternToDataMatrixTransposeMultiplication (CPattern *pAugmentedPattern){

	CDataMatrix2D *DataMatrixTransposeMultiplication = new CDataMatrix2D(pAugmentedPattern->GetNumberOfFeatures(), pAugmentedPattern->GetNumberOfFeatures());

	for (int i=0;i<pAugmentedPattern->GetNumberOfFeatures();i++){
		for (int j=0;j<pAugmentedPattern->GetNumberOfFeatures();j++){
			DataMatrixTransposeMultiplication->SetMatrixValue(i, j, (pAugmentedPattern->GetFeature(i)->GetFeatureValue() * pAugmentedPattern->GetFeature(j)->GetFeatureValue()));
		}
	}

	return DataMatrixTransposeMultiplication;

}

void CLeastSquaresMinimumDistanceClassifierDiscriminantFunction::CalculateClassDiscriminantFunctionLeastSquareMinimumDistance(int iClassIndex, CPattern *pPattern, CDataMatrix2D *TransformationCoefficientsMatrix){

	if (iClassIndex > TransformationCoefficientsMatrix->GetNumberOfRows()){
		m_dblDiscriminantFunctionValue = -1;
		return;
	}

	double dblRet = 0.0f;

	for (int i=0;i<pPattern->GetNumberOfFeatures();i++){
		dblRet = dblRet + (pPattern->GetFeature(i)->GetFeatureValue() * TransformationCoefficientsMatrix->GetMatrixValue(iClassIndex, i));
	}

	SetDiscriminantFunctionValue(dblRet);

}
