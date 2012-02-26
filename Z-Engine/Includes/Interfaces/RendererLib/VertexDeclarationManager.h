/**
 *	@file Z-Engine\Z-Engine\Interfaces\RendererLib\VertexDeclarationManager.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _VERTEXDECLARATIONMANAGER_H__Included_1770243345
#define _VERTEXDECLARATIONMANAGER_H__Included_1770243345

#include "CoreLib/AssetManager.h"
#include "RendererLib/VertexDeclaration.h"

namespace ZGE
{
	class IVertexDeclaration;

	class IVertexDeclarationManager : public CAssetManager< IVertexDeclaration >
	{
	public:

		IVertexDeclarationManager( )
		{
			m_kpcManagerId = "Vertex declaration manager";
		}

		virtual ~IVertexDeclarationManager( ) {}


		/*
		*	Creates a vertex declaraton using a vertex description.
		*	Param _rDesc  : The vertex description.
		*	Param _pAsset : To be pop[ulated with the created asset
		*	Return : Success. 
		*/
		virtual bool CreateDeclaration( CVertexDescription& _rDesc, IVertexDeclaration*& _pAsset  ) = 0;


		/*
		* Returns athe deafult vertex declaration
		*/
		virtual IVertexDeclaration* GetDefaultDecl( ) = 0;

		/*
		* Returns the currently set vertex declaration
		*/
		virtual IVertexDeclaration* GetActiveDeclaration( ) = 0;

		/*
		*
		*/ 
		virtual void SetActiveDecl( IVertexDeclaration* _pDecl ) = 0;

	};
}
#endif //_VERTEXDECLARATIONMANAGER_H__Included_1770243345

