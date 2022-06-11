#include "stdafx.h"
#include "BayesianClassifier.h"

CBayesianClassifier::CBayesianClassifier()
{

}

CBayesianClassifier::~CBayesianClassifier()
{

}

void CBayesianClassifier::Classify (CDataSet *pDataSet, CPattern *pUnknownPattern){

	int iClassIndexRet = 0;
	int i, j, k;
	int iMaxDiscriminantFunctionClassIndex = 0;
	double dblMaxDiscriminantFunctionValue = (std::numeric_limits<double>::max)();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		if (pDataSet->GetClass(0)->GetNumberOfFeaturesPerPattern() !=  pDataSet->GetClass(i)->GetNumberOfFeaturesPerPattern()){
			return;
		}
	}

	CBayesianClassifierDiscriminantFunction *DiscriminantFunction = new CBayesianClassifierDiscriminantFunction[pDataSet->GetNumberOfClasses()];
	CDataMatrix2D *ClassesCovarianceMatrix = new CDataMatrix2D[pDataSet->GetNumberOfClasses()];
	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		ClassesCovarianceMatrix[i].CreateDataMatrix(pDataSet->GetClass(0)->GetNumberOfFeaturesPerPattern(), pDataSet->GetClass(0)->GetNumberOfFeaturesPerPattern());
	}
	CDataMatrix2D *ClassCovarianceMatrix = NULL;
	
	for (k=0;k<pDataSet->GetNumberOfClasses();k++){
		ClassCovarianceMatrix = CalculateClassCovarianceMatrix(pDataSet->GetClass(k));
		for (i=0;i<ClassCovarianceMatrix->GetNumberOfRows();i++){
			for (j=0;j<ClassCovarianceMatrix->GetNumberOfColumns();j++){
				ClassesCovarianceMatrix[k].SetMatrixValue(i, j, ClassCovarianceMatrix->GetMatrixValue(i, j));
			}
		}
		delete ClassCovarianceMatrix;
		ClassCovarianceMatrix = NULL;
	}

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		DiscriminantFunction[i].CalculateClassDiscriminantFunctionBayesian(pDataSet->GetClass(i), pUnknownPattern, ClassesCovarianceMatrix, pDataSet->GetNumberOfClasses());
	}

	dblMaxDiscriminantFunctionValue = DiscriminantFunction[0].GetDiscriminantFunctionValue();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		if (DiscriminantFunction[i].GetDiscriminantFunctionValue() > dblMaxDiscriminantFunctionValue){
			dblMaxDiscriminantFunctionValue = DiscriminantFunction[i].GetDiscriminantFunctionValue();
			iMaxDiscriminantFunctionClassIndex = i;
		}
	}

	iClassIndexRet = iMaxDiscriminantFunctionClassIndex;

	delete [] ClassesCovarianceMatrix;
	ClassesCovarianceMatrix = NULL;
	delete [] DiscriminantFunction;
	DiscriminantFunction = NULL;

	SetClassifierOutput(iClassIndexRet);

}

void CBayesianClassifier::ClassifyQuadratic (CDataSet *pDataSet, CPattern *pUnknownPattern){

	int iClassIndexRet = 0;
	int i;
	int iMaxDiscriminantFunctionClassIndex = 0;
	double dblMaxDiscriminantFunctionValue = (std::numeric_limits<double>::max)();
	int iTotalPatternNumber = 0;
	double dblClassProbability = 0.0f;

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		if (pDataSet->GetClass(0)->GetNumberOfFeaturesPerPattern() !=  pDataSet->GetClass(i)->GetNumberOfFeaturesPerPattern()){
			return;
		}
	}

	CBayesianClassifierDiscriminantFunction *DiscriminantFunction = new CBayesianClassifierDiscriminantFunction[pDataSet->GetNumberOfClasses()];
	CDataMatrix2D *ClassCovarianceMatrix = NULL;

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		iTotalPatternNumber = iTotalPatternNumber + pDataSet->GetClass(i)->GetNumberOfPatterns();
	}
	
	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		ClassCovarianceMatrix = CalculateClassCovarianceMatrix(pDataSet->GetClass(i));
		dblClassProbability = ((double)pDataSet->GetClass(i)->GetNumberOfPatterns() / (double)iTotalPatternNumber);
		DiscriminantFunction[i].CalculateClassDiscriminantFunctionBayesianQuadratic(pDataSet->GetClass(i), pUnknownPattern, ClassCovarianceMatrix, dblClassProbability);
		delete ClassCovarianceMatrix;
		ClassCovarianceMatrix = NULL;
	}

	dblMaxDiscriminantFunctionValue = DiscriminantFunction[0].GetDiscriminantFunctionValue();

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		if (DiscriminantFunction[i].GetDiscriminantFunctionValue() > dblMaxDiscriminantFunctionValue){
			dblMaxDiscriminantFunctionValue = DiscriminantFunction[i].GetDiscriminantFunctionValue();
			iMaxDiscriminantFunctionClassIndex = i;
		}
	}

	iClassIndexRet = iMaxDiscriminantFunctionClassIndex;

	delete [] DiscriminantFunction;
	DiscriminantFunction = NULL;

	SetClassifierOutput(iClassIndexRet);

}

