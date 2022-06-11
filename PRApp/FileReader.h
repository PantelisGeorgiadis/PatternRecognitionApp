#if !defined(AFX_FILEREADER_H__50BFDFE8_EB43_4AAB_8B38_06D654CC1A87__INCLUDED_)
#define AFX_FILEREADER_H__50BFDFE8_EB43_4AAB_8B38_06D654CC1A87__INCLUDED_

#include <stdio.h>
#include <memory.h>

class CFileReader  
{
public:
	CFileReader();
	virtual ~CFileReader();

	bool ParseFile (char *szFilename);
	bool ReadFile (char *szFilename);
	
	bool Clear (void);

	unsigned long GetFileSize (void) { return m_ulLength; }
	char *GetFileData (void) { return m_cpbuffer; }
	unsigned long GetLine (unsigned long ulLineNumber, char *buf, size_t len);

	unsigned long GetLineCount (void) { return m_ulNumLines; }
	unsigned long LongestLine (void);
	
private:
	
	bool InitLineBuffer (void);

	char *m_cpbuffer;
	unsigned long m_ulLength;

	unsigned long *m_plpLineBuffer;
	unsigned long  m_ulNumLines;



};

#endif 
