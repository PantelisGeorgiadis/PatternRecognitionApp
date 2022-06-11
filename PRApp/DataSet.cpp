#include "stdafx.h"
#include "DataSet.h"

CDataSet::CDataSet()
{

	m_Class = NULL;
	m_TruthTable = new CTruthTable(1);

}

CDataSet::~CDataSet()
{

	RemoveAllClasses();
	delete m_TruthTable;
	m_TruthTable = NULL;

}

void CDataSet::AddClass (int iNumberOfPatterns, int iNumberOfFeaturesPerPattern){

	m_Class = NULL;
	
	if ((iNumberOfPatterns > 0) && (iNumberOfFeaturesPerPattern > 0)){
		m_TruthTable->DeleteTruthTable();
		m_Class = new CClass (iNumberOfPatterns, iNumberOfFeaturesPerPattern);	
		m_vClasses.push_back(m_Class);		
		m_TruthTable->CreateTruthTable(GetNumberOfClasses());
	}

}

void CDataSet::AddEmptyClass (void){

	m_Class = NULL;
	
	m_TruthTable->DeleteTruthTable();
	m_Class = new CClass (1, 1);
	m_Class->RemoveAllPatterns();
	m_vClasses.push_back(m_Class);		
	m_TruthTable->CreateTruthTable(GetNumberOfClasses());
	
}

void CDataSet::AddClass (CClass *pClass){

	if ((pClass) && (pClass->GetNumberOfPatterns() > 0) && (pClass->GetNumberOfFeaturesPerPattern() > 0)){
		m_TruthTable->DeleteTruthTable();
		m_vClasses.push_back(pClass);		
		m_TruthTable->CreateTruthTable(GetNumberOfClasses());
	}

}

void CDataSet::AddClassFromFile (char *szFileName, int iFeaturesPerLine, int iFeatureDigits){

	m_Class = NULL;
	if (iFeaturesPerLine > 0){
		CFileReader *FileReader = new CFileReader();

		if (FileReader->ParseFile(szFileName)){
			if (FileReader->GetLineCount() > 0){
				if (FileReader->LongestLine() > 0){
					char *szLineBuffer = new char[(FileReader->LongestLine() + 1)];
					char *szFeatureBuffer = new char[iFeatureDigits + 1];

					m_TruthTable->DeleteTruthTable();
					m_Class = new CClass (FileReader->GetLineCount(), iFeaturesPerLine);	
					m_vClasses.push_back(m_Class);		
					m_TruthTable->CreateTruthTable(GetNumberOfClasses());
					
					for (int i=0;i<FileReader->GetLineCount();i++){
						memset(szLineBuffer, 0, (FileReader->LongestLine() + 1) * sizeof(char));
						FileReader->GetLine(i, szLineBuffer, FileReader->LongestLine());
											
						for (int j=0;j<m_Class->GetNumberOfFeaturesPerPattern();j++){
							memset(szFeatureBuffer, 0, (iFeatureDigits + 1) * sizeof(char));
							strncpy(szFeatureBuffer, szLineBuffer + ((iFeatureDigits + 1) * j), iFeatureDigits);
							m_Class->GetPattern(i)->GetFeature(j)->SetFeatureValue(atof(szFeatureBuffer));
						}
					}

					delete [] szFeatureBuffer;
					szFeatureBuffer = NULL;
					delete [] szLineBuffer;
					szLineBuffer = NULL;
				}
			}
			FileReader->Clear();
		}

		delete FileReader;
		FileReader = NULL;
	}

}

