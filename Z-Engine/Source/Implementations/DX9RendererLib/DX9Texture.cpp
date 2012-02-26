/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9Texture.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/


#include "CoreLib/Core.h"


#include <d3dx9.h>

#include "DX9RendererLib/DX9Texture.h"

using namespace ZGE;

CDX9Texture::CDX9Texture( IDirect3DTexture9* _pD3DTexture, IDirect3DDevice9* _pDevice )
: m_pD3DTexture( _pD3DTexture )
, m_pDevice( _pDevice )
, m_pD3DSurface( NULL )
, m_bDepthStencil( false )
{
	++m_uRefCount;
	
	// Am i a null texture?
	if( m_pD3DTexture )
	{
		// No 
		m_pD3DTexture->GetSurfaceLevel( 0, &m_pD3DSurface );
		
		D3DSURFACE_DESC Desc;
		m_pD3DTexture->GetLevelDesc( 0, &Desc );
		m_uWidth  = Desc.Width;
		m_uHeight = Desc.Height;
	}
}
//
CDX9Texture::CDX9Texture( IDirect3DSurface9* _pD3DSurface, IDirect3DDevice9* _pDevice, bool _bDepthStencil )
: m_pD3DTexture( NULL )
, m_pD3DSurface( _pD3DSurface )
, m_pDevice( _pDevice )
, m_bDepthStencil( _bDepthStencil )
{
	++m_uRefCount;
}

CDX9Texture::~CDX9Texture(void)
{
	SafeRelease( m_pD3DTexture );
	SafeRelease( m_pD3DSurface );
}

/*
*	Sets the texture on the renderer at the specified index
*/
void CDX9Texture::Apply( uint32 uIndex )
{
	if( FAILED( m_pDevice->SetTexture( uIndex, m_pD3DTexture ) ) )
	{
		//assert_now( "Failed to set texture on the device" );
	}
}

/*
*	Lockes the texels lof a texture
*/
bool CDX9Texture::LockTexels( uint32* _pTextels )
{
	UNUSED_VAR( _pTextels );
	return false;
}
/*
*	Unlockes a textures texels
*/
bool CDX9Texture::UnlockTexels( )
{
	return false;
}
/*
*	Targets the texture for writing
*/
bool CDX9Texture::Target( const uint32 _kuIndex )
{
	if( m_bDepthStencil )
	{
		if( FAILED( m_pDevice->SetDepthStencilSurface( m_pD3DSurface ) ) )
		{
			return false;
		}
	}
	else
	{
		if( FAILED( m_pDevice->SetRenderTarget( _kuIndex, m_pD3DSurface ) ) )
		{
			return false;
		}
	}
	return true;
}
/*
* Returns the textures width
*/
uint32 CDX9Texture::GetWidth( ) const
{
	return m_uWidth;
}
/*
* Returns the textures height
*/
uint32 CDX9Texture::GetHeight( ) const
{
	return m_uHeight;
}
