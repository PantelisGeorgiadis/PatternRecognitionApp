#if !defined(AFX_TRACE_H__DEFC6D78_9089_423B_B792_4E38968EE761__INCLUDED_)
#define AFX_TRACE_H__DEFC6D78_9089_423B_B792_4E38968EE761__INCLUDED_

#include "DataSet.h"
#include "DataMatrix1D.h"
#include "DataMatrix2D.h"
#include "Combination.h"

class CTrace  
{
public:
	CTrace();
	virtual ~CTrace();

	static void PrintClassToConsole (CClass *pClass, char *szDescription);
	static void PrintPatternToConsole (CPattern *pPattern, char *szDescription);
	static void PrintTruthTableToConsole (CTruthTable *pTruthTable, char *szDescription);
	static void PrintCombinationToConsole (CCombination *pCombination, char *szDescription);
	static void PrintDataMatrix2DToConsole (CDataMatrix2D *pDataMatrix2D, char *szDescription);
	static void PrintDataMatrix1DToConsole (CDataMatrix1D *pDataMatrix1D, char *szDescription);
	static void PrintExchaustiveSearchCombinationToConsole (CCombination* pCombination, CDataSet* pDataSet);

};

#endif 
