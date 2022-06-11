#include "stdafx.h"
#include "DataMatrix3D.h"

CDataMatrix3D::CDataMatrix3D()
{

	m_DataMatrix2D = NULL;
	m_iNumberOfRows = 0;
	m_iNumberOfColumns = 0;
	m_iNumberOfLayers = 0;

}

CDataMatrix3D::CDataMatrix3D(int iNumberOfRows, int iNumberOfColumns, int iNumberOfLayers)
{

	m_DataMatrix2D = NULL;
	CreateDataMatrix(iNumberOfRows, iNumberOfColumns, iNumberOfLayers);

}

CDataMatrix3D::~CDataMatrix3D()
{

	DeleteDataMatrix();

}

void CDataMatrix3D::CreateDataMatrix (int iNumberOfRows, int iNumberOfColumns, int iNumberOfLayers){

	if ((iNumberOfRows <= 0) || (iNumberOfColumns <= 0) || (iNumberOfLayers <= 0)){
		return;
	}

	m_iNumberOfRows = iNumberOfRows;
	m_iNumberOfColumns = iNumberOfColumns;
	m_iNumberOfLayers = iNumberOfLayers;
	
	for (int i=0;i<iNumberOfLayers;i++){
		m_DataMatrix2D = new CDataMatrix2D (iNumberOfRows, iNumberOfColumns);
		m_vLayers.push_back(m_DataMatrix2D);
	}
	Zeros();

}

void CDataMatrix3D::DeleteDataMatrix (void){
	
	CDataMatrix2D *DataMatrix2D = NULL;

	for (int i=0;i<GetNumberOfLayers();i++){
		DataMatrix2D = GetLayer(i);
		delete DataMatrix2D;
		DataMatrix2D = NULL;
	}

	if (!m_vLayers.empty()){
		m_vLayers.clear();
	}

}

CDataMatrix2D *CDataMatrix3D::GetLayer (int iLayerIndex){

	if (iLayerIndex > GetNumberOfLayers()){
		return NULL;
	}

	return (CDataMatrix2D *)m_vLayers[iLayerIndex];

}

void CDataMatrix3D::Zeros (void){

	for (int i=0;i<GetNumberOfLayers();i++){
		GetLayer(i)->Zeros();
	}

}

CDataMatrix3D *CDataMatrix3D::CopyDataMatrix3D (void){

	CDataMatrix3D *CopiedDataMatrix3D = new CDataMatrix3D(GetNumberOfRows(), GetNumberOfColumns(), GetNumberOfLayers());

	for (int i=0;i<GetNumberOfLayers();i++){
		for (int j=0;j<GetNumberOfRows();j++){
			for (int k=0;k<GetNumberOfColumns();k++){
				CopiedDataMatrix3D->SetMatrixValue(i, j, k, GetMatrixValue(i, j, k));
			}
		}
	}

	return CopiedDataMatrix3D;

}

double CDataMatrix3D::GetMatrixValue (int iLayerIndex, int iRowIndex, int iColumnIndex){

	if ((iLayerIndex > GetNumberOfLayers()) || (iRowIndex > GetNumberOfRows()) || (iColumnIndex > GetNumberOfColumns())){
		return 0.0f;
	}

	return (GetLayer(iLayerIndex)->GetMatrixValue(iRowIndex, iColumnIndex));

}

void CDataMatrix3D::SetMatrixValue (int iLayerIndex, int iRowIndex, int iColumnIndex, double dblValue){

	if ((iLayerIndex > GetNumberOfLayers()) || (iRowIndex > GetNumberOfRows()) || (iColumnIndex > GetNumberOfColumns())){
		return;
	}

	GetLayer(iLayerIndex)->SetMatrixValue(iRowIndex, iColumnIndex, dblValue);

}

CDataMatrix2D *CDataMatrix3D::GetLayerAsDataMatrix2D (int iLayerIndex){

	return GetLayer(iLayerIndex);

}
