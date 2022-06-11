#if !defined(AFX_RECTANGLE_H__4C353B4C_1B6E_44F6_8CF3_4139492B5C3E__INCLUDED_)
#define AFX_RECTANGLE_H__4C353B4C_1B6E_44F6_8CF3_4139492B5C3E__INCLUDED_

#include <stdlib.h>

class CRectangle  
{
public:
	CRectangle();
	CRectangle(int iXStart, int iYStart, int iXEnd, int iYEnd);
	virtual ~CRectangle();

	void CreateRectangle (int iXStart, int iYStart, int iXEnd, int iYEnd);

	int GetXStart (void) { return m_iXStart; }
	int GetXEnd (void) { return m_iXEnd; }
	int GetYStart (void) { return m_iYStart; }
	int GetYEnd (void) { return m_iYEnd; }

	int GetWidth (void) { return abs(m_iXEnd - m_iXStart); }
	int GetHeight (void) { return abs(m_iYEnd - m_iYStart); }

protected:

	int m_iXStart;
	int m_iXEnd;
	int m_iYStart;
	int m_iYEnd;

};

#endif 
