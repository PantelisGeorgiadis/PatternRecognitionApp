#ifndef XMLWRITER_H
#define XMLWRITER_H

#ifdef USE_XML_SUPPORT

#ifndef __GNUC__
#pragma warning(disable : 4786)
#endif

#include <stdio.h>
#include <string>
#include <vector>
#include <stack>

typedef std::stack<std::string> StackStrings;

class CXmlWriter{
public:

	CXmlWriter(std::string sTmp);
	~CXmlWriter();
	void CreateChild(std::string sTag, std::string sValue);
	void CreateTag(std::string sTag);
	void CloseLastTag();
	void CloseAllTags();
	void AddAtributes(std::string sAttrName, std::string sAttrvalue);
	void AddComment(std::string sComment);

private:
	
	std::string m_sXmlFile;
	std::vector<std::string> m_vectAttrData;
	FILE *fp;
	int m_iLevel;
	StackStrings m_sTagStack;

};

#endif

#endif
