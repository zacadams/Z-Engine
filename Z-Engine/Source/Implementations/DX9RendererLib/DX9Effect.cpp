/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9Effect.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/

#include "CoreLib/Core.h"

#include <d3dx9.h>

#include "DX9RendererLib/DX9Effect.h"

using namespace ZGE;
CDX9Effect::CDX9Effect( IDirect3DDevice9* _pDevice, ID3DXEffect* _pEffect )
: m_pDevice( _pDevice )
, m_pD3DEffect( _pEffect )
{
}

CDX9Effect::~CDX9Effect(void)
{
	m_pD3DEffect->Release( );
}
// Set methods
/*
*	Sets the active technique on shader
*/
bool CDX9Effect::SetTechnique( const char8* _kpcTechnique )
{
	if( FAILED( m_pD3DEffect->SetTechnique( _kpcTechnique )) )
	{
		return false;
	}
	return true;
}
/*
*	Sets data onto a shader using a memory and size
*	Param _kpcId  : The value to set the data on
*	Param _pData  : The data to set
*	Param _kuSize : The size of the  data 
*/
bool CDX9Effect::SetValue( const char8* _kpcId, void* _pData, const uint32 _kuSize )
{
	if( FAILED( m_pD3DEffect->SetRawValue( _kpcId, _pData, 0, _kuSize ) ) )
	{
		return false;
	}
	return true;
}
// Render techniques
/*
*	Beginsan effect
*	Param _ruPassCount : The number of passes in the active technique
*/
bool CDX9Effect::BeginEffect( uint32& _ruPassCount )
{
	if( FAILED( m_pD3DEffect->Begin( &_ruPassCount, 0 ) ) )
	{
		return false;
	}
	return true;
}
/*
*	Begins a pass on the effects active technique
*	Param _kuPass : The effect to use
*/
bool CDX9Effect::BeginPass( const uint32& _kuPass )
{
	if( FAILED( m_pD3DEffect->BeginPass( _kuPass ) ) )
	{
		return false;
	}
	return true;
}
/*
*	Ends a technique pass
*/
bool CDX9Effect::EndPass( )
{
	if( FAILED( m_pD3DEffect->EndPass( ) ) )
	{
		return false; 
	}
	return true;
}
/*
*	Ends a technique
*/
bool CDX9Effect::EndTechnique( )
{
	if( FAILED( m_pD3DEffect->End( ) ) )
	{
		return false;
	}
	return true;
}