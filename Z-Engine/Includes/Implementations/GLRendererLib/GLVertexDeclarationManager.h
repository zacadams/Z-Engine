/**
 *	@file Z-Engine\Z-Engine\Implementations\GLRendererLib\GLVertexDeclarationManager.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _GLVERTEXDECLARATIONMANAGER_H__Included_1604565397
#define _GLVERTEXDECLARATIONMANAGER_H__Included_1604565397

#include "RendererLib/VertexDeclarationManager.h"

namespace ZGE
{
	class CGLVertexDeclaration;

	class CGLVertexDeclarationManager : public IVertexDeclarationManager
	{
	public:
		CGLVertexDeclarationManager(void);
		~CGLVertexDeclarationManager(void);

		/*
		*	Creates a vertex declaraton using a vertex description.
		*	Param _rDesc  : The vertex description.
		*	Param _pAsset : To be pop[ulated with the created asset
		*	Return : Success. 
		*/
		virtual bool CreateDeclaration( CVertexDescription& _rDesc, IVertexDeclaration*& _pAsset  );


		/*
		*	To be overriden to load assets of a derived manager.
		*	Param _rAssetId : The assets id, ( could be the file name ).
		*	Param _pAsset   : To be populated with the loaded asset.
		*	Return : Success.
		*/
		virtual bool LoadAsset( CAssetId& _rAssetId, IVertexDeclaration *& _pAsset );

		/*
		*	To be overidden to release a managers assets.
		*	Param _pAsset : The asset to release.
		*	Return : Success.
		*/
		virtual bool ReleaseAsset( IVertexDeclaration* _pAsset );

		/*
		* Returns athe deafult vertex declaration
		*/
		virtual IVertexDeclaration* GetDefaultDecl( );

		/*
		* Returns the currently set vertex declaration
		*/
		virtual IVertexDeclaration* GetActiveDeclaration( );

		// Sets the active vertex declaration
		//void SetActiveDecl( CGLVertexDeclaration* _pDecl );

		/*
		*
		*/ 
		virtual void SetActiveDecl( IVertexDeclaration* _pDecl );

	protected:

		IVertexDeclaration* m_pActiveDecl;
		IVertexDeclaration*  m_pDefaultDecl;
	};
}

#endif //_GLVERTEXDECLARATIONMANAGER_H__Included_1604565397

