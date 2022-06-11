#if !defined(AFX_DATAMATRIX3D_H__94502D18_9E16_4566_B0D5_FDC9FCE80AD5__INCLUDED_)
#define AFX_DATAMATRIX3D_H__94502D18_9E16_4566_B0D5_FDC9FCE80AD5__INCLUDED_

#ifndef __GNUC__
#pragma warning(disable : 4786)
#endif

#include <vector>
#include "DataMatrix2D.h"

typedef std::vector<CDataMatrix2D*> vLayers;

class CDataMatrix3D  
{
public:
	CDataMatrix3D();
	CDataMatrix3D(int iNumberOfRows, int iNumberOfColumns, int iNumberOfLayers);
	virtual ~CDataMatrix3D();

	void CreateDataMatrix (int iNumberOfRows, int iNumberOfColumns, int iNumberOfLayers);
	void DeleteDataMatrix (void);
	void Zeros (void);
	CDataMatrix3D *CopyDataMatrix3D (void);
	int GetNumberOfRows (void) { return m_iNumberOfRows; }
	int GetNumberOfColumns (void) { return m_iNumberOfColumns; }
	int GetNumberOfLayers (void) { return m_iNumberOfLayers; }
	double GetMatrixValue (int iLayerIndex, int iRowIndex, int iColumnIndex);
	void SetMatrixValue (int iLayerIndex, int iRowIndex, int iColumnIndex, double dblValue);
	CDataMatrix2D *GetLayerAsDataMatrix2D (int iLayerIndex);

protected:

	int m_iNumberOfRows;
	int m_iNumberOfColumns;
	int m_iNumberOfLayers;

	CDataMatrix2D *m_DataMatrix2D;
	vLayers m_vLayers;

	CDataMatrix2D *GetLayer (int iLayerIndex);

};

#endif 
