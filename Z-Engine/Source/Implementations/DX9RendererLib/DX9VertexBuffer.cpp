/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9VertexBuffer.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "DX9RendererLib/DX9Renderer.h"
#include "RendererLib/VertexDeclaration.h"
#include "RendererLib/VertexDescription.h"
#include <d3dx9.h>

#include "DX9RendererLib/DX9VertexBuffer.h"

using namespace ZGE;
CDX9VertexBuffer::CDX9VertexBuffer(  )
: m_pDX9VertexBuffer( NULL )
, m_pVertexDecl( NULL )
{
}

CDX9VertexBuffer::~CDX9VertexBuffer(void)
{
	SafeRelease( m_pDX9VertexBuffer );
}
// Initialises the vertex buffer.
// _kuVertexCount : The number of vertices.
// _kuStride The size of a vertex.
// _bDynamic Determins if the buffer is dynamic.
// return Success.
bool CDX9VertexBuffer::Initialise( const uint32 _kuVertexCount, const uint32 _kuStride, IVertexDeclaration* _pVertexDecl , bool _bDynamic )
{
	m_uVertexCount = _kuVertexCount;
	m_uStride      = _kuStride;
	m_uSize        = _kuVertexCount * _kuStride;
	m_bDynamic     = _bDynamic;
	m_pVertexDecl  = _pVertexDecl;

	DWORD dwUsage = _bDynamic ? D3DUSAGE_DYNAMIC : D3DUSAGE_WRITEONLY;

	if( FAILED( CDX9Renderer::GetDevice( )->CreateVertexBuffer( m_uSize, dwUsage, NULL, D3DPOOL_DEFAULT, &m_pDX9VertexBuffer, NULL ) ) )
	{
		assert_now( "Failed to create vertex buffer!" );
		return false;
	}
	return true;
}

// Locks the vertex buffer and accesses the specified data.
// Param _kuSize   : The size of the vertex data to lock
// Param _kuOffSet : The position to lock from
// Return : void* containin the nedded data
bool CDX9VertexBuffer::Lock( const uint32 _kuSize, const uint32 _kuOffSet,  void*& _pVertices, bool _bReadOnly  )
{
	DWORD dwUsage = _bReadOnly ? D3DLOCK_READONLY : 0;

	if( FAILED( m_pDX9VertexBuffer->Lock( _kuOffSet, _kuSize, &_pVertices, dwUsage ) ) )
	{
		assert_now( "Failed to lock vertex buffer!" );
		return false;
	}
	return true;
}

// Un-locks the vertex buffer
bool CDX9VertexBuffer::Unlock( )
{
	if( FAILED( m_pDX9VertexBuffer->Unlock( ) ) )
	{
		assert_now( "Failed to unlock vertex buffer!" );
		return false;
	}
	return true;
}
// Applies the vertex buffer onto the device.
bool CDX9VertexBuffer::Apply( )
{
	assert_msg( m_pDX9VertexBuffer, "Buffer is not initialised!" );
	m_pVertexDecl->Apply( );
	if( FAILED( CDX9Renderer::GetDevice( )->SetStreamSource( m_pVertexDecl->GetDescription( ).GetTargetStream( ), 
								m_pDX9VertexBuffer,
								0,
								m_uStride ) ) )
	{
		assert_now( "Failed to apply vertex buffer!" );
		return false;
	}
	return true;
}
