#include "stdafx.h"
#include "PrincipalComponentAnalysis.h"
#include "Trace.h"

CPrincipalComponentAnalysis::CPrincipalComponentAnalysis()
{

}

CPrincipalComponentAnalysis::~CPrincipalComponentAnalysis()
{

}

CClass *CPrincipalComponentAnalysis::PrincipalComponentAnalysis (CClass *pClass, PrincipalComponentTypeOfAnalysis pcta){

// n = atoi(argv[2]);              /* # rows */
// m = atoi(argv[3]);              /* # columns */

	CDataMatrix2D *pDataMatrix2D = NULL;
	CClass *pRetClass = NULL;

	CClassToDataMatrix *ClassToDataMatrix = new CClassToDataMatrix();
	pDataMatrix2D = ClassToDataMatrix->ClassToDataMatrix(pClass);
	
	CDataMatrix2D *PCADataMatrix = new CDataMatrix2D(pDataMatrix2D->GetNumberOfRows(), pDataMatrix2D->GetNumberOfColumns());
	CDataMatrix2D *AnalyzedDataMatrix = new CDataMatrix2D(pDataMatrix2D->GetNumberOfColumns(), pDataMatrix2D->GetNumberOfColumns());

	switch (pcta){
		case TYPEOFANALYSIS_CORRELATION:
			CorrelationColumns(pDataMatrix2D, AnalyzedDataMatrix);
			break;
		case TYPEOFANALYSIS_VARIANCE_COVARIANCE:
		
			break;
		case TYPEOFANALYSIS_SSCP:
		
			break;
	}

	CDataMatrix1D *EigenValuesMatrix = new CDataMatrix1D(pDataMatrix2D->GetNumberOfColumns());
	CDataMatrix1D *IntermediateMatrix = new CDataMatrix1D(pDataMatrix2D->GetNumberOfColumns());
	CDataMatrix2D *AnalyzedDataMatrixDuplicate = NULL;
	AnalyzedDataMatrixDuplicate = AnalyzedDataMatrix->CopyDataMatrix2D();
	
	TriangularDecomposition(AnalyzedDataMatrix, EigenValuesMatrix, IntermediateMatrix);
	
	CTrace::PrintDataMatrix1DToConsole(EigenValuesMatrix, "Eigen1");
	
	
	
	
	
//	TridiagonalQLImplicit(EigenValuesMatrix, IntermediateMatrix, AnalyzedDataMatrix);

	CTrace::PrintDataMatrix1DToConsole(EigenValuesMatrix, "Eigen2");
	

	pRetClass = ClassToDataMatrix->DataMatrixToClass(PCADataMatrix);

	delete AnalyzedDataMatrixDuplicate;
	AnalyzedDataMatrixDuplicate = NULL;
	delete IntermediateMatrix;
	IntermediateMatrix = NULL;
	delete EigenValuesMatrix;
	EigenValuesMatrix = NULL;
	delete AnalyzedDataMatrix;
	AnalyzedDataMatrix = NULL;
	delete PCADataMatrix;
	PCADataMatrix = NULL;
	delete ClassToDataMatrix;
	ClassToDataMatrix = NULL;
	delete pDataMatrix2D;
	pDataMatrix2D = NULL;

	return pRetClass;

}

