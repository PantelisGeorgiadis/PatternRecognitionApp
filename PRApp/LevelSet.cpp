#include "stdafx.h"
#include "FastMath.h"
#include "LevelSet.h"

#define ADDINGFACTOR 1e-10

CLevelSet::CLevelSet()
{

	m_pLevelSetCallBack = NULL;

}

CLevelSet::CLevelSet(LevelSetCallBack pLevelSetCallBack)
{

	SetLevelSetCallBackCallBackFunction(pLevelSetCallBack);

}

CLevelSet::~CLevelSet()
{

}

/*
CALLBACK EXAMPLE

void LevelSetCB (CDataMatrix2D* LevelSetFunctionMatrix, LEVELSETINFO* lsi, int iIteration){


}

*/

void CLevelSet::LevelSet (CDataMatrix2D *pDataMatrix2D, CRectangle *pRectangle, LEVELSETINFO *lsi, int iIterations){

	int i, j;

	CGradient *Gradient = new CGradient();
	CDataMatrix2D *GradientDataMatrix2DX = NULL;
	CDataMatrix2D *GradientDataMatrix2DY = NULL;
	CDataMatrix2D *Tmp = new CDataMatrix2D(pDataMatrix2D->GetNumberOfRows(), pDataMatrix2D->GetNumberOfColumns());
	CDataMatrix2D *EdgeIndicatorMatrix = new CDataMatrix2D(pDataMatrix2D->GetNumberOfRows(), pDataMatrix2D->GetNumberOfColumns());
	CDataMatrix2D *BinaryROIMatrix = new CDataMatrix2D(pDataMatrix2D->GetNumberOfRows(), pDataMatrix2D->GetNumberOfColumns());
	CDataMatrix2D *InitialLevelSetFunctionMatrix = new CDataMatrix2D(pDataMatrix2D->GetNumberOfRows(), pDataMatrix2D->GetNumberOfColumns());
	CDataMatrix2D *LevelSetFunctionMatrix = NULL;
	CDataMatrix2D *LevelSetFunctionMatrixTmp = NULL;

	Gradient->CalculateMatrixGradient(pDataMatrix2D);
	GradientDataMatrix2DX = Gradient->GetGradientDataMatrix2DX();
	GradientDataMatrix2DY = Gradient->GetGradientDataMatrix2DY();
	
	for (i=0;i<Tmp->GetNumberOfRows();i++){
		for (j=0;j<Tmp->GetNumberOfColumns();j++){
			Tmp->SetMatrixValue(i, j, (pow(GradientDataMatrix2DX->GetMatrixValue(i, j), 2) + pow(GradientDataMatrix2DY->GetMatrixValue(i, j), 2)));
		}
	}

	Tmp->AddScalarToMatrix(1.0f);

	for (i=0;i<EdgeIndicatorMatrix->GetNumberOfRows();i++){
		for (j=0;j<EdgeIndicatorMatrix->GetNumberOfColumns();j++){
			EdgeIndicatorMatrix->SetMatrixValue(i, j, (1.0f / Tmp->GetMatrixValue(i, j)));
		}
	}

	BinaryROIMatrix = pDataMatrix2D->CreateDataMatrixBinaryMask(pRectangle);

	for (i=0;i<InitialLevelSetFunctionMatrix->GetNumberOfRows();i++){
		for (j=0;j<InitialLevelSetFunctionMatrix->GetNumberOfColumns();j++){
			InitialLevelSetFunctionMatrix->SetMatrixValue(i, j, (0.5f - BinaryROIMatrix->GetMatrixValue(i, j)));
		}
	}

	InitialLevelSetFunctionMatrix->MultiplyScalarToMatrix(lsi->c0 * 2.0f);
	LevelSetFunctionMatrix = InitialLevelSetFunctionMatrix->CopyDataMatrix2D();
	
	for (i=0;i<iIterations;i++){
		LevelSetFunctionMatrixTmp = EvolveLevelSet(LevelSetFunctionMatrix, EdgeIndicatorMatrix, lsi->dblLambda, lsi->mu, lsi->dblAlpha, lsi->dblEpsilon, lsi->iTimeStep);
		delete LevelSetFunctionMatrix;
		LevelSetFunctionMatrix = NULL;
		LevelSetFunctionMatrix = LevelSetFunctionMatrixTmp->CopyDataMatrix2D();
		delete LevelSetFunctionMatrixTmp;
		LevelSetFunctionMatrixTmp = NULL;

		if (m_pLevelSetCallBack != NULL){
			m_pLevelSetCallBack(LevelSetFunctionMatrix, lsi, i);
		}
	}

	delete LevelSetFunctionMatrix;
	LevelSetFunctionMatrix = NULL;
	delete InitialLevelSetFunctionMatrix;
	InitialLevelSetFunctionMatrix = NULL;
	delete BinaryROIMatrix;
	BinaryROIMatrix = NULL;
	delete EdgeIndicatorMatrix;
	EdgeIndicatorMatrix = NULL;
	delete Tmp;
	Tmp = NULL;
	delete Gradient;
	Gradient = NULL;

}

