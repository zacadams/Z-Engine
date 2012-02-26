/**
 *	@file Z-Engine\ModelLib\Mesh.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/

#include "CoreLib/Core.h"
#include "MathLib/FMat4x4.h"

#include "Mesh.h"

using namespace ZGE;

CMesh::CMesh(void)
{
}

CMesh::~CMesh(void)
{
}

// Sets the meshes material
void CMesh::SetMaterial( IMaterial* _kpMaterial )
{
	m_pMaterial = _kpMaterial;
}

// Sets the meshes vertex declaration
void CMesh::SetVertexDeclaration( IVertexDeclaration* _kpVertexDeclaration )
{
	m_pDecl = _kpVertexDeclaration;
}

// Sets the meshes vertex buffer
void CMesh::SetVertexBuffer( IVertexBuffer* _kpVertexBuffer )
{
	m_pVertexBuffer = _kpVertexBuffer;
}

// Gets the meshes material
IMaterial* CMesh::GetMaterial( ) const
{
	return m_pMaterial;
}

// Gets the meshes vertex declaration
IVertexDeclaration* CMesh::GetVertexDeclaration( ) const
{
	return m_pDecl;
}

// Gets the meshes vertex buffer
IVertexBuffer* CMesh::GetVertexBuffer( ) const
{
	return m_pVertexBuffer;
}

// Draws the mesh
void CMesh::Draw( IRendererInterface* _pRenderer, const CFMat4x4& _krmWorld )
{
	// Get the material to draw`

	// m_pMaterial->DrawMesh( _pRenderer, _krmWorld ); 
}

