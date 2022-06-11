#if !defined(AFX_FEATURE2DGRAYLEVELNONUNIFORMITY_H__F8E6938A_38F2_4A54_8FB2_83A39BEA3D18__INCLUDED_)
#define AFX_FEATURE2DGRAYLEVELNONUNIFORMITY_H__F8E6938A_38F2_4A54_8FB2_83A39BEA3D18__INCLUDED_

#include <cmath>
#include "DataMatrix2D.h"
#include "Feature2DSum.h"

class CFeature2DGrayLevelNonUniformity  
{
public:
	CFeature2DGrayLevelNonUniformity();
	virtual ~CFeature2DGrayLevelNonUniformity();

	void CalculateGrayLevelNonUniformity (CDataMatrix2D *pDataMatrix2D);
	double GetGrayLevelNonUniformity (void) { return m_dblGrayLevelNonUniformity; }

protected:

	double m_dblGrayLevelNonUniformity;

};

#endif 
