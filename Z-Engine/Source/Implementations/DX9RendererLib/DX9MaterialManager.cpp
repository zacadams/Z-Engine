/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9MaterialManager.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/


#include "CoreLib/Core.h"
#include "DX9RendererLib/DX9Renderer.h"
#include "RendererLib/Material.h"
#include "DX9RendererLib/DX9Material.h"

#include "DX9RendererLib/DX9MaterialManager.h"


using namespace ZGE;

CDX9MaterialManager::CDX9MaterialManager( )
{
}

CDX9MaterialManager::~CDX9MaterialManager(void)
{
}

/*
*	Creates a material using a material description
*	Param _rAssetyId : The materials id
*	Param _rMaterialDesc : Containes the materials properties
*	Param _pAsset	: To be populated with the IMaterial instance
*/
bool CDX9MaterialManager::CreateMaterial( CAssetId& _rAssetId, CMaterialDecription& _rMaterialDesc, IMaterial*& _pAsset )
{
	UNUSED_VAR( _rAssetId );
	_pAsset = new CDX9Material( CDX9Renderer::GetDevice( ), _rMaterialDesc );
	// We are not usin the interface load asset. 
	// So we have to add the asset to the managers list manualy
	AddPreCreatedAsset( _rAssetId, _pAsset );
	return true;
}

/*
*	To be overriden to load assets of a derived manager.
*	Param _rAssetId : The assets id, ( could be the file name ).
*	Param _pAsset   : To be populated with the loaded asset.
*	Return : Success.
*/
bool CDX9MaterialManager::LoadAssetImplementation( CAssetId& _rAssetId, IMaterial*& _pAsset )
{
	UNUSED_VAR( _rAssetId );
	UNUSED_VAR( _pAsset );
	return false;
}
/*
*	To be overidden to release a managers assets.
*	Param _pAsset : The asset to release.
*	Return : Success.
*/
bool CDX9MaterialManager::ReleaseAsset( IMaterial* _pAsset )
{
	delete reinterpret_cast< CDX9Material* >( _pAsset );
	_pAsset = NULL;
	return true;
}