void CPrincipalComponentAnalysis::CorrelationColumns (CDataMatrix2D *pDataMatrix2D, CDataMatrix2D *pAnalyzedDataMatrix){

	double dblEps = 0.005f;
	int i, j, k, l;
	double x = 0.0f;

	CDataMatrix2D *CopiedDataMatrix2D = pDataMatrix2D->CopyDataMatrix2D();
	CDataMatrix1D *MeanColumns = new CDataMatrix1D(pDataMatrix2D->GetNumberOfColumns());
	CDataMatrix1D *StandardDeviationColumns = new CDataMatrix1D(pDataMatrix2D->GetNumberOfColumns());

	for (j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
		MeanColumns->SetMatrixValue(j, 0.0f);
		for (i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
			MeanColumns->SetMatrixValue(j, (MeanColumns->GetMatrixValue(j) + pDataMatrix2D->GetMatrixValue(i, j)));
		}
		MeanColumns->SetMatrixValue(j, (MeanColumns->GetMatrixValue(j) / (double)(pDataMatrix2D->GetNumberOfRows())));
    }

	for (j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
		StandardDeviationColumns->SetMatrixValue(j, 0.0f);
		for (i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
			StandardDeviationColumns->SetMatrixValue(j, (StandardDeviationColumns->GetMatrixValue(j) + ((pDataMatrix2D->GetMatrixValue(i, j) - MeanColumns->GetMatrixValue(j)) * (pDataMatrix2D->GetMatrixValue(i, j) - MeanColumns->GetMatrixValue(j)))));
		}
		StandardDeviationColumns->SetMatrixValue(j, (StandardDeviationColumns->GetMatrixValue(j) / (double)(pDataMatrix2D->GetNumberOfRows())));
		StandardDeviationColumns->SetMatrixValue(j, sqrt(StandardDeviationColumns->GetMatrixValue(j)));
        if (StandardDeviationColumns->GetMatrixValue(j) <= dblEps){
			StandardDeviationColumns->SetMatrixValue(j, 1.0f);
		} 
    }

	for (i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
		for (j=0;j<pDataMatrix2D->GetNumberOfColumns();j++){
			CopiedDataMatrix2D->SetMatrixValue(i, j, (CopiedDataMatrix2D->GetMatrixValue(i, j) - MeanColumns->GetMatrixValue(j)));
			x = sqrt((double)(pDataMatrix2D->GetNumberOfRows()));
			x = x * StandardDeviationColumns->GetMatrixValue(j);
			CopiedDataMatrix2D->SetMatrixValue(i, j, (CopiedDataMatrix2D->GetMatrixValue(i, j) / x));
        }
    }

	for (k=0;k<(pDataMatrix2D->GetNumberOfColumns() - 1);k++){
		pAnalyzedDataMatrix->SetMatrixValue(k, k, 1.0f);
		for (l=(k + 1);l<pDataMatrix2D->GetNumberOfColumns();l++){
			pAnalyzedDataMatrix->SetMatrixValue(k, l, 0.0f);
			for (i=0;i<pDataMatrix2D->GetNumberOfRows();i++){
				pAnalyzedDataMatrix->SetMatrixValue(k, l, (pAnalyzedDataMatrix->GetMatrixValue(k, l) + CopiedDataMatrix2D->GetMatrixValue(i, k) * CopiedDataMatrix2D->GetMatrixValue(i, l)));
			}
			pAnalyzedDataMatrix->SetMatrixValue(l, k, pAnalyzedDataMatrix->GetMatrixValue(k, l));
		}
    }
	pAnalyzedDataMatrix->SetMatrixValue((pDataMatrix2D->GetNumberOfColumns() - 1), (pDataMatrix2D->GetNumberOfColumns() - 1), 1.0f);
    
	delete StandardDeviationColumns;
	StandardDeviationColumns = NULL;
	delete MeanColumns;
	MeanColumns = NULL;
	delete CopiedDataMatrix2D;
	CopiedDataMatrix2D = NULL;
	
}

