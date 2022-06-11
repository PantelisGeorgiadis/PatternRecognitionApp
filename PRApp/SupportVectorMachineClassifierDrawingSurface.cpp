#include "stdafx.h"
#include "SupportVectorMachineClassifierDrawingSurface.h"

CSupportVectorMachineClassifierDrawingSurface::CSupportVectorMachineClassifierDrawingSurface()
{

	srand(time(0));
	m_svmi.svmkt = SVMKERNELTYPE_LINEAR;
	m_svmi.dblGaussianSigma = 0.0f;
	m_svmi.iPolynomialDegree = 0;
	m_svmi.dblSigmoidC = 0.0f;
	m_svmi.dblSigmoidV = 1.0f;
	m_svmi.dblTolerance = 0.001;
	m_svmi.dblC = 1.0f; 

	m_AlphaMatrix = NULL;
	m_dblb = 0.0f;
	m_iC = 0;
	m_ErrorCacheMatrix = NULL;
	m_iAlphaNonBound = 0;
	m_bAlphaBound = NULL;
	m_iRandlist = NULL;

}

CSupportVectorMachineClassifierDrawingSurface::~CSupportVectorMachineClassifierDrawingSurface()
{

}

CDrawingSurface *CSupportVectorMachineClassifierDrawingSurface::CreateSupportVectorMachineClassifierDrawingSurface (CDataSet *pDataSet, SVMINFO *svmi){

	int i, j;
	int iPatternSum = 0;

	if (pDataSet->GetNumberOfClasses() > 2){
		return NULL;
	}

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		for (j=0;j<pDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			iPatternSum++;
		}
	}
	
	m_svmi.svmkt = svmi->svmkt;
	m_svmi.dblGaussianSigma = svmi->dblGaussianSigma;
	m_svmi.iPolynomialDegree = svmi->iPolynomialDegree;
	m_svmi.dblSigmoidC = svmi->dblSigmoidC;
	m_svmi.dblSigmoidV = svmi->dblSigmoidV;
	m_svmi.dblTolerance = svmi->dblTolerance;
	m_svmi.dblC = svmi->dblC;
	
	CDrawingSurface *DrawingSurface = new CDrawingSurface(SVMDRAWINGSURFACEDIMENSION);

	for (i=0;i<pDataSet->GetNumberOfClasses();i++){
		DrawingSurface->AddClass(pDataSet->GetClass(i));
	}

	CDataSet *NormalizedDataSet = DrawingSurface->NormalizeDataSetToDrawingSurface();
	for (i=0;i<NormalizedDataSet->GetClass(0)->GetNumberOfPatterns();i++){
		NormalizedDataSet->GetClass(0)->GetPattern(i)->SetReservedValue(1);
	}
	
	for (i=0;i<NormalizedDataSet->GetClass(1)->GetNumberOfPatterns();i++){
		NormalizedDataSet->GetClass(1)->GetPattern(i)->SetReservedValue(-1);
	}


	CClass *CombinedClass = NormalizedDataSet->MergeDataSet();
	CClassToDataMatrix *ClassToDataMatrix = new CClassToDataMatrix();
	CDataMatrix2D *CombinedDataSetMatrix = ClassToDataMatrix->ClassToDataMatrix(CombinedClass);
	CDataMatrix1D *LabelMatrix = new CDataMatrix1D(iPatternSum);
	CDataMatrix1D *LagrangianMatrix = NULL;

	for (i=0;i<LabelMatrix->GetNumberOfColumns();i++){
		LabelMatrix->SetMatrixValue(i, CombinedClass->GetPattern(i)->GetReservedValue());
	}

	//NormalizedDataSet->WriteDataSetDataToFile("C:\\Norm", ".txt");
	//CombinedDataSetMatrix->WriteMatrixDataToFile("CombData.txt");
	//LabelMatrix->GetDataMatrix1DAsDataMatrix2D()->WriteMatrixDataToFile("Labels.txt");

	LagrangianMatrix = DesignSupportVectorMachineClassifier(CombinedDataSetMatrix, LabelMatrix, LagrangianMatrix);
	
	
	SVMDRAWINGINFO *svmdi = new SVMDRAWINGINFO [SVMDRAWINGSURFACEDIMENSION * SVMDRAWINGSURFACEDIMENSION];
	CPattern *UnknownPattern = new CPattern(2);

	for (i=0;i<SVMDRAWINGSURFACEDIMENSION;i++){
		for (j=0;j<SVMDRAWINGSURFACEDIMENSION;j++){
			
			UnknownPattern->GetFeature(0)->SetFeatureValue(j);
			UnknownPattern->GetFeature(1)->SetFeatureValue(i);
			
			svmdi[(i * SVMDRAWINGSURFACEDIMENSION) + j].x = j;
			svmdi[(i * SVMDRAWINGSURFACEDIMENSION) + j].y = i;
			svmdi[(i * SVMDRAWINGSURFACEDIMENSION) + j].iLabel = Classify(UnknownPattern, CombinedDataSetMatrix, LabelMatrix, LagrangianMatrix);

		}
	}

	for (i=0;i<SVMDRAWINGSURFACEDIMENSION;i++){
		for (j=0;j<SVMDRAWINGSURFACEDIMENSION;j++){
			if (svmdi[(i * SVMDRAWINGSURFACEDIMENSION) + j].iLabel == 0){
				DrawingSurface->SetPixel(j, i, 180);
			}
			if (svmdi[(i * SVMDRAWINGSURFACEDIMENSION) + j].iLabel == 1){
				DrawingSurface->SetPixel(j, i, 255);
			}
		}
	}

	DrawingSurface->Render();
	DrawingSurface->SaveDrawingSurfaceToBmpFile8("C:\\a.bmp");

	delete UnknownPattern;
	UnknownPattern = NULL;
	delete [] svmdi;
	svmdi = NULL;
	delete NormalizedDataSet;
	NormalizedDataSet = NULL;
	delete LagrangianMatrix;
	LagrangianMatrix = NULL;
	delete LabelMatrix;
	LabelMatrix = NULL;
	delete CombinedDataSetMatrix;
	CombinedDataSetMatrix = NULL;
	delete ClassToDataMatrix;
	ClassToDataMatrix = NULL;
	delete CombinedClass;
	CombinedClass = NULL;

	return DrawingSurface;

}

