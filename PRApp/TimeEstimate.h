#if !defined(AFX_TIMEESTIMATE_H__D5802FEC_6C9F_4F1B_82BA_262739AAC4C1__INCLUDED_)
#define AFX_TIMEESTIMATE_H__D5802FEC_6C9F_4F1B_82BA_262739AAC4C1__INCLUDED_

#include <stdio.h>
#include <time.h>
#include <string.h>

class CTimeSpanEx  
{
public:
	CTimeSpanEx() { m_timeSpan = 0; }
	CTimeSpanEx(time_t time) { m_timeSpan = time; }
	CTimeSpanEx(long lDays, int nHours, int nMins, int nSecs) { m_timeSpan = nSecs + 60* (nMins + 60* (nHours + 24* lDays)); }
	CTimeSpanEx(const CTimeSpanEx& timeSpanSrc) { m_timeSpan = timeSpanSrc.m_timeSpan; }

	const CTimeSpanEx& operator=(const CTimeSpanEx& timeSpanSrc) { m_timeSpan = timeSpanSrc.m_timeSpan; return *this; }
	CTimeSpanEx operator-(CTimeSpanEx timeSpan) const { return CTimeSpanEx(m_timeSpan - timeSpan.m_timeSpan); }
	CTimeSpanEx operator+(CTimeSpanEx timeSpan) const { return CTimeSpanEx(m_timeSpan + timeSpan.m_timeSpan); }
	const CTimeSpanEx& operator+=(CTimeSpanEx timeSpan) { m_timeSpan += timeSpan.m_timeSpan; return *this; }
	const CTimeSpanEx& operator-=(CTimeSpanEx timeSpan) { m_timeSpan -= timeSpan.m_timeSpan; return *this; }
	bool operator==(CTimeSpanEx timeSpan) const { return m_timeSpan == timeSpan.m_timeSpan; }
	bool operator!=(CTimeSpanEx timeSpan) const { return m_timeSpan != timeSpan.m_timeSpan; }
	bool operator<(CTimeSpanEx timeSpan) const { return m_timeSpan < timeSpan.m_timeSpan; }
	bool operator>(CTimeSpanEx timeSpan) const { return m_timeSpan > timeSpan.m_timeSpan; }
	bool operator<=(CTimeSpanEx timeSpan) const { return m_timeSpan <= timeSpan.m_timeSpan; }
	bool operator>=(CTimeSpanEx timeSpan) const { return m_timeSpan >= timeSpan.m_timeSpan; }

	long GetDays() const { return m_timeSpan / (24 * 3600); }
	long GetTotalHours() const { return m_timeSpan / 3600; }
	int GetHours() const { return (int)(GetTotalHours() - GetDays() * 24); }
	long GetTotalMinutes() const { return m_timeSpan / 60; }
	int GetMinutes() const { return (int)(GetTotalMinutes() - GetTotalHours() * 60); }
	long GetTotalSeconds() const { return m_timeSpan; }
	int GetSeconds() const { return (int)(GetTotalSeconds() - GetTotalMinutes() * 60); }

protected:

	long m_timeSpan;

};

class CTimeEstimate  
{
public:
	CTimeEstimate();
	virtual ~CTimeEstimate();

	void StartProcess (void);
	void PauseProcess (void);
	void ResumeProcess (void);
	void StopProcess (void);
	void GetProcessEstimatedTime (char *szEstimatedTime);
	void SetProcessSize (double dblProcessSize);
	void OffsetProcessPosition (double dblOffset);
	double GetProcessSize (void);

protected:

	int m_nLastTotalSeconds;
	double m_dblProcessSize;
	char m_szEstimatedTime[50];
	double m_dblDonePart;
	double m_dblCounter;
	double m_dblCycleSize;
	time_t m_tmStartTime;
	CTimeSpanEx m_ElapsedTime;
	
};

#endif 
