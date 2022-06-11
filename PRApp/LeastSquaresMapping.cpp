#include "stdafx.h"
#include "LeastSquaresMapping.h"

CLeastSquaresMapping::CLeastSquaresMapping()
{

#ifdef USE_MATLAB_INVERSE
	m_MatlabEngine = NULL;
	m_MatlabEngine = new CMatlabEngine();
	m_MatlabEngine->Open(NULL);
	m_MatlabEngine->SetVisible(true);
#endif

}

CLeastSquaresMapping::~CLeastSquaresMapping()
{

#ifdef USE_MATLAB_INVERSE
	if (m_MatlabEngine != NULL){
		m_MatlabEngine->Close();
		delete m_MatlabEngine;
		m_MatlabEngine = NULL;
	}
#endif

}

CDataSet *CLeastSquaresMapping::LeastSquaresMapping (CDataSet *pDataSet, int iOrder, CPattern *pClusteringPoints, int iClusteringPointsSize){

// 	CClassToMxArray *ClassToMxArray = new CClassToMxArray();
// 	CDataSet *MappedDataSet = new CDataSet();
// 	
// 	mxArray *A = NULL;
// 	mxArray *B = NULL;
// 	mxArray *mA = NULL;
// 	mxArray *mB = NULL;
// 	A = ClassToMxArray->ClassToMxArray(pDataSet->GetClass(0));
// 	B = ClassToMxArray->ClassToMxArray(pDataSet->GetClass(1));
// 	m_MatlabEngine->PutVariable("A", A);
// 	m_MatlabEngine->PutVariable("B", B);
// 	m_MatlabEngine->EvalString("cd('C:\\Program Files\\MATLAB\\R2006a\\work\\PatternRecognition')");
// 	m_MatlabEngine->EvalString("[mA, mB] = LeastSquaresMapping2(A, B, 2);");
// 	mA = m_MatlabEngine->GetVariable("mA");
// 	mB = m_MatlabEngine->GetVariable("mB");
// 	
// 	MappedDataSet->AddClass(ClassToMxArray->MxArrayToClass(mA));
// 	MappedDataSet->AddClass(ClassToMxArray->MxArrayToClass(mB));
// 	
// 	mxDestroyArray(A);
// 	mxDestroyArray(B);
// 	mxDestroyArray(mA);
// 	mxDestroyArray(mB);
// 
// 	delete ClassToMxArray;
// 	ClassToMxArray = NULL;
// 
// 	return MappedDataSet;

	int i, j, k;
	int iNumberOfMappedFeatures = 0;
	CClassToDataMatrix *ClassToDataMatrix = new CClassToDataMatrix();
	CDataSet *AugmentedDataSet = new CDataSet();
	double *dblClassProbability = new double [pDataSet->GetNumberOfClasses()];
	CDataMatrix2D *MatrixTransposeMultiplicationTmp = NULL;
	CDataMatrix2D *AugmentedMatrixTransposeMultiplicationTmp = NULL;
	CDataMatrix2D *SumAugmentedMatrixTransposeMultiplicationInversed = NULL;
	CDataMatrix2D *TransformationCoefficientsMatrix = NULL;
	CDataMatrix2D *AugmentedDataSetMatrix = new CDataMatrix2D[pDataSet->GetNumberOfClasses()];
	CDataMatrix2D *AugmentedDataSetMatrixTmp = NULL;
	CDataMatrix2D *AugmentedDataSetMatrixTransposedTmp = NULL;
	CDataMatrix2D *MappedMatrix = new CDataMatrix2D[pDataSet->GetNumberOfClasses()];
	CDataMatrix2D *MappedMatrixTmp = NULL;
	CDataMatrix2D *MappedMatrixTransposedTmp = NULL;
	CDataSet *MappedDataSet = new CDataSet();

#ifdef USE_MATLAB_INVERSE
	CDataMatrixToMxArray *DataMatrixToMxArray = new CDataMatrixToMxArray();
#endif

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
	
#ifdef USE_MATLAB_INVERSE
	mxArray *M = NULL;
	mxArray *IM = NULL;
	M = DataMatrixToMxArray->DataMatrix2DToMxArray(SumAugmentedMatrixTransposeMultiplication);
	m_MatlabEngine->PutVariable("M", M);
	m_MatlabEngine->EvalString("IM = inv(M)");
	IM = m_MatlabEngine->GetVariable("IM");
	SumAugmentedMatrixTransposeMultiplicationInversed = DataMatrixToMxArray->MxArrayToDataMatrix2D(IM);
	mxDestroyArray(M);
	mxDestroyArray(IM);
#else
	SumAugmentedMatrixTransposeMultiplicationInversed = SumAugmentedMatrixTransposeMultiplication->InverseMatrix();
#endif
	
	TransformationCoefficientsMatrix = SumMatrixTransposeMultiplication->Multiply(SumAugmentedMatrixTransposeMultiplicationInversed);

	for (i=0;i<AugmentedDataSet->GetNumberOfClasses();i++){
		AugmentedDataSetMatrixTmp = ClassToDataMatrix->ClassToDataMatrix(AugmentedDataSet->GetClass(i));
		AugmentedDataSetMatrixTransposedTmp = AugmentedDataSetMatrixTmp->TransposeMatrix();
		AugmentedDataSetMatrix[i].CreateDataMatrix(AugmentedDataSetMatrixTransposedTmp->GetNumberOfRows(), AugmentedDataSetMatrixTransposedTmp->GetNumberOfColumns());
		for (j=0;j<AugmentedDataSetMatrixTransposedTmp->GetNumberOfRows();j++){
			for (k=0;k<AugmentedDataSetMatrixTransposedTmp->GetNumberOfColumns();k++){
				AugmentedDataSetMatrix[i].SetMatrixValue(j, k, AugmentedDataSetMatrixTransposedTmp->GetMatrixValue(j, k));
			}
		}
		delete AugmentedDataSetMatrixTransposedTmp;
		AugmentedDataSetMatrixTransposedTmp = NULL;
		delete AugmentedDataSetMatrixTmp;
		AugmentedDataSetMatrixTmp = NULL;
	}
	
	for (i=0;i<AugmentedDataSet->GetNumberOfClasses();i++){
		MappedMatrixTmp = TransformationCoefficientsMatrix->Multiply(&AugmentedDataSetMatrix[i]);
		MappedMatrixTransposedTmp = MappedMatrixTmp->TransposeMatrix();
		MappedMatrix[i].CreateDataMatrix(MappedMatrixTransposedTmp->GetNumberOfRows(), MappedMatrixTransposedTmp->GetNumberOfColumns());
		for (j=0;j<MappedMatrixTransposedTmp->GetNumberOfRows();j++){
			for (k=0;k<MappedMatrixTransposedTmp->GetNumberOfColumns();k++){
				MappedMatrix[i].SetMatrixValue(j, k, MappedMatrixTransposedTmp->GetMatrixValue(j, k));
			}
		}
		delete MappedMatrixTransposedTmp;
		MappedMatrixTransposedTmp = NULL;
		delete MappedMatrixTmp;
		MappedMatrixTmp = NULL;
	}
	
	for (i=0;i<AugmentedDataSet->GetNumberOfClasses();i++){
		MappedDataSet->AddClass(ClassToDataMatrix->DataMatrixToClass(&MappedMatrix[i]));
	}

#ifdef USE_MATLAB_INVERSE
	delete DataMatrixToMxArray;
	DataMatrixToMxArray = NULL;
#endif
	
	delete [] MappedMatrix;
	MappedMatrix = NULL;
	delete [] AugmentedDataSetMatrix;
	AugmentedDataSetMatrix = NULL;
	delete TransformationCoefficientsMatrix;
	TransformationCoefficientsMatrix = NULL;
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
	delete ClassToDataMatrix;
	ClassToDataMatrix = NULL;

	return MappedDataSet;

}

