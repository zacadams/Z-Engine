/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9VertexDeclarationManager.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/

#include "CoreLib/Core.h"
#include "DX9RendererLib/DX9Renderer.h"
// Vertex includes 

#include "RendererLib/VertexDeclaration.h"
#include "RendererLib/VertexDescription.h"
#include "RendererLib/VertexElement.h"
#include "DX9RendererLib/DX9VertexDeclaration.h"


#include "DX9RendererLib/DX9VertexDeclarationManager.h"

using namespace ZGE;

CDX9VertexDeclarationManager::CDX9VertexDeclarationManager(  )
: m_pDefaultDecl ( NULL )
{

	uint32 uStride = 24;
	CVertexElement pElements[3] = 
	{
		CVertexElement( 0, CVertexElement::ES_POSITIONT, 0, CVertexElement::ET_FLOAT32, 3 ),
		CVertexElement( 12, CVertexElement::ES_COLOUR,    0, CVertexElement::ET_UINT8,   4 ),
		CVertexElement( 16, CVertexElement::ES_TEXCOORD,    0, CVertexElement::ET_FLOAT32,  2 ),
	};

	CVertexDescription Desc( pElements, 3, uStride, 1 );
	m_pDefaultDecl = new CDX9VertexDeclaration( Desc, CDX9Renderer::GetDevice( ), this );


}

CDX9VertexDeclarationManager::~CDX9VertexDeclarationManager(void)
{
	SafeDelete( m_pDefaultDecl );
}
/*
*	To be overriden to load assets of a derived manager.
*	Param _rAssetId : The assets id, ( could be the file name ).
*	Param _pAsset   : To be populated with the loaded asset.
*	Return : Success.
*/
bool CDX9VertexDeclarationManager::LoadAssetImplementation( CAssetId& _rAssetId, IVertexDeclaration*& _pAsset )
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
bool CDX9VertexDeclarationManager::ReleaseAsset( IVertexDeclaration* _pAsset )
{
	delete reinterpret_cast< CDX9VertexDeclaration* >( _pAsset );
	_pAsset = NULL;
	return true;
}
/*
*	Creates a vertex declaraton using a vertex description.
*	Param _rDesc : The vertex description.
		*	Param _pAsset : To be pop[ulated with the created asset
*	Return : Success. 
*/
bool CDX9VertexDeclarationManager::CreateDeclaration( CVertexDescription& _rDesc, IVertexDeclaration*& _pAsset )
{

	// Craete a asset id for the description
	
	CAssetId AssetId( "VertexDecl" );

	// Does the asset exist?
	IVertexDeclaration* pDecl = GetAssetById( _rDesc.CreateAssetId( ) );
	
	if( pDecl )
	{
		// Exists 
		pDecl->AddRef( );
		_pAsset = pDecl;
		return true;
	}

	// does not exist, create the asset

	_pAsset = new CDX9VertexDeclaration( _rDesc, CDX9Renderer::GetDevice( ), this );
	// We are not usin the interface load asset. 
	// So we have to add the asset to the managers list manualy
	AddPreCreatedAsset( AssetId, _pAsset );
	return true;
}
/*
* Returns athe deafult vertex declaration
*/
IVertexDeclaration* CDX9VertexDeclarationManager::GetDefaultDecl( )
{
	return m_pDefaultDecl;
}
/*
* Returns the currently set vertex declaration
*/
IVertexDeclaration*  CDX9VertexDeclarationManager::GetActiveDeclaration( )
{
	return m_pActiveDecl;
}

// Sets the active vertex declaration
void CDX9VertexDeclarationManager::SetActiveDecl( IVertexDeclaration* _pDecl )
{
	m_pActiveDecl = _pDecl;
}