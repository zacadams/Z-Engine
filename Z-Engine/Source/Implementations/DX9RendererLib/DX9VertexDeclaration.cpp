/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9VertexDeclaration.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/

#include "CoreLib/Core.h"

// DX includes

#include <d3dx9.h>

// Vertex includes
#include "RendererLib/VertexDescription.h"
#include "RendererLib/VertexElement.h"

#include "DX9RendererLib/DX9VertexDeclarationManager.h"
#include "DX9RendererLib/DX9VertexDeclaration.h"

using namespace ZGE;

CDX9VertexDeclaration::CDX9VertexDeclaration( CVertexDescription& _rVertexDecsription, IDirect3DDevice9* _pDevice, CDX9VertexDeclarationManager* _pManager )
: m_pDevice( _pDevice )
, m_pD3DDecl( NULL )
, m_pManager ( _pManager )
{

	m_VertexDecsription=_rVertexDecsription;
	
	// DirectX look up tables

	static uint32 uSemantic[] = 
	{
		D3DDECLUSAGE_POSITIONT, //	ES_POSITIONT,	//!< Pre transformed position, posi
								//  Note: a vertex with this seman
		D3DDECLUSAGE_POSITION,	//  ES_POSITION,	//!< un transformed position, will 
		D3DDECLUSAGE_NORMAL,	//	ES_NORMAL,		//!< Vertex normal
		D3DDECLUSAGE_TEXCOORD,	//	ES_TEXCOORD
		D3DDECLUSAGE_COLOR,		//	ES_COLOUR,		//!< Colour of a vertex
		D3DDECLUSAGE_BINORMAL,	//	ES_BINORMAL,	//!< Binormal, used in basis vector
		D3DDECLUSAGE_TANGENT,	//	ES_TANGENT,		//!< Tangent, used in basis vectors	
		D3DDECLUSAGE_BLENDINDICES,//	ES_BLENDINDICES,
		D3DDECLUSAGE_BLENDWEIGHT,						//	ES_BLENDWEIGHTS,
	};

	static uint32 uTypes[][4] = 
	{
		D3DDECLTYPE_FLOAT1, D3DDECLTYPE_FLOAT2, D3DDECLTYPE_FLOAT3, D3DDECLTYPE_FLOAT4, 
		D3DDECLTYPE_UNUSED, D3DDECLTYPE_UNUSED, D3DDECLTYPE_UNUSED, D3DDECLTYPE_D3DCOLOR, 
	};

	uint32 uElemenCount = _rVertexDecsription.GetElementCount( );

	D3DVERTEXELEMENT9* pD3DElements = new D3DVERTEXELEMENT9[uElemenCount + 1];

	for( uint32 i = 0; i < uElemenCount; ++i )
	{
		CVertexElement VE = _rVertexDecsription.GetElement( i );

		pD3DElements[i].Type   = ( BYTE  )uTypes[VE.GetType()][ VE.GetCount( ) - 1 ];
		pD3DElements[i].Usage  = static_cast< BYTE >( uSemantic[VE.GetSemantic()] );
		pD3DElements[i].Offset = static_cast< WORD> ( VE.GetOffset( ) );
		pD3DElements[i].Stream = static_cast< WORD >( VE.GetTargetStream( ) );
		pD3DElements[i].Method = D3DDECLMETHOD_DEFAULT;
		pD3DElements[i].UsageIndex = 0;
	}


	//WORD Stream;
 //   WORD Offset;
 //   BYTE Type;
 //   BYTE Method;
 //   BYTE Usage;
 //   BYTE UsageIndex;

	 //{0xFF,0,D3DDECLTYPE_UNUSED, 0,0,0}

	pD3DElements[uElemenCount].Stream = 0xFF;
	pD3DElements[uElemenCount].Offset = 0;
	pD3DElements[uElemenCount].Type	  = D3DDECLTYPE_UNUSED;
	pD3DElements[uElemenCount].Method = 0;
	pD3DElements[uElemenCount].Usage  = 0;
	pD3DElements[uElemenCount].UsageIndex = 0;

	if( FAILED( m_pDevice->CreateVertexDeclaration( pD3DElements, &m_pD3DDecl ) ) )
	{
		int i = 0; i;
		assert_now( "Failed to create D3D vertex declaration" );
	}

	delete pD3DElements;
}

CDX9VertexDeclaration::~CDX9VertexDeclaration(void)
{
	SafeRelease( m_pD3DDecl );
}
/*
*	Applys the vertex declararion on tp the renderer
*/
bool CDX9VertexDeclaration::Apply( )
{
	if( SUCCEEDED( m_pDevice->SetVertexDeclaration( m_pD3DDecl ) ) )
	{
		m_pManager->SetActiveDecl( this );
		return true;
	}
	return false;
}
/*
*	Accessor to the vertex declaration description
*/
CVertexDescription& CDX9VertexDeclaration::GetDescription( )
{
	return m_VertexDecsription;
}