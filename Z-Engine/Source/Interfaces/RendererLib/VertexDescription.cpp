 /*	@file Z-Engine\Z-Engine\Interfaces\RendererLib\VertexDescription.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
 // Z-Engine includes
#include "CoreLib/Core.h"
#include "CoreLib/AssetId.h"

// Library includes
#include <stdio.h>

// Local includes 
#include "RendererLib/VertexElement.h"

#include "RendererLib/VertexDescription.h"



using namespace ZGE;

CVertexDescription::CVertexDescription(void)
: m_uElementCount( 0 )
, m_AssetId( "NEED TO SET AN ID! " )
, m_uStride( 0 )
{
	
}

CVertexDescription::CVertexDescription( const CVertexDescription& _kr )
: m_AssetId( _kr.m_AssetId )
{
	for( uint32 i = 0; i < _kr.m_uElementCount; ++i )
	{
		m_pVertexElements[i] = _kr.m_pVertexElements[i];
	}
	m_uStride = _kr.m_uStride;
	m_uElementCount = _kr.m_uElementCount;
	
}

CVertexDescription::~CVertexDescription(void)
{
	//SafeDeleteArray( m_pVertexElements );
	//SafeDeleteArray( m_pStrides );
}
/*
*	Overloaded to pass a descritions data on creation.
*	Param _pVertexElements : An array of vertex element that create a description.
*	Param _kuCount		   : The number of elements
*	Param _kuStride		   : The size of a vertex 
*	Param _uStream		   : The target stream
*/
CVertexDescription::CVertexDescription( CVertexElement* _pVertexElements, const uint32 _kuCount, const uint32 _kuStride, uint32 _kuStrideCount, const uint32 _kuStreamTarget )
: m_AssetId( "NEED TO SET AN ID! " )
{
	m_uStreamTarget = _kuStreamTarget;
	m_uElementCount = _kuCount;

	//m_pVertexElements = new CVertexElement[_kuCount];

	for( uint32 i = 0; i < _kuCount; ++i )
	{
		m_pVertexElements[i] = _pVertexElements[i];
	}

	m_uStride = _kuStride;
	//m_uStrideCounts = _kuStrideCount;
	//m_pStrides = new uint32[_kuStrideCount];
	//for( uint32 i = 0; i < _kuStrideCount; ++i )
	//{
	//	m_pStrides[i] = _pStrides[i];	
	//}
}
/*
*	retrives a descriptions element at the specified index.
*	Return : CVertexElement. 
*/
CVertexElement& CVertexDescription::GetElement( const uint32 _kuElement )
{
	// Is the index valid
	assert_msg( _kuElement < m_uElementCount, "Element index to big!" );
	return m_pVertexElements[_kuElement];
}
/*
*	Return: the number of vertex elemensts containes in the description.
*/
uint32 CVertexDescription::GetElementCount( ) const
{
	return m_uElementCount;
}
/*
*	Generates an asset id for the decsription.
*	Return : The descriptions asset id.
*/
CAssetId& CVertexDescription::CreateAssetId( )
{
	// loop throught for all elements

	//static char* kpcSemanticIds[] = 
	//{
	//	"POSITIONT", //	ES_POSITIONT,	//!< Pre transformed position, posi
	//				//   Note: a vertex with this seman
	//	"POSITION",	//  ES_POSITION,	//!< un transformed position, will 
	//	"COLOUR",	//	ES_COLOUR,		//!< Colour of a vertex
	//	"NORMAL",	//	ES_NORMAL,		//!< Vertex normal
	//	"BINORMAL",	//	ES_BINORMAL,	//!< Binormal, used in basis vector
	//	"TANGENT",	//	ES_TANGENT,		//!< Tangent, used in basis vectors	
	//};

	//static char* kpcTypeIds[] = 
	//{
	//	"FlOAT32",	//	ET_FLOAT32,	//!< 32 bit floating point number
	//	"FLOAT16",	//	ET_FLOAT16,	//!< 16 bit floating point number
	//	"UINT8",	//	ET_UINT8,	//!< unsigned 8 bit integer
	//	"UINT32",	//	ET_UINT32,	//!< unsigned 32 bit intiger
	//};

	//char pId[512];
	//for( uint32 i = 0; i < m_uElementCount; ++i )
	//{
	//	// offset

	//	char* pOffset[10];
	//	sprintf_s( pOffset, "%d", m_pVertexElements[i].GetCount( ) );

	//	// semantice 

	//	const char* kpcSemantice = kpcSemanticIds[m_pVertexElements[i].GetSemantic( ) ];

	//	// someting 
	//	
	//	const char* kpcSomeThing = "0";

	//	// type 

	//	const char* kpcType = kpcType[m_pVertexElements[i].GetType( ) ];

	//	// count

	//	char pCount[10];
	//	sprintf_s( pCount, "%d", m_pVertexElements[i].GetCount( ) );
	//}

	return m_AssetId;
}

/*
* Returns the vertex element with the specified semantic
* Param _krSemantic : The semantice of the required element
* Param _rVertexElement : To be populated with the wanted element
* Return : True if the element exist
*/
bool CVertexDescription::GetElement( const CVertexElement::EElementSemantic& _krSemantic, CVertexElement& _rVertexElement )
{
	for( uint32 i = 0; i < m_uElementCount; ++i )
	{
		if( m_pVertexElements[i].GetSemantic( ) == _krSemantic )
		{
			_rVertexElement = m_pVertexElements[i];
			return true;
		}
	}
	return false;
}
/**
 * Adds a vertex element to the vertx description.
 * @param _rVertexElement The element to add.
 * @return Success
 */
bool CVertexDescription::AddElement( CVertexElement& _rVertexElement )
{
	if( m_uElementCount != CVertexElement::ES_COUNT )
	{
		m_pVertexElements[m_uElementCount++] = _rVertexElement;

		//if( NULL == m_pStrides )
		//{
	//		m_pStrides = new uint32[1]; 
//			m_pStrides[0]=0;
	//	}
		// Add 4 bytes * the number of values
		//m_pStrides[0] += ( 4 * _rVertexElement.GetCount( ) );
		m_uStride += ( 4 * _rVertexElement.GetCount( ) );

		return true;
	}
	return false;
}

