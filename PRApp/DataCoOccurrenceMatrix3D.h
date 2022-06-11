#if !defined(AFX_DATACOOCCURRENCEMATRIX3D_H__D85F39EB_BD60_405B_8768_130740317E50__INCLUDED_)
#define AFX_DATACOOCCURRENCEMATRIX3D_H__D85F39EB_BD60_405B_8768_130740317E50__INCLUDED_

#include "DataMatrix2D.h"
#include "DataMatrix3D.h"

class CDataCoOccurrenceMatrix3D  
{
public:
	CDataCoOccurrenceMatrix3D();
	virtual ~CDataCoOccurrenceMatrix3D();

	void FillDataCoOccurrenceMatrixes (CDataMatrix3D *pDataMatrix3D, int iDepth);
	CDataMatrix2D *GetDataCoOccurrenceMatrix (int iIndex);
	void CreateDataCoOccurrenceMatrixes (void);
	void DeleteDataCoOccurrenceMatrixes (void);

protected:

	CDataMatrix2D *m_pDataCoOccurrenceMatrixes;

};

#endif 
