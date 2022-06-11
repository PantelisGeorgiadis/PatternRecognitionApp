# Microsoft Developer Studio Project File - Name="PRApp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=PRApp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PRApp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PRApp.mak" CFG="PRApp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PRApp - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "PRApp - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PRApp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x408 /d "NDEBUG"
# ADD RSC /l 0x408 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "PRApp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# SUBTRACT CPP /WX
# ADD BASE RSC /l 0x408 /d "_DEBUG"
# ADD RSC /l 0x408 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "PRApp - Win32 Release"
# Name "PRApp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\LibAnn.cpp
# End Source File
# Begin Source File

SOURCE=.\MetVSMen.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MRISeriesEnsebmle.cpp
# End Source File
# Begin Source File

SOURCE=.\PRApp.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Resample.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\LibAnn.h
# End Source File
# Begin Source File

SOURCE=.\Resample.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "PRLib"

# PROP Default_Filter ""
# Begin Group "DataSet"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Class.cpp
# End Source File
# Begin Source File

SOURCE=.\Class.h
# End Source File
# Begin Source File

SOURCE=.\DataSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DataSet.h
# End Source File
# Begin Source File

SOURCE=.\Feature.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature.h
# End Source File
# Begin Source File

SOURCE=.\Pattern.cpp
# End Source File
# Begin Source File

SOURCE=.\Pattern.h
# End Source File
# End Group
# Begin Group "Classifiers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BayesianClassifier.cpp
# End Source File
# Begin Source File

SOURCE=.\BayesianClassifier.h
# End Source File
# Begin Source File

SOURCE=.\Classifier.cpp
# End Source File
# Begin Source File

SOURCE=.\Classifier.h
# End Source File
# Begin Source File

SOURCE=.\DiscriminantFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\DiscriminantFunction.h
# End Source File
# Begin Source File

SOURCE=.\KNearestNeighborClassifier.cpp
# End Source File
# Begin Source File

SOURCE=.\KNearestNeighborClassifier.h
# End Source File
# Begin Source File

SOURCE=.\LeastSquaresMinimumDistanceClassifier.cpp
# End Source File
# Begin Source File

SOURCE=.\LeastSquaresMinimumDistanceClassifier.h
# End Source File
# Begin Source File

SOURCE=.\LibSupportVectorMachine.cpp
# End Source File
# Begin Source File

SOURCE=.\LibSupportVectorMachine.h
# End Source File
# Begin Source File

SOURCE=.\MinimumDistanceClassifier.cpp
# End Source File
# Begin Source File

SOURCE=.\MinimumDistanceClassifier.h
# End Source File
# Begin Source File

SOURCE=.\ProbabilisticNeuralNetwork.cpp
# End Source File
# Begin Source File

SOURCE=.\ProbabilisticNeuralNetwork.h
# End Source File
# Begin Source File

SOURCE=.\SupportVectorMachineClassifier.cpp
# End Source File
# Begin Source File

SOURCE=.\SupportVectorMachineClassifier.h
# End Source File
# Begin Source File

SOURCE=.\SupportVectorMachineClassifierEx.cpp
# End Source File
# Begin Source File

SOURCE=.\SupportVectorMachineClassifierEx.h
# End Source File
# End Group
# Begin Group "FeatureCalculation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DataMatrixToFeatureDataMatrix.cpp
# End Source File
# Begin Source File

SOURCE=.\DataMatrixToFeatureDataMatrix.h
# End Source File
# Begin Source File

SOURCE=.\DataMeanCoOccurrenceMatrix2D.cpp
# End Source File
# Begin Source File

SOURCE=.\DataMeanCoOccurrenceMatrix2D.h
# End Source File
# Begin Source File

SOURCE=.\DataMeanRunLenghtMatrix2D.cpp
# End Source File
# Begin Source File

SOURCE=.\DataMeanRunLenghtMatrix2D.h
# End Source File
# Begin Source File

SOURCE=.\DataRowsCollumnsOperationsMatrix2D.cpp
# End Source File
# Begin Source File

SOURCE=.\DataRowsCollumnsOperationsMatrix2D.h
# End Source File
# Begin Source File

SOURCE=.\Feature1DKurtosis.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature1DKurtosis.h
# End Source File
# Begin Source File

SOURCE=.\Feature1DMeanValue.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature1DMeanValue.h
# End Source File
# Begin Source File