CDataMatrix2D *CLevelSet::EvolveLevelSet (CDataMatrix2D *LevelSetFunctionMatrix, CDataMatrix2D *EdgeIndicatorMatrix, double dblLamda, double mu, double dblAlpha, double dblEpsilon, int iTimeStep){

	int i, j;
	
	CGradient *Gradient = new CGradient();
	CDataMatrix2D *LevelSetFunctionMatrixRet = NULL;
	CDataMatrix2D *EdgeIndicatorMatrixGradientX = NULL;
	CDataMatrix2D *EdgeIndicatorMatrixGradientY = NULL;
	CDataMatrix2D *NeumannLevelSetFunctionMatrixGradientX = NULL;
	CDataMatrix2D *NeumannLevelSetFunctionMatrixGradientY = NULL;
	CDataMatrix2D *NormalizationMatrix = new CDataMatrix2D(LevelSetFunctionMatrix->GetNumberOfRows(), LevelSetFunctionMatrix->GetNumberOfColumns());
	CDataMatrix2D *NormalizationMatrixX = new CDataMatrix2D(LevelSetFunctionMatrix->GetNumberOfRows(), LevelSetFunctionMatrix->GetNumberOfColumns());
	CDataMatrix2D *NormalizationMatrixY = new CDataMatrix2D(LevelSetFunctionMatrix->GetNumberOfRows(), LevelSetFunctionMatrix->GetNumberOfColumns());
	CDataMatrix2D *DiracFunctionMatrix = NULL;
	CDataMatrix2D *CurvatureCentralMatrix = NULL;
	CDataMatrix2D *WeightedLengthTermMatrix = new CDataMatrix2D(LevelSetFunctionMatrix->GetNumberOfRows(), LevelSetFunctionMatrix->GetNumberOfColumns());
	CDataMatrix2D *PenalizingTermMatrix = new CDataMatrix2D(LevelSetFunctionMatrix->GetNumberOfRows(), LevelSetFunctionMatrix->GetNumberOfColumns());
	CDataMatrix2D *WeightedAreaTermMatrix = new CDataMatrix2D(LevelSetFunctionMatrix->GetNumberOfRows(), LevelSetFunctionMatrix->GetNumberOfColumns());
	
	LevelSetFunctionMatrixRet = LevelSetFunctionMatrix->CopyDataMatrix2D();
	
	Gradient->CalculateMatrixGradient(EdgeIndicatorMatrix);
	EdgeIndicatorMatrixGradientX = Gradient->GetGradientDataMatrix2DX()->CopyDataMatrix2D();
	EdgeIndicatorMatrixGradientY = Gradient->GetGradientDataMatrix2DY()->CopyDataMatrix2D();

	NeumannBoundaryCondition(LevelSetFunctionMatrixRet);
	Gradient->CalculateMatrixGradient(LevelSetFunctionMatrixRet);
	NeumannLevelSetFunctionMatrixGradientX = Gradient->GetGradientDataMatrix2DX()->CopyDataMatrix2D();
	NeumannLevelSetFunctionMatrixGradientY = Gradient->GetGradientDataMatrix2DY()->CopyDataMatrix2D();

	for (i=0;i<NormalizationMatrix->GetNumberOfRows();i++){
		for (j=0;j<NormalizationMatrix->GetNumberOfColumns();j++){
			NormalizationMatrix->SetMatrixValue(i, j, (CFastMath::FastSqrt(pow(NeumannLevelSetFunctionMatrixGradientX->GetMatrixValue(i, j), 2) + pow(NeumannLevelSetFunctionMatrixGradientY->GetMatrixValue(i, j), 2) + ADDINGFACTOR)));
		}
	}

	for (i=0;i<NormalizationMatrix->GetNumberOfRows();i++){
		for (j=0;j<NormalizationMatrix->GetNumberOfColumns();j++){
			NormalizationMatrixX->SetMatrixValue(i, j, (NeumannLevelSetFunctionMatrixGradientX->GetMatrixValue(i, j) / NormalizationMatrix->GetMatrixValue(i, j)));
			NormalizationMatrixY->SetMatrixValue(i, j, (NeumannLevelSetFunctionMatrixGradientY->GetMatrixValue(i, j) / NormalizationMatrix->GetMatrixValue(i, j)));
		}
	}

	DiracFunctionMatrix = DiracFunction(LevelSetFunctionMatrixRet, dblEpsilon);
	CurvatureCentralMatrix = CurvatureCentral(NormalizationMatrixX, NormalizationMatrixY);

	for (i=0;i<WeightedLengthTermMatrix->GetNumberOfRows();i++){
		for (j=0;j<WeightedLengthTermMatrix->GetNumberOfColumns();j++){
			WeightedLengthTermMatrix->SetMatrixValue(i, j, (dblLamda * DiracFunctionMatrix->GetMatrixValue(i, j) * ((EdgeIndicatorMatrixGradientX->GetMatrixValue(i, j) * NormalizationMatrixX->GetMatrixValue(i, j)) + (EdgeIndicatorMatrixGradientY->GetMatrixValue(i, j) * NormalizationMatrixY->GetMatrixValue(i, j)) + (EdgeIndicatorMatrix->GetMatrixValue(i, j) * CurvatureCentralMatrix->GetMatrixValue(i, j)))));
		}
	}

	// penalizingTerm=mu*(4*del2(u)-K);

	for (i=0;i<WeightedAreaTermMatrix->GetNumberOfRows();i++){
		for (j=0;j<WeightedAreaTermMatrix->GetNumberOfColumns();j++){
			WeightedAreaTermMatrix->SetMatrixValue(i, j, (dblAlpha * DiracFunctionMatrix->GetMatrixValue(i, j) * EdgeIndicatorMatrix->GetMatrixValue(i, j)));
		}
	}

	for (i=0;i<LevelSetFunctionMatrixRet->GetNumberOfRows();i++){
		for (j=0;j<LevelSetFunctionMatrixRet->GetNumberOfColumns();j++){
			LevelSetFunctionMatrixRet->SetMatrixValue(i, j, (LevelSetFunctionMatrixRet->GetMatrixValue(i, j) + (double)(iTimeStep) * (WeightedLengthTermMatrix->GetMatrixValue(i, j) + WeightedAreaTermMatrix->GetMatrixValue(i, j) + PenalizingTermMatrix->GetMatrixValue(i, j))));
		}
	}

	delete WeightedAreaTermMatrix;
	WeightedAreaTermMatrix = NULL;
	delete PenalizingTermMatrix;
	PenalizingTermMatrix = NULL;
	delete WeightedLengthTermMatrix;
	WeightedLengthTermMatrix = NULL;
	delete CurvatureCentralMatrix;
	CurvatureCentralMatrix = NULL;
	delete DiracFunctionMatrix;
	DiracFunctionMatrix = NULL;
	delete NormalizationMatrixY;
	NormalizationMatrixY = NULL;
	delete NormalizationMatrixX;
	NormalizationMatrixX = NULL;
	delete NormalizationMatrix;
	NormalizationMatrix = NULL;
	delete NeumannLevelSetFunctionMatrixGradientY;
	NeumannLevelSetFunctionMatrixGradientY = NULL;
	delete NeumannLevelSetFunctionMatrixGradientX;
	NeumannLevelSetFunctionMatrixGradientX = NULL;
	delete EdgeIndicatorMatrixGradientY;
	EdgeIndicatorMatrixGradientY = NULL;
	delete EdgeIndicatorMatrixGradientX;
	EdgeIndicatorMatrixGradientX = NULL;
	delete Gradient;
	Gradient = NULL;

	return LevelSetFunctionMatrixRet;

}