void CPrincipalComponentAnalysis::TriangularDecomposition(CDataMatrix2D *pAnalyzedDataMatrix, CDataMatrix1D *EigenValuesMatrix, CDataMatrix1D *IntermediateMatrix){

	// a, n, d, e
	// a = pAnalyzedDataMatrix
	// n = columns
	// d = EigenValuesMatrix
	// e = IntermediateMatrix

	int i, j, k, l;
	double dblScale, hh, h, g, f;
	
	for (i=pAnalyzedDataMatrix->GetNumberOfColumns()-1;i>=2;i--){
		l = i - 1;
		h = dblScale = 0.0;
		if (l > 1){
			for (k=0;k<l;k++){
				dblScale += fabs(pAnalyzedDataMatrix->GetMatrixValue(i, k));
			}
			if (dblScale == 0.0){
				IntermediateMatrix->SetMatrixValue(i, pAnalyzedDataMatrix->GetMatrixValue(i, l));
			}
			else{
				for (k=0;k<l;k++){
					pAnalyzedDataMatrix->SetMatrixValue(i, k, (pAnalyzedDataMatrix->GetMatrixValue(i, k) / dblScale));
					h += (pAnalyzedDataMatrix->GetMatrixValue(i, k) * pAnalyzedDataMatrix->GetMatrixValue(i, k));
				}
				f = pAnalyzedDataMatrix->GetMatrixValue(i, l);
				g = f>0 ? -sqrt(h) : sqrt(h);
				IntermediateMatrix->SetMatrixValue(i, (dblScale * g));
				h -= f * g;
				pAnalyzedDataMatrix->SetMatrixValue(i, l, (f - g));
				f = 0.0;
				for (j=0;j<l;j++){
					pAnalyzedDataMatrix->SetMatrixValue(j, i, (pAnalyzedDataMatrix->GetMatrixValue(i, j) / h));
					g = 0.0;
					for (k=0;k<j;k++){
						g += pAnalyzedDataMatrix->GetMatrixValue(j, k) * pAnalyzedDataMatrix->GetMatrixValue(i, k);
					}
					for (k=(j+1);k<l;k++){
						g += pAnalyzedDataMatrix->GetMatrixValue(k, j) * pAnalyzedDataMatrix->GetMatrixValue(i, k);
					}
					IntermediateMatrix->SetMatrixValue(j, (g / h));
					f += (IntermediateMatrix->GetMatrixValue(j) * pAnalyzedDataMatrix->GetMatrixValue(i, j));
				}
				hh = f / (h + h);
				for (j=0;j<l;j++){
					f = pAnalyzedDataMatrix->GetMatrixValue(i, j);
					//e[j] = g = e[j] - hh * f; ???????
					g = IntermediateMatrix->GetMatrixValue(j) - hh * f;
					IntermediateMatrix->SetMatrixValue(j, g);
					for (k=0;k<=j;k++){
						pAnalyzedDataMatrix->SetMatrixValue(j, k, (pAnalyzedDataMatrix->GetMatrixValue(j, k) - (f * IntermediateMatrix->GetMatrixValue(k) + g * pAnalyzedDataMatrix->GetMatrixValue(i, k))));
					}
				}
			}
		}
		else{
			IntermediateMatrix->SetMatrixValue(i, pAnalyzedDataMatrix->GetMatrixValue(i, l));
		}	
		EigenValuesMatrix->SetMatrixValue(i, h);
    }
	
	EigenValuesMatrix->SetMatrixValue(1, 0.0f);
	IntermediateMatrix->SetMatrixValue(1, 0.0f);
	
	for (i=0;i<pAnalyzedDataMatrix->GetNumberOfColumns();i++){
		l = i;// - 1;
		if (EigenValuesMatrix->GetMatrixValue(i)){
			for (j=0;j<l;j++){
				g = 0.0;
				for (k=0;k<l;k++){
					g += pAnalyzedDataMatrix->GetMatrixValue(i, k) * pAnalyzedDataMatrix->GetMatrixValue(k, j);
				}
				for (k=0;k<l;k++){
					pAnalyzedDataMatrix->SetMatrixValue(k, j, (pAnalyzedDataMatrix->GetMatrixValue(k, j) - g * pAnalyzedDataMatrix->GetMatrixValue(k, i)));
				}
			}
		}
		
		EigenValuesMatrix->SetMatrixValue(i, pAnalyzedDataMatrix->GetMatrixValue(i, i));
		pAnalyzedDataMatrix->SetMatrixValue(i, i, 1.0f);
		
		for (j=0;j<l;j++){
			pAnalyzedDataMatrix->SetMatrixValue(i, j, 0.0f);
			pAnalyzedDataMatrix->SetMatrixValue(j, i, 0.0f);
		}
    }

}