int CSupportVectorMachineClassifierDrawingSurface::Classify (CPattern *pUnknownPattern, CDataMatrix2D *CombinedDataSetMatrix, CDataMatrix1D *LabelMatrix, CDataMatrix1D *LagrangianMatrix){

	int i, j;
	double dblDiscriminant = 0.0f;
	
	double *p1 = new double [CombinedDataSetMatrix->GetNumberOfColumns()];
	double *p2 = new double [pUnknownPattern->GetNumberOfFeatures()];
	for (i=0;i<pUnknownPattern->GetNumberOfFeatures();i++){
		p2[i] = pUnknownPattern->GetFeature(i)->GetFeatureValue();
	}

	switch (m_svmi.svmkt){
		case SVMKERNELTYPE_LINEAR:
			for (i=0;i<CombinedDataSetMatrix->GetNumberOfRows();i++){
				for (j=0;j<CombinedDataSetMatrix->GetNumberOfColumns();j++){
					p1[j] = CombinedDataSetMatrix->GetMatrixValue(i, j);
				}
				dblDiscriminant = dblDiscriminant + (LabelMatrix->GetMatrixValue(i) * LagrangianMatrix->GetMatrixValue(i) * CalculateLinearKernelValue(p1, p2, CombinedDataSetMatrix->GetNumberOfColumns()));
			}
			break;
		case SVMKERNELTYPE_POLYNOMIAL:
			for (i=0;i<CombinedDataSetMatrix->GetNumberOfRows();i++){
				for (j=0;j<CombinedDataSetMatrix->GetNumberOfColumns();j++){
					p1[j] = CombinedDataSetMatrix->GetMatrixValue(i, j);
				}
				dblDiscriminant = dblDiscriminant + (LabelMatrix->GetMatrixValue(i) * LagrangianMatrix->GetMatrixValue(i) * CalculatePolynomialKernelValue(p1, p2, CombinedDataSetMatrix->GetNumberOfColumns()));
			}
			break;
		case SVMKERNELTYPE_RBF:
			for (i=0;i<CombinedDataSetMatrix->GetNumberOfRows();i++){
				for (j=0;j<CombinedDataSetMatrix->GetNumberOfColumns();j++){
					p1[j] = CombinedDataSetMatrix->GetMatrixValue(i, j);
				}
				dblDiscriminant = dblDiscriminant + (LabelMatrix->GetMatrixValue(i) * LagrangianMatrix->GetMatrixValue(i) * CalculateGaussianKernelValue(p1, p2, CombinedDataSetMatrix->GetNumberOfColumns()));
			}
			break;
		case SVMKERNELTYPE_SIGMOID:
			for (i=0;i<CombinedDataSetMatrix->GetNumberOfRows();i++){
				for (j=0;j<CombinedDataSetMatrix->GetNumberOfColumns();j++){
					p1[j] = CombinedDataSetMatrix->GetMatrixValue(i, j);
				}
				dblDiscriminant = dblDiscriminant + (LabelMatrix->GetMatrixValue(i) * LagrangianMatrix->GetMatrixValue(i) * CalculateSigmoidKernelValue(p1, p2, CombinedDataSetMatrix->GetNumberOfColumns()));
			}
			break;
	}

	delete [] p1;
	p1 = NULL;
	delete [] p2;
	p2 = NULL;

	dblDiscriminant = dblDiscriminant - m_dblb;

	//return (int)(dblDiscriminant);
	if (dblDiscriminant < 0){
		return 1;
	}
	else{
		return 0;
	}
	
	/*if ((pUnknownPattern->GetReservedValue() > 0) && (dblDiscriminant > 0)){
		if (pUnknownPattern->GetReservedValue() > 0){
			return 0;
		}
		else{
			return 1;
		}
	}
	else if ((pUnknownPattern->GetReservedValue() < 0) && (dblDiscriminant <= 0)){
		if (pUnknownPattern->GetReservedValue() > 0){
			return 0;
		}
		else{
			return 1;
		}
	} 
	else{
		if (pUnknownPattern->GetReservedValue() > 0){
			return 1;
		}
		else{
			return 0;
		}
	}*/

}

