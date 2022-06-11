#if !defined(AFX_PRINCIPALCOMPONENTANALYSIS_H__F9780E7F_77C9_4F09_9CE0_7B2506E15330__INCLUDED_)
#define AFX_PRINCIPALCOMPONENTANALYSIS_H__F9780E7F_77C9_4F09_9CE0_7B2506E15330__INCLUDED_

#include <cmath>
#include "DataMatrix2D.h"
#include "DataMatrix1D.h"
#include "ClassToDataMatrix.h"

#define SIGN(a, b) ((b) < 0 ? -fabs(a) : fabs(a))

enum PrincipalComponentTypeOfAnalysis {TYPEOFANALYSIS_CORRELATION, TYPEOFANALYSIS_VARIANCE_COVARIANCE, TYPEOFANALYSIS_SSCP};

class CPrincipalComponentAnalysis  
{
public:
	CPrincipalComponentAnalysis();
	virtual ~CPrincipalComponentAnalysis();

	CClass *PrincipalComponentAnalysis (CClass *pClass, PrincipalComponentTypeOfAnalysis pcta = TYPEOFANALYSIS_CORRELATION);

protected:

	void CorrelationColumns (CDataMatrix2D *pDataMatrix2D, CDataMatrix2D *pAnalyzedDataMatrix);

	void TriangularDecomposition(CDataMatrix2D *pAnalyzedDataMatrix, CDataMatrix1D *EigenValuesMatrix, CDataMatrix1D *IntermediateMatrix);
	void TridiagonalQLImplicit(CDataMatrix1D *EigenValuesMatrix, CDataMatrix1D *IntermediateMatrix, CDataMatrix2D *pAnalyzedDataMatrix);

};

#endif 
