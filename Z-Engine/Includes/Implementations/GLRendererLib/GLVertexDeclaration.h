/**
 *	@file Z-Engine\Z-Engine\Implementations\GLRendererLib\GLVertexDeclaration.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _GLVERTEXDECLARATION_H__Included_1116616536
#define _GLVERTEXDECLARATION_H__Included_1116616536
#
#include "RendererLib/VertexDeclaration.h"
#include "RendererLib/VertexDescription.h"

namespace ZGE
{
	class CGLVertexDeclarationManager;

	class CGLVertexDeclaration : public IVertexDeclaration
	{
	public:
		CGLVertexDeclaration( const CVertexDescription& _rDesc, CGLVertexDeclarationManager* _pManager );
		~CGLVertexDeclaration(void);

		/*
		*	Applys the vertex declararion on tp the renderer
		*/
		virtual bool Apply( );

		/*
		*	Accessor to the vertex declaration description
		*/
		virtual CVertexDescription& GetDescription( );

	protected:

		CVertexDescription m_VertexDesc;
		CGLVertexDeclarationManager* m_pManager;
	};
}

#endif //_GLVERTEXDECLARATION_H__Included_1116616536

