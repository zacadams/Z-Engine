/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\RendererLib\RenderLoop.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "RendererLib/RenderEffect.h"
#include "RendererLib/RenderAsset.h"
#include "RendererLib/RenderLoop.h"
using namespace ZGE;
IRenderLoop::IRenderLoop(void)
{
}

IRenderLoop::~IRenderLoop(void)
{
}

/**
 *	Adds a renderable actor to the render loop.
 *	@param _pRenderableActor The actot to add.
 *	@return Success.
 */
void IRenderLoop::AddRenderAsset( IRenderAsset* _pRenderAsset )
{
	m_lRenderList.push_back( _pRenderAsset );
	//_pRenderableActor->SetRenderLoop( this );
}

/**
 *	Removes a renderable actor from the render loop.
 *	@param _pRenderableActor The actor to remove.
 *	@return Success.
 */
void IRenderLoop::RemoveRenderAsset( IRenderAsset* _pRenderAsset )
{
	m_lRenderList.remove( _pRenderAsset );
}

/**
 *	Sets the render loops effect.
 *	@param _pRenderEffect The effect used to render the actors in the loop.
 */
void IRenderLoop::SetRenderEffect( IRenderEffect* _pRenderEffect )
{
	m_pRenderEffect = _pRenderEffect;
}

///**
// *	Renders all render able actors in the render loop.
// *	@return Success.
// */
//bool IRenderLoop::Render( )
//{
//	// Begin the effect.
//	m_pRenderEffect->BeginEffect( );
//	
//	// Render all contained actors.
//	LoopRenderList::iterator iter = m_lRenderList.begin( );
//	for( iter; iter != m_lRenderList.end( ); ++iter )
//	{
//		m_pRenderEffect->Render( NULL, 0, 0);
//	}
//
//	// End the effect.
//	m_pRenderEffect->EndEffect( );
//	return true;
//}

/**
 *	Checks if the render loop is designed for the render asset.
 *	@param _pRenderAsset The asset to check compatibily with the render loop.
 *	@return Compatibility.
 */
bool IRenderLoop::IsCompatibleWith( IRenderAsset* _pRenderAsset )
{
	// Compare with the first element in this render loop.
	IRenderAsset* pFirstElement = (*m_lRenderList.begin( ));
	
	// Check the render effects are the same.
	if( _pRenderAsset->m_pRenderEffect == pFirstElement->m_pRenderEffect )
	{
		// They have the same render effects.
		return true;
	}
	return false;
}

/**
 *	Clears the render loop.
 */
void IRenderLoop::Clear( )
{
	m_lRenderList.clear( );
}
