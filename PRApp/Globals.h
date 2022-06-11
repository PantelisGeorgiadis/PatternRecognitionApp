#ifndef GLOBALS_H
#define GLOBALS_H

#ifdef __GNUC__
#define _int64 long long
#define UNIT64 1LL
#else
#define UNIT64 1I64
#endif

#ifndef NULL
#define NULL (0)
#endif

// #ifndef BOOL
// #define BOOL bool
// #endif
// 
// #ifndef TRUE
// #define TRUE true
// #endif
// 
// #ifndef FALSE
// #define FALSE false
// #endif

// #ifndef ULONG
// #define ULONG unsigned long
// #endif

#ifndef max
#define max(a, b)	(((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a, b)	(((a) < (b)) ? (a) : (b))
#endif

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

#ifndef SAFEDELETE
#define SAFEDELETE (p) { if(p) { delete (p); (p) = NULL; } }
#endif
#ifndef SAFEDELETEARRAY
#define SAFEDELETEARRAY(p) { if(p) { delete [] (p); (p) = NULL; } }
#endif

//#define USE_MATLAB_ENGINE
//#define USE_GLUT
//#define USE_XML_SUPPORT
//#define MSC_IDE
#define USE_PERFORMANCETIMER
//#define USE_OPENMP


#ifdef USE_OPENMP
#include <omp.h>
// void InitializeOpenMP (void){
// 	int iCPUCount = omp_get_num_procs();
// 	omp_set_num_threads(iCPUCount);
// }
#endif

enum ClassificationScheme{
	
	CLASSIFIER_NONE = 0,	
	CLASSIFIER_MINIMUMDISTANCE, 
	CLASSIFIER_KNN_AVERAGE,					
	CLASSIFIER_KNN_MV,							
	CLASSIFIER_PNN_GAUSSIAN,					
	CLASSIFIER_PNN_EXPONENTIAL,			
	CLASSIFIER_PNN_RECIPROCAL,				
	CLASSIFIER_BAYESIAN,							
	CLASSIFIER_BAYESIAN_QUADRATIC,	
	CLASSIFIER_LEASTSQUARES_MINIMUMDISTANCE,
	CLASSIFIER_SUPPORTVECTORMACHINE,
	CLASSIFIER_SUPPORTVECTORMACHINEEX
	
};

enum EvaluationMethod{
	
	EVALUATIONMETHOD_SELFCONSISTENCY = 0,
	EVALUATIONMETHOD_LEAVEONEOUT,
	EVALUATIONMETHOD_KFOLD
	
};

enum SupportVectorMachineKernelType {SVMKERNELTYPE_LINEAR, SVMKERNELTYPE_POLYNOMIAL, SVMKERNELTYPE_RBF, SVMKERNELTYPE_SIGMOID};

typedef struct _tagSVMINFO 
{
	
	SupportVectorMachineKernelType svmkt;
	int iPolynomialDegree;					// For Polynomial Kernel
	double dblGaussianSigma;				// For RBF (Gaussian) Kernel
	double dblSigmoidC;						// For Sigmoid Kernel
	double dblSigmoidV;						// For Sigmoid Kernel
	double dblGammaEx;						// For Polynomial/RBF (Gaussian)/Sigmoid Kernel
	double dblCoef0Ex;						// for Polynomial/Sigmoid
	double dblTolerance;					// Convergence Tolerance
	double dblC;							// Box constraint (for possibly overlapping data).
	double dblCostEx;						// Cost

} SVMINFO;

typedef struct _tagEVALUATIONINFO 
{

	EvaluationMethod em;
	int iNumberOfNeighbors;					// For KNN
	double dblSmoothingFactor;				// For PNN
	int iNumberOfFolds;						// For K-Fold
	int iOrder;								// For LSMD
	void *pClusteringPoints;				// For LSMD !!! Needs casting to CPattern*
	int iNumberOfClusteringPoints;			// For LSMD
	SVMINFO svminfo;						// For SVM				

}EVALUATIONINFO;