void CBayesianClassifier::Classify (CDataSet *pDataSet, CDataSet *pUnknownPatterns){

	for (int i=0;i<pUnknownPatterns->GetNumberOfClasses();i++){
		for (int j=0;j<pUnknownPatterns->GetClass(i)->GetNumberOfPatterns();j++){
			Classify(pDataSet, pUnknownPatterns->GetClass(i)->GetPattern(j));
			pUnknownPatterns->GetTruthTable()->SetTruthTableValue(i, GetClassifierOutput(), pUnknownPatterns->GetTruthTable()->GetTruthTableValue(i, GetClassifierOutput()) + 1);
		}
	}

}

void CBayesianClassifier::ClassifyQuadratic (CDataSet *pDataSet, CDataSet *pUnknownPatterns){

	for (int i=0;i<pUnknownPatterns->GetNumberOfClasses();i++){
		for (int j=0;j<pUnknownPatterns->GetClass(i)->GetNumberOfPatterns();j++){
			ClassifyQuadratic(pDataSet, pUnknownPatterns->GetClass(i)->GetPattern(j));
			pUnknownPatterns->GetTruthTable()->SetTruthTableValue(i, GetClassifierOutput(), pUnknownPatterns->GetTruthTable()->GetTruthTableValue(i, GetClassifierOutput()) + 1);
		}
	}

}

CDataMatrix2D *CBayesianClassifier::CalculateClassCovarianceMatrix (CClass *pClass){

	int i, j, k;
	
	CDataMatrix2D *ClassCovarianceMatrix = NULL;
	CDataMatrix2D *TransposedMultipliedPatterns = new CDataMatrix2D[pClass->GetNumberOfPatterns()];
	CDataMatrix2D *TransposedMultipliedMatrix = NULL;
	CDataMatrix2D *SumTransposedMultipliedPatterns = new CDataMatrix2D(pClass->GetNumberOfFeaturesPerPattern(), pClass->GetNumberOfFeaturesPerPattern());
	CCentroid *ClassCentroid = new CCentroid();
	CPattern *MeanPattern = NULL;
	CDataMatrix2D *TransposedMultipliedCentroidPattern = NULL;
	CDataMatrix2D *ScalarDividedSumTransposedMultipliedPatterns = NULL;
	
	for (i=0;i<pClass->GetNumberOfPatterns();i++){
		TransposedMultipliedPatterns[i].CreateDataMatrix(pClass->GetNumberOfFeaturesPerPattern(), pClass->GetNumberOfFeaturesPerPattern());
	}

	for (k=0;k<pClass->GetNumberOfPatterns();k++){
		TransposedMultipliedMatrix = PatternToDataMatrixTransposeMultiplication(pClass->GetPattern(k));
		for (i=0;i<TransposedMultipliedMatrix->GetNumberOfRows();i++){
			for (j=0;j<TransposedMultipliedMatrix->GetNumberOfColumns();j++){
				TransposedMultipliedPatterns[k].SetMatrixValue(i, j, TransposedMultipliedMatrix->GetMatrixValue(i, j));
			}
		}
		delete TransposedMultipliedMatrix;
		TransposedMultipliedMatrix = NULL;
	}

	for (i=0;i<SumTransposedMultipliedPatterns->GetNumberOfRows();i++){
		for (j=0;j<SumTransposedMultipliedPatterns->GetNumberOfColumns();j++){
			for (k=0;k<pClass->GetNumberOfPatterns();k++){
				SumTransposedMultipliedPatterns->SetMatrixValue(i, j, (SumTransposedMultipliedPatterns->GetMatrixValue(i, j) + TransposedMultipliedPatterns[k].GetMatrixValue(i, j)));
			}
		}
	}

	ScalarDividedSumTransposedMultipliedPatterns = SumTransposedMultipliedPatterns->DivideScalar(pClass->GetNumberOfPatterns());
	MeanPattern = ClassCentroid->CalculateClassCentroid(pClass);
	TransposedMultipliedCentroidPattern = PatternToDataMatrixTransposeMultiplication(MeanPattern);
	ClassCovarianceMatrix = ScalarDividedSumTransposedMultipliedPatterns->Subtract(TransposedMultipliedCentroidPattern);

	delete ScalarDividedSumTransposedMultipliedPatterns;
	ScalarDividedSumTransposedMultipliedPatterns = NULL;
	delete TransposedMultipliedCentroidPattern;
	TransposedMultipliedCentroidPattern = NULL;
	delete MeanPattern;
	MeanPattern = NULL;
	delete ClassCentroid;
	ClassCentroid = NULL;
	delete SumTransposedMultipliedPatterns;
	SumTransposedMultipliedPatterns = NULL;
	delete [] TransposedMultipliedPatterns;
	TransposedMultipliedPatterns = NULL;

	return ClassCovarianceMatrix;

}

