#if !defined(AFX_DISTANCESORT_H__A1755707_74BA_4357_86D3_F6B365021B83__INCLUDED_)
#define AFX_DISTANCESORT_H__A1755707_74BA_4357_86D3_F6B365021B83__INCLUDED_

#include "Distance.h"

class CDistanceSort  
{
public:
	CDistanceSort();
	virtual ~CDistanceSort();

	void SortDistancesAscending (CDistance *pDistances, int iDistancesSize);
	void SortDistancesDescending (CDistance *pDistances, int iDistancesSize);
	void SortSquaredDistancesAscending (CSquaredDistance *pSquaredDistances, int iSquaredDistancesSize);
	void SortSquaredDistancesDescending (CSquaredDistance *pSquaredDistances, int iSquaredDistancesSize);

};

#endif 