void CLevelSet::NeumannBoundaryCondition (CDataMatrix2D *pDataMatrix2D){

	int i, j;

	CDataMatrix2D *Tmp = NULL;
	Tmp = pDataMatrix2D->CopyDataMatrix2D();
	
	Replace4(Tmp, 0, (Tmp->GetNumberOfRows() - 1), 0, (Tmp->GetNumberOfColumns() - 1), 2, (Tmp->GetNumberOfRows() - 3), 2, (Tmp->GetNumberOfColumns() - 3));
	for (i=1;i<(Tmp->GetNumberOfColumns() - 1);i++){
		Replace3C(Tmp, 0, (Tmp->GetNumberOfRows() - 1), i, 2, (Tmp->GetNumberOfRows() - 3), i);
	}
	for (i=1;i<(Tmp->GetNumberOfRows() - 1);i++){
		Replace3R(Tmp, i, 0, (Tmp->GetNumberOfColumns() - 1), i, 2, (Tmp->GetNumberOfColumns() - 3));
	}

	for (i=0;i<Tmp->GetNumberOfRows();i++){
		for (j=0;j<Tmp->GetNumberOfColumns();j++){
			pDataMatrix2D->SetMatrixValue(i, j, Tmp->GetMatrixValue(i, j));
		}
	}

	delete Tmp;
	Tmp = NULL;

}

