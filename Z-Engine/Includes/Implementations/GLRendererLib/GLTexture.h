
/**
 *	@file Z-Engine\Z-Engine\Implementations\GLRendererLib\GLTexture.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _GLTEXTURE_H__Included_1652592730
#define _GLTEXTURE_H__Included_1652592730

#pragma once

#include "RendererLib/Texture.h"

namespace ZGE
{
	class CGLTexture : public ITexture
	{
	public:
		CGLTexture(void);
		~CGLTexture(void);

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

		uint32 m_uWidth; //!< The textures width  in pixels
		uint32 m_uHeight;//!< The textures height in pixels
	};
}

#endif //_GLTEXTURE_H__Included_1652592730

