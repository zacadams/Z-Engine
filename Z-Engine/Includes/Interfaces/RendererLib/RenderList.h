/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\RendererLib\RenderList.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _RENDERLIST_H__Included_319289004
#define _RENDERLIST_H__Included_319289004

#include "RendererLib/RenderLoop.h"
#include <list>
namespace ZGE
{
	class IRenderAsset;

	/**
	 *	This class is responsible for containing and batching visible objects found in the scene.
	 *	Renderable entities are bached to reduce render state and texture changes.
	 */
	class IRenderList
	{
	public:
		enum ERenderListType
		{
			RLT_2D = 0, //!< 2D render list specifier.
			RLT_3D,		//!< 3D render list specifier.
			RLT_COUNT,
		};
	public:
		IRenderList(void);
		virtual ~IRenderList(void);

		/**
		 *	Adds a visible renderable actor to be rendered.
		 *	@param _pRenderableActor The visible actor to add.
		 */
		virtual void AddRenderAsset( IRenderAsset* _pRenderAsset );
		
		/**
		 *	Renders the render able actors.
		 */
		virtual bool Renderlist( );

		/**
		 *	Clears the render list.
		 */
		virtual void Clear( );

		/**
		 *	Adds a render loop to the render list.
		 *	@param _pRenderableActor the type of actor to create the loop for.
		 *	@return Success.
		 */
		virtual bool AddRenderLoop( IRenderAsset* _pRenderAsset ) = 0; 

		ERenderListType GetType( )const { return m_eRenderListType; }

	protected:
		typedef std::list< IRenderLoop* > RenderList;
		RenderList	m_lRenderList;	//!< The render list.
		ERenderListType m_eRenderListType;

	};
};

#endif //_RENDERLIST_H__Included_319289004

