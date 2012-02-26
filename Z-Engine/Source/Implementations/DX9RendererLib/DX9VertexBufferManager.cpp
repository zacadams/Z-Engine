/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Implementations\DX9RendererLib\DX9VertexBufferManager.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "RendererLib/VertexBuffer.h"
#include "DX9RendererLib/DX9VertexBuffer.h"
#include "DX9RendererLib/DX9VertexBufferManager.h"
using namespace ZGE;
CDX9VertexBufferManager::CDX9VertexBufferManager(void)
{
}

CDX9VertexBufferManager::~CDX9VertexBufferManager(void)
{
}

/**
* Creates a vertex buffer.
* @param _rAssetId The vertex buffers asset id.
*/
IVertexBuffer* CDX9VertexBufferManager::CreateVertexBuffer( CAssetId& _rAssetId )
{
	IVertexBuffer* pVertexBuffer = NULL;
	pVertexBuffer = GetAssetById( _rAssetId );
	if( pVertexBuffer )
	{
		pVertexBuffer->AddRef( );
		return pVertexBuffer;
	}

	// Vertex buffer does not exist
	pVertexBuffer = new CDX9VertexBuffer( );
	pVertexBuffer->SetAssetId( _rAssetId );
	AddPreCreatedAsset( _rAssetId, pVertexBuffer );
	pVertexBuffer->AddRef( );
	return pVertexBuffer;
}


/**
*	To be overriden to load assets of a derived manager.
*	Param _rAssetId : The assets id, ( could be the file name ).
*	Param _pAsset   : To be populated with the loaded asset.
*	Return : Success.
*/
bool CDX9VertexBufferManager::LoadAssetImplementation( CAssetId& _rAssetId, tAsset*& _pAsset )
{
	assert_now( "This function not intended to be used!, use CreateVertexBuffer( )" );
	return false;
}

/**
*	To be overidden to release a managers assets.
*	Param _pAsset : The asset to release.
*	Return : Success.
*/
bool CDX9VertexBufferManager::ReleaseAsset( tAsset* _pAsset )
{
	delete reinterpret_cast< CDX9VertexBuffer* >( _pAsset );
	return true;
}
