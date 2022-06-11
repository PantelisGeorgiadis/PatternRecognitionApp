#include "stdafx.h"
#include "TimeEstimate.h"

CTimeEstimate::CTimeEstimate()
{

	m_dblCounter = 0;
	m_dblCycleSize = 1;
	m_dblDonePart = 0;
	m_tmStartTime = 0;
	m_dblProcessSize = 0;
	m_ElapsedTime = 0;
	m_nLastTotalSeconds = 0;
	memset(m_szEstimatedTime, 0, 50 * sizeof(char));

}

CTimeEstimate::~CTimeEstimate()
{

}

void CTimeEstimate::GetProcessEstimatedTime (char *szEstimatedTime){

	if (szEstimatedTime){
		strcpy(szEstimatedTime, m_szEstimatedTime);
	}

}

void CTimeEstimate::SetProcessSize (double dblProcessSize){
	
	m_dblProcessSize = dblProcessSize;

}

void CTimeEstimate::StartProcess (void){
	
	time(&m_tmStartTime);
	m_dblDonePart = 0;

}

void CTimeEstimate::PauseProcess (void){

	time_t tmCurrentTime;
	time(&tmCurrentTime);
	m_ElapsedTime += tmCurrentTime - m_tmStartTime;

}

void CTimeEstimate::StopProcess (void){

	m_dblCounter = 0;
	m_nLastTotalSeconds = 0;
	m_ElapsedTime = 0;
	m_ElapsedTime = 0;
	m_dblCycleSize = 1;
	memset(m_szEstimatedTime, 0, 50 * sizeof(char));

}

void CTimeEstimate::OffsetProcessPosition (double dblOffset){
	
	m_dblCounter += dblOffset;
	m_dblDonePart += dblOffset;
	time_t tmCurrentTime;
	time(&tmCurrentTime);
	CTimeSpanEx LastTimeInterval(tmCurrentTime - m_tmStartTime);
	LastTimeInterval += m_ElapsedTime;
	long lTotalElapsedSec = LastTimeInterval.GetTotalSeconds();

	if ((lTotalElapsedSec > 1) && (lTotalElapsedSec - m_nLastTotalSeconds > 0)){
		if (m_dblCounter >= m_dblCycleSize){
			m_dblCounter = 0;
			m_dblCycleSize = m_dblDonePart / lTotalElapsedSec;
			m_nLastTotalSeconds = lTotalElapsedSec;
			double dRemainingSecs = ((m_dblProcessSize - m_dblDonePart) * lTotalElapsedSec) / m_dblDonePart;
			CTimeSpanEx TempSpan((long)dRemainingSecs);
			sprintf(m_szEstimatedTime, "%02d:%02d:%02d", TempSpan.GetHours(), TempSpan.GetMinutes(), TempSpan.GetSeconds());
		}
	}

}

void CTimeEstimate::ResumeProcess (void){

	time(&m_tmStartTime);

}

double CTimeEstimate::GetProcessSize (void){
	
	return m_dblProcessSize;

}
