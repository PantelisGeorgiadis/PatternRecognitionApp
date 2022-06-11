#if !defined(AFX_GRADIENT_H__DFF192D7_5CE0_4EBA_A025_F980A825BE9F__INCLUDED_)
#define AFX_GRADIENT_H__DFF192D7_5CE0_4EBA_A025_F980A825BE9F__INCLUDED_

#include "DataMatrix2D.h"

class CGradient  
{
public:
	CGradient();
	virtual ~CGradient();

	void CalculateMatrixGradient (CDataMatrix2D *pDataMatrix2D);
	void DeleteGradientDataMatrixes (void);

	CDataMatrix2D *GetGradientDataMatrix2DX (void) { return m_GradientDataMatrix2DX; }
	CDataMatrix2D *GetGradientDataMatrix2DY (void) { return m_GradientDataMatrix2DY; }
	
protected:

	CDataMatrix2D *m_GradientDataMatrix2DX;
	CDataMatrix2D *m_GradientDataMatrix2DY;

};

#endif 
