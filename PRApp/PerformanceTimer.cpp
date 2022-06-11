#include "stdafx.h"
#include "PerformanceTimer.h"

#ifdef USE_PERFORMANCETIMER

__int64 CPerformanceTimer::m_Freq = 0; 
__int64 CPerformanceTimer::m_Adjust = 0; 

bool CPerformanceTimer::IsSupported()
{
	
	return (m_Freq > 1);
	
}

const double CPerformanceTimer::Resolution (void)
{
	
	return 1.0f / (double)m_Freq;
	
}

const double CPerformanceTimer::Resolutionms (void)
{
	
	return 1000.0f / (double)m_Freq;
	
}

const double CPerformanceTimer::Resolutionus (void)
{ 
	
	return 1000000.0f / (double)m_Freq;
	
}

#endif
