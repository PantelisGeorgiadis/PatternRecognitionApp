#include "stdafx.h"
#include "Rectangle.h"

CRectangle::CRectangle()
{

	m_iXStart = 0;
	m_iXEnd = 0;
	m_iYStart = 0;
	m_iYEnd = 0;

}

CRectangle::CRectangle(int iXStart, int iYStart, int iXEnd, int iYEnd)
{

	CreateRectangle(iXStart, iYStart, iXEnd, iYEnd);

}

CRectangle::~CRectangle()
{

}

void CRectangle::CreateRectangle (int iXStart, int iYStart, int iXEnd, int iYEnd){

	m_iXStart = iXStart;
	m_iXEnd = iXEnd;
	m_iYStart = iYStart;
	m_iYEnd = iYEnd;

}
