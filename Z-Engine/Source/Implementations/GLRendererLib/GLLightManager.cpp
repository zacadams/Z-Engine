/**
 *	@file Z-Engine\Z-Engine\Implementations\GLRendererLib\GLLightManager.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "GLLIght.h"
#include "GLLightManager.h"
using namespace ZGE;
CGLLightManager::CGLLightManager(void)
{
}

CGLLightManager::~CGLLightManager(void)
{
}

/*
*	Creates a light using the parsed in description
*	Param _krLightDec : The lights description
*/
bool CGLLightManager::CreateLight( CLighDecription& _rLightDesc, ILight*& _pAsset )
{
	_pAsset = new CGLLight( _rLightDesc );
	return true;
}

/*
*	To be overriden to load assets of a derived manager.
*	Param _rAssetId : The assets id, ( could be the file name ).
*	Param _pAsset   : To be populated with the loaded asset.
*	Return : Success.
*/
bool CGLLightManager::LoadAsset( CAssetId& _rAssetId, ILight*& _pAsset )
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
bool CGLLightManager::ReleaseAsset( ILight* _pAsset )
{
	delete reinterpret_cast< CGLLight* >( _pAsset );
	_pAsset = NULL;
	return false;
}