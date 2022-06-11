#include "XmlWriter.h"

#ifdef USE_XML_SUPPORT

CXmlWriter::CXmlWriter(std::string sTmp)
{
    
	m_sXmlFile = sTmp;
    fp = NULL;
    m_iLevel = 0;
    fp = fopen(m_sXmlFile.c_str(), "w");
    if (fp == NULL){
		return;
  	}
	else{
		fprintf(fp,"<?xml version=\"1.0\" encoding=\"UTF-8\" \?>");
	}

}

CXmlWriter::~CXmlWriter()
{
    if (fp != NULL){
        fclose(fp);
	}
    
	m_vectAttrData.clear();

}

void CXmlWriter::CreateTag(std::string sTag)
{
	fprintf(fp,"\n");
	
	for (int iTmp=0;iTmp<m_iLevel;iTmp++){
		fprintf(fp,"\t");
	}

	fprintf(fp,"<%s",sTag.c_str());
	
	while (0 < m_vectAttrData.size() / 2){
		std::string sTmp = m_vectAttrData.back();
		fprintf(fp," %s=", sTmp.c_str());
		m_vectAttrData.pop_back();
		sTmp = m_vectAttrData.back();
		fprintf(fp,"\"%s\"", sTmp.c_str());
		m_vectAttrData.pop_back();
	}

	m_vectAttrData.clear();
	fprintf(fp,">");
	m_sTagStack.push(sTag);
	m_iLevel++;

}

void CXmlWriter::CloseLastTag()
{
	
	fprintf(fp,"\n");
	m_iLevel--;
    
	for (int iTmp=0;iTmp<m_iLevel;iTmp++){
		fprintf(fp,"\t");
	}
	fprintf(fp,"</%s>",m_sTagStack.top().c_str());
	m_sTagStack.pop();

}

void CXmlWriter::CloseAllTags()
{
	
	while (m_sTagStack.size() != 0){
	   fprintf(fp,"\n");
	   m_iLevel--;
       
	   for (int iTmp=0;iTmp<m_iLevel;iTmp++){
	       fprintf(fp,"\t");
	   }
	   fprintf(fp,"</%s>",m_sTagStack.top().c_str());
	   m_sTagStack.pop();
    }

}

void CXmlWriter::CreateChild(std::string sTag,std::string sValue)
{
	
	fprintf(fp,"\n");
	
	for (int iTmp=0;iTmp<m_iLevel;iTmp++){
		fprintf(fp,"\t");
	}
	fprintf(fp,"<%s",sTag.c_str());
	
	while (0 < m_vectAttrData.size()/2){
		std::string sTmp = m_vectAttrData.back();
		fprintf(fp," %s=", sTmp.c_str());
		m_vectAttrData.pop_back();
		sTmp = m_vectAttrData.back();
		fprintf(fp,"\"%s\"", sTmp.c_str());
		m_vectAttrData.pop_back();
	}
	
	m_vectAttrData.clear();
	
	fprintf(fp,">%s</%s>",sValue.c_str(),sTag.c_str());

}

void CXmlWriter::AddAtributes(std::string sKey, std::string sVal)
{
	
	m_vectAttrData.push_back(sVal);
	m_vectAttrData.push_back(sKey);

}

void CXmlWriter::AddComment(std::string sComment)
{
	
	fprintf(fp,"\n");
	
	for (int iTmp=0;iTmp<m_iLevel;iTmp++){
		fprintf(fp,"\t");
	}
	
	fprintf(fp,"<!--%s-->",sComment.c_str());

}

#endif
