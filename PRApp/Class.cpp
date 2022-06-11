#include "stdafx.h"
#include "Class.h"

CClass::CClass()
{

	m_Pattern = NULL;
	m_cs = CLASSSHAPE_TRIANGLE;

}

CClass::CClass(int iNumberOfPatterns, int iNumberOfFeaturesPerPattern)
{

	CreateClass(iNumberOfPatterns, iNumberOfFeaturesPerPattern);

}

CClass::~CClass()
{

	DeleteClass();

}

void CClass::CreateClass (int iNumberOfPatterns, int iNumberOfFeaturesPerPattern){

	m_Pattern = NULL;

	// OPTIMIZATION: No push_back
	m_vPatterns.resize(iNumberOfPatterns);

	for (int i=0;i<iNumberOfPatterns;i++){
		m_Pattern = new CPattern();
		m_Pattern->CreatePattern (iNumberOfFeaturesPerPattern);
		m_vPatterns[i] = m_Pattern;
	}

}

void CClass::DeleteClass (void){

	CPattern *Pattern = NULL;

	for (int i=0;i<GetNumberOfPatterns();i++){
		Pattern = GetPattern(i);
		Pattern->DeletePattern ();
		delete Pattern;
		Pattern = NULL;
	}

	if (!m_vPatterns.empty()){
		m_vPatterns.clear();
	}

}

void CClass::AddPattern (CPattern *pPattern, int iReservedValue){

	CPattern *Pattern;
	Pattern = new CPattern();
	Pattern->CreatePattern (pPattern->GetNumberOfFeatures());
	
	for (int i=0;i<pPattern->GetNumberOfFeatures();i++){
		Pattern->GetFeature(i)->SetFeatureValue(pPattern->GetFeature(i)->GetFeatureValue());
	}

	Pattern->SetReservedValue(iReservedValue);
	
	m_vPatterns.push_back(Pattern);

}

void CClass::InsertPatternAt (int iPatternIndex, CPattern *pPattern, int iReservedValue){

	CPattern *Pattern;
	Pattern = new CPattern();
	Pattern->CreatePattern (pPattern->GetNumberOfFeatures());
	
	for (int i=0;i<pPattern->GetNumberOfFeatures();i++){
		Pattern->GetFeature(i)->SetFeatureValue(pPattern->GetFeature(i)->GetFeatureValue());
	}

	Pattern->SetReservedValue(iReservedValue);

	std::vector<CPattern*>::iterator it = m_vPatterns.begin() + iPatternIndex;	
	m_vPatterns.insert(it, Pattern);

}

CPattern *CClass::ExtractPattern (int iPatternIndex){

	if (iPatternIndex > GetNumberOfPatterns()){
		return NULL;
	}

	CPattern *ExtractedPattern = new CPattern();
	ExtractedPattern->CreatePattern (GetNumberOfFeaturesPerPattern());

	CPattern *Pattern = NULL;
	Pattern = GetPattern(iPatternIndex);
	
	for (int i=0;i<GetNumberOfFeaturesPerPattern();i++){
		ExtractedPattern->GetFeature(i)->SetFeatureValue(Pattern->GetFeature(i)->GetFeatureValue());
	}

	ExtractedPattern->SetReservedValue(Pattern->GetReservedValue());
	
	Pattern->DeletePattern ();
	delete Pattern;
	Pattern = NULL;

	std::vector<CPattern*>::iterator it = m_vPatterns.begin() + iPatternIndex;
	m_vPatterns.erase(it);

	return ExtractedPattern;

}

CClass *CClass::ExtractPatterns (int *iPatternsIndex, int iPatternCount){

	CPattern *Pattern = NULL;
	int i, j;
	int iTmp;

	for (i=0;i<iPatternCount;i++){
		if (iPatternsIndex[i] > GetNumberOfPatterns()){
			return NULL;
		}
	}

	CClass *ExtractedPatterns = new CClass(iPatternCount, GetNumberOfFeaturesPerPattern());
	for (i=0;i<iPatternCount;i++){
		Pattern = GetPattern(iPatternsIndex[i]);
		for (j=0;j<ExtractedPatterns->GetNumberOfFeaturesPerPattern();j++){
			ExtractedPatterns->GetPattern(i)->GetFeature(j)->SetFeatureValue(Pattern->GetFeature(j)->GetFeatureValue());
		}
		ExtractedPatterns->GetPattern(i)->SetReservedValue(Pattern->GetReservedValue());
		delete Pattern;
		Pattern = NULL;
	}

	for (i=0;i<(iPatternCount - 1);i++){
		for (j=(i + 1);j<iPatternCount;j++){
			if (iPatternsIndex[i] < iPatternsIndex[j]){
				iTmp = iPatternsIndex[i];
				iPatternsIndex[i] = iPatternsIndex[j];
				iPatternsIndex[j] = iTmp;
			}
		}
	}

	std::vector<CPattern*>::iterator it;

	for (i=0;i<iPatternCount;i++){
		it = m_vPatterns.begin() + iPatternsIndex[i];
		m_vPatterns.erase(it);
	}

	return ExtractedPatterns;

}

