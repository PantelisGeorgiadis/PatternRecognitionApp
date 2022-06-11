#include "stdafx.h"
#include "Combination.h"

CCombination::CCombination()
{

	m_iCombinationVectorSize = 0;
	m_iCombinationVector = NULL;

}

CCombination::CCombination(int iCombinationVectorSize)
{

	CreateCombination(iCombinationVectorSize);

}

CCombination::~CCombination()
{

	DeleteCombination();

}

void CCombination::CreateCombination (int iCombinationVectorSize){

	m_iCombinationVectorSize = iCombinationVectorSize;

	if (iCombinationVectorSize > 0){
		m_iCombinationVector = new int [iCombinationVectorSize];
		for (int i=0;i<iCombinationVectorSize;i++){
			m_iCombinationVector[i] = 0;
		}
	}

}

void CCombination::DeleteCombination (void){

	delete [] m_iCombinationVector;
	m_iCombinationVector = NULL;

}

void CCombination::SetCombinationVectorValue (int CombinationVectorIndex, int iValue){

	if (CombinationVectorIndex > GetCombinationVectorSize()){
		return;
	}

	m_iCombinationVector[CombinationVectorIndex] = iValue;

}

int CCombination::GetCombinationVectorValue (int CombinationVectorIndex){

	if (CombinationVectorIndex > GetCombinationVectorSize()){
		return -1;
	}

	return m_iCombinationVector[CombinationVectorIndex];

}

CCombination *CCombination::CopyCombination (void){

	CCombination *Combination = new CCombination(GetCombinationVectorSize());
	
	for (int i=0;i<GetCombinationVectorSize();i++){
		Combination->SetCombinationVectorValue(i, GetCombinationVectorValue(i));
	}

	return Combination;

}
