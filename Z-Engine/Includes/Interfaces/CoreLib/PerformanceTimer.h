#ifndef _PERFORMANCETIMER_H__Included_727605417
#define _PERFORMANCETIMER_H__Included_727605417
#include "CoreLib/Clock.h"
namespace ZGE
{
	/**
	 *	Performace timer.
	 */
	class CPerformanceTimer
	{
	public:
		CPerformanceTimer( const char* _kpcPerformanceTarget );
		~CPerformanceTimer(void);
	protected:
		const char* m_kpcPerformanceTarget;
		CClock		m_PerformanceTimer;
	};
}

#define TIME_FUNCTION( func ) CPerformanceTimer( #func );
#define PERFORMANCE_TIMER( message ) CPerformanceTimer( message );


#endif //_PERFORMANCETIMER_H__Included_727605417

