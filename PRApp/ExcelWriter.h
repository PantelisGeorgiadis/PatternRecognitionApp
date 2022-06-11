#ifndef EXCELWRITER_H
#define EXCELWRITER_H

#ifndef __GNUC__
#pragma warning(disable : 4786)
#endif

#include <vector>
#include <stdio.h>

#define EXCEL_VERSION 	2
#define TYPE_WORKSHEET 	0x10

#define OPCODE_BOF                           0x09
#define OPCODE_FILEPASS                      0x2F
#define OPCODE_INDEX                         0x0B
#define OPCODE_CALCCOUNT                     0x0C
#define OPCODE_CALCMODE                      0x0D
#define OPCODE_PRECISION                     0x0E
#define OPCODE_REFMODE                       0x0F
#define OPCODE_DELTA                         0x10
#define OPCODE_ITERATION                     0x11
#define OPCODE_1904                          0x22
#define OPCODE_BACKUP                        0x40
#define OPCODE_PRINT_ROW_HEADERS             0x2A
#define OPCODE_PRINT_GRIDLINES               0x2B
#define OPCODE_HORIZONTAL_PAGE_BREAKS        0x1B
#define OPCODE_VERTICAL_PAGE_BREAKS          0x1A
#define OPCODE_DEFAULT_ROW_HEIGHT            0x25
#define OPCODE_FONT                          0x31
#define OPCODE_FONT2                         0x32
#define OPCODE_HEADER                        0x14
#define OPCODE_FOOTER                        0x15
#define OPCODE_LEFT_MARGIN                   0x26
#define OPCODE_RIGHT_MARGIN                  0x27
#define OPCODE_TOP_MARGIN                    0x28
#define OPCODE_BOTTOM_MARGIN                 0x29
#define OPCODE_COLWIDTH                      0x24
#define OPCODE_EXTERNCOUNT                   0x16
#define OPCODE_EXTERNSHEET                   0x17
#define OPCODE_EXTERNNAME                    0x23
#define OPCODE_FORMATCOUNT                   0x1F
#define OPCODE_FORMAT                        0x1E
#define OPCODE_NAME                          0x18
#define OPCODE_DIMENSIONS                    0x00
#define OPCODE_COLUMN_DEFAULT                0x20
#define OPCODE_ROW                           0x08
#define OPCODE_BLANK                         0x01
#define OPCODE_INTEGER                       0x02
#define OPCODE_NUMBER                        0x03
#define OPCODE_LABEL                         0x04
#define OPCODE_BOOLERR                       0x05
#define OPCODE_FORMULA                       0x06
#define OPCODE_ARRAY                         0x21
#define OPCODE_CONTINUE                      0x3C
#define OPCODE_STRING                        0x07
#define OPCODE_TABLE                         0x36
#define OPCODE_TABLE2                        0x37
#define OPCODE_PROTECT                       0x12
#define OPCODE_WINDOW_PROTECT                0x19
#define OPCODE_PASSWORD                      0x13
#define OPCODE_NOTE                          0x1C
#define OPCODE_WINDOW1                       0x3D
#define OPCODE_WINDOW2                       0x3E
#define OPCODE_PANE                          0x41
#define OPCODE_SELECTION                     0x1D
#define OPCODE_EOF                           0x0A

#define	ALIGN_GENERAL  						0
#define	ALIGN_LEFT    						1
#define	ALIGN_CENTER  						2
#define	ALIGN_RIGHT   						3
#define	ALIGN_FILL    						4
#define	ALIGN_MULTIPLAN_DEFAULT  			7	

#define BORDER_LEFT    0x08
#define BORDER_RIGHT   0x10
#define BORDER_TOP     0x20
#define BORDER_BOTTOM  0x40

class LittleEndianWriter
{
private:

	FILE 	*m_pFile;

public:
	
	LittleEndianWriter(FILE *f);
	~LittleEndianWriter();
	
	void Write1(char v);
	void Write2(int v);
	void Write4(long v);
	void WriteFloatIEEE(float v);
	void WriteDoubleIEEE(double v);			

};

class BIFFRecord
{
protected: 
	
	BIFFRecord () {}  				
	virtual ~BIFFRecord () {} 
	void Write (LittleEndianWriter *pWriter, int nRecNo, int nRecLen);

public:
	
