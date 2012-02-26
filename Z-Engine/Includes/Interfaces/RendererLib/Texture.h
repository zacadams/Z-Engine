/**
 *	@file Z-Engine\Z-Engine\Interfaces\RendererLib\Texture.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _TEXTURE_H__Included_998667963
#define _TEXTURE_H__Included_998667963

#include "CoreLib/Asset.h"

namespace ZGE
{
	class ITexture : public CAsset< ITexture >
	{
	public:
	
		virtual ~ITexture(void){}


		/*
		*	Sets the texture on the renderer at the specified index
		*/
		virtual void Apply( uint32 uIndex = 0 ) = 0;

		/*
		*	Lockes the texels lof a texture
		*/
		virtual bool LockTexels( uint32* _pTextels ) = 0;

		/*
		*	Unlockes a textures texels
		*/
		virtual bool UnlockTexels( ) = 0;
		/*
		*	Targets the texture for writing
		*/
		virtual bool Target( const uint32 _kuIndex ) = 0;

		/*
		* Returns the textures width
		*/
		virtual uint32 GetWidth( ) const = 0;

		/*
		* Returns the textures height
		*/
		virtual uint32 GetHeight( ) const = 0;


	protected:
	};
}// end namespace

#endif //_TEXTURE_H__Included_998667963

