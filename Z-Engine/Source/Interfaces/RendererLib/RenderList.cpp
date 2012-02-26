/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\RendererLib\RenderList.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "CoreLib/PerformanceManager.h"
#include "RendererLib/RenderList.h"
using namespace ZGE;

IRenderList::IRenderList(void)
: m_eRenderListType( RLT_COUNT )
{
}

IRenderList::~IRenderList(void)
{
}


/**
 *	Adds a visible renderable actor to be rendered.
 *	@param _pRenderableActor The visible actor to add.
 */
void IRenderList::AddRenderAsset( IRenderAsset* _pRenderAsset )
{
	CPerformanceNode* pPerfNode = NULL;
	CREATE_PERFORMANCE_TIMER( pPerfNode, "AddRenderAsset( )", NULL );
	START_PERFORMANCE_TIMER( pPerfNode );
	
	// Find the a comapatible render loop.
	RenderList::iterator iter  = m_lRenderList.begin( );
	for( iter;  iter != m_lRenderList.end( ); ++iter )
	{
		if( (*iter)->IsCompatibleWith( _pRenderAsset ) )
		{
			// Found a compatible render loop.
			(*iter)->AddRenderAsset( _pRenderAsset );
			END_PERFORMANCE_TIMER( pPerfNode );
			return;
		}
	}
	// No compatible render loops, create a new render loop.
	AddRenderLoop( _pRenderAsset );
	
	END_PERFORMANCE_TIMER( pPerfNode );
}

/**
 *	Renders the render able actors.
 */
bool IRenderList::Renderlist( )
{
	// Render the list.
	RenderList::iterator iter = m_lRenderList.begin( );
	for( iter; iter != m_lRenderList.end( ); ++iter )
	{
		(*iter)->Render( );
	}
	return false;
}

/**
 *	Clears the render list.
 */
void IRenderList::Clear( )
{
	RenderList::iterator iter = m_lRenderList.begin( );
	for( iter; iter != m_lRenderList.end( ); ++iter )
	{
		(*iter)->Clear( );
	}
}