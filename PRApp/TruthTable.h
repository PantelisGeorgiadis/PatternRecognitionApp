#if !defined(AFX_TRUTHTABLE_H__542CC9C9_6440_4DA5_832E_4CFD0E8E6896__INCLUDED_)
#define AFX_TRUTHTABLE_H__542CC9C9_6440_4DA5_832E_4CFD0E8E6896__INCLUDED_

#include <stdio.h>

class CTruthTable  
{
public:
	CTruthTable();
	CTruthTable(int iNumberOfClasses);
	virtual ~CTruthTable();

	void CreateTruthTable (int iNumberOfClasses);
	void ResetTruthTable (void);
	void DeleteTruthTable (void);
	int GetTruthTableValue (int iClassBelongingIndex, int iClassClassifiedIndex);
	void SetTruthTableValue (int iClassBelongingIndex, int iClassClassifiedIndex, int iValue);
	CTruthTable *CopyTruthTable (void);
	static void CopyTruthTable (CTruthTable *pTruthTableDest, CTruthTable *pTruthTableSrc);
	int GetNumberOfClasses (void) { return m_iNumberOfClasses; }
	double GetOverallAccuracyPercent (void);
	void WriteTruthTableToFile (char *szFileName);

protected:

	int m_iNumberOfClasses;
	int *m_iTruthTable;

};

#endif 
