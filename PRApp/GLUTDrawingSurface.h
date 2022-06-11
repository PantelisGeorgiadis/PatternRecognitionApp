#if !defined(AFX_GLUTDRAWINGSURFACE_H__4F1E676C_EA5D_4658_8E34_8881BEF0ADED__INCLUDED_)
#define AFX_GLUTDRAWINGSURFACE_H__4F1E676C_EA5D_4658_8E34_8881BEF0ADED__INCLUDED_

#include "DrawingSurface.h"

#ifdef USE_GLUT

#define GLUT_SHAPE_SPAWN 0.01

#include <GL/gl.h>
#include <GL/glut.h>

class CGLUTDrawingSurface : public CDrawingSurface
{
public:
	CGLUTDrawingSurface();
	CGLUTDrawingSurface(int iDimension, char *szWindowTitle);
	virtual ~CGLUTDrawingSurface();

	void GLUTCreateDrawingSurface (int iDimension, char *szWindowTitle);
	void GLUTRender (void);
	

protected:

	int m_iWidth;
	int m_iHeight;

	static void GLUTReshape (int w, int h);
	static void GLUTDisplay (void);
	void GLUTDrawScene (void);
	void GLUTDrawPattern (CPattern *pPattern, ClassShape cs);
	double GLUTXNormalizeToDrawingSurface(double x);
	double GLUTYNormalizeToDrawingSurface(double y);
	int GLUTGetDrawingSurfaceWidth (void) { return m_iWidth; }
	int GLUTGetDrawingSurfaceHeight (void) { return m_iHeight; }
	void GLUTDrawTriangle (double x, double y);
	void GLUTDrawSquare (double x, double y);
	void GLUTDrawCircle (double x, double y, double r);

};

#endif 

#endif
