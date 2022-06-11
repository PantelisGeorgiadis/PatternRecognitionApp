#include "XmlReader.h"

#ifdef USE_XML_SUPPORT

int XMLNode::m_iObjCnt;

XMLNode::XMLNode(std::string sName, XMLNode * Parent)
{
	
	m_iObjCnt++;
	m_NodeCtr = 0;
	m_ParentNode = Parent;
	m_sNodeName = sName;

}

void XMLNode::DeleteAll()
{

	for (XMLNodeMapIter TmpItr = m_XMLChildNodes.begin();TmpItr != m_XMLChildNodes.end(); TmpItr++){
		if (TmpItr->second != NULL) {
			if ((TmpItr->second->GetChildNodeCnt() != 0)){
				TmpItr->second->DeleteAll();
			}
			delete TmpItr->second;
		}
	}

	m_XMLChildNodes.clear(); 
	m_XMLChildElements.clear(); 

}

void XMLNode::ResetReading()
{

	for (XMLNodeMapIter TmpItr = m_XMLChildNodes.begin();TmpItr != m_XMLChildNodes.end(); TmpItr++){
		if (TmpItr->second != NULL) {
			if ((TmpItr->second->GetChildNodeCnt() != 0)){
				TmpItr->second->ResetReading();
			}
			ResetNodeCntr();

		}
	}
}

long XMLNode::GetChildNodeCnt()
{
	
	return m_XMLChildNodes.size();

}

std::string XMLNode::GetElementValue(std::string sName) 
{
	
	return m_XMLChildElements[sName];	 

}

long XMLNode::GetElementCount() 
{
	
	return m_XMLChildElements.size();

}

XMLNode * XMLNode::GetFirstChild()
{
	
	m_NodeCtr = 0;
	
	return m_XMLChildNodes[m_NodeCtr++];

}

XMLNode * XMLNode::GetNextChild()
{

	return m_XMLChildNodes[m_NodeCtr++];	 

}

XMLNode * XMLNode::AddChildNode(std::string sName)
{
	
	static int iTmp;
	XMLNode * Tmp = new XMLNode(sName,this);
	m_XMLChildNodes[m_NodeCtr++] = Tmp;
	iTmp++;
	
	return Tmp;

}

void XMLNode::AddElementVal(std::string sKey,std::string sval)
{
	
	m_XMLChildElements[sKey] = sval;

}

CXmlReader::CXmlReader(std::string sFileName)
{
	
	m_sDocName = sFileName;
	m_XMLRootNode = NULL;
	m_XMLTraverse = NULL;
	ReadFile();

}

bool CXmlReader::ReadFile()
{
	
	FILE *fp = fopen(m_sDocName.c_str(),"r+");
	if (fp == NULL){
		return false;
	}
	char buf[1000];
	while (fgets(buf, 1000, fp)){
		std::string sTmp = buf;
		sTmp = EatupWhiteSpace(sTmp);
		if (ProcessString(sTmp) == false){
			m_XMLRootNode->DeleteAll();
			return false;
		}
	}
	if (m_XMLTraverse != NULL){
		return false;
	}
	fclose(fp);
	
	return true;

}

std::string CXmlReader::EatupWhiteSpace(std::string sInput)
{
	
	int iStart = sInput.find_first_not_of(" \t\n");
	int iEnd = sInput.find_last_not_of(" \t\n");
	if (iStart == -1){
		return "";
	}

	return std::string(sInput, iStart, iEnd - iStart + 1);

}

bool CXmlReader::ProcessString(std::string sInput)
{
	
	if (sInput[0] != '<'){
		return false;
	}
	switch(sInput[1]){
		case '?':
		case '!':
			return true;
			break;
		case '/':
			if (m_XMLTraverse == NULL){
				return false;
			}
			else{
				m_XMLTraverse->ResetNodeCntr();
				m_XMLTraverse = m_XMLTraverse->GetParentNode();
			}
			break;
		default:
			{
				
				sInput = sInput.substr(1);
				int iTmp = sInput.find_first_of("<");
				
				if (iTmp != -1){
					iTmp = sInput.find_first_of(" \t>");
					std::string sKey = sInput.substr(0,iTmp);
					iTmp = sInput.find_first_of(">");
					sInput = sInput.substr(iTmp+1);
					iTmp = sInput.find_first_of("<");
					std::string sVal = sInput.substr(0,iTmp);
					m_XMLTraverse->AddElementVal(sKey,sVal);				
				}
				else{
					iTmp = sInput.find_first_of(" \t>");
					std::string sNodeName = sInput.substr(0,iTmp);
					if (m_XMLRootNode == NULL){
						m_XMLRootNode = new XMLNode(sNodeName.c_str(),NULL);
						m_XMLTraverse = m_XMLRootNode;
					}
					else{
						m_XMLTraverse = m_XMLTraverse->AddChildNode(sNodeName);
					}
				}
				break;
			}
	}

	return true;

}

CXmlReader::~CXmlReader()
{
	
	if ((m_XMLRootNode == NULL) || (XMLNode::GetObjectCnt() == 0)){
		return;
	}
	DeleteAll();
	if (m_XMLRootNode != NULL){
		delete m_XMLRootNode;
	}
	XMLNode::GetObjectCnt();

}

std::string CXmlReader::GetDocName()
{
	
	return m_sDocName;	 

}

std::string CXmlReader::GetRootName()
{
	
	return m_sRootName;	 

}

XMLNode * CXmlReader::GetRootNode()
{
	
	return m_XMLRootNode;	 

}

#endif
