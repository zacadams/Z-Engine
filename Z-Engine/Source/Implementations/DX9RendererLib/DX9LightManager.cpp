/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9LightManager.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/


#include "CoreLib/Core.h"
#include "DX9RendererLib/DX9Renderer.h"

#include "RendererLib/Light.h"
#include "DX9RendererLib/DX9Light.h"

#include "DX9RendererLib/DX9LightManager.h"

using namespace ZGE;

CDX9LightManager::CDX9LightManager( )
{
}

CDX9LightManager::~CDX9LightManager(void)
{
}
/*
*	Creates a light using the parsed in description
*	Param _krLightDec : The lights description
*/
bool CDX9LightManager::CreateLight( CLighDecription& _krLightDesc, ILight*& _pAsset )
{
	_pAsset = new CDX9Light( CDX9Renderer::GetDevice( ), _krLightDesc );
	
	return false;
}
/*
*	To be overriden to load assets of a derived manager.
*	Param _rAssetId : The assets id, ( could be the file name ).
*	Param _pAsset   : To be populated with the loaded asset.
*	Return : Success.
*/
bool CDX9LightManager::LoadAssetImplementation( CAssetId& _rAssetId, ILight*& _pAsset )
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
bool CDX9LightManager::ReleaseAsset( ILight* _pAsset )
{
	delete reinterpret_cast< CDX9Light* >( _pAsset );
	_pAsset = NULL;
	return true;
}