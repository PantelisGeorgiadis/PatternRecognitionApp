#if !defined(AFX_LEVELSET_H__F4E89512_6A5D_4764_B972_CA977BAE1F09__INCLUDED_)
#define AFX_LEVELSET_H__F4E89512_6A5D_4764_B972_CA977BAE1F09__INCLUDED_

#include <cmath>
#include "DataMatrix2D.h"
#include "Rectangle.h"
#include "Gradient.h"

typedef struct _tagLEVELSETINFO 
{
	
	double dblEpsilon;	// (1.5) The parameter in the definition of smoothed Dirac function
	int iTimeStep;		// (5) Time step
	double mu;			// (0.04) Coefficient of the internal (penalizing) energy term P 
						// The product iTimeStep * mu must be less than 0.25 for stability
	double dblLambda;	// (5) Coefficient of the weighted length term L
	double dblAlpha;	// (1.5) Coefficient of the weighted area term A
	int c0;				// (3) The constant value used to define binary level set function

} LEVELSETINFO;

typedef void (*LevelSetCallBack)(CDataMatrix2D*, LEVELSETINFO*, int);

class CLevelSet  
{
public:
	CLevelSet();
	CLevelSet(LevelSetCallBack pLevelSetCallBack);
	virtual ~CLevelSet();

	void LevelSet (CDataMatrix2D *pDataMatrix2D, CRectangle *pRectangle, LEVELSETINFO *lsi, int iIterations);
	void SetLevelSetCallBackCallBackFunction (LevelSetCallBack pLevelSetCallBack) { m_pLevelSetCallBack = pLevelSetCallBack; }

protected:

	LevelSetCallBack m_pLevelSetCallBack;

	CDataMatrix2D *EvolveLevelSet (CDataMatrix2D *LevelSetFunctionMatrix, CDataMatrix2D *EdgeIndicatorMatrix, double dblLamda, double mu, double dblAlpha, double dblEpsilon, int iTimeStep);
	void NeumannBoundaryCondition (CDataMatrix2D *pDataMatrix2D);
	CDataMatrix2D *DiracFunction (CDataMatrix2D *pDataMatrix, double dblSigma);
	CDataMatrix2D *CurvatureCentral (CDataMatrix2D *pDataMatrixX, CDataMatrix2D *pDataMatrixY);
	void Replace4 (CDataMatrix2D *pDataMatrix2D, int A11, int A12, int A21, int A22, int RA11, int RA12, int RA21, int RA22);
	void Replace3C (CDataMatrix2D *pDataMatrix2D, int A11, int A12, int A21, int RA11, int RA12, int RA21);
	void Replace3R (CDataMatrix2D *pDataMatrix2D, int A11, int A21, int A22, int RA11, int RA21, int RA22);

};

#endif 
