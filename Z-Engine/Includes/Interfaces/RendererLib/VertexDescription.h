/**
 *	@file Z-Engine\Z-Engine\Interfaces\RendererLib\VertexDescription.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _VERTEXDESCRIPTION_H__Included_1286210658
#define _VERTEXDESCRIPTION_H__Included_1286210658

#include "CoreLib/AssetId.h"
#include "RendererLib/VertexElement.h"
namespace ZGE
{
	class CVertexElement;
	class CAssetId;

	class CVertexDescription
	{
	public:
		CVertexDescription( );
		CVertexDescription( const CVertexDescription& _kr );
		~CVertexDescription(void);

		/*
		*	Overloaded to pass a descritions data on creation.
		*	Param _pVertexElements : An array of vertex element that create a description.
		*	Param _kuCount		   : The number of elements
		*	Param _kuStride		   : The size of a vertex 
		*	Param _uStream		   : The target stream
		*/
		CVertexDescription( CVertexElement* _pVertexElements, const uint32 _kuCount, const uint32 _kuStride, uint32 _kuStrideCount, const uint32 _kuStreamTarget = 0 );
		/*
		*	retrives a descriptions element at the specified index.
		*	Return : CVertexElement. 
		*/
		CVertexElement& GetElement( const uint32 _kuElement );

		/*
		*	Return: the number of vertex elemensts containes in the description.
		*/
		uint32 GetElementCount( ) const;

		/*
		*	Generates an asset id for the decsription.
		*	Return : The descriptions asset id.
		*/
		CAssetId& CreateAssetId( );

		/*
		* Returns the vertex element with the specified semantic
		* Param _krSemantic : The semantice of the required element
		* Param _rVertexElement : To be populated with the wanted element
		* Return : True if the element exist
		*/
		bool GetElement( const CVertexElement::EElementSemantic& _krSemantic, CVertexElement& _rVertexElement ); 

		/**
		 * Adds a vertex element to the vertx description.
		 * @param _rVertexElement The element to add.
		 * @return Success
		 */
		bool AddElement( CVertexElement& _rVertexElement );

		/**
		 * @return The stride at the index.
	 	 */
		inline uint32 GetStride(  ){ return m_uStride; }

		inline uint32 GetTargetStream( ) const { return m_uStreamTarget; }


	protected:

		CVertexElement m_pVertexElements[CVertexElement::ES_COUNT]; //!< The array of vertex element that make up a vertex structure.
		uint32			m_uElementCount;							//!< The number of element in the decription.
		uint32			m_uStride;									//!< The stride of the vertec
		uint32			m_uStrideCounts;
		uint32			m_uStreamTarget;

		CAssetId m_AssetId;
	};
}// end namespace

#endif //_VERTEXDESCRIPTION_H__Included_1286210658

