/**
 *	@file Z-Engine\Z-Engine\Interfaces\SpriteLib\ComplexAnimatedSprite.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _COMPLEXANIMATEDSPRITE_H__Included_124429141
#define _COMPLEXANIMATEDSPRITE_H__Included_124429141

#include "SpriteLib/AnimationController.h"
#include "CoreLib/Asset.h"
#include <map>

namespace ZGE
{
	class CAnimationSequence;
	class ITexture;
	class CSprite;

	/**
	 * This class represents a complex anmated sprite.
	 * This sprite can have many animations with events.
	 */
	class CAnimatedSprite : public CAsset< CAnimatedSprite >
	{
	public:
		CAnimatedSprite(void);
		~CAnimatedSprite(void);

		/**
		 * Initilaises the animated sprite.
	  	 * @return Succes.	
		 */
		bool Initialise( CSprite* _pSprite );

		/**
		 * Adds an animation to the animated sprite.
		 * from the supplied animation sequence.
		 * @param _kpcAnimationId The animation name.
		 * @param _pAnimationSequence The animation sequence to add.
		 * @return Success.
		 */
		bool AddAnimation( const char* _kpcAnimationId, CAnimationSequence* _pAnimationSequence );
		/**
		 * Makes the animated sprite play the sepcified animation.
		 * @param _kpcAnimationId The animation to play.
		 * @param _pAnimController To be populated with the controller to the playing animation controller.
		 * @return Success.
		 */
		bool PlayAnimation( const char8* _kpcAnimationId, CAnimationController* _pAnimController );
		/**
		 * Returns the specified animation.
		 * @param _kpcAnimationId The animation to return.
		 * @param _pAnimationSequence To be polulated with the target animation sequence.
		 * @return Success.
		 */
		bool GetAnimation( const char8* _kpcAnimationId, CAnimationSequence*& _pAnimationSequence );

		// Returns the animated sprites sprite.
		inline CSprite* GetSprite( ) const { return m_pSprite; }

	protected:

		// Checks if the target animation exist.
		bool DoesAnimationExist( const char* _kpcAnimationId );

	protected:
		typedef std::map< const char*, CAnimationSequence* > AnimationMap;
		AnimationMap m_mapAnimations;
		CSprite*	m_pSprite;			//!< The sprite.
	};	
}
#endif //_COMPLEXANIMATEDSPRITE_H__Included_124429141

