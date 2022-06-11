#if !defined(AFX_SELFCONSISTENCY_H__A0682B6B_4BB0_498C_A0BE_B5A94658A4B9__INCLUDED_)
#define AFX_SELFCONSISTENCY_H__A0682B6B_4BB0_498C_A0BE_B5A94658A4B9__INCLUDED_

#include "DataSet.h"
#include "MinimumDistanceClassifier.h"
#include "KNearestNeighborClassifier.h"
#include "ProbabilisticNeuralNetwork.h"
#include "BayesianClassifier.h"
#include "LeastSquaresMinimumDistanceClassifier.h"
#include "SupportVectorMachineClassifier.h"
#include "SupportVectorMachineClassifierEx.h"

class CSelfConsistency  
{
public:
	CSelfConsistency();
	virtual ~CSelfConsistency();

	void SelfConsistencyMinimumDistance (CDataSet *pDataSet);
	void SelfConsistencyKNearestNeighborAverage (CDataSet *pDataSet, int k);
	void SelfConsistencyKNearestNeighborMajorityVote (CDataSet *pDataSet, int k);
	void SelfConsistencyProbabilisticNeuralNetworkGaussian (CDataSet *pDataSet, double dblSmoothingParameter);
	void SelfConsistencyProbabilisticNeuralNetworkExponential (CDataSet *pDataSet, double dblSmoothingParameter);
	void SelfConsistencyProbabilisticNeuralNetworkReciprocal (CDataSet *pDataSet, double dblSmoothingParameter);
	void SelfConsistencyBayesian (CDataSet *pDataSet);
	void SelfConsistencyBayesianQuadratic (CDataSet *pDataSet);
	void SelfConsistencyLeastSquareMinimumDistance (CDataSet *pDataSet, int iOrder, CPattern *pClusteringPoints, int iClusteringPointsSize);
	void SelfConsistencySupportVectorMachine (CDataSet *pDataSet, SVMINFO *svmi);
	void SelfConsistencySupportVectorMachineEx (CDataSet *pDataSet, SVMINFO *svmi);

};

#endif 
