#include "stdafx.h"
#include "DataTokenizer.h"

CDataTokenizer::CDataTokenizer()
{

	m_bDelimiterAsToken = m_bOneByOneDelimiter = m_bDelimitersInSequence = false;
	m_chDelimiter = 0;
	m_lpszNext = NULL;

}

CDataTokenizer::~CDataTokenizer()
{

}

char *CDataTokenizer::GetFirst(char* lpsz, const char* lpcszDelimiters){

	Break();
	m_lpszNext = lpsz;
	
	return GetNext(lpcszDelimiters); 

}

char *CDataTokenizer::GetNext(const char* lpcszDelimiters){

	if (m_lpszNext == NULL){
		return NULL;
	}

	if (m_chDelimiter != 0){
		*m_lpszNext = m_chDelimiter;
	}

	char* lpsz = m_lpszNext;
	if (m_bDelimiterAsToken){
		if (m_bDelimitersInSequence){
			int nLength = strlen(lpcszDelimiters);
			if (memcmp(lpcszDelimiters, m_lpszNext, nLength) == 0){
				m_lpszNext += nLength;
			}
			else{
				m_lpszNext = strstr(m_lpszNext, lpcszDelimiters);
			}
		}
		else{
			if (strchr(lpcszDelimiters, *m_lpszNext)){
				m_lpszNext++;
			}
			else{
				m_lpszNext += strcspn(m_lpszNext, lpcszDelimiters);
			}
		}
	}
	else{
		if (m_bDelimitersInSequence){
			int nLength = strlen(lpcszDelimiters);
			while (memcmp(lpcszDelimiters, lpsz, nLength) == 0){
				lpsz += nLength;
				if (m_bOneByOneDelimiter){
					break;
				}
			}
			m_lpszNext = strstr(lpsz, lpcszDelimiters);
		}
		else{
			if (!m_bOneByOneDelimiter){
				lpsz += strspn(lpsz, lpcszDelimiters);
			}
			else{
				if (strchr(lpcszDelimiters, *lpsz) && m_chDelimiter){
					lpsz++;
				}
			}
			m_lpszNext = lpsz + strcspn(lpsz, lpcszDelimiters);
		}
	}
	
	if ((m_lpszNext == NULL) || (*m_lpszNext == 0)){
		m_chDelimiter = 0;
		m_lpszNext = NULL;
	}
	else{
		m_chDelimiter = *m_lpszNext;
		*m_lpszNext = 0;
	}

	if (*lpsz == 0 && !m_bOneByOneDelimiter){
		return NULL;
	}
	
	return lpsz;

}

void CDataTokenizer::SetNext(const char* lpcszNext){

	if (m_chDelimiter != 0){
		*m_lpszNext = m_chDelimiter;
	}
	m_chDelimiter = 0;
	m_lpszNext = (char*)lpcszNext;

}

bool CDataTokenizer::IsEOB(void){

	return m_lpszNext == NULL;

}

bool CDataTokenizer::IsDelimiter(char ch, const char* lpcszDelimiters){

	return strchr(lpcszDelimiters, ch) != NULL;

}

void CDataTokenizer::Break(void){

	SetNext(NULL);

}

void CDataTokenizer::TrimLeft(char* &lpsz, const char* lpcszDelimiters){

	if (m_lpszNext == NULL){
		return;
	}
	if (lpcszDelimiters == NULL){
		lpcszDelimiters = " \t\r\n";
	}
	while (strchr(lpcszDelimiters, *lpsz)){
		lpsz++;
	}

}

void CDataTokenizer::TrimRight(const char* lpcszDelimiters){

	if (m_lpszNext == NULL){
		return;
	}
	if (lpcszDelimiters == NULL){
		lpcszDelimiters = " \t\r\n";
	}
	char* pNext = m_lpszNext - 1;
	while (strchr(lpcszDelimiters, *pNext)){
		*pNext = 0, pNext--;
	}
	
}


