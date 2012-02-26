/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9EffectManager.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _DX9EFFECTMANAGER_H__Included_183809737
#define _DX9EFFECTMANAGER_H__Included_183809737

#include "RendererLib/EffectManager.h"

struct IDirect3DDevice9;

namespace ZGE
{
	class IEffect;
	class CDX9EffectManager : public IEffectManager
	{
	public:
		CDX9EffectManager(  );
		~CDX9EffectManager(void);

	protected:
		/*
		*	Overriden to create IEffects
		*	Param _rAssetId : The assets id, ( could be the file name ).
		*	Param _pAsset   : To be populated with the loaded asset.
		*	Return : Success.
		*/
		virtual bool LoadAssetImplementation( CAssetId& _rAssetId, IEffect*& _pAsset );

		/*
		*	To be overidden to release a managers assets.
		*	Param _pAsset : The asset to release.
		*	Return : Success.
		*/
		virtual bool ReleaseAsset( IEffect* _pAsset );
	public:
		/*
		* Returns the default rendering effect.
		* Defualts to rendering a mesh with diffuse textures
		* and materials using the fixed function pipeline.
		*/
		virtual IEffect* GetDefaultEffect( );

	protected:

		IDirect3DDevice9* m_pDevice;
	};
}

#endif //_DX9EFFECTMANAGER_H__Included_183809737