SOURCE=.\Feature1DSkewness.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature1DSkewness.h
# End Source File
# Begin Source File

SOURCE=.\Feature1DStandardDeviation.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature1DStandardDeviation.h
# End Source File
# Begin Source File

SOURCE=.\Feature1DSum.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature1DSum.h
# End Source File
# Begin Source File

SOURCE=.\Feature1DVariance.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature1DVariance.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DAngularSecondMoment.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DAngularSecondMoment.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DContrast.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DContrast.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DCorrelation.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DCorrelation.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DDifferenceEntropy.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DDifferenceEntropy.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DDifferenceVariance.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DDifferenceVariance.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DEntropy.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DEntropy.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DGrayLevelNonUniformity.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DGrayLevelNonUniformity.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DInverseDifferenceMoment.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DInverseDifferenceMoment.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DKurtosis.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DKurtosis.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DLongRunEmphasis.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DLongRunEmphasis.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DMeanFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DMeanFeature.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DMeanValue.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DMeanValue.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DRangeFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DRangeFeature.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DRunLengthNonUniformity.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DRunLengthNonUniformity.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DRunPercentage.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DRunPercentage.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DShortRunEmphasis.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DShortRunEmphasis.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DSkewness.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DSkewness.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DStandardDeviation.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DStandardDeviation.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DSum.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DSum.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DSumAverage.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DSumAverage.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DSumEntropy.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DSumEntropy.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DSumOfSquares.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DSumOfSquares.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DSumVariance.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DSumVariance.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DVariance.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DVariance.h
# End Source File
# Begin Source File

SOURCE=.\Feature2DWavelets.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature2DWavelets.h
# End Source File
# Begin Source File

SOURCE=.\Feature3DKurtosis.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature3DKurtosis.h
# End Source File
# Begin Source File

SOURCE=.\Feature3DMeanFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature3DMeanFeature.h
# End Source File
# Begin Source File

SOURCE=.\Feature3DMeanValue.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature3DMeanValue.h
# End Source File
# Begin Source File

SOURCE=.\Feature3DRangeFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature3DRangeFeature.h
# End Source File
# Begin Source File

SOURCE=.\Feature3DSkewness.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature3DSkewness.h
# End Source File
# Begin Source File

SOURCE=.\Feature3DStandardDeviation.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature3DStandardDeviation.h
# End Source File
# Begin Source File

SOURCE=.\Feature3DSum.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature3DSum.h
# End Source File
# Begin Source File

SOURCE=.\Feature3DVariance.cpp
# End Source File
# Begin Source File

SOURCE=.\Feature3DVariance.h
# End Source File
# Begin Source File

SOURCE=.\ROIToPattern.cpp
# End Source File
# Begin Source File

SOURCE=.\ROIToPattern.h
# End Source File
# Begin Source File

SOURCE=.\VOIToPattern.cpp
# End Source File
# Begin Source File

SOURCE=.\VOIToPattern.h
# End Source File
# End Group
# Begin Group "DataMatrix"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DataCoOccurrenceMatrix2D.cpp
# End Source File
# Begin Source File

SOURCE=.\DataCoOccurrenceMatrix2D.h
# End Source File
# Begin Source File

SOURCE=.\DataCoOccurrenceMatrix3D.cpp
# End Source File
# Begin Source File

SOURCE=.\DataCoOccurrenceMatrix3D.h
# End Source File
# Begin Source File

SOURCE=.\DataIdentityMatrix2D.cpp
# End Source File
# Begin Source File

SOURCE=.\DataIdentityMatrix2D.h
# End Source File
# Begin Source File

SOURCE=.\DataMatrix1D.cpp
# End Source File
# Begin Source File

SOURCE=.\DataMatrix1D.h
# End Source File
# Begin Source File

SOURCE=.\DataMatrix2D.cpp
# End Source File
# Begin Source File

SOURCE=.\DataMatrix2D.h
# End Source File
# Begin Source File

SOURCE=.\DataMatrix3D.cpp
# End Source File
# Begin Source File

SOURCE=.\DataMatrix3D.h
# End Source File
# Begin Source File

SOURCE=.\DataRunLengthMatrix2D.cpp
# End Source File
# Begin Source File

SOURCE=.\DataRunLengthMatrix2D.h
# End Source File
# Begin Source File

SOURCE=.\DataRunLengthMatrix3D.cpp
# End Source File
# Begin Source File

