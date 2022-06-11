#if !defined(AFX_RESAMPLE_H__1D395A30_A0DC_45F0_A7D5_6E80D9A2BE7F__INCLUDED_)
#define AFX_RESAMPLE_H__1D395A30_A0DC_45F0_A7D5_6E80D9A2BE7F__INCLUDED_

#include <cmath>
#include "DataMatrix2D.h"

#define DEFAULT_LANCZOS8_RADIUS			8.0
#define DEFAULT_LANCZOS3_RADIUS			3.0
#define DEFAULT_HERMITE_RADIUS			1.0
#define DEFAULT_BOX_RADIUS				0.5
#define DEFAULT_TRIANGLE_RADIUS			1.0
#define DEFAULT_BELL_RADIUS				1.5
#define DEFAULT_CUBICSPLINE_RADIUS		2.0
#define DEFAULT_MITCHELL_RADIUS			2.0
#define DEFAULT_COSINE_RADIUS			1.0
#define DEFAULT_CATMULLROM_RADIUS		2.0
#define DEFAULT_QUADRATIC_RADIUS		1.5
#define DEFAULT_QUADRATICBSPLINE_RADIUS	1.5
#define DEFAULT_CUBICCONVOLUTION_RADIUS	3.0

#define MAX_FILTER_RADIUS				16.0 
#define MIN_RESAMPLE_WIDTH				0x00000001
#define MAX_RESAMPLE_WIDTH				0x00001000
#define MIN_RESAMPLE_HEIGHT				0x00000001
#define MAX_RESAMPLE_HEIGHT				0x00001000

typedef double (*FilterFunction) (double);

class CResample  
{
public:
	CResample();
	virtual ~CResample();

	CDataMatrix2D *ResampleDataMatrix8 (CDataMatrix2D *pDataMatrix2D, int iNewWidth, int iNewHeight, ResampleFilter rf);

protected:

	void SetResampleFilter(ResampleFilter rf, FilterFunction *ppFilterFn, double *pdRadius);

	static double Lanczos8(double);
	static double Lanczos3(double);
	static double Hermite(double);
	static double Box(double);
	static double Triangle(double);
	static double Bell(double);
	static double CubicSpline(double);
	static double Mitchell(double);
	static double Cosine(double);
	static double CatmullRom(double);
	static double Quadratic(double);
	static double QuadraticBSpline(double);
	static double CubicConvolution(double);

};

#endif 
