#include "stdafx.h"
#include "DataCoOccurrenceMatrix3D.h"

#define PIXELNEIGHBOURDISTANCE 1

int iOffsets[13][3] =   { 
						0,							PIXELNEIGHBOURDISTANCE,		0,
						-PIXELNEIGHBOURDISTANCE,	0,							0,
						0,							0,							-PIXELNEIGHBOURDISTANCE,

						-PIXELNEIGHBOURDISTANCE,	PIXELNEIGHBOURDISTANCE,		0,
						-PIXELNEIGHBOURDISTANCE,	-PIXELNEIGHBOURDISTANCE,	0,

						-PIXELNEIGHBOURDISTANCE,	0,							-PIXELNEIGHBOURDISTANCE,
						-PIXELNEIGHBOURDISTANCE,	0,							PIXELNEIGHBOURDISTANCE,

						0,							PIXELNEIGHBOURDISTANCE,		PIXELNEIGHBOURDISTANCE,
						0,							-PIXELNEIGHBOURDISTANCE,	PIXELNEIGHBOURDISTANCE,

						-PIXELNEIGHBOURDISTANCE,	PIXELNEIGHBOURDISTANCE,		PIXELNEIGHBOURDISTANCE,
						-PIXELNEIGHBOURDISTANCE,	-PIXELNEIGHBOURDISTANCE,	PIXELNEIGHBOURDISTANCE,
						PIXELNEIGHBOURDISTANCE,		PIXELNEIGHBOURDISTANCE,		PIXELNEIGHBOURDISTANCE,
						PIXELNEIGHBOURDISTANCE,		-PIXELNEIGHBOURDISTANCE,	PIXELNEIGHBOURDISTANCE
						};


CDataCoOccurrenceMatrix3D::CDataCoOccurrenceMatrix3D()
{

	m_pDataCoOccurrenceMatrixes = NULL;
	CreateDataCoOccurrenceMatrixes();

}

CDataCoOccurrenceMatrix3D::~CDataCoOccurrenceMatrix3D()
{

	DeleteDataCoOccurrenceMatrixes();

}

void CDataCoOccurrenceMatrix3D::CreateDataCoOccurrenceMatrixes (void){

	m_pDataCoOccurrenceMatrixes = new CDataMatrix2D[13];

}

void CDataCoOccurrenceMatrix3D::DeleteDataCoOccurrenceMatrixes (void){

	if (m_pDataCoOccurrenceMatrixes != NULL){
		delete [] m_pDataCoOccurrenceMatrixes;
		m_pDataCoOccurrenceMatrixes = NULL;
	}

}

