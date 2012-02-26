/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9TextureManager.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/

#include "CoreLib/Core.h"
#include "DX9RendererLib/DX9Renderer.h"
// texture

#include "RendererLib/Texture.h"
#include "DX9RendererLib/DX9Texture.h"
#include "CoreLib/AssetId.h"

// Library includs
#include <d3dx9.h>

// this include 

#include "DX9RendererLib/DX9TextureManager.h"





using namespace ZGE;

CDX9TextureManager::CDX9TextureManager(  )
: m_pDefaultRT( NULL )
, m_pDefaultDT( NULL )
, m_pNULLTexture( NULL )
{

	// Create the default render target 

	IDirect3DSurface9* pDefaultRT = NULL;
	CDX9Renderer::GetDevice( )->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &pDefaultRT );

	D3DSURFACE_DESC RTDesc;
	pDefaultRT->GetDesc( &RTDesc );

	m_pDefaultRT = new CDX9Texture( pDefaultRT, CDX9Renderer::GetDevice( ) );

	// Create the default depth target

	IDirect3DSurface9* pDefaultDT = NULL;
	CDX9Renderer::GetDevice( )->GetDepthStencilSurface( &pDefaultDT );

	D3DSURFACE_DESC Desc;
	pDefaultDT->GetDesc( &Desc );


	m_pDefaultDT = new CDX9Texture( pDefaultDT, CDX9Renderer::GetDevice( ), true );

	// Create the null texture

	IDirect3DTexture9* p = NULL;
	m_pNULLTexture = new CDX9Texture( p, CDX9Renderer::GetDevice( ) );
}

CDX9TextureManager::~CDX9TextureManager(void)
{
	SafeDelete( m_pDefaultRT );
	SafeDelete( m_pDefaultDT );
	SafeDelete( m_pNULLTexture );
}
/*
*	Creates a render target
*	Param _kfWidth  : The width of the render terget
*	Param _kfHeight : The height of th erender target
*	Param _keFMT	: The render targets format
*	Return : ITexture, The render target
*/
ITexture* CDX9TextureManager::CreateRenderTarget( CAssetId& _rAssetId,const uint32 _kuWidth, const uint32 _kuHeight, const ESurfaceFormat _keFMT, const bool _bWriteOnly  )
{

	// Check if the render target has already been created.
	ITexture* pRenderTarget = NULL;
	pRenderTarget = GetAssetById( _rAssetId );
	if( pRenderTarget )
	{
		pRenderTarget->AddRef( );
		return pRenderTarget;
	}

	static const D3DFORMAT pFormats[] = 
	{
		D3DFMT_R32F,
		D3DFMT_X8R8G8B8,
		D3DFMT_D16,
	};

	
	// Do we want to crate a depth stencile?
	if( _keFMT == SF_uDepth )
	{
		// Create a depth stencile texture
		IDirect3DSurface9* pSurface = NULL;
		if( FAILED( CDX9Renderer::GetDevice( )->CreateDepthStencilSurface( _kuWidth, _kuHeight, pFormats[_keFMT], D3DMULTISAMPLE_NONE, 0, !_bWriteOnly, &pSurface, 0 ) ) )
		{
			// no
			// assert
			return NULL;
		}
		return new CDX9Texture( pSurface, CDX9Renderer::GetDevice( ), true );
	}

	// Create a render target

	IDirect3DTexture9* pTexture = NULL;
	//NOTE: The 0 may need to be a 1
	if( FAILED( CDX9Renderer::GetDevice( )->CreateTexture( _kuWidth, _kuHeight, 0, D3DUSAGE_RENDERTARGET, pFormats[_keFMT], D3DPOOL_DEFAULT, &pTexture, 0 ) ) )
	{
		// no 
		// assert
		assert_now( "Failed to texture!" );
		return NULL;
	}

	return new CDX9Texture( pTexture, CDX9Renderer::GetDevice( ) ) ;
}

/*
*	To be overriden to load assets of a derived manager.
*	Param _rAssetId : The assets id, ( could be the file name ).
*	Param _pAsset   : To be populated with the loaded asset.
*	Return : Success.
*/
bool CDX9TextureManager::LoadAssetImplementation( CAssetId& _rAssetId, ITexture*& _pAsset )
{

	IDirect3DTexture9* pTexture = NULL;

	if( FAILED( D3DXCreateTextureFromFileA( CDX9Renderer::GetDevice( ), _rAssetId.GetFileName( ), &pTexture ) ) )
	{
		_pAsset = NULL;
		assert_now( "Failed to load texture from file " );
		return false;
	}

	_pAsset = new CDX9Texture( pTexture, CDX9Renderer::GetDevice( ) );
	return true;
}

/*
*	To be overidden to release a managers assets.
*	Param _pAsset : The asset to release.
*	Return : Success.
*/
bool CDX9TextureManager::ReleaseAsset( ITexture* _pAsset )
{
	delete reinterpret_cast< CDX9Texture* >( _pAsset );
	_pAsset = NULL;
	return true;
}
/*
*	Returns the defult render target
*/
ITexture* CDX9TextureManager::GetDefaultRT( )
{
	return m_pDefaultRT;
}
/*
*	Retunrs the defaul depth target
*/
ITexture* CDX9TextureManager::GetDefaultDT( )
{
	return m_pDefaultDT;
}

/*
*	Returns a null texture 
*/
ITexture* CDX9TextureManager::GetNULLTexture( )
{
	return m_pNULLTexture;
}