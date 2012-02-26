/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\RendererLib\VertexBufferManager.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _VERTEXBUFFERMANAGER_H__Included_1244336710
#define _VERTEXBUFFERMANAGER_H__Included_1244336710
#include "CoreLib/AssetManager.h"
namespace ZGE
{
	class IVertexBuffer;
	class IVertexBufferManager : public CAssetManager< IVertexBuffer >
	{
	public:
		virtual ~IVertexBufferManager( ){ }

		/**
		 * Creates a vertex buffer.
		 * @param _rAssetId The vertex buffers asset id.
		 */
		virtual IVertexBuffer* CreateVertexBuffer( CAssetId& _rAssetId ) = 0; 
	protected:
	};
}
#endif //_VERTEXBUFFERMANAGER_H__Included_1244336710