void CDataCoOccurrenceMatrix3D::FillDataCoOccurrenceMatrixes (CDataMatrix3D *pDataMatrix3D, int iDepth){

	int i, j, k, m, l;
	int iIndex1 = 0; int iIndex2 = 0;

	CDataMatrix2D *DataCoOccurrenceMatrixesPositiveDirections = new CDataMatrix2D[13];
	CDataMatrix2D *DataCoOccurrenceMatrixesNegativeDirections = new CDataMatrix2D[13];

	for (i=0;i<13;i++){
		m_pDataCoOccurrenceMatrixes[i].CreateDataMatrix(iDepth, iDepth);
		DataCoOccurrenceMatrixesPositiveDirections[i].CreateDataMatrix(iDepth, iDepth);
		DataCoOccurrenceMatrixesNegativeDirections[i].CreateDataMatrix(iDepth, iDepth);
	}

	int *iTmpOffsets = new int[3];

	for (m=0;m<13;m++){

		for (l=0;l<3;l++){
			iTmpOffsets[l] = iOffsets[m][l];
		}

		for (k=0;k<pDataMatrix3D->GetNumberOfLayers();k++){
			for (j=0;j<pDataMatrix3D->GetNumberOfColumns();j++){
				for (i=0;i<pDataMatrix3D->GetNumberOfRows();i++){

					if ((i + iTmpOffsets[0] < 0) || (i + iTmpOffsets[0] >= pDataMatrix3D->GetNumberOfRows()) ||
						(j + iTmpOffsets[1] < 0) || (j + iTmpOffsets[1] >= pDataMatrix3D->GetNumberOfColumns()) ||
						(k + iTmpOffsets[2] < 0) || (k + iTmpOffsets[2] >= pDataMatrix3D->GetNumberOfLayers())
						)
					{
						continue;
					}

					iIndex1 = (int)pDataMatrix3D->GetMatrixValue(k, i, j);
					iIndex2 = (int)pDataMatrix3D->GetMatrixValue((k + iTmpOffsets[2]), (i + iTmpOffsets[0]), (j + iTmpOffsets[1]));
					
					DataCoOccurrenceMatrixesPositiveDirections[m].SetMatrixValue(iIndex1, iIndex2, DataCoOccurrenceMatrixesPositiveDirections[m].GetMatrixValue(iIndex1, iIndex2) + 1.0f);

				}
			}
		}

	}

	for (m=0;m<13;m++){

		for (l=0;l<3;l++){
			iTmpOffsets[l] = -1 * (iOffsets[m][l]);
		}

		for (k=0;k<pDataMatrix3D->GetNumberOfLayers();k++){
			for (j=0;j<pDataMatrix3D->GetNumberOfColumns();j++){
				for (i=0;i<pDataMatrix3D->GetNumberOfRows();i++){

					if ((i + iTmpOffsets[0] < 0) || (i + iTmpOffsets[0] >= pDataMatrix3D->GetNumberOfRows()) ||
						(j + iTmpOffsets[1] < 0) || (j + iTmpOffsets[1] >= pDataMatrix3D->GetNumberOfColumns()) ||
						(k + iTmpOffsets[2] < 0) || (k + iTmpOffsets[2] >= pDataMatrix3D->GetNumberOfLayers())
						)
					{
						continue;
					}

					iIndex1 = (int)pDataMatrix3D->GetMatrixValue(k, i, j);
					iIndex2 = (int)pDataMatrix3D->GetMatrixValue((k + iTmpOffsets[2]), (i + iTmpOffsets[0]), (j + iTmpOffsets[1]));
					
					DataCoOccurrenceMatrixesNegativeDirections[m].SetMatrixValue(iIndex1, iIndex2, DataCoOccurrenceMatrixesNegativeDirections[m].GetMatrixValue(iIndex1, iIndex2) + 1.0f);

				}
			}
		}

	}

	for (m=0;m<13;m++){
		for (i=0;i<m_pDataCoOccurrenceMatrixes[m].GetNumberOfRows();i++){
			for (j=0;j<m_pDataCoOccurrenceMatrixes[m].GetNumberOfColumns();j++){
				m_pDataCoOccurrenceMatrixes[m].SetMatrixValue(i, j, (DataCoOccurrenceMatrixesPositiveDirections[m].GetMatrixValue(i, j) + DataCoOccurrenceMatrixesNegativeDirections[m].GetMatrixValue(i, j)));
			}
		}
	}

	delete [] iTmpOffsets;
	iTmpOffsets = NULL;
	delete [] DataCoOccurrenceMatrixesNegativeDirections;
	DataCoOccurrenceMatrixesNegativeDirections = NULL;
	delete [] DataCoOccurrenceMatrixesPositiveDirections;
	DataCoOccurrenceMatrixesPositiveDirections = NULL;

}

CDataMatrix2D *CDataCoOccurrenceMatrix3D::GetDataCoOccurrenceMatrix (int iIndex){

	CDataMatrix2D *DataMatrix2D = NULL;
	
	DataMatrix2D = m_pDataCoOccurrenceMatrixes[iIndex].CopyDataMatrix2D();

	return DataMatrix2D;

}
