/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\RendererLib\FixedFunctionRenderEffect.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "RendererLib/RendererInterface.h"
#include "RendererLib/VertexBuffer.h"
#include "RendererLib/FixedFunctionRenderEffect.h"
using namespace ZGE;
CFixedFunctionRenderEffect::CFixedFunctionRenderEffect(void)
{
}

CFixedFunctionRenderEffect::~CFixedFunctionRenderEffect(void)
{
}

/**
 *	Initialise the render effect.
 */
bool CFixedFunctionRenderEffect::Initialise( )
{
	return false;
}

/**
 * Renders a render asset using this effect.
 */
void CFixedFunctionRenderEffect::Render( const EPrimitiveTypes _kePrimitiveType, void* _pVertices, const uint32 _kuPrimitiveCount, const uint32 _kuVertexStride )
{
}

				/**
 * Renders a render asset using this effect.
 */
void CFixedFunctionRenderEffect::Render( const EPrimitiveTypes _kePrimitiveType, IVertexBuffer* _pVertexBuffer, const uint32 _kuPrimitiveCount  )
{
	_pVertexBuffer->Apply( );
	ZEngine::GetRendererInterface( )->DrawPrimitives( _kePrimitiveType, _kuPrimitiveCount );
}


/**
 * Renders a render asset using this effect.
 */
void CFixedFunctionRenderEffect::Render( CMesh* _pMesh )
{
}

/**
 * To be implemented to set up device states for a render effect. 
 */
void CFixedFunctionRenderEffect::BeginEffect( )
{
	// Set the render states.
	uint32 uCount = m_vecRenderStateTargets.size( );
	IRendererInterface* pRenderer = ZEngine::GetRendererInterface( );
	for( uint32 uRenderState = 0; uRenderState < uCount; ++uRenderState )
	{
		pRenderer->SetRenderState( static_cast< ERenderStates >( m_vecRenderStateTargets[uRenderState].uRenderState ), m_vecRenderStateTargets[uRenderState].uValue );
	}

	// Set the texture stage states.
	uCount = m_vecTextureStateTargets.size( );
	for( uint32 uRenderState = 0; uRenderState < uCount; ++uRenderState )
	{
		// pRenderer->SetTexureStageState
	}

}

/**
 * To be implemented to clean up device states after an effect has rendered.
 */
void CFixedFunctionRenderEffect::EndEffect( )
{
		// Set the render states.
	uint32 uCount = m_vecRenderStateTargets.size( );
	IRendererInterface* pRenderer = ZEngine::GetRendererInterface( );
	for( uint32 uRenderState = 0; uRenderState < uCount; ++uRenderState )
	{
		pRenderer->SetRenderState( static_cast< ERenderStates >( m_vecRenderStateTargets[uRenderState].uRenderState ), m_vecRenderStateTargets[uRenderState].uResetValue );
	}

	// Set the texture stage states.
	uCount = m_vecTextureStateTargets.size( );
	for( uint32 uRenderState = 0; uRenderState < uCount; ++uRenderState )
	{
		// pRenderer->SetTexureStageState
	}
}


// Adds a render state target.
void CFixedFunctionRenderEffect::AddRenderStateTarget( const SRenderStateTarget& _krsRenderStateTarget )
{
	m_vecRenderStateTargets.push_back( _krsRenderStateTarget );
}
// Adds a texture state target.
void CFixedFunctionRenderEffect::AddTextureStateTarget( const STextureStageStateTarget& _krsTextureStateTarget )
{
	m_vecTextureStateTargets.push_back( _krsTextureStateTarget );
}