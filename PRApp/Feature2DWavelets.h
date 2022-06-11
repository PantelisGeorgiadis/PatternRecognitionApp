#if !defined(AFX_FEATURE2DWAVELETS_H__B4F074AE_4DC7_4ADD_8877_FA29CC1C3E85__INCLUDED_)
#define AFX_FEATURE2DWAVELETS_H__B4F074AE_4DC7_4ADD_8877_FA29CC1C3E85__INCLUDED_

#include "DataMatrix2D.h"

#define h0 0.4829629131445341
#define h1 0.8365163037378079
#define h2 0.2241438680420134
#define h3 -0.1294095225512604

#define g0 -0.1294095225512604
#define g1 -0.2241438680420134
#define g2 0.8365163037378079
#define g3 -0.4829629131445341

#define Ih0 0.2241438680420134
#define Ih1 0.8365163037378079
#define Ih2 0.4829629131445341
#define Ih3 -0.1294095225512604

#define Ig0 -0.1294095225512604
#define Ig1 -0.4829629131445341
#define Ig2 0.8365163037378079
#define Ig3 -0.2241438680420134

class CFeature2DWavelets  
{
public:
	CFeature2DWavelets();
	virtual ~CFeature2DWavelets();

	void CalculateWavelet (CDataMatrix2D *pDataMatrix2D, int iLevel);
	double GetWavelet (void) { return m_dblWavelet; }

protected:

	double m_dblWavelet;

	void WaveletTransform (double *dpData, int iDataLenght);
	void InverseWaveletTransform (double *dpData, int iDataLenght);

};

#endif 
