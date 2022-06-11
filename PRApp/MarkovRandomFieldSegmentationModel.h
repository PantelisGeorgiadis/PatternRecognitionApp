#if !defined(AFX_MARKOVRANDOMFIELDSEGMENTATIONMODEL_H__62DFD31C_8D08_4A43_9D9E_54845974C51E__INCLUDED_)
#define AFX_MARKOVRANDOMFIELDSEGMENTATIONMODEL_H__62DFD31C_8D08_4A43_9D9E_54845974C51E__INCLUDED_

#include <cmath>
#include <time.h>
#include "DataMatrix2D.h"
#include "Rectangle.h"
#include "Feature2DMeanValue.h"
#include "Feature2DVariance.h"
#include "MersenneTwister.h"

enum MarkovRandomFieldOptimizationAlgorithm 
{ 
	
	MRFOA_METROPOLIS = 0,// Simulated Annealing using Metropolis dynamics
	MRFOA_GIBBS,		 // Simulated Annealing using a Gibbs sampler
	MRFOA_ICM,			 // Iterated Conditional Modes, a deterministic suboptimal method (depends on a good initialization)
	MRFOA_MMD			 // Modified Metropolis Dynamics, a pseudo-stochastic suboptimal method which is less sensitive to initialization than ICM.

};

typedef void (*MarkovRandomFieldSegmentationModelCallBack)(MarkovRandomFieldOptimizationAlgorithm, int, double, double, CDataMatrix2D*);

class CMarkovRandomFieldSegmentationModel  
{
public:
	CMarkovRandomFieldSegmentationModel();
	CMarkovRandomFieldSegmentationModel(MarkovRandomFieldSegmentationModelCallBack pMarkovRandomFieldSegmentationModelCallBack);
	virtual ~CMarkovRandomFieldSegmentationModel();


	void Segment (CDataMatrix2D *pDataMatrix2D, CRectangle *ClassRegions, int iNumberOfClasses, double alpha, double beta, double t, double T0, double c, MarkovRandomFieldOptimizationAlgorithm mrfoa);
	void DeleteSegmentedDataMatrix (void);
	int GetNumberOfClasses (void) { return m_iNumberOfClasses; }
	double GetAlpha (void) { return m_alpha; }
	double GetBeta (void) { return m_beta; }
	int GetNumberOfIterations (void) { return m_iNumberOfIterations; }
	double GetEnergy (void) { return m_dblEnergy; }
	CDataMatrix2D *GetSegmentedDataMatrix (void) { return m_SegmentedDataMatrix2D; }
	void SetMarkovRandomFieldSegmentationModelCallBackFunction (MarkovRandomFieldSegmentationModelCallBack pMarkovRandomFieldSegmentationModelCallBack) { m_pMarkovRandomFieldSegmentationModelCallBack = pMarkovRandomFieldSegmentationModelCallBack; }

protected:

	CDataMatrix2D *m_SegmentedDataMatrix2D;
	CDataMatrix2D *RegionDataMatrix2D;
	int m_iNumberOfClasses;
	int m_iNumberOfIterations;

	MarkovRandomFieldSegmentationModelCallBack m_pMarkovRandomFieldSegmentationModelCallBack;
	
	double m_alpha;			// Alpha value for Modified Metropolis Dynamics
	double m_beta;			// Strength of second order clique potential
	double m_t;				// Stop criterion threshold: stop if (dblSummDeltaE < m_t)
	double m_T;				// Current temperature
	double m_T0;			// Initial temperature (not used by ICM)
	double m_c;				// Temperature scheduler's factor: T(n+1)=c*T(n).
	double m_dblEnergy;		// Current global energy
	double m_dblEnergyOld;	// Global energy in the previous iteration

	// Computes singleton potential at site (i,j) having a label "iLabel"
	double Singleton(CDataMatrix2D *pDataMatrix2D, CFeature2DMeanValue *Feature2DMeanValue, CFeature2DVariance *Feature2DVariance, int i, int j, int iLabel);
	// Computes doubleton potential at site (i,j) having a label "iLabel"
	double Doubleton(CDataMatrix2D *ClassesDataMatrix, int i, int j, int iLabel);
	// Computes global energy based on the current labeling in data
	double CalculateEnergy(CDataMatrix2D *pDataMatrix2D, CDataMatrix2D *ClassesDataMatrix, CFeature2DMeanValue *Feature2DMeanValue, CFeature2DVariance *Feature2DVariance);
	// Computes the local energy at site (i,j) assuming "label" has been assigned to it
	double LocalEnergy(CDataMatrix2D *pDataMatrix2D, CDataMatrix2D *ClassesDataMatrix, CFeature2DMeanValue *Feature2DMeanValue, CFeature2DVariance *Feature2DVariance, int i, int j, int iLabel);
	void CreateSegmentedDataMatrix (CDataMatrix2D *ClassesDataMatrix);

	void Metropolis(CDataMatrix2D *pDataMatrix2D, CDataMatrix2D *ClassesDataMatrix, CFeature2DMeanValue *Feature2DMeanValue, CFeature2DVariance *Feature2DVariance, bool bModifiedMetropolisDynamics);
	void IteratedConditionalModes(CDataMatrix2D *pDataMatrix2D, CDataMatrix2D *ClassesDataMatrix, CFeature2DMeanValue *Feature2DMeanValue, CFeature2DVariance *Feature2DVariance);
	void Gibbs(CDataMatrix2D *pDataMatrix2D, CDataMatrix2D *ClassesDataMatrix, CFeature2DMeanValue *Feature2DMeanValue, CFeature2DVariance *Feature2DVariance);

};

#endif 
