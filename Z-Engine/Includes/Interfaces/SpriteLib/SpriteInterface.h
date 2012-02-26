/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\SpriteLib\SpriteInterface.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _SPRITEINTERFACE_H__Included_1151042945
#define _SPRITEINTERFACE_H__Included_1151042945

namespace ZGE
{
	class CSpriteManager;
	class CAnimatedSpriteManager;
	class CAnimationManager;
	class ISpriteParser;
	/**
	 *	Sprite interface.
	 */
	class CSpriteInterface
	{
	public:
		// Initialises the sprite interface.
		bool InitialiseSpriteInterface( );

		// Deinitialises the sprite interface.
		bool DeinitilaiseSpriteInterface( );

		// @return The sprite manager instance.
		CSpriteManager* GetSpriteManager( );

		//@return The animated sprite interface.
		CAnimatedSpriteManager* GetAnimatedSpriteManager( );

		//@return the sprite animation manager
		CAnimationManager* GetAnimationManager( );

		// Sets the sprite parser implementation.
		void SetSpriteParser( ISpriteParser* _pParser );

	protected:
		// Creates the sprite manager.
		void  CreateSpriteManager( );

		// Creates the animated sprite manager.
		void CreateAnimatedSpriteManager( );

		// Creates the animation manager.
		void CreateAnimationManager( );
	protected:
		CSpriteManager*			m_pSpriteManager;			//!< The sprite manager instance.
	    CAnimatedSpriteManager* m_pAnimatedSpriteManager;	//!< The animated sprite manager instance.
		CAnimationManager*		m_pAnimationManager;		//!< The sprite animation manager.
	};
}

#endif //_SPRITEINTERFACE_H__Included_1151042945

