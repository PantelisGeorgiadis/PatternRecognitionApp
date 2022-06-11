#if !defined(AFX_LINEARDISCRMINANTMAPPING_H__5C6DEDE9_8FA1_49EA_BE19_745EFB275371__INCLUDED_)
#define AFX_LINEARDISCRMINANTMAPPING_H__5C6DEDE9_8FA1_49EA_BE19_745EFB275371__INCLUDED_

#include "DataSet.h"
#include "DataMatrix2D.h"
#include "Covariance.h"
#include "DataSetToDataMatrix.h"
#include "MeanValue.h"

class CLinearDiscrminantMapping  
{
public:
	CLinearDiscrminantMapping();
	virtual ~CLinearDiscrminantMapping();

	CDataSet *LinearDiscrminantMapping (CDataSet *pDataSet);

protected:

	CDataMatrix2D *CrossProduct (CDataMatrix2D *DataMatrix2D1, CDataMatrix2D *DataMatrix2D2);

};

#endif 
