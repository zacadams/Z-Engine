 /**
 *	@file Z-Engine\Z-Engine\Implementations\RenderEffects\DefaultRenderEffect.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/

#include "CoreLib/Core.h"
#include "RendererLib/RendererInterface.h"
#include "ModelLib/Mesh.h"
#include "RendererLib/Material.h"
#include "RendererLib/Texture.h"
#include "RendererLib/VertexDeclaration.h"
#include "RendererLib/VertexBuffer.h"
#include "RendererLib/IndexBuffer.h"

#include "DefaultRenderEffect.h"

using namespace ZGE;

CDefaultRenderEffect::CDefaultRenderEffect(void)
{
}

CDefaultRenderEffect::~CDefaultRenderEffect(void)
{
}

void CDefaultRenderEffect::DrawMesh( CMesh* _pMesh, IRendererInterface* _pRenderer )
{
	//// Renders a mesh with its materials.
	//// Textures and materials.
	//// Apply the texture.
	//uint32 uTextureCount = 0;
	//ITexture** ppTextures = _pMesh->GetTextures( uTextureCount );

	//for( uint32 i = 0; i < uTextureCount; ++i )
	//{
	//	ppTextures[i]->Apply( i );
	//}

	//// Apply the material.
	//_pMesh->GetMaterial( )->Apply( );

	//// Apply the vertex data.
	//_pMesh->GetVertexDeclaration( )->Apply( );
	//_pMesh->GetVertexBuffer( )->Apply( );
	//IIndexBuffer* pIndexBuffer = _pMesh->GetIndexBuffer( );

	//
	//_pRendererInerface->DrawPrimitivesUP(   _pMesh->GetPrimitiveCount( );


}

void CDefaultRenderEffect::BeginEffect( )
{
}

void CDefaultRenderEffect::EndEffect( )
{
}