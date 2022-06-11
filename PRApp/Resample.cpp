#include "stdafx.h"
#include "Resample.h"

CResample::CResample()
{

}

CResample::~CResample()
{

}

CDataMatrix2D *CResample::ResampleDataMatrix8 (CDataMatrix2D *pDataMatrix2D, int iNewWidth, int iNewHeight, ResampleFilter rf){

	double (*pFilterFunction)(double);
	double dRadius;
	SetResampleFilter(rf, &pFilterFunction, &dRadius);
	CDataMatrix2D *pResampledDataMatrix2D = NULL;

	const int COLOR_COMPONENTS = 1;
	
	long i, j, n, c;
	double xScale, yScale;

	double *h_weight; // Weight contribution    [ow][MAX_CONTRIBS]
	long    *h_pixel; // Pixel that contributes [ow][MAX_CONTRIBS]
	long    *h_count; // How many contribution for the pixel [ow]
	double *h_wsum;   // Sum of weights [ow]
										 
	double * v_weight; // Weight contribution    [oh][MAX_CONTRIBS]
	long   * v_pixel;  // Pixel that contributes [oh][MAX_CONTRIBS]
	long  * v_count;	 // How many contribution for the pixel [oh]
	double * v_wsum;   // Sum of weights [oh]

	double intensity[COLOR_COMPONENTS];

	double center;				// Center of current sampling 
	double weight;				// Current wight
	long left;						// Left of current sampling
	long right;						// Right of current sampling

	double * p_weight;		// Temporary pointer
	long   * p_pixel;     // Temporary pointer

	long MAX_CONTRIBS;    // Almost-const: max number of contribution for current sampling
	double SCALED_RADIUS;	// Almost-const: scaled radius for downsampling operations
	double FILTER_FACTOR; // Almost-const: filter factor for downsampling operations

	if ((iNewWidth == pDataMatrix2D->GetNumberOfColumns()) && (iNewHeight == pDataMatrix2D->GetNumberOfRows())){
		return pDataMatrix2D->CopyDataMatrix2D();
	}

	pResampledDataMatrix2D = new CDataMatrix2D(iNewHeight, iNewWidth);

	xScale = ((double)iNewWidth / pDataMatrix2D->GetNumberOfColumns());
	yScale = ((double)iNewHeight / pDataMatrix2D->GetNumberOfRows());

	if (xScale > 1.0){
		/* Horizontal upsampling */
		FILTER_FACTOR = 1.0;
		SCALED_RADIUS = dRadius;
	}
	else{ 
		/* Horizontal downsampling */ 
		FILTER_FACTOR = xScale;
		SCALED_RADIUS = dRadius / xScale;
	}
	/* The maximum number of contributions for a target pixel */
	MAX_CONTRIBS = (int) (2 * SCALED_RADIUS + 1);

	h_weight = new double[pResampledDataMatrix2D->GetNumberOfColumns() * MAX_CONTRIBS];//(double *) GlobalAlloc( 0, iNewWidth * MAX_CONTRIBS * sizeof(double)); /* weights */
	h_pixel  = new long[pResampledDataMatrix2D->GetNumberOfColumns() * MAX_CONTRIBS];//(int *) GlobalAlloc( 0, iNewWidth * MAX_CONTRIBS * sizeof(int)); /* the contributing pixels */
	h_count  = new long[pResampledDataMatrix2D->GetNumberOfColumns()];//(int *) GlobalAlloc( 0, iNewWidth * sizeof(int)); /* how may contributions for the target pixel */
	h_wsum   = new double[pResampledDataMatrix2D->GetNumberOfColumns()];//(double *)GlobalAlloc( 0, iNewWidth * sizeof(double)); /* sum of the weights for the target pixel */

	for (i=0;i<pResampledDataMatrix2D->GetNumberOfColumns();i++)
	{
		p_weight    = h_weight + i * MAX_CONTRIBS;
		p_pixel     = h_pixel  + i * MAX_CONTRIBS;

		h_count[i] = 0;
		h_wsum[i] =  0.0;
		
		center = ((double)i) / xScale;
		left = (int)((center + .5) - SCALED_RADIUS);
		right = (int)(left + 2 * SCALED_RADIUS);

		for (j = left; j<= right; j++)
		{
			if ( j < 0 || j >= pDataMatrix2D->GetNumberOfColumns()){
				continue;
			}
		
			weight = (*pFilterFunction)( (center - j) * FILTER_FACTOR);
			
			if (weight == 0.0) continue;

			n = h_count[i]; /* Since h_count[i] is our current index */
			p_pixel[n] = j;
			p_weight[n] = weight;
			h_wsum[i] += weight;
			h_count[i]++; /* Increment contribution count */
		}/* j */
	}/* i */

// 	/* Filter horizontally from input to temporary buffer */
// 	for (n = 0; n < pDataMatrix2D->GetNumberOfRows(); n++)
// 	{
// 		/* Here 'n' runs on the vertical coordinate */
// 		for ( i = 0; i < pResampledDataMatrix2D->GetNumberOfColumns(); i++)
// 		{/* i runs on the horizontal coordinate */
// 			p_weight = h_weight + i * MAX_CONTRIBS;
// 			p_pixel  = h_pixel  + i * MAX_CONTRIBS;
// 
// 			for (c=0; c<COLOR_COMPONENTS; c++)
// 			{
// 				intensity[c] = 0.0;
// 			}
// 			for (j=0; j < h_count[i]; j++)
// 			{
// 				weight = p_weight[j];	
// 				val = ib[p_pixel[j] + n * iw]; /* Using val as temporary storage */
// 				/* Acting on color components */
// 				for (c=0; c<COLOR_COMPONENTS; c++)
// 				{
// 					intensity[c] += (val & 0xFF) * weight;
// 					val = val >> 8;
// 				}				
// 			}
// 			/* val is already 0 */
// 			for (c= 0 ; c < COLOR_COMPONENTS; c++)
// 			{
// 				val = val << 8;
// 				col = (int)(intensity[COLOR_COMPONENTS - c - 1] / h_wsum[i]);
// 			  if (col < 0) col = 0;
// 				if (col > 255) col = 255;
// 				val |= col; 
// 			}
// 			tb[i+n*ow] = val; /* Temporary buffer ow x ih */
// 		}/* i */
// 	}/* n */


	return pResampledDataMatrix2D;

}

