#if !defined(AFX_LEAVEONEOUT_H__7E026FE5_2B64_48BB_998E_2EE187A7404C__INCLUDED_)
#define AFX_LEAVEONEOUT_H__7E026FE5_2B64_48BB_998E_2EE187A7404C__INCLUDED_

#include "DataSet.h"
#include "MinimumDistanceClassifier.h"
#include "KNearestNeighborClassifier.h"
#include "ProbabilisticNeuralNetwork.h"
#include "BayesianClassifier.h"
#include "LeastSquaresMinimumDistanceClassifier.h"
#include "SupportVectorMachineClassifier.h"
#include "SupportVectorMachineClassifierEx.h"

class CLeaveOneOut  
{
public:
	CLeaveOneOut();
	virtual ~CLeaveOneOut();

	void LeaveOneOutMinimumDistance (CDataSet *pDataSet);
	void LeaveOneOutKNearestNeighborAverage (CDataSet *pDataSet, int k);
	void LeaveOneOutKNearestNeighborMajorityVote (CDataSet *pDataSet, int k);
	void LeaveOneOutProbabilisticNeuralNetworkGaussian (CDataSet *pDataSet, double dblSmoothingParameter);
	void LeaveOneOutProbabilisticNeuralNetworkExponential (CDataSet *pDataSet, double dblSmoothingParameter);
	void LeaveOneOutProbabilisticNeuralNetworkReciprocal (CDataSet *pDataSet, double dblSmoothingParameter);
	void LeaveOneOutBayesian (CDataSet *pDataSet);
	void LeaveOneOutBayesianQuadratic (CDataSet *pDataSet);
	void LeaveOneOutLeastSquareMinimumDistance (CDataSet *pDataSet, int iOrder, CPattern *pClusteringPoints, int iClusteringPointsSize);
	void LeaveOneOutSupportVectorMachine (CDataSet *pDataSet, SVMINFO *svmi);
	void LeaveOneOutSupportVectorMachineEx (CDataSet *pDataSet, SVMINFO *svmi);

};

#endif 