SOURCE=.\DataRunLengthMatrix3D.h
# End Source File
# End Group
# Begin Group "FeatureReduction"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PrincipalComponentAnalysis.cpp
# End Source File
# Begin Source File

SOURCE=.\PrincipalComponentAnalysis.h
# End Source File
# End Group
# Begin Group "FeatureSelection"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Combination.cpp
# End Source File
# Begin Source File

SOURCE=.\Combination.h
# End Source File
# Begin Source File

SOURCE=.\ExhaustiveSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\ExhaustiveSearch.h
# End Source File
# End Group
# Begin Group "Evaluation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\EvaluationResult.cpp
# End Source File
# Begin Source File

SOURCE=.\EvaluationResult.h
# End Source File
# Begin Source File

SOURCE=.\EvaluationResultContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\EvaluationResultContainer.h
# End Source File
# Begin Source File

SOURCE=.\ExternalCrossValidation.cpp
# End Source File
# Begin Source File

SOURCE=.\ExternalCrossValidation.h
# End Source File
# Begin Source File

SOURCE=.\KFold.cpp
# End Source File
# Begin Source File

SOURCE=.\KFold.h
# End Source File
# Begin Source File

SOURCE=.\LeaveOneOut.cpp
# End Source File
# Begin Source File

SOURCE=.\LeaveOneOut.h
# End Source File
# Begin Source File

SOURCE=.\SelfConsistency.cpp
# End Source File
# Begin Source File

SOURCE=.\SelfConsistency.h
# End Source File
# Begin Source File

SOURCE=.\TruthTable.cpp
# End Source File
# Begin Source File

SOURCE=.\TruthTable.h
# End Source File
# End Group
# Begin Group "Clustering"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\FuzzyCMeans.cpp
# End Source File
# Begin Source File

SOURCE=.\FuzzyCMeans.h
# End Source File
# Begin Source File

SOURCE=.\KMeans.cpp
# End Source File
# Begin Source File

SOURCE=.\KMeans.h
# End Source File
# End Group
# Begin Group "Segmentation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LevelSet.cpp
# End Source File
# Begin Source File

SOURCE=.\LevelSet.h
# End Source File
# Begin Source File

SOURCE=.\MarkovRandomFieldSegmentationModel.cpp
# End Source File
# Begin Source File

SOURCE=.\MarkovRandomFieldSegmentationModel.h
# End Source File
# End Group
# Begin Group "Helpers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Bisector.cpp
# End Source File
# Begin Source File

SOURCE=.\Bisector.h
# End Source File
# Begin Source File

SOURCE=.\Centroid.cpp
# End Source File
# Begin Source File

SOURCE=.\Centroid.h
# End Source File
# Begin Source File

SOURCE=.\ClassToDataMatrix.cpp
# End Source File
# Begin Source File

SOURCE=.\ClassToDataMatrix.h
# End Source File
# Begin Source File

SOURCE=.\Covariance.cpp
# End Source File
# Begin Source File

SOURCE=.\Covariance.h
# End Source File
# Begin Source File

SOURCE=.\DataSetToDataMatrix.cpp
# End Source File
# Begin Source File

SOURCE=.\DataSetToDataMatrix.h
# End Source File
# Begin Source File

SOURCE=.\DataTokenizer.cpp
# End Source File
# Begin Source File

SOURCE=.\DataTokenizer.h
# End Source File
# Begin Source File

SOURCE=.\Determinant.cpp
# End Source File
# Begin Source File

SOURCE=.\Determinant.h
# End Source File
# Begin Source File

SOURCE=.\DiscreteLaplacian.cpp
# End Source File
# Begin Source File

SOURCE=.\DiscreteLaplacian.h
# End Source File
# Begin Source File

SOURCE=.\Distance.cpp
# End Source File
# Begin Source File

SOURCE=.\Distance.h
# End Source File
# Begin Source File

SOURCE=.\DistanceSort.cpp
# End Source File
# Begin Source File

SOURCE=.\DistanceSort.h
# End Source File
# Begin Source File

SOURCE=.\EvaluationResultSort.cpp
# End Source File
# Begin Source File

SOURCE=.\EvaluationResultSort.h
# End Source File
# Begin Source File

SOURCE=.\ExcelWriter.cpp
# End Source File
# Begin Source File

SOURCE=.\ExcelWriter.h
# End Source File
# Begin Source File

SOURCE=.\FastMath.cpp
# End Source File
# Begin Source File

