#if !defined(AFX_TRACETOFILE_H__0B600154_99C5_4B49_BA6E_9147018EA65E__INCLUDED_)
#define AFX_TRACETOFILE_H__0B600154_99C5_4B49_BA6E_9147018EA65E__INCLUDED_

#include <stdio.h>
#include "DataSet.h"
#include "Combination.h"

class CTraceToFile  
{
public:
	CTraceToFile();
	virtual ~CTraceToFile();

	static void AppendStringToFile (char *szFileName, char *szString);
	static void AppendExchaustiveSearchCombinationToFile (char *szFileName, CCombination* pCombination, CDataSet* pDataSet);
	static void WriteExchaustiveSearchCombinationToFile (char *szFileName, CCombination* pCombination, CDataSet* pDataSet);

};

#endif 
