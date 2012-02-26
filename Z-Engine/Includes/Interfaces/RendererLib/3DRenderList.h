/**
 *	@file Z-Engine\Z-Engine\Includes\Interfaces\RendererLib\3DRenderList.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _3DRENDERLIST_H__Included_2073081611
#define _3DRENDERLIST_H__Included_2073081611

#include "RendererLib/RenderList.h"
namespace ZGE
{
	/**
	 *	3D render list implementation for 3d graphics.
	 */
	class C3DRenderList : public IRenderList
	{
	public:
		C3DRenderList(void);
		~C3DRenderList(void);

				/**
		 *	Adds a render loop to the render list.
		 *	@param _pRenderableActor the type of actor to create the loop for.
		 *	@return Success.
		 */
		virtual bool AddRenderLoop( CRenderableActor* _pRenderableActor ); 
	};
}

#endif //_3DRENDERLIST_H__Included_2073081611

