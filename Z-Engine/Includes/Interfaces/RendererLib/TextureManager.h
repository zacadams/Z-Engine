/**
 *	@file Z-Engine\Z-Engine\Interfaces\RendererLib\TextureManager.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _TEXTUREMANAGER_H__Included_1324583618
#define _TEXTUREMANAGER_H__Included_1324583618

#include "CoreLib/AssetManager.h"
#include "RendererLib/RendererTypes.h"

namespace ZGE
{
	class ITexture;

	class ITextureManager : public CAssetManager< ITexture >
	{
	public:

		ITextureManager( )
		{
			m_kpcManagerId = "Texture manager";
		}

		virtual ~ITextureManager(void){}

		/*
		*	Creates a render target
		*	Param _kfWidth  : The width of the render terget
		*	Param _kfHeight : The height of th erender target
		*	Param _keFMT	: The render targets format
		*	Return : ITexture, The render target
		*/
		virtual ITexture* CreateRenderTarget( CAssetId& _rAssetId, const uint32 _kuWidth, const uint32 _kuHeight, const ESurfaceFormat _keFMT, const bool _bWriteOnly  ) = 0;
		/*
		*	Returns the defult render target
		*/
		virtual ITexture* GetDefaultRT( ) = 0;
		/*
		*	Retunrs the defaul depth target
		*/
		virtual ITexture* GetDefaultDT( ) = 0;	
		/*
		*	Returns a null texture 
		*/
		virtual ITexture* GetNULLTexture( ) = 0;
	protected:


	};
}// end namespace

#endif //_TEXTUREMANAGER_H__Included_1324583618