void CResample::SetResampleFilter(ResampleFilter rf, FilterFunction *ppFilterFn, double *pdRadius)
{

	switch(rf){
		case RESAMPLEFILTER_LANCZOS3:
			*ppFilterFn = CResample::Lanczos3;
			*pdRadius = DEFAULT_LANCZOS3_RADIUS;
			break;
		case RESAMPLEFILTER_LANCZOS8:
			*ppFilterFn = CResample::Lanczos8;
			*pdRadius = DEFAULT_LANCZOS8_RADIUS;
			break;
		case RESAMPLEFILTER_HERMITE:
			*ppFilterFn = CResample::Hermite;
			*pdRadius = DEFAULT_HERMITE_RADIUS;
			break;
		case RESAMPLEFILTER_BOX:
			*ppFilterFn = CResample::Box;
			*pdRadius = DEFAULT_BOX_RADIUS;
			break;
		case RESAMPLEFILTER_TRIANGLE:
			*ppFilterFn = CResample::Triangle;
			*pdRadius = DEFAULT_TRIANGLE_RADIUS;
			break;
		case RESAMPLEFILTER_BELL:
			*ppFilterFn = CResample::Bell;
			*pdRadius = DEFAULT_BELL_RADIUS;
			break;
		case RESAMPLEFILTER_CUBICSPLINE:
			*ppFilterFn = CResample::CubicSpline;
			*pdRadius = DEFAULT_CUBICSPLINE_RADIUS;
			break;
		case RESAMPLEFILTER_MITCHELL:
			*ppFilterFn = CResample::Mitchell;
			*pdRadius = DEFAULT_MITCHELL_RADIUS;
			break;
		case RESAMPLEFILTER_COSINE:
			*ppFilterFn = CResample::Cosine;
			*pdRadius = DEFAULT_COSINE_RADIUS;
			break;
		case RESAMPLEFILTER_CATMULLROM:
			*ppFilterFn = CResample::CatmullRom;
			*pdRadius = DEFAULT_CATMULLROM_RADIUS;
			break;
		case RESAMPLEFILTER_QUADRATIC:
			*ppFilterFn = CResample::Quadratic;
			*pdRadius = DEFAULT_QUADRATIC_RADIUS;
			break;
		case RESAMPLEFILTER_QUADRATICBSPLINE:
			*ppFilterFn = CResample::QuadraticBSpline;
			*pdRadius = DEFAULT_QUADRATICBSPLINE_RADIUS;
			break;
		case RESAMPLEFILTER_CUBICCONVOLUTION:
			*ppFilterFn = CResample::CubicConvolution;
			*pdRadius = DEFAULT_CUBICCONVOLUTION_RADIUS;
			break;
	}
	
}

