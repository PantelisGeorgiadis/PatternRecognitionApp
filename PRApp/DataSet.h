#if !defined(AFX_DATASET_H__26E68103_0957_4CDA_B6F3_E770765EEF08__INCLUDED_)
#define AFX_DATASET_H__26E68103_0957_4CDA_B6F3_E770765EEF08__INCLUDED_

#ifndef __GNUC__
#pragma warning(disable : 4786)
#endif

#include <vector>
#include <cmath>

#include "Class.h"
#include "TruthTable.h"
#include "MeanValue.h"
#include "StandardDeviation.h"
#include "FileReader.h"
#include "XmlWriter.h"
#include "XmlReader.h"
#include "Combination.h"
#include "DataTokenizer.h"

typedef std::vector<CClass*> vClasses;

class CDataSet
{
public:
	CDataSet();
	virtual ~CDataSet();

	void AddClass (int iNumberOfPatterns, int iNumberOfFeaturesPerPattern);
	void AddClass (CClass *pClass);
	void AddEmptyClass (void);
	void AddClassFromFile (char *szFileName, int iFeaturesPerLine, int iFeatureDigits);
	void AddClassFromFile (char *szFileName);
	void InsertClassAt (CClass *pClass, int iDataSetIndex);
	void RemoveClass (int iClass);
	void RemoveAllClasses (void);
	CClass *GetClass (int iClass);
	int GetNumberOfClasses(void) { return m_vClasses.size(); }
	CTruthTable *GetTruthTable (void) { if (m_TruthTable){ return m_TruthTable; } return NULL; }
	CDataSet *CopyDataSet (void);
	static void CopyDataSet (CDataSet *pDataSetDest, CDataSet *pDataSetSrc);
	CDataSet *CopyDataSetFromCombination (CCombination *pCombination);
	CClass *MergeDataSet (void);
	CDataSet *NormalizeDataSet (void);
#ifdef USE_XML_SUPPORT
	void ExportDataSetToXMLFile (char *szFileName);
	CDataSet *ImportDataSetFromXMLFile (char *szFileName);
#endif
	void WriteDataSetDataToFile (char *szFileNamePattern, char *szExtension);

protected:

	vClasses m_vClasses;

	CClass *m_Class;
	CTruthTable *m_TruthTable;
	
};

#endif 