void CLeastSquaresMapping::MapPattern (CPattern *pPattern, CPattern *pMappedPattern, int iOrder){

	int i, j, k, l, m;

	CPattern *CombinationPattern = NULL;
	CPattern *TmpPattern = NULL;
	CPattern *TmpPattern2 = NULL;
	CFeature *AugmentationFeature = new CFeature();
	AugmentationFeature->SetFeatureValue(-1.0f);

	pMappedPattern->RemoveAllFeatures();

// 	CExhaustiveSearch *ExhaustiveSearch = new CExhaustiveSearch[pPattern->GetNumberOfFeatures()];
// 	for (i=0;i<pPattern->GetNumberOfFeatures();i++){
// 		ExhaustiveSearch[i].CreateCombinations(pPattern->GetNumberOfFeatures(), (i + 1));
// 	}
// 
// 	for (i=0;i<pPattern->GetNumberOfFeatures();i++){
// 		for (j=0;j<(iOrder - GetCombination(i)->GetCombinationVectorSize() + 1);j++){
// 			
// 
// 		}
// 	}

	if (iOrder == 1){
		for (i=0;i<pPattern->GetNumberOfFeatures();i++){
			pMappedPattern->AddFeature(pPattern->GetFeature(i));
		}
	}
	else{
		for (i=0;i<pPattern->GetNumberOfFeatures();i++){
			CreateCombinations(pPattern->GetNumberOfFeatures(), (i + 1));
				for (k=0;k<(iOrder - GetCombination(0)->GetCombinationVectorSize() + 1);k++){
					for (j=0;j<GetNumberOfCombinations();j++){
						if (k == 0){
							CombinationPattern = pPattern->CopyPatternFromCombination(GetCombination(j));
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
							for (l=0;l<GetCombination(0)->GetCombinationVectorSize();l++){
								CombinationPattern = pPattern->CopyPatternFromCombination(GetCombination(j));
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
			DeleteCombinations();
		}
	}

	pMappedPattern->AddFeature(AugmentationFeature);

// 	delete [] ExhaustiveSearch;
// 	ExhaustiveSearch = NULL;
	delete AugmentationFeature;
	AugmentationFeature = NULL;

}

CPattern *CLeastSquaresMapping::CalculateFeatures (CPattern *pPattern){

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

CDataMatrix2D *CLeastSquaresMapping::PatternToDataMatrixTransposeMultiplication (CPattern *pClassClusteringPoint, CPattern *pPattern){

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

CDataMatrix2D *CLeastSquaresMapping::AugmentedPatternToDataMatrixTransposeMultiplication (CPattern *pAugmentedPattern){

	CDataMatrix2D *DataMatrixTransposeMultiplication = new CDataMatrix2D(pAugmentedPattern->GetNumberOfFeatures(), pAugmentedPattern->GetNumberOfFeatures());

	for (int i=0;i<pAugmentedPattern->GetNumberOfFeatures();i++){
		for (int j=0;j<pAugmentedPattern->GetNumberOfFeatures();j++){
			DataMatrixTransposeMultiplication->SetMatrixValue(i, j, (pAugmentedPattern->GetFeature(i)->GetFeatureValue() * pAugmentedPattern->GetFeature(j)->GetFeatureValue()));
		}
	}

	return DataMatrixTransposeMultiplication;

}
