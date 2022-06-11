#if !defined(AFX_CLASSTOMXARRAY_H__FBC99940_0035_4ABB_9423_673970B0AE07__INCLUDED_)
#define AFX_CLASSTOMXARRAY_H__FBC99940_0035_4ABB_9423_673970B0AE07__INCLUDED_

#include "MatlabEngine.h"
#include "Class.h"

#ifdef USE_MATLAB_ENGINE

class CClassToMxArray  
{
public:
	CClassToMxArray();
	virtual ~CClassToMxArray();

	mxArray *ClassToMxArray(CClass *pClass);
	CClass *MxArrayToClass(mxArray *Array);

};

#endif

#endif 
