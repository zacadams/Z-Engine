/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\RendererLib\RendererInterface.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes
#include "CoreLib/Core.h"
#include "RendererLib/RenderList.h"
#include "CoreLib/PerformanceManager.h"
#include "RendererLib/RenderEffectManager.h"

// Library includes

// Local includes 
#include "RendererLib/RendererInterface.h"

using namespace ZGE;

// Returns the render effect manager.
CRenderEffectManager* IRendererInterface::GetRenderEffectManager( )
{
	return m_pRenderEffectMngr;
}


// Adds a render list.
void IRendererInterface::AddRenderList( IRenderList* pRenderList )
{
	m_vecRenderLists.push_back( pRenderList );
}

// @return The specified render list.
IRenderList* IRendererInterface::GetRenderList( const uint32 _kuRenderListType )
{
	uint32 uRenderListCount = m_vecRenderLists.size( );
	for( uint32 uRenderList = 0; uRenderList < uRenderListCount; ++uRenderList )
	{
		if( m_vecRenderLists[uRenderList]->GetType( ) == _kuRenderListType )
		{
			return m_vecRenderLists[uRenderList];
		}
	}
	return NULL;
}

//Notifies and sets up the renderer for rendering
bool IRendererInterface::BeginScene( )
{
	CPerformanceNode* pPerf = NULL;
	CREATE_PERFORMANCE_TIMER( pPerf, "BeginScene( )", NULL );
	START_PERFORMANCE_TIMER( pPerf );
	uint32 uRenderListCount =	 m_vecRenderLists.size( );
	for( uint32 uRenderList = 0; uRenderList < uRenderListCount; ++uRenderList )
	{
		m_vecRenderLists[uRenderList]->Clear( );
	}
	END_PERFORMANCE_TIMER( pPerf );
	return false;
}


//Ends th scene.
bool IRendererInterface::EndScene( )
{
		CPerformanceNode* pPerf = NULL;
	CREATE_PERFORMANCE_TIMER( pPerf, "EndScene( )", NULL );
	START_PERFORMANCE_TIMER( pPerf );
	uint32 uRenderListCount =	 m_vecRenderLists.size( );
	for( uint32 uRenderList = 0; uRenderList < uRenderListCount; ++uRenderList )
	{
		m_vecRenderLists[uRenderList]->Renderlist( );
	}
	END_PERFORMANCE_TIMER( pPerf );
	return false;
}