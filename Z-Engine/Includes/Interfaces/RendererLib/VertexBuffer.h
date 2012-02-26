/**
 *	@file Z-Engine\Z-Engine\Interfaces\RendererLib\VertexBuffer.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _VERTEXBUFFER_H__Included_823099429
#define _VERTEXBUFFER_H__Included_823099429
#include "CoreLib/Asset.h"
namespace ZGE
{	
	class IVertexDeclaration;

	/*
	* A buffer of vertices
	*/
	class IVertexBuffer : public CAsset< IVertexBuffer >
	{
	public:
		IVertexBuffer(void){ }
		virtual ~IVertexBuffer(void){ }

		// Initialises the vertex buffer.
		// _kuVertexCount : The number of vertices.
		// _kuStride The size of a vertex.
		// _pVertices The vertex data.
		// _bDynamic Determins if the buffer is dynamic.
		// return Success.
		virtual bool Initialise( const uint32 _kuVertexCount, const uint32 _kuStride, IVertexDeclaration* _pVertexDecl, bool _bDynamic = false ) = 0;

		// Locks the vertex buffer and accesses the specified data.
		// Param _kuSize   : The size of the vertex data to lock
		// Param _kuOffSet : The position to lock from
		// Return : Success
		virtual bool Lock( const uint32 _kuSize, const uint32 _kuOffSet, void*& _pVertices, bool _bReadOnly = false  ) = 0;

		// Un-locks the vertex buffer
		virtual bool Unlock( ) = 0;

		// Applies the vertex buffer onto the device.
		virtual bool Apply( ) = 0;

		// Returns the bufferes vertex count
		inline const uint32 GetVertexCount( ) const { return m_uVertexCount; };

		// Returs the bufferes allocated size in bytes
		inline const uint32 GetSize( ) const { return m_uSize; }

		// Returns the stride of the buffers contained vertices
		inline const uint32 GetStride( ) const { return m_uStride; }

	protected:

		uint32 m_uVertexCount;  //!< The number of vertices contained by the buffer
		uint32 m_uSize;		    //!< The size of the buffer in bytes
		uint32 m_uStride;	    //!< The stride of the contained vertices
		bool   m_bDynamic;		//!< Determines if the vertex buffer is dynamic.
	};
}

#endif //_VERTEXBUFFER_H__Included_823099429