CDataMatrix2D *CLevelSet::DiracFunction (CDataMatrix2D *pDataMatrix, double dblSigma){

	int i, j;

	CDataMatrix2D *DiracFunctionRet = new CDataMatrix2D(pDataMatrix->GetNumberOfRows(), pDataMatrix->GetNumberOfColumns());
	CDataMatrix2D *Tmp = new CDataMatrix2D(pDataMatrix->GetNumberOfRows(), pDataMatrix->GetNumberOfColumns());
	
	for (i=0;i<DiracFunctionRet->GetNumberOfRows();i++){
		for (j=0;j<DiracFunctionRet->GetNumberOfColumns();j++){
			DiracFunctionRet->SetMatrixValue(i, j, ((1.0f / 2.0f / dblSigma) * (1.0f + cos(PI * pDataMatrix->GetMatrixValue(i, j) / dblSigma))));
		}
	}

	for (i=0;i<Tmp->GetNumberOfRows();i++){
		for (j=0;j<Tmp->GetNumberOfColumns();j++){
			if ((pDataMatrix->GetMatrixValue(i, j) <= dblSigma) && (pDataMatrix->GetMatrixValue(i, j) >= -dblSigma)){
				Tmp->SetMatrixValue(i, j, 1.0f);
			}
		}
	}

	for (i=0;i<DiracFunctionRet->GetNumberOfRows();i++){
		for (j=0;j<DiracFunctionRet->GetNumberOfColumns();j++){
			DiracFunctionRet->SetMatrixValue(i, j, (DiracFunctionRet->GetMatrixValue(i, j) * Tmp->GetMatrixValue(i, j)));
		}
	}

	delete Tmp;
	Tmp = NULL;
	
	return DiracFunctionRet;

}

CDataMatrix2D *CLevelSet::CurvatureCentral (CDataMatrix2D *pDataMatrixX, CDataMatrix2D *pDataMatrixY){

	CGradient *GradientX = new CGradient();
	CGradient *GradientY = new CGradient();
	CDataMatrix2D *CurvatureCentralMatrix = NULL;

	GradientX->CalculateMatrixGradient(pDataMatrixX);
	GradientY->CalculateMatrixGradient(pDataMatrixY);

	CurvatureCentralMatrix = GradientX->GetGradientDataMatrix2DX()->Add(GradientY->GetGradientDataMatrix2DY());

	delete GradientY;
	GradientY = NULL;
	delete GradientX;
	GradientX = NULL;

	return CurvatureCentralMatrix;

}

void CLevelSet::Replace4 (CDataMatrix2D *pDataMatrix2D, int A11, int A12, int A21, int A22, int RA11, int RA12, int RA21, int RA22){

	pDataMatrix2D->SetMatrixValue(A11, A21, pDataMatrix2D->GetMatrixValue(RA11, RA21));
	pDataMatrix2D->SetMatrixValue(A11, A22, pDataMatrix2D->GetMatrixValue(RA11, RA22));

	pDataMatrix2D->SetMatrixValue(A12, A21, pDataMatrix2D->GetMatrixValue(RA12, RA21));
	pDataMatrix2D->SetMatrixValue(A12, A22, pDataMatrix2D->GetMatrixValue(RA12, RA22));

}

void CLevelSet::Replace3C (CDataMatrix2D *pDataMatrix2D, int A11, int A12, int A21, int RA11, int RA12, int RA21){

	pDataMatrix2D->SetMatrixValue(A11, A21, pDataMatrix2D->GetMatrixValue(RA11, RA21));
	pDataMatrix2D->SetMatrixValue(A12, A21, pDataMatrix2D->GetMatrixValue(RA12, RA21));

}

void CLevelSet::Replace3R (CDataMatrix2D *pDataMatrix2D, int A11, int A21, int A22, int RA11, int RA21, int RA22){

	pDataMatrix2D->SetMatrixValue(A11, A21, pDataMatrix2D->GetMatrixValue(RA11, RA21));
	pDataMatrix2D->SetMatrixValue(A11, A22, pDataMatrix2D->GetMatrixValue(RA11, RA22));

}
