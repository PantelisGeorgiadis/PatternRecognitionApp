#ifndef PRLIB_H
#define PRLIB_H

#include "Globals.h"

// DataSet
#include "DataSet.h"

// DataMatrix
#include "DataMatrix1D.h"
#include "DataMatrix2D.h"
#include "DataMatrix3D.h"

// Classifiers
#include "MinimumDistanceClassifier.h"
#include "KNearestNeighborClassifier.h"
#include "ProbabilisticNeuralNetwork.h"
#include "BayesianClassifier.h"
#include "LeastSquaresMinimumDistanceClassifier.h"
#include "SupportVectorMachineClassifier.h"
#include "SupportVectorMachineClassifierEx.h"

// Feature Calculation
#include "ROIToPattern.h"
#include "VOIToPattern.h"

// Feature Reduction
#include "PrincipalComponentAnalysis.h"

// Feature Selection
#include "ExhaustiveSearch.h"

// Evaluation
#include "EvaluationResultContainer.h"
#include "SelfConsistency.h"
#include "LeaveOneOut.h"
#include "KFold.h"
#include "ExternalCrossValidation.h"

// Clustering
#include "KMeans.h"
#include "FuzzyCMeans.h"

// Segmentation
#include "MarkovRandomFieldSegmentationModel.h"
#include "LevelSet.h"

// Matlab 
#ifdef USE_MATLAB_ENGINE
#include "MatlabEngine.h"
#include "ClassToMxArray.h"
#include "DataMatrixToMxArray.h"
#endif

// Ensemble
#include "Ensemble.h"
#include "Bagging.h"

// Mapping
#include "LeastSquaresMapping.h"

// Tracing
#include "Trace.h"
#include "TraceToFile.h"

// Type Conversion
#include "ClassToDataMatrix.h"

// Timing
#include "TimeEstimate.h"

// Performance Timing
#ifdef USE_PERFORMANCETIMER
#include "PerformanceTimer.h"
#endif

// Shuffle
#include "ShuffleDataSet.h"

#endif
