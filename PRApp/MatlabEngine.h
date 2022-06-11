#if !defined(AFX_MATLABENGINE_H__37037FBF_0913_4865_A528_8D0B42C042E5__INCLUDED_)
#define AFX_MATLABENGINE_H__37037FBF_0913_4865_A528_8D0B42C042E5__INCLUDED_

#include "Globals.h"

#ifdef USE_MATLAB_ENGINE

#include <Engine.h>
#pragma comment(lib, "libeng.lib")
#pragma comment(lib, "libmx.lib")
#pragma comment(lib, "libmat.lib")

class CMatlabEngine  
{
public:
	
	CMatlabEngine();
	virtual ~CMatlabEngine();

	int OutputBuffer(char *p, int n);
	void OpenSingleUse(const char *startcmd, void *dcom, int *retstatus);
	int GetVisible(bool *value);
	int SetVisible(bool value);
	mxArray* GetVariable(const char *szName);
	int PutVariable(const char *szName, const mxArray *mp);
	int EvalString(const char *szString);
	void Open(const char *szStartCmd);
	int Close();

protected:
	
	Engine *m_pEngine;

};

#endif

#endif 
