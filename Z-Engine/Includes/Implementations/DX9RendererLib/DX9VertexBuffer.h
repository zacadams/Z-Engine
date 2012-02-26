/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9VertexBuffer.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _DX9VERTEXBUFFER_H__Included_1942285779
#define _DX9VERTEXBUFFER_H__Included_1942285779

#include "RendererLib/VertexBuffer.h"


struct IDirect3DVertexBuffer9;
struct IDirect3DDevice9;

namespace ZGE
{
	// DirectX vertex buffer implementation 
	class CDX9VertexBuffer : public IVertexBuffer
	{
	public:
		CDX9VertexBuffer( );
		~CDX9VertexBuffer(void);

		// Initialises the vertex buffer.
		// _kuVertexCount : The number of vertices.
		// _kuStride The size of a vertex.
		// _pVertices The vertex data.
		// _bDynamic Determins if the buffer is dynamic.
		// return Success.
		virtual bool Initialise( const uint32 _kuVertexCount, const uint32 _kuStride, IVertexDeclaration* _pVertexDecl, bool _bDynamic = false );

		// Locks the vertex buffer and accesses the specified data.
		// Param _kuSize   : The size of the vertex data to lock
		// Param _kuOffSet : The position to lock from
		// Return : void* containin the nedded data
		virtual bool Lock( const uint32 _kuSize, const uint32 _kuOffSet,   void*& _pVertices, bool _bReadOnly = false  );

		// Un-locks the vertex buffer
		virtual bool Unlock( );

		// Applies the vertex buffer onto the device.
		virtual bool Apply( );
	protected:

		IDirect3DVertexBuffer9* m_pDX9VertexBuffer;	//!< The directX vertex buffer.
		IVertexDeclaration*     m_pVertexDecl;
	};
}//end namespace

#endif //_DX9VERTEXBUFFER_H__Included_1942285779

