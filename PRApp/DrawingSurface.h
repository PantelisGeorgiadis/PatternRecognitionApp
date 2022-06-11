#if !defined(AFX_DRAWINGSURFACE_H__4B1C4046_12FE_426D_A708_E8EA95150AD0__INCLUDED_)
#define AFX_DRAWINGSURFACE_H__4B1C4046_12FE_426D_A708_E8EA95150AD0__INCLUDED_

#include <cmath>
#include "DataMatrix2D.h"
#include "DataSet.h"

#define SHAPE_SPAWN	2
#define EXTENSION_RATE	0.1

class CDrawingSurface  
{
public:
	CDrawingSurface();
	CDrawingSurface(int iDimension);
	virtual ~CDrawingSurface();

	void CreateDrawingSurface (int iDimension);
	void ClearDrawingSurface (void);
	void DeleteDrawingSurface (void);
	int GetDrawingSurfaceWidth (void) { return m_iWidth; }
	int GetDrawingSurfaceHeight (void) { return m_iHeight; }
	CDataMatrix2D *GetDrawingBuffer (void) { return m_DrawingBuffer; }
	CDataSet *GetDrawingDataSet (void) { return m_DrawingDataSet; }
	void SaveDrawingSurfaceToBmpFile8 (char *szFileName);
	void SetPixel (int x, int y, unsigned char ucTone);
	unsigned char GetPixel (int x, int y);
	void FillDrawingSurface (unsigned char ucTone);
	void DrawFrame (unsigned char ucTone);
	void DrawLine (int X0, int Y0, int X1, int Y1, unsigned char ucTone);
	void DrawCircle (int x, int y, int r, unsigned char ucTone);
	void DrawSquare (int x, int y, unsigned char ucTone);
	void DrawTriangle (int x, int y, unsigned char ucTone);
	void DrawAsterisk (int x, int y, unsigned char ucTone);
	void DrawCross (int x, int y, unsigned char ucTone);
	void AddClass (CClass *pClass);
	void SetXYFeatureIndex (int iXFeatureIndex, int iYFeatureIndex);
	int GetXFeatureIndex (void) { return m_iXFeatureIndex; }
	int GetYFeatureIndex (void) { return m_iYFeatureIndex; }
	CDataSet *NormalizeDataSetToDrawingSurface (void);
	void Render (void);
	int XNormalizeToDrawingSurface(double x);
	int YNormalizeToDrawingSurface(double y);
	double GetXMin (void) { return m_nMinX; }
	double GetXMax (void) { return m_nMaxX; }
	double GetYMin (void) { return m_nMinY; }
	double GetYMax (void) { return m_nMaxY; }


protected:

	int m_iWidth;
	int m_iHeight;
	int m_iXFeatureIndex;
	int m_iYFeatureIndex;
	CDataMatrix2D *m_DrawingBuffer;
	CDataSet *m_DrawingDataSet;
	double m_nMinY, m_nMaxY;
	double m_nMinX, m_nMaxX;

	void DrawAntiAliasedLine (int X0, int Y0, int X1, int Y1, unsigned char ucTone);
	void GetMinMaxX(double dblExtensionRate);
	void GetMinMaxY(double dblExtensionRate);
	void DrawPattern (CPattern *pPattern, ClassShape cs);

};

#endif 
