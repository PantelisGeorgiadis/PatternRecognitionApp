#if !defined(AFX_KFOLD_H__AB7B5630_8BBC_411C_89F7_27D876B5704C__INCLUDED_)
#define AFX_KFOLD_H__AB7B5630_8BBC_411C_89F7_27D876B5704C__INCLUDED_

#include "DataSet.h"
#include "SelfConsistency.h"
#include "MinimumDistanceClassifier.h"
#include "KNearestNeighborClassifier.h"
#include "ProbabilisticNeuralNetwork.h"
#include "BayesianClassifier.h"
#include "LeastSquaresMinimumDistanceClassifier.h"
#include "SupportVectorMachineClassifier.h"
#include "SupportVectorMachineClassifierEx.h"

class CKFold  
{
public:
	CKFold();
	CKFold(int k);
	virtual ~CKFold();

	void SetNumberOfFolds (int k) { m_iNumberOfFolds = k; }
	int GetNumberOfFolds (void) { return m_iNumberOfFolds; }

	void KFoldMinimumDistance (CDataSet *pDataSet);
	void KFoldKNearestNeighborAverage (CDataSet *pDataSet, int kn);
	void KFoldKNearestNeighborMajorityVote (CDataSet *pDataSet, int kn);
	void KFoldProbabilisticNeuralNetworkGaussian (CDataSet *pDataSet, double dblSmoothingParameter);
	void KFoldProbabilisticNeuralNetworkExponential (CDataSet *pDataSet, double dblSmoothingParameter);
	void KFoldProbabilisticNeuralNetworkReciprocal (CDataSet *pDataSet, double dblSmoothingParameter);
	void KFoldBayesian (CDataSet *pDataSet);
	void KFoldBayesianQuadratic (CDataSet *pDataSet);
	void KFoldLeastSquareMinimumDistance (CDataSet *pDataSet, int iOrder, CPattern *pClusteringPoints, int iClusteringPointsSize);
	void KFoldSupportVectorMachine (CDataSet *pDataSet, SVMINFO *svmi);
	void KFoldSupportVectorMachineEx (CDataSet *pDataSet, SVMINFO *svmi);

protected:

	int m_iNumberOfFolds;

};

#endif 
