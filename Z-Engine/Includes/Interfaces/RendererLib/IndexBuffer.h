/**
 *	@file Z-Engine\Z-Engine\Interfaces\RendererLib\IndexBuffer.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _INDEXBUFFER_H__Included_1642553511
#define _INDEXBUFFER_H__Included_1642553511

namespace ZGE
{
	// ZEngines index buffer.
	class IIndexBuffer
	{
	public:
		enum EIndexType
		{
			IT_32 = 0,	// 32 bit indices
			IT_16,		// 16 bit indices
		};
	public:

		IIndexBuffer(void){ }
		virtual ~IIndexBuffer(void){ }

		// Locks the idex buffer for writing.
		// _kuStart index The offset into the buffer to start from.
		// _kuOffset The number of indices to lock from the start offset,
		virtual bool Lock( const uint32 _kuStartIndex, const uint32 _kuOffset, void*& _pIndices , bool _bReadOnly = false) = 0;

		// Unlocks the index buffer.
		virtual bool Unlock ( ) = 0;

		// Initialise 
		virtual bool Initialise( const uint32 _kuIndexCount, const EIndexType _keIndexType, bool _bDynamic = false) = 0;

		// Returns the size of the index buffer
		inline uint32 GetSize( ) const { return m_uSize; }

		// Applies the index buffer onto the device.
		virtual bool Apply( ) = 0;

	protected:
		uint32		m_uIndexCount;		//!< The number of indices in the buffer.
		EIndexType	m_eIndexType;		//!< The index type.
		uint32		m_uStride;			//!< The stride of each indice.
		uint32		m_uSize;			//!< The size in bytes of the indexbuffer.
	};
}

#endif //_INDEXBUFFER_H__Included_1642553511