void CDataSet::AddClassFromFile (char *szFileName){

	m_Class = NULL;

	int iFeatureCounter = 0;
	int iPatternCounter = 0;
	CDataTokenizer *DataTokenizer = new CDataTokenizer[3];
	CFileReader *FileReader = new CFileReader();
	CPattern *Pattern = NULL;
	CFeature *Feature = NULL;

	if (FileReader->ReadFile(szFileName)){		
		if (FileReader->GetFileSize() > 0){
			m_TruthTable->DeleteTruthTable();
			m_Class = new CClass (1, 1);
			m_Class->RemoveAllPatterns();
			m_vClasses.push_back(m_Class);		
			m_TruthTable->CreateTruthTable(GetNumberOfClasses());
			DataTokenizer[0].m_bDelimitersInSequence = true;
			char* pRow = DataTokenizer[0].GetFirst(FileReader->GetFileData(), "\r\n");
			while(pRow){
				Pattern = new CPattern(1);
				Pattern->RemoveAllFeatures();
				m_Class->AddPattern(Pattern, -1);
				delete Pattern;
				Pattern = NULL;
				char* pCol = DataTokenizer[1].GetFirst(pRow, "\t");
				while(pCol){
					char* pToken = DataTokenizer[2].GetFirst(pCol, DELIMITERS);
					while(pToken){
						Feature = new CFeature();
						Feature->SetFeatureValue(atof(pToken));
						m_Class->GetPattern(iPatternCounter)->AddFeature(Feature);
						delete Feature;
						Feature = NULL;
						pToken = DataTokenizer[2].GetNext(DELIMITERS);
					}
					pCol = DataTokenizer[1].GetNext("\t");
				}
				pRow = DataTokenizer[0].GetNext("\r\n");
				iPatternCounter++;
			}
		}
		FileReader->Clear();
	}

	delete FileReader;
	FileReader = NULL;
	delete [] DataTokenizer;
	DataTokenizer = NULL;
	
}

void CDataSet::InsertClassAt (CClass *pClass, int iDataSetIndex){

	if ((pClass) && (pClass->GetNumberOfPatterns() > 0) && (pClass->GetNumberOfFeaturesPerPattern() > 0) && (iDataSetIndex < GetNumberOfClasses())){
		std::vector<CClass*>::iterator it = m_vClasses.begin() + iDataSetIndex;		
		m_TruthTable->DeleteTruthTable();
		m_vClasses.insert(it, pClass);		
		m_TruthTable->CreateTruthTable(GetNumberOfClasses());
	}
	
}

CClass *CDataSet::GetClass (int iClass){

	if (iClass > GetNumberOfClasses()){
		return NULL;
	}

	return (CClass *)m_vClasses[iClass];

}

void CDataSet::RemoveClass (int iClass){

	CClass *Class = NULL;
	Class = GetClass(iClass);
	Class->DeleteClass ();
	delete Class;
	Class = NULL;

	std::vector<CClass*>::iterator it = m_vClasses.begin() + iClass;
	m_vClasses.erase(it);

}

void CDataSet::RemoveAllClasses (void){

	CClass *Class = NULL;

	for (int i=0;i<GetNumberOfClasses();i++){
		Class = GetClass(i);
		Class->DeleteClass ();
		delete Class;
		Class = NULL;
	}

	if (!m_vClasses.empty()){
		m_vClasses.clear();
	}

}

CDataSet *CDataSet::CopyDataSet (void){

	CDataSet *CoppiedDataSet = new CDataSet ();
	int i, j, k;

	for (i=0;i<GetNumberOfClasses();i++){
		CoppiedDataSet->m_TruthTable->DeleteTruthTable();
		m_Class = new CClass (GetClass(i)->GetNumberOfPatterns(), GetClass(i)->GetNumberOfFeaturesPerPattern());	
		CoppiedDataSet->m_vClasses.push_back(m_Class);		
		CoppiedDataSet->m_TruthTable->CreateTruthTable(GetNumberOfClasses());
	}

	for (i=0;i<GetNumberOfClasses();i++){
		for (j=0;j<GetClass(i)->GetNumberOfPatterns();j++){
			for (k=0;k<GetClass(i)->GetNumberOfFeaturesPerPattern();k++){
				CoppiedDataSet->GetClass(i)->GetPattern(j)->GetFeature(k)->SetFeatureValue(GetClass(i)->GetPattern(j)->GetFeature(k)->GetFeatureValue());
			}
			CoppiedDataSet->GetClass(i)->GetPattern(j)->SetReservedValue(GetClass(i)->GetPattern(j)->GetReservedValue());
		}
		CoppiedDataSet->GetClass(i)->SetClassShape(GetClass(i)->GetClassShape());
	}

	return CoppiedDataSet;

}