	virtual void Write (LittleEndianWriter *pWriter) = 0; 	

};	

class ExcelValueAttributes
{
private:
	
	int m_nRow;
	int m_nColumn;
	
	char m_nAttr1;  
	char m_nAttr2;
	char m_nAttr3;

public:					
	
	ExcelValueAttributes ();
	ExcelValueAttributes (int nRow,int nColumn);
	~ExcelValueAttributes (){}
	
	void CopyAttributes(ExcelValueAttributes v){
		m_nRow = v.m_nRow;
		m_nColumn = v.m_nColumn;
		m_nAttr1 = v.m_nAttr1;
		m_nAttr2 = v.m_nAttr2;
		m_nAttr3 = v.m_nAttr3;
	}
	
	void Write (LittleEndianWriter *pWriter);
	
	int  GetRow();
	void SetRow(int v); 
	
	int  GetColumn();
	void SetColumn(int v);
	
	void SetHidden (bool v);
	bool GetHidden ();
	
	void SetLocked (bool v);
	bool GetLocked ();
	
	void SetShaded (bool v);
	bool GetShaded ();
	
	void SetBorder (int type);
	int  GetBorder ();
	
	void SetAlignament (int type);
	int  GetAlignament ();
	
	void SetFontNum (int v);
	int  GetFontNum ();
	
	void SetFormatNum (int v);
	int  GetFormatNum ();
	
};

class ExcelBOF : public BIFFRecord
{
private:
	
	int	m_nVersion;
	int	m_nType;

public:
	
	ExcelBOF (int nVer,int nType):m_nVersion(nVer),m_nType(nType){}
	~ExcelBOF(){}
	void Write (LittleEndianWriter *pWriter);
	
};

class ExcelNumber : public BIFFRecord,
					public ExcelValueAttributes
{
private:
	
	double m_nValue;

public:
	
	ExcelNumber (){
		m_nValue = 0;
	}
	
	ExcelNumber (double val){
		m_nValue = val;
	}
	
	void SetValue (double v){
		m_nValue = v;
	}
	
	double GetValue (){
		return m_nValue;
	}
	
	void Write (LittleEndianWriter *pWriter);

};	

class ExcelLabel :  public BIFFRecord,
					public ExcelValueAttributes
{
private:
	
	char		m_pchValue[257];

public:			 
	
	ExcelLabel (){
		m_pchValue[0] = '\0';
	}
	
	ExcelLabel (const char *v){
		strncpy (m_pchValue, v, sizeof (m_pchValue));
		m_pchValue[sizeof(m_pchValue) - 1] = '\0';
	}
	
	void setValue (const char *v){
		strncpy (m_pchValue, v, sizeof (m_pchValue));
		m_pchValue[sizeof(m_pchValue) - 1] = '\0';
	}
	
	const char *getValue (){
		return m_pchValue;
	}
	
	void Write (LittleEndianWriter *pWriter);

};

class ExcelEOF : public BIFFRecord
{
public:
	
	ExcelEOF() {}
	~ExcelEOF() {}
	void Write (LittleEndianWriter *pWriter);		

};

class ExcelCell : public ExcelValueAttributes
{
private:
	
	char	*m_pchValue;
	double	m_nValue;
	int		m_nType;

public:
	
	ExcelCell ();
	ExcelCell (const ExcelCell &v);
	~ExcelCell ();
	
	enum{
		TYPE_NONE	= 0,
		TYPE_NUMBER = 1,
		TYPE_STRING = 2
	};
	
	int GetType(){
		
		return m_nType;

	}
	
	void clear();
	
	ExcelCell& operator=(const ExcelCell &v);
	
	ExcelCell& operator=(double v);
	operator double();
	
	ExcelCell& operator=(const char *v);
	operator const char *();
	
	void Write (LittleEndianWriter *pWriter);		
	
};

class CExcelWriter
{
private:
	
	std::vector< std::vector<ExcelCell> > m_vvTableValues;

public:
	
	CExcelWriter ();
	~CExcelWriter ();
	
	ExcelCell &operator() (unsigned row, unsigned column);
	void Write (FILE *dest);
	void SaveAs (char *szFileName);

};

#endif
