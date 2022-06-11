#if !defined(AFX_DISTANCE_H__EED09986_A769_4AAA_BB2C_86CC217088A0__INCLUDED_)
#define AFX_DISTANCE_H__EED09986_A769_4AAA_BB2C_86CC217088A0__INCLUDED_

#include <cmath>
#include "Pattern.h"

class CDistance  
{
public:
	CDistance();
	virtual ~CDistance();

	void CalculatePatternsDistance (CPattern *pPattern1, int iPatternClassIndex1, CPattern *pPattern2, int iPatternClassIndex2);
	void CalculatePatternsDistance (CPattern *pPattern1, CPattern *pPattern2);
	double GetDistanceValue (void) { return m_dblDistance; }
	void SetDistanceValue (double dblDistance) { m_dblDistance = dblDistance; }
	int GetPattern1ClassIndex (void) { return m_iPatternClassIndex1; }
	void SetPattern1ClassIndex (int iPatternClassIndex1) { m_iPatternClassIndex1 = iPatternClassIndex1; }
	int GetPattern2ClassIndex (void) { return m_iPatternClassIndex2; }
	void SetPattern2ClassIndex (int iPatternClassIndex2) { m_iPatternClassIndex2 = iPatternClassIndex2; }

protected:

	double m_dblDistance;
	int m_iPatternClassIndex1;
	int m_iPatternClassIndex2;

};

class CSquaredDistance  
{
public:
	CSquaredDistance();
	virtual ~CSquaredDistance();

	void CalculatePatternsSquaredDistance (CPattern *pPattern1, int iPatternClassIndex1, CPattern *pPattern2, int iPatternClassIndex2);
	void CalculatePatternsSquaredDistance (CPattern *pPattern1, CPattern *pPattern2);
	double GetSquaredDistanceValue (void) { return m_dblSquaredDistance; }
	void SetSquaredDistanceValue (double dblSquaredDistance) { m_dblSquaredDistance = dblSquaredDistance; }
	int GetPattern1ClassIndex (void) { return m_iPatternClassIndex1; }
	void SetPattern1ClassIndex (int iPatternClassIndex1) { m_iPatternClassIndex1 = iPatternClassIndex1; }
	int GetPattern2ClassIndex (void) { return m_iPatternClassIndex2; }
	void SetPattern2ClassIndex (int iPatternClassIndex2) { m_iPatternClassIndex2 = iPatternClassIndex2; }

protected:

	double m_dblSquaredDistance;
	int m_iPatternClassIndex1;
	int m_iPatternClassIndex2;

};

#endif 
