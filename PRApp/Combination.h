#if !defined(AFX_COMBINATION_H__D122AFBE_2A75_4D9F_994D_AA1EC540A0A6__INCLUDED_)
#define AFX_COMBINATION_H__D122AFBE_2A75_4D9F_994D_AA1EC540A0A6__INCLUDED_

#include "Globals.h"

class CCombination  
{
public:
	CCombination();
	CCombination(int iCombinationVectorSize);
	virtual ~CCombination();

	void CreateCombination (int iCombinationVectorSize);
	void DeleteCombination (void);
	int GetCombinationVectorSize (void) { return m_iCombinationVectorSize; }
	void SetCombinationVectorValue (int CombinationVectorIndex, int iValue);
	int GetCombinationVectorValue (int CombinationVectorIndex);
	CCombination *CopyCombination (void);

protected:

	int m_iCombinationVectorSize;
	int *m_iCombinationVector;


};

#endif 
