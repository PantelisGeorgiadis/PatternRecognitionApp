#if !defined(AFX_DATATOKENIZER_H__565041E5_B3AD_4132_8A3C_BF67BCA782B6__INCLUDED_)
#define AFX_DATATOKENIZER_H__565041E5_B3AD_4132_8A3C_BF67BCA782B6__INCLUDED_

#include <string.h>

#define DELIMITERS " ,;"

class CDataTokenizer  
{
public:
	CDataTokenizer();
	virtual ~CDataTokenizer();

	bool m_bDelimiterAsToken;
	bool m_bOneByOneDelimiter;
	bool m_bDelimitersInSequence;
	char *m_lpszNext;
	char m_chDelimiter;

	char *GetFirst(char* lpsz, const char* lpcszDelimiters);
	char *GetNext(const char* lpcszDelimiters);
	void SetNext(const char* lpcszNext);
	bool IsEOB(void);
	void Break(void);
	void TrimLeft(char* &lpsz, const char* lpcszDelimiters = NULL);
	void TrimRight(const char* lpcszDelimiters = NULL);

	static bool IsDelimiter(char ch, const char* lpcszDelimiters);

};

#endif 