CDataMatrix2D *CBayesianClassifier::PatternToDataMatrixTransposeMultiplication (CPattern *pPattern){

	CDataMatrix2D *DataMatrixTransposeMultiplication = new CDataMatrix2D(pPattern->GetNumberOfFeatures(), pPattern->GetNumberOfFeatures());

	for (int i=0;i<pPattern->GetNumberOfFeatures();i++){
		for (int j=0;j<pPattern->GetNumberOfFeatures();j++){
			DataMatrixTransposeMultiplication->SetMatrixValue(i, j, (pPattern->GetFeature(i)->GetFeatureValue() * pPattern->GetFeature(j)->GetFeatureValue()));
		}
	}

	return DataMatrixTransposeMultiplication;

}

void CBayesianClassifierDiscriminantFunction::CalculateClassDiscriminantFunctionBayesian (CClass *pClass, CPattern *pPattern, CDataMatrix2D *ClassesCovarianceMatrix, int iNumberOfClasses){

	int i, j, k;
	
	CDataMatrix2D *ClassesCovarianceMeanMatrix = new CDataMatrix2D(ClassesCovarianceMatrix[0].GetNumberOfRows(), ClassesCovarianceMatrix[0].GetNumberOfColumns());
	CDataMatrix2D *ClassesCovarianceInverseMeanMatrix = NULL;
	CDataMatrix2D *PatternMatrix = new CDataMatrix2D(1, pPattern->GetNumberOfFeatures());
	CDataMatrix2D *Tmp = NULL;
	CDataMatrix2D *Tmp2 = NULL;
	CCentroid *ClassCentroid = new CCentroid();
	CPattern *MeanPattern = NULL;
	CDataMatrix2D *MeanPatternMatrix = new CDataMatrix2D(1, pPattern->GetNumberOfFeatures());
	CDataMatrix2D *MeanPatternTransposedMatrix = NULL;
	CDataMatrix2D *FirstEquationTerm = NULL;
	CDataMatrix2D *SecondEquationTerm = NULL;

	for (i=0;i<ClassesCovarianceMeanMatrix->GetNumberOfRows();i++){
		for (j=0;j<ClassesCovarianceMeanMatrix->GetNumberOfColumns();j++){
			for (k=0;k<iNumberOfClasses;k++){
				ClassesCovarianceMeanMatrix->SetMatrixValue(i, j, (ClassesCovarianceMeanMatrix->GetMatrixValue(i, j) + ClassesCovarianceMatrix[k].GetMatrixValue(i, j)));
			}
		}
	}

	for (i=0;i<ClassesCovarianceMeanMatrix->GetNumberOfRows();i++){
		for (j=0;j<ClassesCovarianceMeanMatrix->GetNumberOfColumns();j++){
			ClassesCovarianceMeanMatrix->SetMatrixValue(i, j, (ClassesCovarianceMeanMatrix->GetMatrixValue(i, j) / iNumberOfClasses));
		}
	}

	ClassesCovarianceInverseMeanMatrix = ClassesCovarianceMeanMatrix->InverseMatrix();

	for (i=0;i<pPattern->GetNumberOfFeatures();i++){
		PatternMatrix->SetMatrixValue(0, i, pPattern->GetFeature(i)->GetFeatureValue());
	}

	Tmp = PatternMatrix->Multiply(ClassesCovarianceInverseMeanMatrix);

	MeanPattern = ClassCentroid->CalculateClassCentroid(pClass);
	for (i=0;i<MeanPattern->GetNumberOfFeatures();i++){
		MeanPatternMatrix->SetMatrixValue(0, i, MeanPattern->GetFeature(i)->GetFeatureValue());
	}

	MeanPatternTransposedMatrix = MeanPatternMatrix->TransposeMatrix();

	FirstEquationTerm = Tmp->Multiply(MeanPatternTransposedMatrix);
	delete Tmp;
	Tmp = NULL;

	Tmp = MeanPatternMatrix->Multiply(ClassesCovarianceInverseMeanMatrix);
	Tmp2 = Tmp->Multiply(MeanPatternTransposedMatrix);
	SecondEquationTerm = Tmp2->DivideScalar(2.0f);

	SetDiscriminantFunctionValue(FirstEquationTerm->GetMatrixValue(0, 0) - SecondEquationTerm->GetMatrixValue(0, 0));

	delete SecondEquationTerm;
	SecondEquationTerm = NULL;
	delete FirstEquationTerm;
	FirstEquationTerm = NULL;
	delete MeanPatternTransposedMatrix;
	MeanPatternTransposedMatrix = NULL;
	delete MeanPatternMatrix;
	MeanPatternMatrix = NULL;
	delete MeanPattern;
	MeanPattern = NULL;
	delete Tmp;
	Tmp = NULL;
	delete Tmp2;
	Tmp2 = NULL;
	delete ClassCentroid;
	ClassCentroid = NULL;
	delete PatternMatrix;
	PatternMatrix = NULL;
	delete ClassesCovarianceInverseMeanMatrix;
	ClassesCovarianceInverseMeanMatrix = NULL;
	delete ClassesCovarianceMeanMatrix;
	ClassesCovarianceMeanMatrix = NULL;

}

