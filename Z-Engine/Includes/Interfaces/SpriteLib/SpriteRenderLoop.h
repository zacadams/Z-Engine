/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\SpriteLib\SpriteRenderLoop.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _SPRITERENDERLOOP_H__Included_840205516
#define _SPRITERENDERLOOP_H__Included_840205516

#include "RendererLib/RenderLoop.h"
#include<vector>

namespace ZGE
{
#define Z_MAX_SPRITE_BATCH 10000
	class IVertexBuffer;
	/**
	 *	Sprite render loop, used to batch sprites into a single draw call.
	 */
	class CSpriteRenderLoop : public IRenderLoop
	{
	public:
		CSpriteRenderLoop(void);
		~CSpriteRenderLoop(void);


		/**
		 *	Overridden to update the sprite batch vertex buffer.
		 *	@param _pRenderableActor The actor to add.
		 *	@return Success.
		 */
		virtual void AddRenderAsset( IRenderAsset* _pRenderAsset );

		/**
		 *	Overridden to update the sprite batch vertex buffer.
		 *	@param _pRenderableActor The actor to remove.
		 *	@return Success.
		 */
		virtual void RemoveRenderAsset( IRenderAsset* _pRenderAsset );
		
		/**
		 *	Overridden to batch render sprites.
		 *	@return Success.
		 */
		virtual bool Render( );

		/**
		 *	Checks if the render loop is designed for the renderable actor.
		 *	@param _pRenderableActor The actor to check compatibily with the render loop.
		 *	@return Compatibility.
		 */
		virtual bool IsCompatibleWith( IRenderAsset* _pRenderAsset );

	protected:
		/**
		 * Creates the loops vertex buffer.
		 */
		void CreateSpriteBatch( IRenderAsset* _pRenderAsset );

	protected:
		IVertexBuffer* m_pVertexBuffer;
		bool m_bContainsLitSprites;
	};
}

#endif //_SPRITERENDERLOOP_H__Included_840205516

