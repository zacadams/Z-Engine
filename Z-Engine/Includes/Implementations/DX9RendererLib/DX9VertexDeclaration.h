/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9VertexDeclaration.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _DX9VERTEXDECLARATION_H__Included_172000841
#define _DX9VERTEXDECLARATION_H__Included_172000841

#include "RendererLib/VertexDeclaration.h"

struct IDirect3DDevice9;
struct IDirect3DVertexDeclaration9;

namespace ZGE
{
	class CVertexDescription;
	class CDX9VertexDeclarationManager;
	class IVertexDeclarationManager;

	class CDX9VertexDeclaration : public IVertexDeclaration
	{
	public:
		CDX9VertexDeclaration( CVertexDescription& _rDesc, IDirect3DDevice9* _pDevice, CDX9VertexDeclarationManager* _pManager );
		~CDX9VertexDeclaration(void);

		/*
		*	Applys the vertex declararion on tp the renderer
		*/
		virtual bool Apply( );

		/*
		*	Accessor to the vertex declaration description
		*/
		virtual CVertexDescription& GetDescription( );

	protected:

		void operator= ( const CDX9VertexDeclaration& _kr ); 

	protected:

		CVertexDescription m_VertexDecsription;	//!< The vertex declaration vertex description.
		IDirect3DDevice9*	m_pDevice;				//!< The DX reendering device
		IDirect3DVertexDeclaration9*	m_pD3DDecl;	//!< The DX vertex declaration 
		//CDX9VertexDeclarationManager*   m_pManager;
		IVertexDeclarationManager*   m_pManager;
	};
}// ens namespace

#endif //_DX9VERTEXDECLARATION_H__Included_172000841

