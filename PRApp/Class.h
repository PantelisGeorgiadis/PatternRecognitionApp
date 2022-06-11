#if !defined(AFX_CLASS_H__264C3C6B_1B34_4A3A_A95B_70AF8F56A1E4__INCLUDED_)
#define AFX_CLASS_H__264C3C6B_1B34_4A3A_A95B_70AF8F56A1E4__INCLUDED_

#ifndef __GNUC__
#pragma warning(disable : 4786)
#endif

#include <vector>
#include <stdio.h>
#include "Pattern.h"
#include "Globals.h"

typedef std::vector<CPattern*> vPatterns;

class CClass  
{
public:
	CClass();
	CClass(int iNumberOfPatterns, int iNumberOfFeaturesPerPattern);
	virtual ~CClass();

	void CreateClass (int iNumberOfPatterns, int iNumberOfFeaturesPerPattern);
	void DeleteClass (void);
	void SetClassShape (ClassShape cs) { m_cs = cs; }
	ClassShape GetClassShape (void) { return m_cs; }
	int GetNumberOfPatterns(void) { return m_vPatterns.size(); }
	int GetNumberOfFeaturesPerPattern (void) { return GetPattern(0)->GetNumberOfFeatures(); }
	CPattern *GetPattern (int iPatternIndex);
	CClass *CopyClass (void);
	static void CopyClass (CClass *pClassDest, CClass *pClassSrc);
	void AddPattern (CPattern *pPattern, int iReservedValue);
	void InsertPatternAt (int iPatternIndex, CPattern *pPattern, int iReservedValue);
	CPattern *ExtractPattern (int iPatternIndex);
	CClass *ExtractPatterns (int *iPatternsIndex, int iPatternCount);
	CClass *ExportPatterns (int *iPatternsIndex, int iPatternCount);
	void RemoveAllPatterns (void);
	void ExtractAllFeatures (int iFeaturesIndex);
	void WriteClassDataToFile (char *szFileName);

protected:
	
	vPatterns m_vPatterns;
	CPattern *m_Pattern;
	ClassShape m_cs;

};

#endif 
