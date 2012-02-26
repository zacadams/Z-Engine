/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9LightManager.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _DX9LIGHTMANAGER_H__Included_1864350059
#define _DX9LIGHTMANAGER_H__Included_1864350059

#include "RendererLib/LightManager.h"

struct IDirect3DDevice9;

namespace ZGE
{
	class CDX9LightManager : public ILightManager
	{
	public:
		CDX9LightManager( );
		~CDX9LightManager(void);

		/*
		 *	Creates a light using the parsed in description
		 *	Param _krLightDec : The lights description
		 */
		virtual bool CreateLight( CLighDecription& _rLightDesc, ILight*& _pAsset );
	protected:

		/*
		*	To be overriden to load assets of a derived manager.
		*	Param _rAssetId : The assets id, ( could be the file name ).
		*	Param _pAsset   : To be populated with the loaded asset.
		*	Return : Success.
		*/
		virtual bool LoadAssetImplementation( CAssetId& _rAssetId, ILight*& _pAsset );

		/*
		*	To be overidden to release a managers assets.
		*	Param _pAsset : The asset to release.
		*	Return : Success.
		*/
		virtual bool ReleaseAsset( ILight* _pAsset );

	protected:
	};
}

#endif //_DX9LIGHTMANAGER_H__Included_1864350059