CDataMatrix1D *CSupportVectorMachineClassifierDrawingSurface::DesignSupportVectorMachineClassifier (CDataMatrix2D *CombinedDataSetMatrix, CDataMatrix1D *LabelMatrix, CDataMatrix1D *LagrangianMatrix){

	int i;
	int iChangedNumber = 0;
	int iLoopCounter = 0;
	bool bExaminedAll = true;

	m_AlphaMatrix = new CDataMatrix1D(LabelMatrix->GetNumberOfColumns());
	m_bAlphaBound = new bool [m_AlphaMatrix->GetNumberOfColumns()];
	for (i=0;i<m_AlphaMatrix->GetNumberOfColumns();i++){
		m_bAlphaBound[i] = true;
	}

	m_dblb = 0.0f;
	m_iC = m_svmi.dblC;
	m_iAlphaNonBound = 0;

	m_ErrorCacheMatrix = new CDataMatrix1D(m_AlphaMatrix->GetNumberOfColumns());
	for (i=0;i<m_AlphaMatrix->GetNumberOfColumns();i++){
		m_ErrorCacheMatrix->SetMatrixValue(i, -LabelMatrix->GetMatrixValue(i));
	}

	m_iRandlist = new int[m_AlphaMatrix->GetNumberOfColumns()];

	while ((iChangedNumber > 0) || (bExaminedAll == true)){
		iLoopCounter++;
		iChangedNumber = 0;
		if (bExaminedAll == true){
			for (i=0;i<m_AlphaMatrix->GetNumberOfColumns();i++){
				iChangedNumber += ExamineExample(CombinedDataSetMatrix, LabelMatrix, i);
			} 
		}
		else{
			for (i=0;i<m_AlphaMatrix->GetNumberOfColumns();i++){
				if (m_bAlphaBound[i] == false){
					iChangedNumber += ExamineExample(CombinedDataSetMatrix, LabelMatrix, i);
				}
			}
		}
		
		if (bExaminedAll == true){
			bExaminedAll = false;
		}
		else if (iChangedNumber == 0){
			bExaminedAll = true;
		}
	}

	delete [] m_iRandlist;
	m_iRandlist = NULL;
	delete m_ErrorCacheMatrix;
	m_ErrorCacheMatrix = NULL;
	delete [] m_bAlphaBound;
	m_bAlphaBound = NULL;

	return m_AlphaMatrix;

}

