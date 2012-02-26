/**
 *	@file Z-Engine\Z-Engine\Source\Interfaces\RendererLib\3DRenderList.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes
#include "CoreLib/Core.h"
// Library includes

// Local includes
#include "RendererLib/3DRenderList.h"
using namespace ZGE;
C3DRenderList::C3DRenderList(void)
{
}

C3DRenderList::~C3DRenderList(void)
{
}

/**
 *	Adds a render loop to the render list.
 *	@param _pRenderableActor the type of actor to create the loop for.
 *	@return Success.
 */
bool C3DRenderList::AddRenderLoop( CRenderableActor* _pRenderableActor )
{
	return false;
}
