/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9IndexBuffer.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _DX9INDEXBUFFER_H__Included_902483470
#define _DX9INDEXBUFFER_H__Included_902483470

#include "RendererLib/IndexBuffer.h"

struct IDirect3DIndexBuffer9;

namespace ZGE
{
	// DirectX index buffer.
	class CDX9IndexBuffer : public IIndexBuffer
	{
	public:
		CDX9IndexBuffer(void);
		~CDX9IndexBuffer(void);

		// Lockes the imdex buffer for writing.
		// _kuStart index The offset into the buffer to start from.
		// _kuOffset The number of indices to lock from the start offset,
		virtual bool Lock( const uint32 _kuStartIndex, const uint32 _kuOffset, void*& _pIndices, bool _bReadOnly = false  );

		// Unlocks the index buffer.
		virtual bool Unlock ( );

		// Initialise 
		virtual bool Initialise( const uint32 _kuIndexCount, const EIndexType _keIndexType, bool _bDynamic = false );

				// Applies the index buffer onto the device.
		virtual bool Apply( );
	protected:
		IDirect3DIndexBuffer9* m_pDX9IndexBuffer;	//!< The XirectX index buffer.
	};
}

#endif //_DX9INDEXBUFFER_H__Included_902483470

