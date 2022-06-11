#ifndef __PERFORMANCETIMER_H__
#define __PERFORMANCETIMER_H__

#include "Globals.h"

#ifdef USE_PERFORMANCETIMER

#include <windows.h>
#include <tchar.h>

class CPerformanceTimer
{
public:
	
	CPerformanceTimer(bool bStart = false) { Init(bStart); }
	
	CPerformanceTimer(const CPerformanceTimer& Src); 
	
	virtual ~CPerformanceTimer() {;}
	
	void Start(bool bReset = false);
	void Stop();
	bool IsRunning();
	bool IsSupported();
	
	const double Resolution();         
	const double Resolutionms();       
	const double Resolutionus();       
	
	const double Elapsed();            
	const double Elapsedms();          
	const double Elapsedus();          
	
	const CPerformanceTimer& operator=(const CPerformanceTimer& Src); 
	
	CPerformanceTimer operator+(const CPerformanceTimer& Src) const;
	CPerformanceTimer operator-(const CPerformanceTimer& Src) const;
	const CPerformanceTimer& operator+=(const CPerformanceTimer& Src);
	const CPerformanceTimer& operator-=(const CPerformanceTimer& Src);
	CPerformanceTimer operator+(const double Secs) const;
	CPerformanceTimer operator-(const double Secs) const;
	const CPerformanceTimer& operator+=(const double Secs);
	const CPerformanceTimer& operator-=(const double Secs);
	bool operator<(const CPerformanceTimer& Src);
	bool operator>(const CPerformanceTimer& Src);
	bool operator<=(const CPerformanceTimer& Src);
	bool operator>=(const CPerformanceTimer& Src);
	bool operator<(const double Secs);
	bool operator>(const double Secs);
	bool operator<=(const double Secs);
	bool operator>=(const double Secs);
	
	virtual void Lock() const {;}
	virtual void Unlock() const {;}

protected:
	
	void Init(bool bStart);
	void Copy(const CPerformanceTimer& Src);
	
private:
	
	__int64 m_Start;
	static __int64 m_Freq;
	static __int64 m_Adjust;

};

class CPerformanceTimerT : public CPerformanceTimer
{ 
public:
	
	CPerformanceTimerT(bool bStart = false)
	{
		m_hMutex = CreateMutex(NULL, false, _T(""));
		Init(bStart);
	}
	
	CPerformanceTimerT(const CPerformanceTimerT& Src) 
	{ 
		m_hMutex = CreateMutex(NULL, false, _T(""));
		Copy(Src); 
	}
	
	CPerformanceTimerT(const CPerformanceTimer& Src) 
	{ 
		m_hMutex = CreateMutex(NULL, false, _T(""));
		Copy(Src); 
	}
	
	virtual ~CPerformanceTimerT() { CloseHandle(m_hMutex); }
	
	const CPerformanceTimerT& operator=(const CPerformanceTimerT& Src) 
	{
		Copy(Src);
		return *this; 
	}
	
	virtual void Lock() const { WaitForSingleObject(m_hMutex, 10000); }   
	virtual void Unlock() const { ReleaseMutex(m_hMutex); }   

private:

	HANDLE m_hMutex;

};

inline void CPerformanceTimer::Init(bool bStart)
{
	
	if (!m_Freq){
		QueryPerformanceFrequency((LARGE_INTEGER *)&m_Freq); 
		if (!m_Freq){
			m_Freq = 1;
		}
		m_Start = 0; 
		m_Adjust = 0; 
		Start();
		Stop(); 
		m_Adjust = m_Start;
	}
	
	m_Start = 0; 
	if (bStart){
		Start();
	}

}

inline CPerformanceTimer::CPerformanceTimer(const CPerformanceTimer& Src)  
{
	
	Copy(Src);

}

inline void CPerformanceTimer::Copy(const CPerformanceTimer& Src)
{
	
	if (&Src == this){
		return;
	}
	Src.Lock();
	Lock();
	m_Start = Src.m_Start; 
	Unlock();
	Src.Unlock();

}

inline void CPerformanceTimer::Start(bool bReset) 
{ 
	
	__int64 i;
	QueryPerformanceCounter((LARGE_INTEGER *)&i);
	Lock();
	if ((!bReset) && (m_Start < 0)){
		m_Start += i;
	}
	else{
		m_Start = i;
	}
	Unlock();

} 

inline void CPerformanceTimer::Stop() 
{ 
	
	Lock();
	if (m_Start <= 0){
		Unlock();
		return;
	}
	__int64 i;
	QueryPerformanceCounter((LARGE_INTEGER *)&i); 
	m_Start += -i;        
	if (m_Start < m_Adjust){
		m_Start -= m_Adjust;
	}
	else{ 
		m_Start = 0;
	}
	Unlock();

} 

inline bool CPerformanceTimer::IsRunning() 
{ 
	
	Lock();
	bool bRet = (m_Start > 0);
	Unlock();
	return bRet;   

}

inline const double CPerformanceTimer::Elapsed()
{ 
	
	CPerformanceTimer Result(*this);
	Result.Stop();
	return (double)(-Result.m_Start) / (double)m_Freq; 

}

