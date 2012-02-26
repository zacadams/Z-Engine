/**
 *	@file Z-Engine\Z-Engine\Includes\Interfaces\RendererLib\2DRenderList.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _2DRENDERLIST_H__Included_436205514
#define _2DRENDERLIST_H__Included_436205514

#include "RendererLib/RenderList.h"
namespace ZGE
{
	/**
	 * Render list implementation for 2D graphics.
	 */
	class C2DRenderList : public IRenderList
	{
	public:
		C2DRenderList(void);
		~C2DRenderList(void);

				/**
		 *	Adds a render loop to the render list.
		 *	@param _pRenderAsset the type of asset to create the loop for.
		 *	@return Success.
		 */
		virtual bool AddRenderLoop( IRenderAsset* _pRenderAsset );
	};
}

#endif //_2DRENDERLIST_H__Included_436205514

