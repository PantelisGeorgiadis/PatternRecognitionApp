#if !defined(AFX_SUPPORTVECTORMACHINECLASSIFIERDRAWINGSURFACE_H__12727D47_A01B_43A3_8651_D6FD01725DD7__INCLUDED_)
#define AFX_SUPPORTVECTORMACHINECLASSIFIERDRAWINGSURFACE_H__12727D47_A01B_43A3_8651_D6FD01725DD7__INCLUDED_

#include "DrawingSurface.h"
#include "SupportVectorMachineClassifier.h"
#include "ClassToDataMatrix.h"

#define SVMDRAWINGSURFACEDIMENSION	300

typedef struct tagSVMDRAWINGINFO
{

	int x;
	int y;
	int iLabel;

} SVMDRAWINGINFO;

class CSupportVectorMachineClassifierDrawingSurface  
{
public:
	CSupportVectorMachineClassifierDrawingSurface();
	virtual ~CSupportVectorMachineClassifierDrawingSurface();

	CDrawingSurface *CreateSupportVectorMachineClassifierDrawingSurface (CDataSet *pDataSet, SVMINFO *svmi);

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

	int Classify (CPattern *pUnknownPattern, CDataMatrix2D *CombinedDataSetMatrix, CDataMatrix1D *LabelMatrix, CDataMatrix1D *LagrangianMatrix);
	CDataMatrix1D *DesignSupportVectorMachineClassifier (CDataMatrix2D *CombinedDataSetMatrix, CDataMatrix1D *LabelMatrix, CDataMatrix1D *LangrangianMatrix);
	double CalculateLinearKernelValue (double *x1, double *x2, int d);
	double CalculateGaussianKernelValue (double *x1, double *x2, int d);
	double CalculatePolynomialKernelValue (double *x1, double *x2, int d);
	double CalculateSigmoidKernelValue (double *x1, double *x2, int d);
	double CalculateRadialBasisFunctionKernelValue (double *x1, double *x2, int d);

};

#endif 
