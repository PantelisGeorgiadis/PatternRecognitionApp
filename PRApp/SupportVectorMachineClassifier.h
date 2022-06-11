#if !defined(AFX_SUPPORTVECTORMACHINECLASSIFIER_H__74C99A28_AA23_494A_8B9A_046820881171__INCLUDED_)
#define AFX_SUPPORTVECTORMACHINECLASSIFIER_H__74C99A28_AA23_494A_8B9A_046820881171__INCLUDED_

#include <time.h>
#include <cmath>
#include "DataSet.h"
#include "DataMatrix2D.h"
#include "Classifier.h"
#include "ClassToDataMatrix.h"

class CSupportVectorMachineClassifier : public CClassifier 
{
public:
	CSupportVectorMachineClassifier();
	CSupportVectorMachineClassifier(SVMINFO *svmi);
	virtual ~CSupportVectorMachineClassifier();

	void SetSupportVectorMachineInfo (SVMINFO *svmi);
	static void LabelDataSet (CDataSet *pDataSet);
	void Classify (CDataSet *pDataSet, CPattern *pUnknownPattern);

protected:

	SVMINFO m_svmi;

	CDataMatrix1D *m_AlphaMatrix;		// Lagrange multipliers 
	double m_dblb;						// Threshold 
	int m_iC;							// Bounding box parameter
	CDataMatrix1D *m_ErrorCacheMatrix;	// Error cache
	int m_iAlphaNonBound;				// Number of non-bound examples
	bool *m_bAlphaBound;				// Is alpha bound?
	int *m_iRandlist;					// For storing random permutations

	int ExamineExample (CDataMatrix2D *CombinedDataSetMatrix, CDataMatrix1D *LabelMatrix, int iRowIndex);
	int TakeStep (CDataMatrix2D *CombinedDataSetMatrix, CDataMatrix1D *LabelMatrix, int iIndex1, int iIndex2);
	int FindMinError (int iNumberOfPatterns);
	int FindMaxError (int iNumberOfPatterns);
	void RandomSwap (int* A, int n);

	CDataMatrix1D *DesignSupportVectorMachineClassifier (CDataMatrix2D *CombinedDataSetMatrix, CDataMatrix1D *LabelMatrix, CDataMatrix1D *LangrangianMatrix);
	double CalculateLinearKernelValue (double *x1, double *x2, int d);
	double CalculateGaussianKernelValue (double *x1, double *x2, int d);
	double CalculatePolynomialKernelValue (double *x1, double *x2, int d);
	double CalculateSigmoidKernelValue (double *x1, double *x2, int d);
	double CalculateRadialBasisFunctionKernelValue (double *x1, double *x2, int d);

};

#endif 
