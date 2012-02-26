/**
 *	@file Z-Engine\Z-Engine\Interfaces\SpriteLib\AnimationSequence.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "SpriteLib/AnimationSequence.h"

using namespace ZGE;
CAnimationSequence::CAnimationSequence(void)
{
}

CAnimationSequence::~CAnimationSequence(void)
{
}
/**
 * Adds an frame to the animation sequence.
 * @param _rFrame The frame to add.
 * @return Success.
 */
bool CAnimationSequence::AddAnimationFrame( CAnimationFrame& _rFrame )
{
	// Add the frame.
	m_vecAnimationFrames.push_back( _rFrame );
	return true; // Could not think of a failing case.
}

// returns the animation frame at th spcified index.
CAnimationFrame& CAnimationSequence::GetAnimationFrame( const uint32 _kuIndex )
{
	assert_msg( _kuIndex < GetFrameCount( ), "Index too large!" );
	return m_vecAnimationFrames[_kuIndex];
}