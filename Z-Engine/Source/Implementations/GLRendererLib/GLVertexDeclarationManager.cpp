/**
 *	@file Z-Engine\Z-Engine\Implementations\GLRendererLib\GLVertexDeclarationManager.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/

#include "CoreLib/Core.h"

#include "RendererLib/VertexDescription.h"
#include "RendererLib/VertexElement.h"

#include "GLVertexDeclaration.h"

#include "GLVertexDeclarationManager.h"

using namespace ZGE;
CGLVertexDeclarationManager::CGLVertexDeclarationManager(void)
: m_pActiveDecl ( NULL )
{

	uint32 uStride = 24;
	CVertexElement pElements[3] = 
	{
		CVertexElement( 0, CVertexElement::ES_POSITIONT, 0, CVertexElement::ET_FLOAT32, 3 ),
		CVertexElement( 12, CVertexElement::ES_COLOUR,    0, CVertexElement::ET_UINT8,   4 ),
		CVertexElement( 16, CVertexElement::ES_TEXCOORD,    0, CVertexElement::ET_FLOAT32,  2 ),
	};

	CVertexDescription Desc( pElements, 3, &uStride, 1 );
	if( false == CreateDeclaration( Desc, m_pDefaultDecl ) )
	{
		assert_now( "Failed to crate default DirectX vertex declaration!" );
	}


}

CGLVertexDeclarationManager::~CGLVertexDeclarationManager(void)
{
	SafeDelete( m_pDefaultDecl );
}
/*
*	Creates a vertex declaraton using a vertex description.
*	Param _rDesc  : The vertex description.
*	Param _pAsset : To be pop[ulated with the created asset
*	Return : Success. 
*/
bool CGLVertexDeclarationManager::CreateDeclaration( CVertexDescription& _rDesc, IVertexDeclaration*& _pAsset  )
{
	_pAsset = new CGLVertexDeclaration( _rDesc, this );
	return true;
}


/*
*	To be overriden to load assets of a derived manager.
*	Param _rAssetId : The assets id, ( could be the file name ).
*	Param _pAsset   : To be populated with the loaded asset.
*	Return : Success.
*/
bool CGLVertexDeclarationManager::LoadAsset( CAssetId& _rAssetId, IVertexDeclaration *& _pAsset )
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
bool CGLVertexDeclarationManager::ReleaseAsset( IVertexDeclaration* _pAsset )
{
	delete reinterpret_cast< CGLVertexDeclaration* > ( _pAsset );
	_pAsset = NULL;
	return false;
}

/*
* Returns athe deafult vertex declaration
*/
IVertexDeclaration* CGLVertexDeclarationManager::GetDefaultDecl( )
{
	return m_pDefaultDecl;
}

/*
* Returns the currently set vertex declaration
*/
IVertexDeclaration* CGLVertexDeclarationManager::GetActiveDeclaration( )
{
	return m_pActiveDecl;
}
// Sets the active vertex declaration
void CGLVertexDeclarationManager::SetActiveDecl( IVertexDeclaration* _pDecl )
{
	m_pActiveDecl = _pDecl;
}
