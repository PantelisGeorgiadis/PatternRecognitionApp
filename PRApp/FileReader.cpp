#include "stdafx.h"
#include "FileReader.h"
#include "Globals.h"

CFileReader::CFileReader()
{

	m_cpbuffer = NULL;
	m_ulLength = 0;
	m_plpLineBuffer = NULL;
	m_ulNumLines = 0;

}

CFileReader::~CFileReader()
{
	
	Clear();

}

bool CFileReader::ReadFile (char *szFilename){

	FILE *fp;
	size_t ulNumRead;

	fp = fopen(szFilename, "rb");
	if (fp == NULL){
		return false;
	}

	fseek(fp, 0, SEEK_END);
	m_ulLength = ftell(fp); 
	fseek(fp,0,SEEK_SET);
	if (m_ulLength == 0){
		return false;
	}

	if ((m_cpbuffer = new char[m_ulLength]) == 0){
		return false;
	}

	ulNumRead = fread(m_cpbuffer, m_ulLength, 1, fp);

	fclose(fp);

	return true;

}

bool CFileReader::ParseFile (char *szFilename){

	FILE *fp;
	size_t ulNumRead;

	fp = fopen(szFilename, "rb");
	if (fp == NULL){
		return false;
	}

	fseek(fp, 0, SEEK_END);
	m_ulLength = ftell(fp); 
	fseek(fp,0,SEEK_SET);
	if (m_ulLength == 0){
		return false;
	}

	if ((m_cpbuffer = new char[m_ulLength]) == 0){
		return false;
	}

	ulNumRead = fread(m_cpbuffer, m_ulLength, 1, fp);

	if (!InitLineBuffer()){
		Clear();
	}

	fclose(fp);
	
	return true;

}

bool CFileReader::InitLineBuffer (void){

	unsigned long i;
	unsigned long ulLineStart = 0;

	if ((m_plpLineBuffer = new unsigned long[m_ulLength]) == 0){
		return false;
	}

	m_ulNumLines = 0;

	for (i=0;i<m_ulLength;){
		if (m_cpbuffer[i++] == '\r'){
			if (m_cpbuffer[i] == '\n'){
				i++;
			}
			m_plpLineBuffer[m_ulNumLines++] = ulLineStart;
			ulLineStart = i;
		}
	}

	if (m_ulLength > 0){
		m_plpLineBuffer[m_ulNumLines++] = ulLineStart;
	}
	m_plpLineBuffer[m_ulNumLines] = m_ulLength;

	return true;

}

bool CFileReader::Clear (void){

	if (m_cpbuffer){
		delete m_cpbuffer;
		m_cpbuffer = NULL;
		m_ulLength = 0;
	}

	if (m_plpLineBuffer){
		delete m_plpLineBuffer;
		m_plpLineBuffer  = NULL;
		m_ulNumLines = 0;
	}

	return true;
}

unsigned long CFileReader::GetLine (unsigned long ulLineNumber, char *buf, size_t len){

	char *cpLinePtr;
	unsigned long ulLineLen;

	if ((ulLineNumber >= m_ulNumLines) || (m_cpbuffer == NULL) || (m_ulLength == 0)){
		return 0;
	}

	cpLinePtr = m_cpbuffer + m_plpLineBuffer[ulLineNumber];
	ulLineLen = m_plpLineBuffer[ulLineNumber + 1] - m_plpLineBuffer[ulLineNumber];
	ulLineLen = min(len, ulLineLen);
	memcpy(buf, cpLinePtr, ulLineLen);
	
	return ulLineLen;

}

unsigned long CFileReader::LongestLine (void){

	unsigned long i;
	unsigned long ulLen;
	unsigned long ulLongest = 0;

	for (i=0;i<m_ulNumLines;i++){
		ulLen = m_plpLineBuffer[i + 1] - m_plpLineBuffer[i];

		if (m_cpbuffer[m_plpLineBuffer[i + 1] - 1] == '\n'){
			ulLen--;
		}
		if (m_cpbuffer[m_plpLineBuffer[i + 1] - 2] == '\r'){
			ulLen--;
		}

		ulLongest = max(ulLongest, ulLen);
		
	}

	if (ulLongest > 600){	
		ulLongest = 600;
	}

	return ulLongest;

}
