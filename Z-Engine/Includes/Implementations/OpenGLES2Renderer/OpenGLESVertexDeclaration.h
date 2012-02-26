/**
 *	@file Z-Engine\Z-Engine\Includes\Implementations\OpenGLES2Renderer\OpenGLESVertexDeclaration.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _OPENGLESVERTEXDECLARATION_H__Included_1948801708
#define _OPENGLESVERTEXDECLARATION_H__Included_1948801708
#include "RendererLib/VertexDeclaration.h"
#include "RendererLib/VertexDescription.h"
namespace ZGE
{
	class COpenGLESVertexDeclarationManager;
	class COpenGLESVertexDeclaration : public IVertexDeclaration
	{
	public:
		COpenGLESVertexDeclaration(const CVertexDescription& _rDesc, COpenGLESVertexDeclarationManager* _pManager );
		~COpenGLESVertexDeclaration();

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
		COpenGLESVertexDeclarationManager* m_pManager;
	};
}
#endif //_OPENGLESVERTEXDECLARATION_H__Included_1948801708

