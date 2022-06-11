#if !defined(AFX_PATTERN_H__ECA52628_0B8E_4B77_911F_CE16D43B45A0__INCLUDED_)
#define AFX_PATTERN_H__ECA52628_0B8E_4B77_911F_CE16D43B45A0__INCLUDED_

#ifndef __GNUC__
#pragma warning(disable : 4786)
#endif

#include <vector>
#include <stdio.h>
#include "Feature.h"
#include "Combination.h"

typedef std::vector<CFeature*> vFeatures;

class CPattern  
{
public:
	CPattern();
	CPattern(int iNumberOfFeatures);
	virtual ~CPattern();

	void CreatePattern (int iNumberOfFeatures);
	void DeletePattern (void);
	void AddFeature (CFeature *pFeature);
	int GetNumberOfFeatures (void) { return m_vFeatures.size(); }
	CFeature *GetFeature (int iFeatureIndex);
	CFeature *ExtractFeature (int iFeatureIndex);
	void RemoveAllFeatures (void);
	CPattern *CopyPattern (void);
	static void CopyPattern (CPattern *pPatternDest, CPattern *pPatternSrc);
	CPattern *CopyPatternFromCombination (CCombination *pCombination);
	void WritePatternDataToFile (char *szFileName);
	void SetReservedValue (int iReservedValue) { m_iReservedValue = iReservedValue; }
	int GetReservedValue (void) { return m_iReservedValue; }

protected:

	CFeature *m_Feature;
	vFeatures m_vFeatures;
	int m_iReservedValue;

};

#endif 
