#if !defined(AFX_DATAMEANCOOCCURRENCEMATRIX2D_H__1BFC837A_06E8_45A1_9197_E0366BD531FA__INCLUDED_)
#define AFX_DATAMEANCOOCCURRENCEMATRIX2D_H__1BFC837A_06E8_45A1_9197_E0366BD531FA__INCLUDED_

#include "DataCoOccurrenceMatrix2D.h"

class CDataMeanCoOccurrenceMatrix2D  
{
public:
	CDataMeanCoOccurrenceMatrix2D();
	virtual ~CDataMeanCoOccurrenceMatrix2D();

	CDataCoOccurrenceMatrix2D *CalculateMeanCoOccurrenceMatrix(CDataCoOccurrenceMatrix2D *pDataCoOccurrenceMatrix2D0, CDataCoOccurrenceMatrix2D *pDataCoOccurrenceMatrix2D45, CDataCoOccurrenceMatrix2D *pDataCoOccurrenceMatrix2D90, CDataCoOccurrenceMatrix2D *pDataCoOccurrenceMatrix2D135);

};

#endif 
