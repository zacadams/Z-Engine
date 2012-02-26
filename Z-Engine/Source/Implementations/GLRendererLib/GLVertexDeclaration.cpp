/**
 *	@file Z-Engine\Z-Engine\Implementations\GLRendererLib\GLVertexDeclaration.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/

#include "CoreLib/Core.h"

#include "GLVertexDeclarationManager.h"

#include "GLVertexDeclaration.h"

using namespace ZGE;

CGLVertexDeclaration::CGLVertexDeclaration( const CVertexDescription& _krDesc, CGLVertexDeclarationManager* _pManager )
: m_VertexDesc( _krDesc )
, m_pManager( _pManager )
{
}

CGLVertexDeclaration::~CGLVertexDeclaration(void)
{
}
/*
*	Applys the vertex declararion on tp the renderer
*/
bool CGLVertexDeclaration::Apply( )
{
	m_pManager->SetActiveDecl( this );
	return true;
}

/*
*	Accessor to the vertex declaration description
*/
CVertexDescription& CGLVertexDeclaration::GetDescription( )
{
	return m_VertexDesc;
}