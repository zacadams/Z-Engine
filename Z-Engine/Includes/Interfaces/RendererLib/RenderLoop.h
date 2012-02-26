/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\RendererLib\RenderLoop.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _RENDERLOOP_H__Included_1092986139
#define _RENDERLOOP_H__Included_1092986139

#include <list> 

namespace ZGE
{
	class IRenderEffect;
	class IRenderAsset;

	/**
	 *	Used to batch like objects to avoid costly texture and render state changes.
	 */
	class IRenderLoop
	{
	public:
		IRenderLoop(void);
		~IRenderLoop(void);

		/**
		 *	Adds a render asset to the render loop.
		 *	@param _pRenderAsset The asset to add.
		 *	@return Success.
		 */
		virtual void AddRenderAsset( IRenderAsset* _pRenderAsset );

		/**
		 *	Removes a render asset from the render loop.
		 *	@param _pRenderAsset The asset to remove.
		 *	@return Success.
		 */
		virtual void RemoveRenderAsset( IRenderAsset* _pRenderAsset );

		/**
		 *	Sets the render loops effect.
		 *	@param _pRenderEffect The effect used to render the actors in the loop.
		 */
		void SetRenderEffect( IRenderEffect* _pRenderEffect );

		/**
		 *	Renders all render able actors in the render loop.
		 *	@return Success.
		 */
		virtual bool Render( ) = 0;

		/**
		 *	Checks if the render loop is designed for the render asset.
		 *	@param _pRenserAsset The asset to check compatibily with the render loop.
		 *	@return Compatibility.
		 */
		virtual bool IsCompatibleWith( IRenderAsset* _pRenderAsset );

		/**
		 *	Clears the render loop.
		 */
		void Clear( );

	protected:
		typedef std::list< IRenderAsset* > LoopRenderList;
		LoopRenderList	m_lRenderList;		//!< Containes all the assets to be rendered.
		IRenderEffect* m_pRenderEffect;		//!< The effect used to render the contained actors.
	};
}

#endif //_RENDERLOOP_H__Included_1092986139

