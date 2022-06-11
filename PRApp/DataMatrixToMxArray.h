#if !defined(AFX_DATAMATRIXTOMXARRAY_H__54DA4AA3_0276_4DFA_96A3_5C7B6541471F__INCLUDED_)
#define AFX_DATAMATRIXTOMXARRAY_H__54DA4AA3_0276_4DFA_96A3_5C7B6541471F__INCLUDED_

#include "MatlabEngine.h"
#include "DataMatrix2D.h"
#include "DataMatrix1D.h"

#ifdef USE_MATLAB_ENGINE

class CDataMatrixToMxArray  
{
public:
	CDataMatrixToMxArray();
	virtual ~CDataMatrixToMxArray();

	mxArray *DataMatrix2DToMxArray(CDataMatrix2D *pDataMatrix);
	CDataMatrix2D *MxArrayToDataMatrix2D(mxArray *Array);
	mxArray *DataMatrix1DToMxArray(CDataMatrix1D *pDataMatrix);
	CDataMatrix1D *MxArrayToDataMatrix1D(mxArray *Array);

};

#endif

#endif 