double CResample::Lanczos8(double x){
	
	const double R = 8.0f;
	if (x < 0.0){
		x = - x;
	}
	
	if (x == 0.0){
		return 1;
	}
	
	if (x < R){
		x *= PI;
		return R * sin(x) * sin(x / R) / (x * x);
	}

	return 0.0f;

}

double CResample::Lanczos3(double x){

	const double R = 3.0f;
	if (x < 0.0){
		x = - x;
	}
	
	if (x == 0.0){
		return 1.0f;
	}
	
	if (x < R){
		x *= PI;
		return R * sin(x) * sin(x / R) / (x * x);
	}

	return 0.0f;

}

double CResample::Hermite(double x){

	if (x < 0.0){
		x = - x;
	}
	
	if (x < 1.0){
		return ((2.0 * x - 3) * x * x + 1.0);
	}
	
	return 0.0f;  

}

double CResample::Box(double x){

	if (x < 0.0){
		x = - x;
	}
	
	if (x <= 0.5){
		return 1.0f;
	}
	
	return 0.0f;  

}

double CResample::Triangle(double x){

	if (x < 0.0){
		x = - x;
	}
	if (x < 1.0){
		return (1.0 - x);
	}
	
	return 0.0f;   

}

double CResample::Bell(double x){

	if (x < 0.0){
		x = - x;
	}
	if (x < 0.5){
		return (0.75 - x * x);
	}
	if (x < 1.5){
		return (0.5 * pow(x - 1.5, 2.0));
	}
	
	return 0.0f;    

}

double CResample::CubicSpline(double x){

	double x2;
	
	if (x < 0.0){
		x = - x;
	}
	if (x < 1.0){
		x2 = x * x;
		return (0.5 * x2 * x - x2 + 2.0 / 3.0);
	}
	if (x < 2.0){
		x = 2.0 - x;
		return (pow(x, 3.0) / 6.0);
	}

	return 0.0f;   

}

double CResample::Mitchell(double x){

	const double C = 1.0f / 3.0f;
	double x2;
	
	if (x < 0.0){
		x = - x;
	}
	x2 = x * x;
	if (x < 1.0) {
		x = (((12.0 - 9.0 * C - 6.0 * C) * (x * x2)) + ((-18.0 + 12.0 * C + 6.0 * C) * x2) + (6.0 - 2.0 * C));
		return (x / 6.0);
	}
	if (x < 2.0){
		x = (((-C - 6.0 * C) * (x * x2)) + ((6.0 * C + 30.0 * C) * x2) + ((-12.0 * C - 48.0 * C) * x) + (8.0 * C + 24.0 * C));
		return (x / 6.0);
	}

	return 0.0f;

}

double CResample::Cosine(double x){

	if ((x >= -1.0) && (x <= 1.0)){
		return ((cos(x * PI) + 1.0) / 2.0);
	}
	
	return 0.0f; 
	
}

double CResample::CatmullRom(double x){

	const double C = 0.5f;      
	double x2;
	if (x < 0.0){
		x = - x;
	}
	x2= x * x;
	
	if (x <= 1.0){
		return (1.5 * x2 * x - 2.5 * x2 + 1);
	}
	if (x <= 2.0){
		return (- 0.5 * x2 * x + 2.5 * x2 - 4 * x + 2);
	}
	return 0.0f;
	
}

double CResample::Quadratic(double x) {

	if (x < 0.0){
		x = - x;
	}
	if (x <= 0.5){
		return (- 2.0 * x * x + 1);
	}
	if (x <= 1.5){
		return (x * x - 2.5* x + 1.5);
	}

	return 0.0f;

}

double CResample::QuadraticBSpline(double x){
	
	if (x < 0.0){
		x = - x;
	}
	if (x <= 0.5){
		return (- x * x + 0.75);
	}
	if (x <= 1.5){
		return (0.5 * x * x - 1.5 * x + 1.125);
	}

	return 0.0f;

}

double CResample::CubicConvolution(double x){

	double x2;
	if (x < 0.0){
		x = - x;
	}
	x2 = x * x;
	if (x <= 1.0){
		return ((4.0 / 3.0)* x2 * x - (7.0 / 3.0) * x2 + 1.0);
	}
	if (x <= 2.0){
		return (- (7.0 / 12.0) * x2 * x + 3 * x2 - (59.0 / 12.0) * x + 2.5);
	}
	if (x <= 3.0){
		return ( (1.0/12.0) * x2 * x - (2.0 / 3.0) * x2 + 1.75 * x - 1.5);
	}

	return 0.0f;
    
}
