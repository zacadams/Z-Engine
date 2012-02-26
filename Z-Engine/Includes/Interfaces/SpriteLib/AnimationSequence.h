/**
 *	@file Z-Engine\Z-Engine\Interfaces\SpriteLib\AnimationSequence.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _ANIMATIONSEQUENCE_H__Included_995492861
#define _ANIMATIONSEQUENCE_H__Included_995492861

#include "CoreLib/Asset.h"

#include "SpriteLib/AnimationFrame.h"
#include <vector>
namespace ZGE
{
	/**
	 * This class represents an animation. It is 
	 * responsible for an animations key frames.
	 */
	class CAnimationSequence : public CAsset< CAnimationSequence >
	{
	public:
		CAnimationSequence(void);
		~CAnimationSequence(void);

		/**
		 * Adds an frame to the animation sequence.
		 * @param _rFrame The frame to add.
		 * @return Success.
		 */
		bool AddAnimationFrame( CAnimationFrame& _rFrame ); 

		// Returns the animation sequences frame count.
		inline uint32 GetFrameCount( ) const { return m_vecAnimationFrames.size( ); }

		// returns the animation frame at th spcified index.
		CAnimationFrame& GetAnimationFrame( const uint32 _kuIndex );
	protected:
		std::vector< CAnimationFrame > m_vecAnimationFrames; //!< The animation frames.
	};
}// end namespace

#endif //_ANIMATIONSEQUENCE_H__Included_995492861