inline const double CPerformanceTimer::Elapsedms() 
{ 
	
	CPerformanceTimer Result(*this);
	Result.Stop();
	return (-Result.m_Start * 1000.0f) / (double)m_Freq; 

}

inline const double CPerformanceTimer::Elapsedus() 
{ 
	
	CPerformanceTimer Result(*this);
	Result.Stop();
	return (-Result.m_Start * 1000000.0f) / (double)m_Freq; 

}

inline const CPerformanceTimer& CPerformanceTimer::operator=(const CPerformanceTimer& Src) 
{
	
	Copy(Src);
	return *this; 

}

inline CPerformanceTimer CPerformanceTimer::operator+(const CPerformanceTimer& Src) const
{
	
	CPerformanceTimer Result(*this);
	Result += Src; 
	return Result; 

}

inline CPerformanceTimer CPerformanceTimer::operator-(const CPerformanceTimer& Src) const
{
	
	CPerformanceTimer Result(*this);
	Result -= Src; 
	return Result; 

}

inline const CPerformanceTimer& CPerformanceTimer::operator+=(const CPerformanceTimer& Src)
{
	
	CPerformanceTimer SrcStop(Src);
	SrcStop.Stop();
	Lock();
	m_Start += SrcStop.m_Start;
	Unlock();
	return *this; 

}

inline const CPerformanceTimer& CPerformanceTimer::operator-=(const CPerformanceTimer& Src)
{
	
	CPerformanceTimer SrcStop(Src);
	SrcStop.Stop();
	Lock();
	m_Start -= SrcStop.m_Start; 
	Unlock();
	return *this; 

}

inline CPerformanceTimer CPerformanceTimer::operator+(const double Secs) const
{
	
	CPerformanceTimer Result(*this);
	Result += Secs; 
	return Result; 

}

inline CPerformanceTimer CPerformanceTimer::operator-(const double Secs) const
{
	
	CPerformanceTimer Result(*this);
	Result += Secs; 
	return Result; 

}

inline const CPerformanceTimer& CPerformanceTimer::operator+=(const double Secs)
{
	
	Lock();
	m_Start -= (__int64)(Secs*(double)m_Freq);
	Unlock();
	return *this; 

}

inline const CPerformanceTimer& CPerformanceTimer::operator-=(const double Secs)
{
	
	Lock();
	m_Start += (__int64)(Secs*(double)m_Freq);
	Unlock();
	return *this; 

}

inline bool CPerformanceTimer::operator<(const CPerformanceTimer& Src)
{ 
	
	bool bRet; 
	CPerformanceTimer Temp(Src);
	Lock();
	if (m_Start <= 0){
		Temp.Stop();
		bRet = (m_Start > Temp.m_Start); 
		Unlock();
		return bRet;
	}
	else{
		if (Temp.m_Start > 0){
			bRet = (m_Start < Temp.m_Start); 
			Unlock();
			return bRet;
		}
		else{
			Unlock();
			CPerformanceTimer ThisStop(*this);
			ThisStop.Stop();
			return (ThisStop.m_Start > Temp.m_Start); 
		}
	}

}

inline bool CPerformanceTimer::operator>(const CPerformanceTimer& Src)
{ 
	
	bool bRet; 
	CPerformanceTimer Temp(Src);
	Lock();
	if (m_Start <= 0){
		Temp.Stop();
		bRet = (m_Start < Temp.m_Start); 
		Unlock();
		return bRet;
	}
	else{
		if (Temp.m_Start > 0){
			bRet = (m_Start > Temp.m_Start); 
			Unlock();
			return bRet;
		}
		else{
			Unlock();
			CPerformanceTimer ThisStop(*this);
			ThisStop.Stop();
			return (ThisStop.m_Start < Temp.m_Start); 
		}
	}

}

inline bool CPerformanceTimer::operator<=(const CPerformanceTimer& Src)
{ 
	
	return !(*this > Src);

}

inline bool CPerformanceTimer::operator>=(const CPerformanceTimer& Src)
{ 
	
	return !(*this < Src);

}

inline bool CPerformanceTimer::operator<(const double Secs)
{ 
	
	bool bRet; 
	Lock();
	if (m_Start <= 0){
		bRet = (m_Start > (__int64)(-Secs*(double)m_Freq)); 
		Unlock();
		return bRet;
	}
	else{
		Unlock();
		CPerformanceTimer ThisStop(*this);
		ThisStop.Stop();
		return (ThisStop.m_Start > (__int64)(-Secs*(double)m_Freq)); 
	}

}

inline bool CPerformanceTimer::operator>(const double Secs)
{ 
	
	bool bRet; 
	Lock();
	if (m_Start <= 0){
		bRet = (m_Start < (__int64)(-Secs*(double)m_Freq)); 
		Unlock();
		return bRet;
	}
	else{
		Unlock();
		CPerformanceTimer ThisStop(*this);
		ThisStop.Stop();
		return (ThisStop.m_Start < (__int64)(-Secs*(double)m_Freq)); 
	}

}

inline bool CPerformanceTimer::operator<=(const double Secs)
{ 
	
	return !(*this > Secs);

}

inline bool CPerformanceTimer::operator>=(const double Secs)
{ 
	
	return !(*this < Secs);

}

#endif

#endif