CClass *CClass::ExportPatterns (int *iPatternsIndex, int iPatternCount){

	CPattern *Pattern = NULL;
	int i, j;

	for (i=0;i<iPatternCount;i++){
		if (iPatternsIndex[i] > GetNumberOfPatterns()){
			return NULL;
		}
	}

	CClass *ExportedPatterns = new CClass(iPatternCount, GetNumberOfFeaturesPerPattern());
	for (i=0;i<iPatternCount;i++){
		Pattern = GetPattern(iPatternsIndex[i]);
		for (j=0;j<ExportedPatterns->GetNumberOfFeaturesPerPattern();j++){
			ExportedPatterns->GetPattern(i)->GetFeature(j)->SetFeatureValue(Pattern->GetFeature(j)->GetFeatureValue());
		}
		ExportedPatterns->GetPattern(i)->SetReservedValue(Pattern->GetReservedValue());
	}

	return ExportedPatterns;

}

void CClass::RemoveAllPatterns (void){

	CPattern *RemovedPattern;

	do{
		RemovedPattern = ExtractPattern(0);
		delete RemovedPattern;
		RemovedPattern = NULL;
	}while (GetNumberOfPatterns() != 0);

}

void CClass::ExtractAllFeatures (int iFeaturesIndex){

	if (iFeaturesIndex > GetNumberOfFeaturesPerPattern()){
		return;
	}

	CFeature *ExtractedFeature = NULL;
	
	for (int i=0;i<GetNumberOfPatterns();i++){
		ExtractedFeature = GetPattern(i)->ExtractFeature(iFeaturesIndex);
		delete ExtractedFeature;
		ExtractedFeature = NULL;
	}

}

CPattern *CClass::GetPattern (int iPatternIndex){

	if (iPatternIndex > GetNumberOfPatterns()){
		return NULL;
	}

	return (CPattern *)m_vPatterns[iPatternIndex];

}

CClass *CClass::CopyClass (void){

	CClass *CopiedClass = new CClass ();
	CopiedClass->CreateClass (GetNumberOfPatterns(), GetNumberOfFeaturesPerPattern());

	for (int i=0;i<GetNumberOfPatterns();i++){
		for (int j=0;j<GetNumberOfFeaturesPerPattern();j++){
			CopiedClass->GetPattern(i)->GetFeature(j)->SetFeatureValue(GetPattern(i)->GetFeature(j)->GetFeatureValue());
		}
		CopiedClass->GetPattern(i)->SetReservedValue(GetPattern(i)->GetReservedValue());
	}

	CopiedClass->SetClassShape(GetClassShape());

	return CopiedClass;
	
}

void CClass::CopyClass (CClass *pClassDest, CClass *pClassSrc){
	
	if (pClassDest->GetNumberOfPatterns() != pClassSrc->GetNumberOfPatterns()){
		return;
	}
	
	for (int i=0;i<pClassDest->GetNumberOfPatterns();i++){
		CPattern::CopyPattern(pClassDest->GetPattern(i), pClassSrc->GetPattern(i));
	}
	
	pClassDest->SetClassShape(pClassSrc->GetClassShape());
	
}

void CClass::WriteClassDataToFile (char *szFileName){

	FILE *fp;

	fp = fopen(szFileName, "w");
	if (fp == NULL){
		return;
	}

	for (int i=0;i<GetNumberOfPatterns();i++){
		for (int j=0;j<GetNumberOfFeaturesPerPattern();j++){
			fprintf(fp, "%.16lf\t", GetPattern(i)->GetFeature(j)->GetFeatureValue()); 
		}
		fprintf(fp, "\n"); 
	}

	fclose(fp);

}