int CSupportVectorMachineClassifierDrawingSurface::ExamineExample (CDataMatrix2D *CombinedDataSetMatrix, CDataMatrix1D *LabelMatrix, int iRowIndex){
  
	int y2 = 0;
	double alpha2 = 0.0f;
	double C2 = 0.0f;
	double E2 = 0.0f;
	double r2 = 0.0f;
	int	N = 0;
	int i1 = 0;
	int k = 0;
	
	N = LabelMatrix->GetNumberOfColumns();
	y2 = LabelMatrix->GetMatrixValue(iRowIndex);
	alpha2 = m_AlphaMatrix->GetMatrixValue(iRowIndex);
	C2 = m_iC;
	E2 = m_ErrorCacheMatrix->GetMatrixValue(iRowIndex);
	r2 = E2 * y2;
	
	if (((r2 < -m_svmi.dblTolerance) && (alpha2 < C2)) || ((r2 > m_svmi.dblTolerance) && (alpha2 > 0))){
		if (m_iAlphaNonBound > 1){
			if (E2 > 0){
				i1 = FindMinError(N);
			}
			else{
				i1 = FindMaxError(N);
			}
			
			if (i1 >= 0) {
				if (TakeStep(CombinedDataSetMatrix, LabelMatrix, i1, iRowIndex)){
					return 1;
				}
			}
		} 
		
		RandomSwap (m_iRandlist, N);
		for (k=0;k<N;k++){
			i1 = m_iRandlist[k];
			
			if (m_bAlphaBound[i1] == false){
				if (TakeStep(CombinedDataSetMatrix, LabelMatrix, i1, iRowIndex)){
					return 1;
				}
			}
		}
		
		RandomSwap (m_iRandlist, N);
		for (k=0;k<N;k++){
			i1 = m_iRandlist[k];
			if (TakeStep(CombinedDataSetMatrix, LabelMatrix, i1, iRowIndex)){
				return 1;
			}
		} 
	} 
	
	return 0;

} 

