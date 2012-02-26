/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9TextureManager.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _DX9TEXTUREMANAGER_H__Included_1637172940
#define _DX9TEXTUREMANAGER_H__Included_1637172940

#include "RendererLib/TextureManager.h"

namespace ZGE
{
	class CDX9TextureManager : public ITextureManager
	{
	public:
		CDX9TextureManager( );
		~CDX9TextureManager(void);

		/*
		*	Creates a render target
		*	Param _kfWidth  : The width of the render terget
		*	Param _kfHeight : The height of th erender target
		*	Param _keFMT	: The render targets format
		*	Return : ITexture, The render target
		*/
		virtual ITexture* CreateRenderTarget( CAssetId& _rAssetId, const uint32 _kfWidth, const uint32 _kfHeight, const ESurfaceFormat _keFMT, const bool _bWriteOnly  );
		
	protected:
		/*
		*	To be overriden to load assets of a derived manager.
		*	Param _rAssetId : The assets id, ( could be the file name ).
		*	Param _pAsset   : To be populated with the loaded asset.
		*	Return : Success.
		*/
		virtual bool LoadAssetImplementation( CAssetId& _rAssetId, ITexture*& _pAsset );

		/*
		*	To be overidden to release a managers assets.
		*	Param _pAsset : The asset to release.
		*	Return : Success.
		*/
		virtual bool ReleaseAsset( ITexture* _pAsset );
	public:
		/*
		*	Returns the defult render target
		*/
		virtual ITexture* GetDefaultRT( );
		/*
		*	Retunrs the defaul depth target
		*/
		virtual ITexture* GetDefaultDT( );	
				/*
		*	Returns a null texture 
		*/
		virtual ITexture* GetNULLTexture( );

	protected:

		ITexture*		  m_pDefaultRT;
		ITexture*		  m_pDefaultDT;
		ITexture*		  m_pNULLTexture;

	};
}// end namespace 

#endif //_DX9TEXTUREMANAGER_H__Included_1637172940

