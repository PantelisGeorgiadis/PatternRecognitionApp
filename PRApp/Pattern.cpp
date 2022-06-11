#include "stdafx.h"
#include "Pattern.h"

CPattern::CPattern()
{

	m_Feature = NULL;
	m_iReservedValue = -1;

}

CPattern::CPattern(int iNumberOfFeatures)
{

	CreatePattern(iNumberOfFeatures);

}

CPattern::~CPattern()
{

	DeletePattern();

}

void CPattern::CreatePattern (int iNumberOfFeatures){

	m_Feature = NULL;

// OPTIMIZATION: No push_back
	m_vFeatures.resize(iNumberOfFeatures);

	if (iNumberOfFeatures > 0){
		for (int i=0;i<iNumberOfFeatures;i++){
			m_Feature = new CFeature ();
			m_vFeatures[i] = m_Feature;
		}
	}

}

void CPattern::DeletePattern (void){

	CFeature *Feature = NULL;

	for (int i=0;i<GetNumberOfFeatures();i++){
		Feature = GetFeature(i);
		delete Feature;
		Feature = NULL;
	}

	if (!m_vFeatures.empty()){
		m_vFeatures.clear();
	}

}

void CPattern::AddFeature (CFeature *pFeature){

	CFeature *Feature;
	Feature = new CFeature();
	Feature->SetFeatureValue(pFeature->GetFeatureValue());

	m_vFeatures.push_back(Feature);

}

CFeature *CPattern::GetFeature (int iFeatureIndex){

	if (iFeatureIndex > GetNumberOfFeatures()){
		return NULL;
	}

	return (CFeature *)m_vFeatures[iFeatureIndex];

}

CFeature *CPattern::ExtractFeature (int iFeatureIndex){

	if (iFeatureIndex > GetNumberOfFeatures()){
		return NULL;
	}

	CFeature *ExtractedFeature = new CFeature();

	CFeature *Feature = NULL;
	Feature = GetFeature(iFeatureIndex);
	
	ExtractedFeature->SetFeatureValue(Feature->GetFeatureValue());
	
	delete Feature;
	Feature = NULL;

	std::vector<CFeature*>::iterator it = m_vFeatures.begin() + iFeatureIndex;
	m_vFeatures.erase(it);

	return ExtractedFeature;

}

void CPattern::RemoveAllFeatures (void){

	CFeature *RemovedFeature;

	do{
		RemovedFeature = ExtractFeature(0);
		delete RemovedFeature;
		RemovedFeature = NULL;
	}while (GetNumberOfFeatures() != 0);

}

CPattern *CPattern::CopyPattern (void){

	CPattern *CoppiedPattern = new CPattern(GetNumberOfFeatures());

	for (int i=0;i<GetNumberOfFeatures();i++){
		CoppiedPattern->GetFeature(i)->SetFeatureValue(GetFeature(i)->GetFeatureValue());
	}

	CoppiedPattern->SetReservedValue(GetReservedValue());

	return CoppiedPattern;

}

void CPattern::CopyPattern (CPattern *pPatternDest, CPattern *pPatternSrc){
	
	if (pPatternDest->GetNumberOfFeatures() != pPatternSrc->GetNumberOfFeatures()){
		return;
	}
	
	for (int i=0;i<pPatternDest->GetNumberOfFeatures();i++){
		pPatternDest->GetFeature(i)->SetFeatureValue(pPatternSrc->GetFeature(i)->GetFeatureValue());
		pPatternDest->SetReservedValue(pPatternSrc->GetReservedValue());
	}
	
}

CPattern *CPattern::CopyPatternFromCombination (CCombination *pCombination){

	CPattern *CoppiedPattern = new CPattern(pCombination->GetCombinationVectorSize());

	for (int i=0;i<pCombination->GetCombinationVectorSize();i++){
		CoppiedPattern->GetFeature(i)->SetFeatureValue(GetFeature(pCombination->GetCombinationVectorValue(i))->GetFeatureValue());
	}

	CoppiedPattern->SetReservedValue(GetReservedValue());

	return CoppiedPattern;

}

void CPattern::WritePatternDataToFile (char *szFileName){

	FILE *fp;

	fp = fopen(szFileName, "w");
	if (fp == NULL){
		return;
	}

	for (int j=0;j<GetNumberOfFeatures();j++){
		fprintf(fp, "%.9lf", GetFeature(j)->GetFeatureValue()); 
		if (j != (GetNumberOfFeatures() - 1)){
			fprintf(fp, "\t");
		}
	}
		
	fclose(fp);

}
