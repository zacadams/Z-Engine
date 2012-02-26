/**
 *	@file Z-Engine\Z-Engine\Implementations\GLRendererLib\GLMaterialManager.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _GLMATERIALMANAGER_H__Included_2044738473
#define _GLMATERIALMANAGER_H__Included_2044738473

#include "RendererLib/MaterialManager.h"
namespace ZGE
{
	class CGLMaterialManager : public IMaterialManager
	{
	public:
		CGLMaterialManager(void);
		~CGLMaterialManager(void);

		/*
		*	Creates a material using a material description
		*	Param _rAssetyId : The materials id
		*	Param _rMaterialDesc : Containes the materials properties
		*	Param _pAsset	: To be populated with the IMaterial instance
		*/
		virtual bool CreateMaterial( CAssetId& _rAssetId, CMaterialDecription& _rMaterialDesc, IMaterial*& _pAsset );

				/*
		*	To be overriden to load assets of a derived manager.
		*	Param _rAssetId : The assets id, ( could be the file name ).
		*	Param _pAsset   : To be populated with the loaded asset.
		*	Return : Success.
		*/
		virtual bool LoadAsset( CAssetId& _rAssetId, IMaterial*& _pAsset );

		/*
		*	To be overidden to release a managers assets.
		*	Param _pAsset : The asset to release.
		*	Return : Success.
		*/
		virtual bool ReleaseAsset( IMaterial* _pAsset );
	};
}

#endif //_GLMATERIALMANAGER_H__Included_2044738473

