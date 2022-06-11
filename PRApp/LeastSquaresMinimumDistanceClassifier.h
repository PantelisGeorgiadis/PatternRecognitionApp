#if !defined(AFX_LEASTSQUARESMINIMUMDISTANCECLASSIFIER_H__BDECE9F5_7D16_4577_A4B0_1200EC0C0796__INCLUDED_)
#define AFX_LEASTSQUARESMINIMUMDISTANCECLASSIFIER_H__BDECE9F5_7D16_4577_A4B0_1200EC0C0796__INCLUDED_

#include <limits>
#include <cmath>
#include "Classifier.h"
#include "DiscriminantFunction.h"
#include "DataSet.h"
#include "DataMatrix2D.h"
#include "ExhaustiveSearch.h"
#include "ClassToDataMatrix.h"

class CLeastSquaresMinimumDistanceClassifier : public CClassifier
{
public:
	CLeastSquaresMinimumDistanceClassifier();
	CLeastSquaresMinimumDistanceClassifier(CDataSet *pDataSet, int iOrder, CPattern *pClusteringPoints, int iClusteringPointsSize);
	virtual ~CLeastSquaresMinimumDistanceClassifier();

	void InitializeClassifier (CDataSet *pDataSet, int iOrder, CPattern *pClusteringPoints, int iClusteringPointsSize);
	void DeleteTransformationCoefficientsMatrix (void);
	void Classify (CDataSet *pDataSet, CPattern *pUnknownPattern);

	void Classify (CDataSet *pDataSet, CDataSet *pUnknownPatterns);

protected:

	CDataMatrix2D *m_TransformationCoefficientsMatrix;
	int m_iOrder;

	CDataMatrix2D *LeastSquaresMapping (CDataSet *pDataSet, int iOrder, CPattern *pClusteringPoints, int iClusteringPointsSize);
	CPattern *CalculateFeatures (CPattern *pPattern);
	void MapPattern (CPattern *pPattern, CPattern *pMappedPattern, int iOrder);
	CDataMatrix2D *PatternToDataMatrixTransposeMultiplication (CPattern *pClassClusteringPoint, CPattern *pPattern);
	CDataMatrix2D *AugmentedPatternToDataMatrixTransposeMultiplication (CPattern *pAugmentedPattern);

};

class CLeastSquaresMinimumDistanceClassifierDiscriminantFunction : public CDiscriminantFunction
{
public:
	CLeastSquaresMinimumDistanceClassifierDiscriminantFunction() {};
	~CLeastSquaresMinimumDistanceClassifierDiscriminantFunction() {};

	void CalculateClassDiscriminantFunctionLeastSquareMinimumDistance(int iClassIndex, CPattern *pPattern, CDataMatrix2D *TransformationCoefficientsMatrix);

};

#endif
