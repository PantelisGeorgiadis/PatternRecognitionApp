#if !defined(AFX_FEATURE3DSUM_H__A72BA57C_5E4B_422E_B2E1_FA2E55B4CD28__INCLUDED_)
#define AFX_FEATURE3DSUM_H__A72BA57C_5E4B_422E_B2E1_FA2E55B4CD28__INCLUDED_

#include "DataMatrix3D.h"

class CFeature3DSum  
{
public:
	CFeature3DSum();
	virtual ~CFeature3DSum();

	void CalculateSum (CDataMatrix3D *pDataMatrix3D);
	double GetSum (void) { return m_dblSum; }

protected:

	double m_dblSum;

};

#endif 