void CPrincipalComponentAnalysis::TridiagonalQLImplicit(CDataMatrix1D *EigenValuesMatrix, CDataMatrix1D *IntermediateMatrix, CDataMatrix2D *pAnalyzedDataMatrix){

	// d, e, n, z
	// d EigenValuesMatrix
	// e IntermediateMatrix
	// n columns
	// z pAnalyzedDataMatrix

	int m, l, iter, i, k;
	float s, r, p, g, f, dd, c, b;
	void erhand();
	
	for (i=2;i<pAnalyzedDataMatrix->GetNumberOfColumns();i++){
		IntermediateMatrix->SetMatrixValue((i - 1), (IntermediateMatrix->GetMatrixValue(i)));
	}
	IntermediateMatrix->SetMatrixValue((pAnalyzedDataMatrix->GetNumberOfColumns() - 1), 0.0f);
	for (l=0;l<pAnalyzedDataMatrix->GetNumberOfColumns();l++){
		iter = 0;
		do{
			for (m=l;m<(pAnalyzedDataMatrix->GetNumberOfColumns() - 1);m++){
				dd = fabs(EigenValuesMatrix->GetMatrixValue(m)) + fabs(EigenValuesMatrix->GetMatrixValue(m + 1));
				if (fabs(IntermediateMatrix->GetMatrixValue(m)) + dd == dd){
					break;
				} 
			}
			if (m != l){
				if (iter++ == 30){
					return;
					//erhand("No convergence in TLQI.");
				} 
				g = (EigenValuesMatrix->GetMatrixValue(l + 1) - EigenValuesMatrix->GetMatrixValue(l)) / (2.0 * IntermediateMatrix->GetMatrixValue(l));
				r = sqrt((g * g) + 1.0);
				g = EigenValuesMatrix->GetMatrixValue(l + 1) - EigenValuesMatrix->GetMatrixValue(l) + IntermediateMatrix->GetMatrixValue(l) / (g + SIGN(r, g));
				s = c = 1.0;
				p = 0.0;
				for (i=(m - 1);i>l;i--){
					f = s * IntermediateMatrix->GetMatrixValue(i);
					b = c * IntermediateMatrix->GetMatrixValue(i);
					if (fabs(f) >= fabs(g)){
						c = g / f;
						r = sqrt((c * c) + 1.0);
						IntermediateMatrix->SetMatrixValue((i + 1), (f * r));
						c *= (s = 1.0 / r);
                    }
					else{
						s = f / g;
						r = sqrt((s * s) + 1.0);
						IntermediateMatrix->SetMatrixValue((i + 1), (g * r));
						s *= (c = 1.0 / r);
                    }
					g = EigenValuesMatrix->GetMatrixValue(i + 1) - p;
					r = (EigenValuesMatrix->GetMatrixValue(i) - g) * s + 2.0 * c * b;
					p = s * r;
					EigenValuesMatrix->SetMatrixValue((i + 1), (g + p));
					g = c * r - b;
					for (k=0;k<pAnalyzedDataMatrix->GetNumberOfColumns();k++){
						pAnalyzedDataMatrix->GetMatrixValue(k, (i + 1));
						pAnalyzedDataMatrix->SetMatrixValue(k, (i + 1), (s * pAnalyzedDataMatrix->GetMatrixValue(k, i) + c * f));
						pAnalyzedDataMatrix->SetMatrixValue(k, i, (c * pAnalyzedDataMatrix->GetMatrixValue(k, i) - s * f));
					}
				}
				EigenValuesMatrix->SetMatrixValue(l, (EigenValuesMatrix->GetMatrixValue(l) - p));
				IntermediateMatrix->SetMatrixValue(l, g);
				IntermediateMatrix->SetMatrixValue(m, 0.0f);
			}
		}  while (m != l);
	}

}
