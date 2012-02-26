/**
 *	@file Z-Engine\Z-Engine\Source\Interfaces\RendererLib\2DRenderList.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes
#include "CoreLib/Core.h"
#include "SpriteLib/SpriteRenderLoop.h"
#include "RendererLib/RenderAsset.h"

// Library includes

// Local includes 
#include "SpriteLib/2DRenderList.h"
using namespace ZGE;
C2DRenderList::C2DRenderList(void)
{
	m_eRenderListType = RLT_2D; 
}

C2DRenderList::~C2DRenderList(void)
{
}

		/**
 *	Adds a render loop to the render list.
 *	@param _pRenderableActor the type of actor to create the loop for.
 *	@return Success.
 */
bool C2DRenderList::AddRenderLoop( IRenderAsset* _pRenderAsset )
{
	CSpriteRenderLoop* pLoop = new CSpriteRenderLoop( );
	pLoop->SetRenderEffect( _pRenderAsset->m_pRenderEffect );
	m_lRenderList.push_back( pLoop );
	pLoop->AddRenderAsset( _pRenderAsset );
	return false;
}