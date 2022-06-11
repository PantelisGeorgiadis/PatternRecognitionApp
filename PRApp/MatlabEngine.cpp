#include "stdafx.h"
#include "MatlabEngine.h"

#ifdef USE_MATLAB_ENGINE

CMatlabEngine::CMatlabEngine()
{

	m_pEngine = NULL;
}

CMatlabEngine::~CMatlabEngine()
{
	
	if (m_pEngine != NULL){
		//Close();
	}

}

void CMatlabEngine::Open(const char *szStartCmd){

	m_pEngine = engOpen(szStartCmd);

}

int CMatlabEngine::Close(void){

	int iResult = engClose(m_pEngine);
	
	if (iResult == 0){
		m_pEngine = NULL;
	}

	return iResult;

}

int CMatlabEngine::EvalString(const char *szString){

	return (engEvalString(m_pEngine, szString));

}

mxArray* CMatlabEngine::GetVariable(const char *szName){

	return (engGetVariable(m_pEngine, szName));

}

int CMatlabEngine::GetVisible(bool *value){

	return (engGetVisible(m_pEngine, value));

}

void CMatlabEngine::OpenSingleUse(const char *startcmd, void *dcom, int *retstatus){

	m_pEngine = engOpenSingleUse(startcmd, dcom, retstatus);

}

int CMatlabEngine::OutputBuffer(char *p, int n){

	return (engOutputBuffer(m_pEngine, p, n));

}

int CMatlabEngine::PutVariable(const char *szName, const mxArray *mp){

	return (engPutVariable(m_pEngine, szName, mp));

}

int CMatlabEngine::SetVisible(bool value){

	return (engSetVisible(m_pEngine, value));

}

#endif
