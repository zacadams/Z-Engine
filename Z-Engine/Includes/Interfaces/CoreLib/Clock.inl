/**
 *	@file Z-Engine\Z-Engine\Interfaces\CoreLib\Clock.inl
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/

namespace ZGE
{

inline const float32 
CClock::GetDeltaTick() const
{
	if (m_bFreeze)
	{
		return (0.0f);
	}
	else
	{
		return (m_fDeltaTick);
	}
}
inline const float32& 
CClock::GetFrameRate() const
{
	return (m_fFrameRate);
}
inline const float32& 
CClock::GetTotalTimeElapsed() const
{
	return (m_fTotalTimeElapsed); 
}
inline const float32& 
CClock::GetTotalTimeFrozen() const
{
	return (m_fFreezeTimer);
}
}