enum FeatureSelectionMethod{
	
	FEATURESELECTION_EXCHAUSTIVESEARCH = 0	

};

typedef struct _tagSELECTIONINFO 
{

	FeatureSelectionMethod fsm;
	int iNFromFeatureCombinations;			// For Exhaustive Search (Feature Combinations: iNFromFeatureCombinations --> iNToFeatureCombinations)
	int iNToFeatureCombinations;			// For Exhaustive Search (Feature Combinations: iNFromFeatureCombinations --> iNToFeatureCombinations)

}SELECTIONINFO;

enum MatrixRotationDegrees {DEGREES_0, DEGREES_45, DEGREES_90, DEGREES_135};

enum ClassShape{
	
	CLASSSHAPE_TRIANGLE = 0,
	CLASSSHAPE_CIRCLE,
	CLASSSHAPE_SQUARE,
	CLASSSHAPE_ASTERISK,
	CLASSSHAPE_CROSS
		
};

enum Feature{

	FEATURE_MEANVALUE = 0,
	FEATURE_STANDARDDEVIATION,
	FEATURE_SKEWNESS,
	FEATURE_KURTOSIS,
	FEATURE_ANGULARSECONDMOMENT_MEAN,
	FEATURE_CONTRAST_MEAN,
	FEATURE_CORRELATION_MEAN,
	FEATURE_SUMOFSQUARES_MEAN,
	FEATURE_INVERSEDIFFERENCEMOMENT_MEAN,
	FEATURE_SUMAVERAGE_MEAN,
	FEATURE_SUMVARIANCE_MEAN,
	FEATURE_SUMENTROPY_MEAN,
	FEATURE_ENTROPY_MEAN,
	FEATURE_DIFFERENCEVARIANCE_MEAN,
	FEATURE_DIFFERENCEENTROPY_MEAN,
	FEATURE_ANGULARSECONDMOMENT_RANGE,
	FEATURE_CONTRAST_RANGE,
	FEATURE_CORRELATION_RANGE,
	FEATURE_SUMOFSQUARES_RANGE,
	FEATURE_INVERSEDIFFERENCEMOMENT_RANGE,
	FEATURE_SUMAVERAGE_RANGE,
	FEATURE_SUMVARIANCE_RANGE,
	FEATURE_SUMENTROPY_RANGE,
	FEATURE_ENTROPY_RANGE,
	FEATURE_DIFFERENCEVARIANCE_RANGE,
	FEATURE_DIFFERENCEENTROPY_RANGE,
	FEATURE_SHORTRUNEMPHASIS_MEAN, 
	FEATURE_LONGRUNEMPHASIS_MEAN, 
	FEATURE_GRAYLEVELNONUNIFORMITY_MEAN,
	FEATURE_RUNLENGTHNONUNIFORMITY_MEAN,
	FEATURE_RUNPERCENTAGE_MEAN,
	FEATURE_SHORTRUNEMPHASIS_RANGE, 
	FEATURE_LONGRUNEMPHASIS_RANGE, 
	FEATURE_GRAYLEVELNONUNIFORMITY_RANGE,
	FEATURE_RUNLENGTHNONUNIFORMITY_RANGE,
	FEATURE_RUNPERCENTAGE_RANGE

};

enum ResampleFilter{

	RESAMPLEFILTER_BELL = 0,
	RESAMPLEFILTER_BOX,
	RESAMPLEFILTER_CATMULLROM,
	RESAMPLEFILTER_COSINE,
	RESAMPLEFILTER_CUBICCONVOLUTION,
	RESAMPLEFILTER_CUBICSPLINE,
	RESAMPLEFILTER_HERMITE,
	RESAMPLEFILTER_LANCZOS3,
	RESAMPLEFILTER_LANCZOS8,
	RESAMPLEFILTER_MITCHELL,
	RESAMPLEFILTER_QUADRATIC,
	RESAMPLEFILTER_QUADRATICBSPLINE,
	RESAMPLEFILTER_TRIANGLE

};

#endif