int CSupportVectorMachineClassifierDrawingSurface::TakeStep (CDataMatrix2D *CombinedDataSetMatrix, CDataMatrix1D *LabelMatrix, int iIndex1, int iIndex2){
	
	double alpha1;
	int y1;
	double E1;
	
	double alpha2;
	int y2;
	double E2;
	double k11, k12, k22;
	double eta;
	
	int N;
	int d;
	int i, j;
	int s;
	double C, b;
	double L, H;
	double a1, a2;
	double  b1, b2;  
	double *p1 = NULL;
	double *p2 = NULL;
		
	if (iIndex1 == iIndex2){
		return 0;
	}

	N = LabelMatrix->GetNumberOfColumns();
	d = CombinedDataSetMatrix->GetNumberOfColumns();
	C = m_iC;
	b = m_dblb;
	
	alpha1 = m_AlphaMatrix->GetMatrixValue(iIndex1);
	p1 = new double [d];
	for (i=0;i<d;i++){
		p1[i] = CombinedDataSetMatrix->GetMatrixValue(iIndex1, i);
	}
	y1 = LabelMatrix->GetMatrixValue(iIndex1);
	E1 = m_ErrorCacheMatrix->GetMatrixValue(iIndex1);
	

	p2 = new double [d];
	for (i=0;i<d;i++){
		p2[i] = CombinedDataSetMatrix->GetMatrixValue(iIndex2, i);
	}
	alpha2 = m_AlphaMatrix->GetMatrixValue(iIndex2);
	y2 = LabelMatrix->GetMatrixValue(iIndex2);
	E2 = m_ErrorCacheMatrix->GetMatrixValue(iIndex2);
	
	s = ((int)y1) * ((int)y2);
	if (s < 0){
		L = max (0, (alpha2 - alpha1));
		H = min (C, (C + alpha2 - alpha1));
	}
	else{
		L = max (0, (alpha2 + alpha1 - C));
		H = min (C, (alpha2 + alpha1));
	}
	
	if (L == H){
		delete [] p1;
		p1 = NULL;
		delete [] p2;
		p2 = NULL;
		
		return 0;
	}

	switch (m_svmi.svmkt){
		case SVMKERNELTYPE_LINEAR:
			k11 = CalculateLinearKernelValue(p1, p1, d);
			k12 = CalculateLinearKernelValue(p1, p2, d);
			k22 = CalculateLinearKernelValue(p2, p2, d);
			break;
		case SVMKERNELTYPE_POLYNOMIAL:
			k11 = CalculatePolynomialKernelValue(p1, p1, d);
			k12 = CalculatePolynomialKernelValue(p1, p2, d);
			k22 = CalculatePolynomialKernelValue(p2, p2, d);
			break;
		case SVMKERNELTYPE_RBF:
			k11 = CalculateGaussianKernelValue(p1, p1, d);
			k12 = CalculateGaussianKernelValue(p1, p2, d);
			k22 = CalculateGaussianKernelValue(p2, p2, d);
			break;
		case SVMKERNELTYPE_SIGMOID:
			k11 = CalculateSigmoidKernelValue(p1, p1, d);
			k12 = CalculateSigmoidKernelValue(p1, p2, d);
			k22 = CalculateSigmoidKernelValue(p2, p2, d);
			break;
	}

	eta = k11 + k22 - 2 * k12;
	
	if (eta > 0){
		a2 = alpha2 + y2 * (E1 - E2) / eta;
		if (a2 < L){
			a2 = L;
		}
		else if (a2 > H){
			a2 = H;
		}
	}
	else{
		double f1 = y1 * (E1 + b) - alpha1 * k11 - s * alpha2 * k12;
		double f2 = y2 * (E2 + b) - s * alpha1 * k12 - alpha2 * k22;
		double L1 = alpha1 + s * (alpha2 - L);
		double H1 = alpha1 + s * (alpha2 - H);
		double Lobj = L1 * f1 + L * f2 + 0.5f * L1 * L1 * k11 + 0.5f * L * L * k22 + s * L * L1 * k12;
		double Hobj = H1 * f1 + H * f2 + 0.5f * H1 * H1 * k11 + 0.5f * H * H * k22 + s * H * H1 * k12;
		
		if ((Hobj - Lobj) > m_svmi.dblTolerance){
			a2 = L;
		}
		else if ((Lobj - Hobj) > m_svmi.dblTolerance){
			a2 = H;
		}
		else{
			a2 = alpha2;
		}
	}

	if (a2 < 0){
		a2 = 0;
	}
	else if (a2 > C){
		a2 = C;
	}
	
	if (fabs(a2 - alpha2) < m_svmi.dblTolerance * (a2 + alpha2 + m_svmi.dblTolerance)){
		delete [] p1;
		p1 = NULL;
		delete [] p2;
		p2 = NULL;
		
		return 0;
	}
	
	a1 = alpha1 + s * (alpha2 - a2);
	if (a1 < 0){
		a1 = 0;
	}
	else if (a1 > C){
		a1 = C;
	}
	
	if ((a1 == 0.) || (a1 == C)){
		if (m_bAlphaBound[iIndex1] == false){
			m_bAlphaBound[iIndex1] = true;
			m_iAlphaNonBound--;
		}
	} 
	else{ 
		if (m_bAlphaBound[iIndex1] == true){
			m_bAlphaBound[iIndex1] = false;
			m_iAlphaNonBound++;
		}
	}
	
	if ((a2 == 0.) || (a2 == C)){
		if (m_bAlphaBound[iIndex2] == false){
			m_bAlphaBound[iIndex2] = true;
			m_iAlphaNonBound--;
		}
	} 
	else{ 
		if (m_bAlphaBound[iIndex2] == true){
			m_bAlphaBound[iIndex2] = false;
			m_iAlphaNonBound++;
		}
	}
	
	b1 = E1 + y1 * (a1 - alpha1) * k11 + y2 * (a2 - alpha2) * k12 + b;
	b2 = E2 + y1 * (a1 - alpha1) * k12 + y2 * (a2 - alpha2) * k22 + b;
	
	if (m_bAlphaBound[iIndex1] == false){
		m_dblb = b1;
	} 
	else if (m_bAlphaBound[iIndex2] == false){
		m_dblb = b2;
	} 
	else{ 
		m_dblb = .5 * (b1 + b2);
	}
	
	double k1i;
	double k2i;
	double *x = new double [d];
	
	for (i=0;i<N;i++){
		for (j=0;j<d;j++){
			x[j] = CombinedDataSetMatrix->GetMatrixValue(i, j);
		}
		
		switch (m_svmi.svmkt){
			case SVMKERNELTYPE_LINEAR:
				k1i = CalculateLinearKernelValue(x, p1, d);
				k2i = CalculateLinearKernelValue(x, p2, d);
				break;
			case SVMKERNELTYPE_POLYNOMIAL:
				k1i = CalculatePolynomialKernelValue(x, p1, d);
				k2i = CalculatePolynomialKernelValue(x, p2, d);
				break;
			case SVMKERNELTYPE_RBF:
				k1i = CalculateGaussianKernelValue(x, p1, d);
				k2i = CalculateGaussianKernelValue(x, p2, d);
				break;
			case SVMKERNELTYPE_SIGMOID:
				k1i = CalculateSigmoidKernelValue(x, p1, d);
				k2i = CalculateSigmoidKernelValue(x, p2, d);
				break;
		}
		
		m_ErrorCacheMatrix->SetMatrixValue(i, (m_ErrorCacheMatrix->GetMatrixValue(i) + (y1 * (a1 - alpha1) * k1i + y2 * (a2 - alpha2) * k2i - m_dblb + b)));	
	}
	
	m_AlphaMatrix->SetMatrixValue(iIndex1, a1);
	m_AlphaMatrix->SetMatrixValue(iIndex2, a2);

	delete [] x;
	x = NULL;
	delete [] p1;
	p1 = NULL;
	delete [] p2;
	p2 = NULL;
	
	return 1;

}

