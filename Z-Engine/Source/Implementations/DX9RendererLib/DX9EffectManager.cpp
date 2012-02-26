/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9EffectManager.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/


#include "CoreLib/Core.h"

#include "DX9RendererLib/DX9Effect.h"

#include <stdio.h>

#include <d3dx9.h>

#include "DX9RendererLib/DX9EffectManager.h"

using namespace ZGE;
CDX9EffectManager::CDX9EffectManager(  )
{
}

CDX9EffectManager::~CDX9EffectManager(void)
{
}

/*
*	Overriden to create IEffects
*	Param _rAssetId : The assets id, ( could be the file name ).
*	Param _pAsset   : To be populated with the loaded asset.
*	Return : Success.
*/
bool CDX9EffectManager::LoadAssetImplementation( CAssetId& _rAssetId, IEffect*& _pAsset )
{
	ID3DXEffect* pEffect = NULL;

	// Open the effect file
	FILE* pFile = NULL;
	fopen_s( &pFile, _rAssetId.GetFileName( ), "r" );
	
	// Find the end of the file
	fseek (pFile , 0 , SEEK_END);
	uint32 uSize = ftell (pFile);
	rewind (pFile);

	// Create a new buffer for the file
	char* pBuffer = new char[uSize];

	// Read in the effect file
	uint32 uReadSize = fread( pBuffer, 1, uSize, pFile );
	pBuffer[uReadSize] = 0;	// set the end of the buffer to be a null character

	// close the effect file
	fclose( pFile ); 

	ID3DXBuffer* pErrorBuffer = NULL;

	if( D3DXCreateEffect( m_pDevice, pBuffer, uReadSize, 0, 0, 0, 0, &pEffect, &pErrorBuffer ) )
	{
		// failed to create the effect, get the error message
		char* pError =  reinterpret_cast< char*>( pErrorBuffer->GetBufferPointer( ) );
		OutputDebugStringA( pError );
		delete [] pBuffer;	// Delete the buffer
		return false;	// rerturn failure
	}
	// Success, craete the effect
	_pAsset = new CDX9Effect( m_pDevice, pEffect );

	// delete the buffer
	delete [] pBuffer;

	// return success 
	return true;
}

/*
*	Overriden to release IEffects .
*	Param _pAsset : The asset to release.
*	Return : Success.
*/
bool CDX9EffectManager::ReleaseAsset( IEffect* _pAsset )
{
	delete reinterpret_cast< CDX9Effect* >( _pAsset );
	_pAsset = NULL;
	return true;
}

/*
* Returns the default rendering effect.
* Defualts to rendering a mesh with diffuse textures
* and materials using the fixed function pipeline.
*/
IEffect* CDX9EffectManager::GetDefaultEffect( )
{
	return NULL;
}