void CDataSet::CopyDataSet (CDataSet *pDataSetDest, CDataSet *pDataSetSrc){

	if (pDataSetDest->GetNumberOfClasses() != pDataSetSrc->GetNumberOfClasses()){
		return;
	}

	CTruthTable::CopyTruthTable(pDataSetDest->GetTruthTable(), pDataSetSrc->GetTruthTable());

	for (int i=0;i<pDataSetDest->GetNumberOfClasses();i++){
		CClass::CopyClass(pDataSetDest->GetClass(i), pDataSetSrc->GetClass(i));
	}

}

CDataSet *CDataSet::CopyDataSetFromCombination (CCombination *pCombination){

	if ((pCombination == NULL) || (pCombination->GetCombinationVectorSize() == 0)){
		return NULL;
	}
	
	CDataSet *CoppiedDataSet = new CDataSet ();
	int i, j, k;

	for (i=0;i<GetNumberOfClasses();i++){
		CoppiedDataSet->m_TruthTable->DeleteTruthTable();
		m_Class = new CClass (GetClass(i)->GetNumberOfPatterns(), pCombination->GetCombinationVectorSize());	
		CoppiedDataSet->m_vClasses.push_back(m_Class);		
		CoppiedDataSet->m_TruthTable->CreateTruthTable(GetNumberOfClasses());
	}

	for (i=0;i<GetNumberOfClasses();i++){
		for (j=0;j<GetClass(i)->GetNumberOfPatterns();j++){
			for (k=0;k<pCombination->GetCombinationVectorSize();k++){
				CoppiedDataSet->GetClass(i)->GetPattern(j)->GetFeature(k)->SetFeatureValue(GetClass(i)->GetPattern(j)->GetFeature(pCombination->GetCombinationVectorValue(k))->GetFeatureValue());
				CoppiedDataSet->GetClass(i)->GetPattern(j)->SetReservedValue(GetClass(i)->GetPattern(j)->GetReservedValue());
			}
		}
	}

	return CoppiedDataSet;

}

CClass *CDataSet::MergeDataSet (void){

	int iTotalNumberOfPatterns = 0;
	int i, j, k;
	int iPatternMergingIndex = 0;
	
	for (i=0;i<GetNumberOfClasses();i++){
		iTotalNumberOfPatterns = iTotalNumberOfPatterns + GetClass(i)->GetNumberOfPatterns();
	}
	
	for (i=0;i<GetNumberOfClasses();i++){
		if (GetClass(0)->GetNumberOfFeaturesPerPattern() !=  GetClass(i)->GetNumberOfFeaturesPerPattern()){
			return NULL;
		}
	}

	CClass *MergedClass = new CClass(iTotalNumberOfPatterns, GetClass(0)->GetNumberOfFeaturesPerPattern());

	for (i=0;i<GetNumberOfClasses();i++){
		for (j=0;j<GetClass(i)->GetNumberOfPatterns();j++){
			for (k=0;k<GetClass(0)->GetNumberOfFeaturesPerPattern();k++){
				MergedClass->GetPattern(iPatternMergingIndex + j)->GetFeature(k)->SetFeatureValue(GetClass(i)->GetPattern(j)->GetFeature(k)->GetFeatureValue());
				MergedClass->GetPattern(iPatternMergingIndex + j)->SetReservedValue(GetClass(i)->GetPattern(j)->GetReservedValue());
			}
		}
		iPatternMergingIndex = iPatternMergingIndex + GetClass(i)->GetNumberOfPatterns();
	}
	
	return MergedClass;
	
}

