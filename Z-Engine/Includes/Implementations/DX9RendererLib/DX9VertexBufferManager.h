/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Implementations\DX9RendererLib\DX9VertexBufferManager.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _DX9VERTEXBUFFERMANAGER_H__Included_2091860392
#define _DX9VERTEXBUFFERMANAGER_H__Included_2091860392
#include "RendererLib/VertexBufferManager.h"
namespace ZGE
{
	class CDX9VertexBufferManager : public IVertexBufferManager
	{
	public:
		CDX9VertexBufferManager(void);
		~CDX9VertexBufferManager(void);

				/**
		 * Creates a vertex buffer.
		 * @param _rAssetId The vertex buffers asset id.
		 */
		virtual IVertexBuffer* CreateVertexBuffer( CAssetId& _rAssetId ); 

				/**
		 *	To be overriden to load assets of a derived manager.
		 *	Param _rAssetId : The assets id, ( could be the file name ).
		 *	Param _pAsset   : To be populated with the loaded asset.
		 *	Return : Success.
		 */
		virtual bool LoadAssetImplementation( CAssetId& _rAssetId, tAsset*& _pAsset );

		/**
		 *	To be overidden to release a managers assets.
		 *	Param _pAsset : The asset to release.
		 *	Return : Success.
		 */
		virtual bool ReleaseAsset( tAsset* _pAsset );
	};
}

#endif //_DX9VERTEXBUFFERMANAGER_H__Included_2091860392

