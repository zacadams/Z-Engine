/**
 *	@file Z-Engine\Z-Engine\Interfaces\RendererLib\VertexElement.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _VERTEXELEMENT_H__Included_1469249400
#define _VERTEXELEMENT_H__Included_1469249400

namespace ZGE
{
	class CVertexElement
	{
	public:

		/*
		*	Defines the type of data used for an elements semantic.
		*/
		enum EElementType
		{
			ET_FLOAT32 = 0,	//!< 32 bit floating point number
			ET_UINT8,	//!< unsigned 8 bit integer
		};

		/*
		*	Defines the use of a vertex element.
		*/
		enum EElementSemantic
		{
			ES_POSITIONT = 0,	//!< Pre transformed position, position in screen space, 
							//   Note: a vertex with this semantice will skip the lighting and transform stage in hardware
			ES_POSITION,	//!< un transformed position, will be transformed in the hardware stage
			ES_NORMAL,		//!< Vertex normal
			ES_TEXCOORD,	//!< Texture Coordinates
			ES_COLOUR,		//!< Colour of a vertex
			ES_BINORMAL,	//!< Binormal, used in basis vectors for 2D to 3D mapping, i.e normal mapping ect
			ES_TANGENT,		//!< Tangent, used in basis vectors
			ES_BLENDINDICES,
			ES_BLENDWEIGHTS,
			ES_COUNT,
		};
	
		CVertexElement( );
		/*
		*	Over loaded contructor to take in vertex element data
		*	Param _kuOffset   : The offset in byte tha the element is from the start of a vertex
		*	Param _eSemantice : The elements use i.e posotion colour?
		*	Param _uSomething : ?
		*	Param _eType	  : The data's type, i.e 32 bit float ?
		*/
		CVertexElement( const uint32 _kuOffset, CVertexElement::EElementSemantic _eSemantice, uint32 _uSomething, CVertexElement::EElementType _eType, const uint32 _kuCount, uint32 _uStream = 0);
		
		~CVertexElement(void);

		/*
		*	Return : The elements offset in bytes from the start of a vertex.
		*/
		uint32 GetOffset( ) const;
		/*
		*	Return : The number of vertex element types in the semantic.
		*/
		uint32 GetCount( ) const;
		/*
		*	Return : The semantices data type.
		*/
		EElementType GetType( ) const;
		/*
		*	Return : The elements semantic.
		*/
		EElementSemantic GetSemantic( ) const;

		/*
		*	Return : The vertex elements stream target
		*/
		uint32 GetTargetStream( ) const;

	protected:

		EElementType	 m_eType;		//!< The vertex element type
		uint32				 m_uCount;		//!< The number of verex types that a semantice containes 
		EElementSemantic m_eSemantic;	//!< The vertex element semantic 
		uint32				 m_uOffset;		//!< The offset in bytes from the start of the vertex
		uint32				 m_uTargetStream;
	};
}// end namespace

#endif //_VERTEXELEMENT_H__Included_1469249400

