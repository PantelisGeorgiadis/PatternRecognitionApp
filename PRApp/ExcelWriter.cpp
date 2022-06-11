#include "stdafx.h"
#include "ExcelWriter.h"

LittleEndianWriter::LittleEndianWriter (FILE * f)
{
	
	m_pFile = f;

}

LittleEndianWriter::~LittleEndianWriter ()
{
	
	fclose (m_pFile);

}

void LittleEndianWriter::Write1 (char v)
{
	
	fwrite (&v, 1, 1, m_pFile);

}

void LittleEndianWriter::Write2 (int v)
{
	
	Write1 ((v) & 0xff);
	Write1 ((v >> 8) & 0xff);

}

void LittleEndianWriter::Write4 (long v)
{
	
	Write2 ((v) & 0xffff);
	Write2 ((v >> 16) & 0xffff);

}

void LittleEndianWriter::WriteFloatIEEE (float v)
{
	
	fwrite (&v, 1, sizeof (v), m_pFile);

}

void LittleEndianWriter::WriteDoubleIEEE (double v)
{
	
	fwrite (&v, 1, sizeof (v), m_pFile);

}

void BIFFRecord::Write (LittleEndianWriter * pWriter, int nRecNo, int nRecLen)
{
	
	pWriter->Write2 (nRecNo);
	pWriter->Write2 (nRecLen);

}

ExcelValueAttributes::ExcelValueAttributes () {
	
	m_nRow = m_nColumn = 0;
	m_nAttr1 = m_nAttr2 = m_nAttr3 = 0;

}

ExcelValueAttributes::ExcelValueAttributes (int nRow, int nColumn)
{
	
	m_nRow = nRow;
	m_nColumn = nColumn;
	m_nAttr1 = m_nAttr2 = m_nAttr3 = 0;

}

void ExcelValueAttributes::Write (LittleEndianWriter * pWriter)
{
	
	pWriter->Write2 (m_nRow);
	pWriter->Write2 (m_nColumn);
	pWriter->Write1 (m_nAttr1);
	pWriter->Write1 (m_nAttr2);
	pWriter->Write1 (m_nAttr3);

}

int ExcelValueAttributes::GetRow ()
{
	
	return m_nRow;

}

void ExcelValueAttributes::SetRow (int v)
{
	
	m_nRow = v;

}

int ExcelValueAttributes::GetColumn ()
{
	
	return m_nColumn;

}

void ExcelValueAttributes::SetColumn (int v)
{
	
	m_nColumn = v;

}

void ExcelValueAttributes::SetHidden (bool v)
{
	
	if (v){
		m_nAttr1 |= 0x80;
	} 
	else{
		m_nAttr1 &= ~0x80;
	}

}

bool ExcelValueAttributes::GetHidden ()
{
	
	return (m_nAttr1 & 0x80) != 0;

}

void ExcelValueAttributes::SetLocked (bool v)
{
	
	if (v){
		m_nAttr1 |= 0x40;
	} 
	else{
		m_nAttr1 &= ~0x40;
	}

}

bool ExcelValueAttributes::GetLocked ()
{
	
	return (m_nAttr1 & 0x40) != 0;

}

void ExcelValueAttributes::SetShaded (bool v)
{
	
	if (v){
		m_nAttr3 |= 0x80;
	} 
	else{
		m_nAttr3 &= ~0x80;
	}

}

bool ExcelValueAttributes::GetShaded ()
{
	
	return (m_nAttr3 & 0x80) != 0;

}

void ExcelValueAttributes::SetBorder (int type)
{
	
	m_nAttr3 &= ~0x78;
	m_nAttr3 |= (type & 0x78); 

}

int ExcelValueAttributes::GetBorder ()
{
	
	return m_nAttr3 & 0x78;

}

void ExcelValueAttributes::SetAlignament (int type)
{
	
	m_nAttr3 &= ~0x07;
	m_nAttr3 |= type & 0x07;

}

int ExcelValueAttributes::GetAlignament ()
{
	
	return m_nAttr3 & 0x07;

}

void ExcelValueAttributes::SetFontNum (int v)
{
	
	m_nAttr2 &= ~0xE0;
	m_nAttr2 |= (v & 0x03) << 5;
	
}

int ExcelValueAttributes::GetFontNum ()
{
	
	return (m_nAttr2 >> 5) & 0x03;

}

void ExcelValueAttributes::SetFormatNum (int v)
{
	
	m_nAttr2 &= ~0x3F;
	m_nAttr2 |= v & 0x3F;
	
}

int ExcelValueAttributes::GetFormatNum ()
{
	
	return m_nAttr2 & 0x3F;

}

void ExcelBOF::Write (LittleEndianWriter * pWriter)
{
	
	BIFFRecord::Write (pWriter, OPCODE_BOF, 4);
	pWriter->Write2 (m_nVersion);
	pWriter->Write2 (m_nType);

}

