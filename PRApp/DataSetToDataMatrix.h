#if !defined(AFX_DATASETTODATAMATRIX_H__9371A73B_6E79_4735_81E3_7419E2C11D75__INCLUDED_)
#define AFX_DATASETTODATAMATRIX_H__9371A73B_6E79_4735_81E3_7419E2C11D75__INCLUDED_

#include "DataMatrix2D.h"
#include "DataSet.h"
#include "ClassToDataMatrix.h"

class CDataSetToDataMatrix  
{
public:
	CDataSetToDataMatrix();
	virtual ~CDataSetToDataMatrix();

	CDataMatrix2D *DataSetToDataMatrix (CDataSet *pDataSet);
	CDataSet *DataMatrixesToDataSet (CDataMatrix2D *pDataMatrix2D, int iNumberOfDataMatrixes);

};

#endif 
