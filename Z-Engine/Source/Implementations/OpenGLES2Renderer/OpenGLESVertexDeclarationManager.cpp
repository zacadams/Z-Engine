/**
 *	@file Z-Engine\Z-Engine\Source\Implementations\OpenGLES2Renderer\OpenGLESVertexDeclarationManager.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes
#include "CoreLib/Core.h"
// Library includes

#include "RendererLib/VertexDescription.h"
#include "RendererLib/VertexElement.h"

#include "OpenGLES2Renderer/OpenGLESVertexDeclaration.h"
// Local includes 

#include "OpenGLES2Renderer/OpenGLESVertexDeclarationManager.h"
using namespace ZGE;
COpenGLESVertexDeclarationManager::COpenGLESVertexDeclarationManager( )
: m_pActiveDecl ( NULL )
{

	uint32 uStride = 24;
	CVertexElement pElements[3] = 
	{
		CVertexElement( 0, CVertexElement::ES_POSITIONT, 0, CVertexElement::ET_FLOAT32, 3 ),
		CVertexElement( 12, CVertexElement::ES_COLOUR,    0, CVertexElement::ET_UINT8,   4 ),
		CVertexElement( 16, CVertexElement::ES_TEXCOORD,    0, CVertexElement::ET_FLOAT32,  2 ),
	};

	CVertexDescription Desc( pElements, 3, uStride, 1 );
	if( false == CreateDeclaration( Desc, m_pDefaultDecl ) )
	{
		assert_now( "Failed to crate default DirectX vertex declaration!" );
	}
}

COpenGLESVertexDeclarationManager::~COpenGLESVertexDeclarationManager()
{
	SafeDelete( m_pDefaultDecl );
}

/*
*	Creates a vertex declaraton using a vertex description.
*	Param _rDesc  : The vertex description.
*	Param _pAsset : To be pop[ulated with the created asset
*	Return : Success. 
*/
bool COpenGLESVertexDeclarationManager::CreateDeclaration( CVertexDescription& _rDesc, IVertexDeclaration*& _pAsset  )
{
	_pAsset = new COpenGLESVertexDeclaration( _rDesc, this );
	return true;
}


/**
 *	To be overriden to load assets of a derived manager.
 *	Param _rAssetId : The assets id, ( could be the file name ).
 *	Param _pAsset   : To be populated with the loaded asset.
 *	Return : Success.
 */
bool COpenGLESVertexDeclarationManager::LoadAssetImplementation( CAssetId& _rAssetId, IVertexDeclaration*& _pAsset )
{
	return false;
}

/*
*	To be overidden to release a managers assets.
*	Param _pAsset : The asset to release.
*	Return : Success.
*/
bool COpenGLESVertexDeclarationManager::ReleaseAsset( IVertexDeclaration* _pAsset )
{
	delete reinterpret_cast< COpenGLESVertexDeclarationManager* > ( _pAsset );
	_pAsset = NULL;
	return false;
}

/*
* Returns athe deafult vertex declaration
*/
IVertexDeclaration* COpenGLESVertexDeclarationManager::GetDefaultDecl( )
{
	return m_pDefaultDecl;
}

/*
* Returns the currently set vertex declaration
*/
IVertexDeclaration* COpenGLESVertexDeclarationManager::GetActiveDeclaration( )
{
	return m_pActiveDecl;
}
// Sets the active vertex declaration
void COpenGLESVertexDeclarationManager::SetActiveDecl( IVertexDeclaration* _pDecl )
{
	m_pActiveDecl = _pDecl;
}
