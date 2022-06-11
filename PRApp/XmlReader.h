#ifndef XMLREADER_H
#define XMLREADER_H

#ifdef USE_XML_SUPPORT

#ifndef __GNUC__
#pragma warning(disable : 4786)
#endif

#include <stdio.h>
#include <string>
#include <map>

class XMLNode;

typedef std::map<int, XMLNode *> XMLNodeMap;
typedef XMLNodeMap::iterator XMLNodeMapIter;
typedef std::map<std::string, std::string> XMLStringMap;

class XMLNode
{
public:
	XMLNode(std::string sName, XMLNode*); 
	~XMLNode(){m_iObjCnt--;};
	long GetElementCount();
	std::string GetElementValue(std::string sName); 
	XMLNode * GetFirstChild(); 
	XMLNode * GetNextChild(); 
	long GetChildNodeCnt();
	XMLNode* GetParentNode(){return m_ParentNode;};
	void DeleteAll();
	XMLNode * AddChildNode(std::string sName);
	void AddElementVal(std::string sKey,std::string sval);
	void ResetNodeCntr(){m_NodeCtr =0;};
	void ResetReading();
	std::string GetNodeName(){return m_sNodeName;};
	static int GetObjectCnt(){return m_iObjCnt;};
private:
	std::string m_sNodeName; 
	int m_NodeCtr; 
	XMLNode * m_ParentNode; 
	XMLNodeMap m_XMLChildNodes;
	XMLStringMap m_XMLChildElements;
	static int m_iObjCnt;
};

class CXmlReader{
public:
	CXmlReader(std::string sFileName);
	~CXmlReader();
	std::string GetDocName();
	std::string GetRootName();
	XMLNode * GetRootNode();
	bool ReadFile();
	std::string EatupWhiteSpace(std::string);
	bool ProcessString(std::string);
	void ResetReading(){m_XMLRootNode->ResetReading();};
	void DeleteAll(){m_XMLRootNode->DeleteAll();};
private:
	std::string m_sDocName;
	std::string m_sRootName;
	XMLNode *m_XMLRootNode; 
	XMLNode *m_XMLTraverse; 
};

#endif

#endif
