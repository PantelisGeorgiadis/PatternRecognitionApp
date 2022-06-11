#if !defined(AFX_DATAMATRIXTOFEATUREDATAMATRIX_H__37493262_EA4D_401D_BF53_179595461C7A__INCLUDED_)
#define AFX_DATAMATRIXTOFEATUREDATAMATRIX_H__37493262_EA4D_401D_BF53_179595461C7A__INCLUDED_

#include <limits>
#include <stdio.h>
#include "DataMatrix2D.h"
#include "ROIToPattern.h"

class CDataMatrixToFeatureDataMatrix  
{
public:
	CDataMatrixToFeatureDataMatrix();
	virtual ~CDataMatrixToFeatureDataMatrix();

	void DataMatrixToFeatureDataMatrices (CDataMatrix2D *pDataMatrix, int iKernelSize, int iDepth);
	void DeleteFeatureDataMatrices (void);
	void WriteFeatureDataMatricesToFile (char *szFileNamePattern, char *szExtension);
	void WriteFeatureDataMatricesToBMPFile8 (char *szFileNamePattern, char *szExtension);

protected:

	CDataMatrix2D *m_FeatureDataMatrices;

	CDataMatrix2D *NormalizeToGrayscale (CDataMatrix2D *pDataMatrix);

};

#endif 