void ExcelNumber::Write (LittleEndianWriter * pWriter)
{
	
	BIFFRecord::Write (pWriter, OPCODE_NUMBER, 15);
	ExcelValueAttributes::Write (pWriter);
	pWriter->WriteDoubleIEEE (m_nValue);

}

void ExcelLabel::Write (LittleEndianWriter * pWriter)
{
	
	BIFFRecord::Write (pWriter, OPCODE_LABEL, 8 + strlen (m_pchValue));
	ExcelValueAttributes::Write (pWriter);
	pWriter->Write1 (strlen (m_pchValue));
	for (unsigned i = 0; i < strlen (m_pchValue); i++){
		pWriter->Write1 (m_pchValue[i]);
	}

}

void ExcelEOF::Write (LittleEndianWriter * pWriter)
{
	
	BIFFRecord::Write (pWriter, OPCODE_EOF, 0);

}

ExcelCell::ExcelCell (){
	
	m_pchValue = NULL;
	m_nValue = 0;
	m_nType = TYPE_NONE;

}

ExcelCell::ExcelCell(const ExcelCell &v){		
	
	m_nType = v.m_nType;
	if (m_nType == TYPE_STRING){
		m_pchValue = _strdup (v.m_pchValue);
	}
	else{
		m_pchValue = NULL;
	}
	m_nValue = v.m_nValue;
	CopyAttributes(v);

}

ExcelCell::~ExcelCell (){
	
	if (m_pchValue != NULL) {
		free (m_pchValue);
	}

}

ExcelCell & ExcelCell::operator = (double v){
	
	m_nType = TYPE_NUMBER;
	m_nValue = v;
	return *this;

}

ExcelCell::operator double ()
{
	
	return m_nValue;

}

ExcelCell & ExcelCell::operator = (const char *v){
	
	m_nType = TYPE_STRING;
	if (m_pchValue != NULL) {
		free (m_pchValue);
	}
	m_pchValue = _strdup (v);
	return *this;

}

ExcelCell::operator const char *()
{
	
	return m_pchValue;

}

void ExcelCell::clear ()
{
	
	if (m_pchValue != NULL){
		free (m_pchValue);
		m_pchValue = NULL;
	}

	m_nType = TYPE_NONE;

}

ExcelCell& ExcelCell::operator=(const ExcelCell &v){
	
	if (m_pchValue != NULL){
		free (m_pchValue);     
		m_pchValue = NULL;
	}
	m_nType = v.m_nType;
	if (m_nType == TYPE_STRING){
		m_pchValue = _strdup (v.m_pchValue);
	}
	m_nValue = v.m_nValue;
	CopyAttributes(v);
	return *this;

}

void ExcelCell::Write (LittleEndianWriter * pWriter)
{
	
	if (m_nType == TYPE_NONE){
		return;
	}
	if (m_nType == TYPE_NUMBER){
		ExcelNumber n (m_nValue);
		
		n.CopyAttributes (*this);
		n.Write (pWriter);
	} 
	else{
		ExcelLabel n (m_pchValue);
		
		n.CopyAttributes (*this);
		n.Write (pWriter);
	}

}

ExcelCell & CExcelWriter::operator ()(unsigned row, unsigned column) {
	
	while (m_vvTableValues.size () <= row){
		std::vector<ExcelCell> v;
		m_vvTableValues.push_back (v);
	}
	while (m_vvTableValues[row].size () <= column){
		ExcelCell v;
		
		m_vvTableValues[row].push_back (v);
	}

	return m_vvTableValues[row][column];

}

CExcelWriter::CExcelWriter()
{

}

CExcelWriter::~CExcelWriter()
{

}

void CExcelWriter::Write (FILE *dest)
{
	
	LittleEndianWriter writer (dest);
	ExcelBOF biffBOF (EXCEL_VERSION, TYPE_WORKSHEET);
	ExcelEOF biffEOF;
	unsigned row, column;
	
	biffBOF.Write (&writer);
	
	for (row = 0; row < m_vvTableValues.size (); row++) {
		for (column = 0; column < m_vvTableValues[row].size (); column++) {
			if (m_vvTableValues[row][column].GetType () == ExcelCell::TYPE_NUMBER){
				m_vvTableValues[row][column].SetRow (row);
				m_vvTableValues[row][column].SetColumn (column);
				m_vvTableValues[row][column].Write (&writer);
			}
		}
	}
	
	for (row = 0; row < m_vvTableValues.size (); row++) {
		for (column = 0; column < m_vvTableValues[row].size (); column++) {
			if (m_vvTableValues[row][column].GetType () == ExcelCell::TYPE_STRING) {
				m_vvTableValues[row][column].SetRow (row);
				m_vvTableValues[row][column].SetColumn (column);
				m_vvTableValues[row][column].Write (&writer);
			}
		}
	}
	
	biffEOF.Write (&writer);
	
}

void CExcelWriter::SaveAs (char *szFileName){

	FILE *fp;

	fp = fopen(szFileName, "wb");
	if (fp == NULL){
		return;
	}

	Write(fp); // 'Write' closes the file (LittleEndianWriter::~LittleEndianWriter)

}