int CSupportVectorMachineClassifierDrawingSurface::FindMinError (int iNumberOfPatterns){

	int iMin;
	double dblMin;

	dblMin = 0.0f;
	iMin = -1;
	
	for (int i=0;i<iNumberOfPatterns;i++){
		if (m_bAlphaBound[i] == false){
			double dblCandidate = m_ErrorCacheMatrix->GetMatrixValue(i);
			if (iMin < 0){
				iMin = i;
				dblMin = dblCandidate;
			} 
			else if (dblCandidate < dblMin){
				iMin = i;
				dblMin = dblCandidate;
			}
		}
	}
	
	return iMin;

}

int CSupportVectorMachineClassifierDrawingSurface::FindMaxError (int iNumberOfPatterns){

	int iMax;
	double dblMax;

	dblMax = 0;
	iMax = -1;
	
	for (int i=0;i<iNumberOfPatterns;i++){
		if (m_bAlphaBound[i] == false){
			double dblCandidate = m_ErrorCacheMatrix->GetMatrixValue(i);
			if (iMax < 0){
				iMax = i;
				dblMax = dblCandidate;
			} 
			else if (dblCandidate > dblMax){
				iMax = i;
				dblMax = dblCandidate;
			} 
		} 
	} 
	
	return iMax;

}

