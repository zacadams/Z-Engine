/**
 *	@file Z-Engine\Z-Engine\Interfaces\CoreLib\Clock.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes
#include "CoreLib/Core.h"

// Library includes

// Local includes 


// Library Includes
#include <windows.h>

// Local Includes

// This Includes
#include "CoreLib/Clock.h"

// Static Variables

// constants
const ZGE::sint32 g_kllMillisecondToSecond	= 1000;

//   Static Function Prototypes

//   Implementation

using namespace ZGE;

/**
* Constructor.
* @author Zac Adams
**/
CClock::CClock ()
: m_bUsingQPF			(false)			
, m_llTicksPerSec		(0)		
, m_uiInitialTimerValue	(0)	
, m_fDeltaTick			(0.0f)			
, m_uiCurrentTick		(0)		
, m_uiLastTick			(0)			
, m_fFrameRate			(0.0f)			
, m_fTotalTimeElapsed	(0.0f)	
, m_bFreeze				(false)				
, m_fFreezeTimer		(0.0f)
{

}

/**
* Destructor.
* @author Zac Adams
**/
CClock::~CClock ()
{

}

/**
* Initialise.
* @author Zac Adams
**/
bool
CClock::Initialise ()
{

	// create and zero memory a large interger
	LARGE_INTEGER liQPTemp;
	ZeroMemory(&liQPTemp, sizeof(LARGE_INTEGER));
	
	// query the performance counter
	bool bSuccess	= true;
	BOOL wbSuccess	= QueryPerformanceFrequency(&liQPTemp);

	if (wbSuccess == 0)		// Check if we have a performance counter, if so, attain its frequency.
	{						// QueryPerformanceFrequency() failed and we will use system time.
		m_bUsingQPF				= false;
		m_llTicksPerSec			= g_kllMillisecondToSecond;
		m_uiInitialTimerValue	= static_cast<uint32>(timeGetTime()); 
	}
	else
	{	// QueryPerformanceFrequency() succeeded and we will use the performance counter.
		m_bUsingQPF			= true;
		m_llTicksPerSec		= static_cast<sint32>(liQPTemp.QuadPart);
		wbSuccess			= QueryPerformanceCounter(&liQPTemp);

		if (wbSuccess != 0)
		{	// QueryPerformanceCounter() succeeded. 
			m_uiInitialTimerValue	= static_cast<uint32>(liQPTemp.QuadPart);
		}
		else
		{
			bSuccess = false;
		}
	}

	return (bSuccess);
}

/**
* Process.
* @author Zac Adams
**/
void
CClock::Process ()
{
	m_uiLastTick = m_uiCurrentTick;	// Current and Last times.

	if (m_bUsingQPF)		// If using the performance counter.
	{
		LARGE_INTEGER liQPTick;
		ZeroMemory(&liQPTick, sizeof(LARGE_INTEGER));
		BOOL wbSuccess = QueryPerformanceCounter(&liQPTick);

		if (wbSuccess != 0)	// QueryPerformanceCounter() has succeeded.
		{
			m_uiCurrentTick = static_cast<uint32>(liQPTick.QuadPart);
		}
	}
	else					// If using system time.
	{
		m_uiCurrentTick = static_cast<uint32>(timeGetTime());
	}

	m_fDeltaTick = static_cast<float32>(m_uiCurrentTick - m_uiLastTick) / static_cast<float32>(m_llTicksPerSec);
	m_fFrameRate = 1.0f / m_fDeltaTick; 
	m_fTotalTimeElapsed += m_fDeltaTick;

	if (m_bFreeze)
	{
		m_fFreezeTimer += m_fDeltaTick;
	}

}

bool
CClock::Freeze()
{
	m_bFreeze = !m_bFreeze;
	return (m_bFreeze);
}