void CBayesianClassifierDiscriminantFunction::CalculateClassDiscriminantFunctionBayesianQuadratic (CClass *pClass, CPattern *pPattern, CDataMatrix2D *ClassCovarianceMatrix, double dblClassProbability){

	int i;

	double FirstEquationTerm = 0.0f;
	CDeterminant *Determinant = new CDeterminant();
	CDataMatrix2D *InverseClassCovarianceMatrix = NULL;
	CDataMatrix2D *PatternMatrix = new CDataMatrix2D(1, pPattern->GetNumberOfFeatures());
	CDataMatrix2D *PatternTransposedMatrix = NULL;
	CCentroid *ClassCentroid = new CCentroid();
	CPattern *MeanPattern = NULL;
	CDataMatrix2D *MeanPatternMatrix = new CDataMatrix2D(1, pPattern->GetNumberOfFeatures());
	CDataMatrix2D *MeanPatternTransposedMatrix = NULL;
	CDataMatrix2D *Tmp = NULL;
	CDataMatrix2D *Tmp2 = NULL;
	CDataMatrix2D *Tmp3 = NULL;
	CDataMatrix2D *Tmp4 = NULL;
	CDataMatrix2D *SecondEquationTerm = NULL;
	double dblClassCovarianceMatrixDeterminant = 0.0f;
	
	dblClassCovarianceMatrixDeterminant = Determinant->CalculateMatrixDeterminant(ClassCovarianceMatrix);

	if (dblClassCovarianceMatrixDeterminant == 0){
		FirstEquationTerm = log(dblClassProbability) - (0.5f * log(1.0f));
	}
	else{
		FirstEquationTerm = log(dblClassProbability) - (0.5f * log(dblClassCovarianceMatrixDeterminant));
	}

	InverseClassCovarianceMatrix = ClassCovarianceMatrix->InverseMatrix();

	for (i=0;i<pPattern->GetNumberOfFeatures();i++){
		PatternMatrix->SetMatrixValue(0, i, pPattern->GetFeature(i)->GetFeatureValue());
	}

	PatternTransposedMatrix = PatternMatrix->TransposeMatrix();

	MeanPattern = ClassCentroid->CalculateClassCentroid(pClass);
	for (i=0;i<MeanPattern->GetNumberOfFeatures();i++){
		MeanPatternMatrix->SetMatrixValue(0, i, MeanPattern->GetFeature(i)->GetFeatureValue());
	}

	MeanPatternTransposedMatrix = MeanPatternMatrix->TransposeMatrix();

	Tmp = PatternMatrix->Subtract(MeanPatternMatrix);
	Tmp2 = Tmp->Multiply(InverseClassCovarianceMatrix);
	Tmp3 = PatternTransposedMatrix->Subtract(MeanPatternTransposedMatrix);
	Tmp4 = Tmp2->Multiply(Tmp3);
	
	SecondEquationTerm = Tmp4->DivideScalar(2.0f);
	
	SetDiscriminantFunctionValue(FirstEquationTerm - SecondEquationTerm->GetMatrixValue(0, 0));

	delete SecondEquationTerm;
	SecondEquationTerm = NULL;
	delete Tmp;
	Tmp = NULL;
	delete Tmp2;
	Tmp2 = NULL;
	delete Tmp3;
	Tmp3 = NULL;
	delete Tmp4;
	Tmp4 = NULL;
	delete MeanPatternTransposedMatrix;
	MeanPatternTransposedMatrix = NULL;
	delete MeanPatternMatrix;
	MeanPatternMatrix = NULL;
	delete MeanPattern;
	MeanPattern = NULL;
	delete ClassCentroid;
	ClassCentroid = NULL;
	delete PatternTransposedMatrix;
	PatternTransposedMatrix = NULL;
	delete PatternMatrix;
	PatternMatrix = NULL;
	delete InverseClassCovarianceMatrix;
	InverseClassCovarianceMatrix = NULL;
	delete Determinant;
	Determinant = NULL;

}