void CSupportVectorMachineClassifierDrawingSurface::RandomSwap (int* A, int n){

	int i;
	int x;
	
	for (i=0;i<n;i++){
		A[i] = i;
	}
	
	for (i=0;i<n;i++){
		int temp;
		x = rand() % n;
		temp = A[i];
		A[i] = A[x];
		A[x] = temp;
	}

}

double CSupportVectorMachineClassifierDrawingSurface::CalculateLinearKernelValue (double *x1, double *x2, int d){

	int i;
	double dblSum = 0.0f;

	double *p1 = NULL;
	double *p2 = NULL;
	double a = 0.0f;
	double b = 0.0f;

	for (i=0, dblSum=0, p1=x1, p2=x2;i<d;i++, p1++, p2++){
		a = *p1;
		b = *p2;
		dblSum += a * b;
	}

	return dblSum;

}

double CSupportVectorMachineClassifierDrawingSurface::CalculateGaussianKernelValue (double *x1, double *x2, int d){

	int i;
	double dblSum = 0.0f;
	
	double *p1 = NULL;
	double *p2 = NULL;
	double dblDiff = 0.0f;
	
	for (i=0, dblSum=0, p1=x1, p2=x2;i<d;i++, p1++, p2++){
		dblDiff = *p1 - *p2;
		dblSum += dblDiff * dblDiff;
	}
	
	return exp(-m_svmi.dblGaussianSigma * dblSum);

}

double CSupportVectorMachineClassifierDrawingSurface::CalculatePolynomialKernelValue (double *x1, double *x2, int d){
	
	int i;
	double dblSum = 0.0f;
	double dblProduct = 0.0f;

	double *p1 = NULL;
	double *p2 = NULL;
	double a = 0.0f;
	double b = 0.0f;

	for (i=0, dblSum=0, p1=x1, p2=x2;i<d;i++, p1++, p2++){
		a = *p1;
		b = *p2;
		dblSum += a * b;
	}
	
	dblProduct = dblSum;
	for (i=1;i<(m_svmi.iPolynomialDegree / 2);i*=2){
		dblProduct *= dblProduct;
	}

	while(i < m_svmi.iPolynomialDegree) {
		dblProduct *= dblSum;
		i++;
	}
	
	return dblProduct;

}

double CSupportVectorMachineClassifierDrawingSurface::CalculateSigmoidKernelValue (double *x1, double *x2, int d){

	int i;
	double dblSum = 0.0f;
	double dblProduct = 0.0f;
	
	double *p1 = NULL;
	double *p2 = NULL;
	double a = 0.0f;
	double b = 0.0f;
	
	for (i=0, dblSum=0, p1=x1, p2=x2;i<d;i++, p1++, p2++){
		a = *p1;
		b = *p2;
		dblSum += a*b;
	}
	
	dblSum *= m_svmi.dblSigmoidV;
	dblSum += m_svmi.dblSigmoidC;
	
	return 1.0f / (1.0f + exp(dblSum));

}

double CSupportVectorMachineClassifierDrawingSurface::CalculateRadialBasisFunctionKernelValue (double *x1, double *x2, int d){


	return 1;

}