CDataSet *CDataSet::NormalizeDataSet (void){
		
	int i, j, k;
	double dblNormalizedFeatureValue = 0.0f;
	
	CDataSet *NormalizedDataSet = CopyDataSet();
	CClass *MergedClass = NormalizedDataSet->MergeDataSet();
	CMeanValue *FeaturesMeanValues = new CMeanValue[MergedClass->GetNumberOfFeaturesPerPattern()];
	CStandardDeviation *FeaturesStandardDeviation = new CStandardDeviation[MergedClass->GetNumberOfFeaturesPerPattern()];

	for (i=0;i<MergedClass->GetNumberOfFeaturesPerPattern();i++){
		FeaturesMeanValues[i].CalculateFeaturesMeanValue (MergedClass, i);
		FeaturesStandardDeviation[i].CalculateFeaturesStandardDeviation(MergedClass, FeaturesMeanValues[i].GetMeanValue(), i);
	}

	for (i=0;i<GetNumberOfClasses();i++){
		for (j=0;j<GetClass(i)->GetNumberOfPatterns();j++){
			for (k=0;k<GetClass(i)->GetNumberOfFeaturesPerPattern();k++){
				dblNormalizedFeatureValue = (GetClass(i)->GetPattern(j)->GetFeature(k)->GetFeatureValue() - FeaturesMeanValues[k].GetMeanValue()) / FeaturesStandardDeviation[k].GetStandardDeviation();
				NormalizedDataSet->GetClass(i)->GetPattern(j)->GetFeature(k)->SetFeatureValue(dblNormalizedFeatureValue);
			}
		}
	}

	delete [] FeaturesMeanValues;
	FeaturesMeanValues = NULL;
	delete [] FeaturesStandardDeviation;
	FeaturesStandardDeviation = NULL;
	delete MergedClass;
	MergedClass = NULL;
	
	return NormalizedDataSet;

}

#ifdef USE_XML_SUPPORT

void CDataSet::ExportDataSetToXMLFile (char *szFileName){

	int i, j, k;
	CXmlWriter *XmlExporter = new CXmlWriter (szFileName);
	char *szTempStr = new char [1024];
	char *szTempStr2 = new char [1024];

	XmlExporter->AddComment("Created with DataSet XML Exporter");
	XmlExporter->CreateTag("DataSet");
	
	memset(szTempStr, 0, 1024 * sizeof(char));
	sprintf(szTempStr, "%d", GetNumberOfClasses());
	XmlExporter->CreateChild("NumberOfClasses", szTempStr);

	XmlExporter->CreateTag("Classes");

	for (i=0;i<GetNumberOfClasses();i++){	
		memset(szTempStr, 0, 1024 * sizeof(char));
		sprintf(szTempStr, "Class%d", i);
		XmlExporter->CreateTag(szTempStr);
		
		memset(szTempStr, 0, 1024 * sizeof(char));
		sprintf(szTempStr, "%d", GetClass(i)->GetNumberOfPatterns());
		XmlExporter->CreateChild("NumberOfPatterns", szTempStr);

		memset(szTempStr, 0, 1024 * sizeof(char));
		sprintf(szTempStr, "%d", GetClass(i)->GetNumberOfFeaturesPerPattern());
		XmlExporter->CreateChild("NumberOfFeaturesPerPattern", szTempStr);
		
		XmlExporter->CreateTag("Patterns");
		
		for (j=0;j<GetClass(i)->GetNumberOfPatterns();j++){
			memset(szTempStr, 0, 1024 * sizeof(char));
			sprintf(szTempStr, "Pattern%d", j);	
			XmlExporter->CreateTag(szTempStr);
			for (k=0;k<GetClass(i)->GetNumberOfFeaturesPerPattern();k++){				
				memset(szTempStr, 0, 1024 * sizeof(char));
				sprintf(szTempStr, "%.9lf", GetClass(i)->GetPattern(j)->GetFeature(k)->GetFeatureValue());
				memset(szTempStr2, 0, 1024 * sizeof(char));
				sprintf(szTempStr2, "Feature%d", k);
				XmlExporter->CreateChild(szTempStr2, szTempStr);		 
			}
			XmlExporter->CloseLastTag();
		}
		
		XmlExporter->CloseLastTag();
		XmlExporter->CloseLastTag();
	}

	XmlExporter->CloseAllTags();
	
	delete [] szTempStr;
	szTempStr = NULL;

	delete [] szTempStr2;
	szTempStr2 = NULL;

	delete XmlExporter;
	XmlExporter = NULL;

}

