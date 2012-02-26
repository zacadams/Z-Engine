/**
 *	@file Z-Engine\Z-Engine\Interfaces\RendererLib\VertexElement.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes
#include "CoreLib/Core.h"

// Library includes

// Local includes 


#include "RendererLib/VertexElement.h"


namespace ZGE
{
	CVertexElement::CVertexElement( )
	{
	}
	/*
	*	Over loaded contructor to take in vertex element data
	*	Param _kuOffset   : The offset in byte tha the element is from the start of a vertex
	*	Param _eSemantice : The elements use i.e posotion colour?
	*	Param _uSomething : ?
	*	Param _eType	  : The data's type, i.e 32 bit float ?
	*/
	CVertexElement::CVertexElement( const uint32 _kuOffset, CVertexElement::EElementSemantic _eSemantic, uint32 _uSomething, CVertexElement::EElementType _eType, const uint32 _kuCount, uint32 _uStream)
	: m_eType		( _eType )
	, m_uCount		( _kuCount )
	, m_eSemantic	( _eSemantic )
	, m_uOffset		( _kuOffset )
	, m_uTargetStream( _uStream )
	{
		UNUSED_VAR( _uSomething );
	}

	CVertexElement::~CVertexElement(void)
	{
	}
	/*
	*	Return : The elements offset in bytes from the start of a vertex.
	*/
	uint32 CVertexElement::GetOffset( ) const
	{
		return m_uOffset;
	}
	/*
	*	Return : The number of vertex element types in the semantic.
	*/
	uint32 CVertexElement::GetCount( ) const
	{
		return m_uCount;
	}
	/*
	*	Return : The semantices data type.
	*/
	CVertexElement::EElementType CVertexElement::GetType( ) const
	{
		return m_eType;
	}
	/*
	*	Return : The elements semantic.
	*/
	CVertexElement::EElementSemantic CVertexElement::GetSemantic( ) const
	{
		return m_eSemantic;
	}
	/*
	*	Return : The vertex elements stream target
	*/
	uint32 CVertexElement::GetTargetStream( ) const
	{
		return m_uTargetStream;
	}
}