/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9Texture.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _DX9TEXTURE_H__Included_1472232238
#define _DX9TEXTURE_H__Included_1472232238

#include "RendererLib/Texture.h"

struct IDirect3DTexture9;
struct IDirect3DDevice9;
struct IDirect3DSurface9;

namespace ZGE
{
	class CDX9Texture : public ITexture
	{
	public:

		CDX9Texture( IDirect3DTexture9* _pD3DTexture, IDirect3DDevice9* _pDevice );
		CDX9Texture( IDirect3DSurface9* _pD3DSurface, IDirect3DDevice9* _pDevice, bool _bDepthStencil = false );
		~CDX9Texture(void);

		/*
		*	Sets the texture on the renderer at the specified index
		*/
		virtual void Apply( uint32 uIndex = 0 );

		/*
		*	Lockes the texels lof a texture
		*/
		virtual bool LockTexels( uint32* _pTextels );

		/*
		*	Unlockes a textures texels
		*/
		virtual bool UnlockTexels( );

		/*
		*	Targets the texture for writing
		*/
		virtual bool Target( const uint32 _kuIndex );

		/*
		* Returns the textures width
		*/
		virtual uint32 GetWidth( ) const;

		/*
		* Returns the textures height
		*/
		virtual uint32 GetHeight( ) const;

	protected:
	
		IDirect3DTexture9* m_pD3DTexture; //!< The DirectX texture
		IDirect3DDevice9*  m_pDevice;	  //!< D3D Device pointer
		IDirect3DSurface9* m_pD3DSurface;
		bool			   m_bDepthStencil;
		uint32			   m_uWidth;
		uint32			   m_uHeight;
	};
}// end namespace

#endif //_DX9TEXTURE_H__Included_1472232238

