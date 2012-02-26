/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9VertexDeclarationManager.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _DX9VERTEXDECLARATIONMANAGER_H__Included_1144991067
#define _DX9VERTEXDECLARATIONMANAGER_H__Included_1144991067

#include "RendererLib/VertexDeclarationManager.h"

struct IDirect3DDevice9;

namespace ZGE
{
	class CDX9VertexDeclaration;
	class IVertexDeclaration;

	class CDX9VertexDeclarationManager : public IVertexDeclarationManager
	{
	public:
		CDX9VertexDeclarationManager(  );
		~CDX9VertexDeclarationManager(void);
	protected:
		/*
		*	To be overriden to load assets of a derived manager.
		*	Param _rAssetId : The assets id, ( could be the file name ).
		*	Param _pAsset   : To be populated with the loaded asset.
		*	Return : Success.
		*/
		virtual bool LoadAssetImplementation( CAssetId& _rAssetId, IVertexDeclaration*& _pAsset );

		/*
		*	To be overidden to release a managers assets.
		*	Param _pAsset : The asset to release.
		*	Return : Success.
		*/
		virtual bool ReleaseAsset( IVertexDeclaration* _pAsset );
	public:

		/*
		*	Creates a vertex declaraton using a vertex description.
		*	Param _rDesc  : The vertex description.
		*	Param _pAsset : To be pop[ulated with the created asset
		*	Return : Success. 
		*/
		virtual bool CreateDeclaration( CVertexDescription& _rDesc, IVertexDeclaration*& _pAsset  );

		/*
		* Returns athe deafult vertex declaration
		*/
		virtual IVertexDeclaration* GetDefaultDecl( );

		/*
		* Returns the currently set vertex declaration
		*/
		virtual IVertexDeclaration* GetActiveDeclaration( );

		// Sets the active vertex declaration
		//void SetActiveDecl( CDX9VertexDeclaration* _pDecl );

		/*
		*
		*/ 
		virtual void SetActiveDecl( IVertexDeclaration* _pDecl );


	protected:
		IVertexDeclaration* m_pDefaultDecl;

		//CDX9VertexDeclaration* m_pActiveDecl;

		IVertexDeclaration* m_pActiveDecl;
	};
}// end namespace 

#endif //_DX9VERTEXDECLARATIONMANAGER_H__Included_1144991067

