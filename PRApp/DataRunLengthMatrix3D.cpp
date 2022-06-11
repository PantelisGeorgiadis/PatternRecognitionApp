#include "stdafx.h"
#include "DataRunLengthMatrix3D.h"

CDataRunLengthMatrix3D::CDataRunLengthMatrix3D()
{

	m_pDataRunLengthMatrixes = NULL;
	CreateDataRunLengthMatrixes();

}

CDataRunLengthMatrix3D::~CDataRunLengthMatrix3D()
{

	DeleteDataRunLengthMatrixes();

}

void CDataRunLengthMatrix3D::CreateDataRunLengthMatrixes (void){

	m_pDataRunLengthMatrixes = new CDataMatrix2D[13];

}

void CDataRunLengthMatrix3D::DeleteDataRunLengthMatrixes (void){

	if (m_pDataRunLengthMatrixes != NULL){
		delete [] m_pDataRunLengthMatrixes;
		m_pDataRunLengthMatrixes = NULL;
	}

}

void CDataRunLengthMatrix3D::FillDataRunLengthMatrixes (CDataMatrix3D *pDataMatrix3D, int iDepth){



}

CDataMatrix2D *CDataRunLengthMatrix3D::GetDataRunLengthMatrix (int iIndex){

	CDataMatrix2D *DataMatrix2D = NULL;
	
	DataMatrix2D = m_pDataRunLengthMatrixes[iIndex].CopyDataMatrix2D();

	return DataMatrix2D;

}
