/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9MaterialManager.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _DX9MATERIALMANAGER_H__Included_161211422
#define _DX9MATERIALMANAGER_H__Included_161211422

#include "RendererLib/MaterialManager.h"

struct IDirect3DDevice9;
namespace ZGE
{
	class IMaterial;

	class CDX9MaterialManager : public IMaterialManager
	{
	public:
		CDX9MaterialManager( );
		~CDX9MaterialManager(void);
		
		/*
		*	Creates a material using a material description
		*	Param _rAssetyId : The materials id
		*	Param _rMaterialDesc : Containes the materials properties
		*	Param _pAsset	: To be populated with the IMaterial instance
		*/
		virtual bool CreateMaterial( CAssetId& _rAssetId, CMaterialDecription& _rMaterialDesc, IMaterial*& _pAsset );
	protected:
		/*
		*	To be overriden to load assets of a derived manager.
		*	Param _rAssetId : The assets id, ( could be the file name ).
		*	Param _pAsset   : To be populated with the loaded asset.
		*	Return : Success.
		*/
		virtual bool LoadAssetImplementation( CAssetId& _rAssetId, IMaterial*& _pAsset );

		/*
		*	To be overidden to release a managers assets.
		*	Param _pAsset : The asset to release.
		*	Return : Success.
		*/
		virtual bool ReleaseAsset( IMaterial* _pAsset );
		
	protected:
	};
}

#endif //_DX9MATERIALMANAGER_H__Included_161211422

