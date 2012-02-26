/**
 *	@file Z-Engine\Z-Engine\Implementations\GLRendererLib\GLMaterialManager.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "GLMaterial.h"
#include "GLMaterialManager.h"

using namespace ZGE;
CGLMaterialManager::CGLMaterialManager(void)
{
}

CGLMaterialManager::~CGLMaterialManager(void)
{
}
/*
*	Creates a material using a material description
*	Param _rAssetyId : The materials id
*	Param _rMaterialDesc : Containes the materials properties
*	Param _pAsset	: To be populated with the IMaterial instance
*/
bool CGLMaterialManager::CreateMaterial( CAssetId& _rAssetId, CMaterialDecription& _rMaterialDesc, IMaterial*& _pAsset )
{
	UNUSED_VAR( _rAssetId );
	_pAsset = new CGLMaterial( _rMaterialDesc );
	return true;
}

/*
*	To be overriden to load assets of a derived manager.
*	Param _rAssetId : The assets id, ( could be the file name ).
*	Param _pAsset   : To be populated with the loaded asset.
*	Return : Success.
*/
bool CGLMaterialManager::LoadAsset( CAssetId& _rAssetId, IMaterial*& _pAsset )
{
	UNUSED_VAR( _pAsset );
	UNUSED_VAR( _rAssetId );
	return false;
}

/*
*	To be overidden to release a managers assets.
*	Param _pAsset : The asset to release.
*	Return : Success.
*/
bool CGLMaterialManager::ReleaseAsset( IMaterial* _pAsset )
{
	delete reinterpret_cast< CGLMaterial* >( _pAsset );
	_pAsset = NULL;
	return false;
}