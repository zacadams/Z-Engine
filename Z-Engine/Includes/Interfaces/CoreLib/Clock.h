/**
 *	@file Z-Engine\Z-Engine\Interfaces\CoreLib\Clock.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _CLOCK_H__Included_1959487808
#define _CLOCK_H__Included_1959487808


namespace ZGE
{
	class CClock
	{
		// Member Functions
	public:

		CClock ();
		~CClock ();

		bool Initialise ();
		void Process ();

		bool Freeze();

		inline const float32 GetDeltaTick() const;
		inline const float32& GetFrameRate() const;
		inline const float32& GetTotalTimeElapsed() const;
		inline const float32& GetTotalTimeFrozen() const;

	protected:

		bool m_bUsingQPF;			// Boolean flag representing whether or not the clock is using the performance counter or system time. 
		sint64 m_llTicksPerSec;		// Timer frequency in ticks per second. 
		uint32 m_uiInitialTimerValue;	// The initial timer value.

		float32 m_fDeltaTick;			// The difference in time between the current frame and the last. 
		uint32 m_uiCurrentTick;		// The current timer value (evaluated per frame).
		uint32 m_uiLastTick;			// The timer value at the last frame.

		float32 m_fFrameRate;			// Frames per second.

		float32 m_fTotalTimeElapsed;	// Total time elapsed in seconds. 

		bool m_bFreeze;				// Boolean flag representing whether or not the clock is currently frozen. 
		float32 m_fFreezeTimer;			// Time passed since the clock was frozen in seconds.

	private:
		CClock (const CClock& _kr);
		CClock& operator= (const CClock& _kr);

		// Member Variables
	public:

	protected:

	private:

	};
}

#include "Clock.inl"


#endif //_CLOCK_H__Included_1959487808