SOURCE=.\FastMath.h
# End Source File
# Begin Source File

SOURCE=.\FileReader.cpp
# End Source File
# Begin Source File

SOURCE=.\FileReader.h
# End Source File
# Begin Source File

SOURCE=.\Gradient.cpp
# End Source File
# Begin Source File

SOURCE=.\Gradient.h
# End Source File
# Begin Source File

SOURCE=.\MeanValue.cpp
# End Source File
# Begin Source File

SOURCE=.\MeanValue.h
# End Source File
# Begin Source File

SOURCE=.\MersenneTwister.cpp
# End Source File
# Begin Source File

SOURCE=.\MersenneTwister.h
# End Source File
# Begin Source File

SOURCE=.\PerformanceTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\PerformanceTimer.h
# End Source File
# Begin Source File

SOURCE=.\Rectangle.cpp
# End Source File
# Begin Source File

SOURCE=.\Rectangle.h
# End Source File
# Begin Source File

SOURCE=.\ShuffleDataSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ShuffleDataSet.h
# End Source File
# Begin Source File

SOURCE=.\StandardDeviation.cpp
# End Source File
# Begin Source File

SOURCE=.\StandardDeviation.h
# End Source File
# Begin Source File

SOURCE=.\TimeEstimate.cpp
# End Source File
# Begin Source File

SOURCE=.\TimeEstimate.h
# End Source File
# Begin Source File

SOURCE=.\Trace.cpp
# End Source File
# Begin Source File

SOURCE=.\Trace.h
# End Source File
# Begin Source File

SOURCE=.\TraceToFile.cpp
# End Source File
# Begin Source File

SOURCE=.\TraceToFile.h
# End Source File
# Begin Source File

SOURCE=.\XmlReader.cpp
# End Source File
# Begin Source File

SOURCE=.\XmlReader.h
# End Source File
# Begin Source File

SOURCE=.\XmlWriter.cpp
# End Source File
# Begin Source File

SOURCE=.\XmlWriter.h
# End Source File
# End Group
# Begin Group "Matlab"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ClassToMxArray.cpp
# End Source File
# Begin Source File

SOURCE=.\ClassToMxArray.h
# End Source File
# Begin Source File

SOURCE=.\DataMatrixToMxArray.cpp
# End Source File
# Begin Source File

SOURCE=.\DataMatrixToMxArray.h
# End Source File
# Begin Source File

SOURCE=.\MatlabEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\MatlabEngine.h
# End Source File
# End Group
# Begin Group "Drawing"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DrawingSurface.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawingSurface.h
# End Source File
# Begin Source File

SOURCE=.\GLUTDrawingSurface.cpp
# End Source File
# Begin Source File

SOURCE=.\GLUTDrawingSurface.h
# End Source File
# Begin Source File

SOURCE=.\SupportVectorMachineClassifierDrawingSurface.cpp
# End Source File
# Begin Source File

SOURCE=.\SupportVectorMachineClassifierDrawingSurface.h
# End Source File
# End Group
# Begin Group "Ensemble"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Bagging.cpp
# End Source File
# Begin Source File

SOURCE=.\Bagging.h
# End Source File
# Begin Source File

SOURCE=.\Ensemble.cpp
# End Source File
# Begin Source File

SOURCE=.\Ensemble.h
# End Source File
# End Group
# Begin Group "Mapping"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LeastSquaresMapping.cpp
# End Source File
# Begin Source File

SOURCE=.\LeastSquaresMapping.h
# End Source File
# Begin Source File

SOURCE=.\LinearDiscrminantMapping.cpp
# End Source File
# Begin Source File

SOURCE=.\LinearDiscrminantMapping.h
# End Source File
# End Group
# Begin Group "NeuralNetwork"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Layer.cpp
# End Source File
# Begin Source File

SOURCE=.\Layer.h
# End Source File
# Begin Source File

SOURCE=.\Neuron.cpp
# End Source File
# Begin Source File

SOURCE=.\Neuron.h
# End Source File
# Begin Source File

SOURCE=.\Perceptron.cpp
# End Source File
# Begin Source File

SOURCE=.\Perceptron.h
# End Source File
# Begin Source File

SOURCE=.\Synapse.cpp
# End Source File
# Begin Source File

SOURCE=.\Synapse.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Globals.h
# End Source File
# Begin Source File

SOURCE=.\PRLib.h
# End Source File
# End Group
# End Target
# End Project
