/**
 *	@file Z-Engine\Z-Engine\Source\Implementations\OpenGLES2Renderer\OpenGLESVertexDeclaration.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes
#include "CoreLib/Core.h"
// Library includes
#include "OpenGLES2Renderer/OpenGLESVertexDeclarationManager.h"

// Local includes 

#include "OpenGLES2Renderer/OpenGLESVertexDeclaration.h"
using namespace ZGE;
COpenGLESVertexDeclaration::COpenGLESVertexDeclaration( const CVertexDescription& _krDesc, COpenGLESVertexDeclarationManager* _pManager )
: m_VertexDesc( _krDesc )
, m_pManager( _pManager )
{
}

COpenGLESVertexDeclaration::~COpenGLESVertexDeclaration()
{
}

/*
*	Applys the vertex declararion on tp the renderer
*/
bool COpenGLESVertexDeclaration::Apply( )
{
	m_pManager->SetActiveDecl( this );
	return true;
}

/*
*	Accessor to the vertex declaration description
*/
CVertexDescription& COpenGLESVertexDeclaration::GetDescription( )
{
	return m_VertexDesc;
}
