#include "CoreLib/Core.h"
#include "CoreLib/PerformanceTimer.h"
using namespace ZGE;
CPerformanceTimer::CPerformanceTimer(const char* _kpcPerformanceTarget )
: m_kpcPerformanceTarget( _kpcPerformanceTarget )
{
	// Initialise the clock.
	m_PerformanceTimer.Initialise( );

	// Update the clock so that it has the current time.
	m_PerformanceTimer.Process( );
}

CPerformanceTimer::~CPerformanceTimer(void)
{
	// Update the clock.
	m_PerformanceTimer.Process( );

	// Get the time that has elapsed. 
	const float32 kfTimeElapsed = m_PerformanceTimer.GetDeltaTick( );

	// Print to the out put window.
	char pBuffer[256];
	STR_PRINT( pBuffer, 256," Profiled: %s, Time: %.07f", m_kpcPerformanceTarget, kfTimeElapsed );
	//ZUtilities::StrPrint( pBuffer, "Profiled: %s, Time: %f.03f", 256, m_kpcPerformanceTarget, kfTimeElapsed );
#ifdef Z_PLATFORM_WIN
	OutputDebugStringA( pBuffer );
#endif
}