CDataSet *CDataSet::ImportDataSetFromXMLFile (char *szFileName){

	CXmlReader *XmlImporter = new CXmlReader(szFileName);
	XMLNode *RootNode = NULL;
	XMLNode *ClassesNode = NULL;
	XMLNode *ClassNode = NULL;
	XMLNode *PatternsNode = NULL;
	XMLNode *PatternNode = NULL;

	int iNumberOfClasses = 0;
	int iNumberOfPatternsPerClass = 0;
	int iNumberOfFeaturesPerPattern = 0;
	int iClassCounter = 0;
	int iPatternCounter = 0;

	int i;
	char *szFeatureTag = new char [50];

	int iObjectCount = XMLNode::GetObjectCnt();
	if (iObjectCount == 0){
		delete XmlImporter;
		XmlImporter = NULL;
		return NULL;
	}
	
	CDataSet *ImportedDataSet = new CDataSet ();
	CClass *Class = NULL;

	RootNode = XmlImporter->GetRootNode();
	iNumberOfClasses = atoi(RootNode->GetElementValue("NumberOfClasses").c_str());
	if (iNumberOfClasses == 0){
		delete XmlImporter;
		XmlImporter = NULL;
		return NULL;
	}

	ClassesNode = RootNode->GetFirstChild(); 
	
	while (ClassesNode != NULL){
		ClassNode = ClassesNode->GetFirstChild();		
		iClassCounter = 0;
		while (ClassNode != NULL){
		
			iNumberOfPatternsPerClass = atoi(ClassNode->GetElementValue("NumberOfPatterns").c_str());
			if (iNumberOfPatternsPerClass == 0){
				delete XmlImporter;
				XmlImporter = NULL;
				return NULL;
			}
			iNumberOfFeaturesPerPattern = atoi(ClassNode->GetElementValue("NumberOfFeaturesPerPattern").c_str());
			if (iNumberOfFeaturesPerPattern == 0){
				delete XmlImporter;
				XmlImporter = NULL;
				return NULL;
			}

			ImportedDataSet->GetTruthTable()->DeleteTruthTable();
			Class = new CClass (iNumberOfPatternsPerClass, iNumberOfFeaturesPerPattern);	
			ImportedDataSet->m_vClasses.push_back(Class);		
			ImportedDataSet->GetTruthTable()->CreateTruthTable(ImportedDataSet->GetNumberOfClasses());

			PatternsNode = ClassNode->GetFirstChild();
			if (PatternsNode != NULL){
				PatternNode = PatternsNode->GetFirstChild();
				iPatternCounter = 0;
				while (PatternNode != NULL){
					for (i=0;i<iNumberOfFeaturesPerPattern;i++){
						memset(szFeatureTag, 0, 50 * sizeof(char));
						sprintf(szFeatureTag, "Feature%d", i);
						ImportedDataSet->GetClass(iClassCounter)->GetPattern(iPatternCounter)->GetFeature(i)->SetFeatureValue(atof(PatternNode->GetElementValue(szFeatureTag).c_str()));
					}
					iPatternCounter++;
					PatternNode = PatternsNode->GetNextChild();
				}
			}
			iClassCounter++;
			ClassNode = ClassesNode->GetNextChild();		
		}
		ClassesNode = RootNode->GetNextChild();		
	}

	XmlImporter->ResetReading(); 
	XmlImporter->DeleteAll();
	
	delete [] szFeatureTag;
	szFeatureTag = NULL;
	
	delete XmlImporter;
	XmlImporter = NULL;

	return ImportedDataSet;

}

#endif

void CDataSet::WriteDataSetDataToFile (char *szFileNamePattern, char *szExtension){

	char szFileName[255];
	
	for (int i=0;i<GetNumberOfClasses();i++){
		sprintf(szFileName, "%s%d%s", szFileNamePattern, (i + 1), szExtension);
		GetClass(i)->WriteClassDataToFile(szFileName);
	}

}
