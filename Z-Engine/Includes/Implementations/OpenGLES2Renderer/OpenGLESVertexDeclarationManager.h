/**
 *	@file Z-Engine\Z-Engine\Includes\Implementations\OpenGLES2Renderer\OpenGLESVertexDeclarationManager.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _OPENGLESVERTEXDECLARATIONMANAGER_H__Included_504650113
#define _OPENGLESVERTEXDECLARATIONMANAGER_H__Included_504650113
#include "RendererLib/VertexDeclarationManager.h"
namespace ZGE
{
	class COpenGLESVertexDeclarationManager : public IVertexDeclarationManager
	{
	public:
		COpenGLESVertexDeclarationManager();
		~COpenGLESVertexDeclarationManager();

				/*
		*	Creates a vertex declaraton using a vertex description.
		*	Param _rDesc  : The vertex description.
		*	Param _pAsset : To be pop[ulated with the created asset
		*	Return : Success. 
		*/
		virtual bool CreateDeclaration( CVertexDescription& _rDesc, IVertexDeclaration*& _pAsset  );

		/**
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

		/*
		* Returns athe deafult vertex declaration
		*/
		virtual IVertexDeclaration* GetDefaultDecl( );

		/*
		* Returns the currently set vertex declaration
		*/
		virtual IVertexDeclaration* GetActiveDeclaration( );
		virtual void SetActiveDecl( IVertexDeclaration* _pDecl );

	protected:
		IVertexDeclaration* m_pActiveDecl;
		IVertexDeclaration*  m_pDefaultDecl;
	};
}
#endif //_OPENGLESVERTEXDECLARATIONMANAGER_H__Included_504650113

