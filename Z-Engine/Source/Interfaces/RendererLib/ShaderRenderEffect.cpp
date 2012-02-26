/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\RendererLib\ShaderRenderEffect.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "RendererLib/Effect.h"
#include "RendererLib/ShaderRenderEffect.h"
using namespace ZGE;

CShaderRenderEffect::CShaderRenderEffect(void)
{
}

CShaderRenderEffect::~CShaderRenderEffect(void)
{
}

				/**
 *	Initialise the render effect.
 */
bool CShaderRenderEffect::Initialise( )
{
	return false;
}

/**
 * Renders a render asset using this effect.
 */
void CShaderRenderEffect::Render( const EPrimitiveTypes _kePrimitiveType, void* _pVertices, const uint32 _kuPrimitiveCount, const uint32 _kuVertexStride )
{
}

/**
 * Renders a render asset using this effect.
 */
void CShaderRenderEffect::Render( CMesh* _pMesh )
{
}

/**
 * Renders a render asset using this effect.
 */
void CShaderRenderEffect::Render( const EPrimitiveTypes _kePrimitiveType, IVertexBuffer* _pVertexBuffer, const uint32 _kuPrimitiveCount )
{
}

/**
 * To be implemented to set up device states for a render effect. 
 */
void CShaderRenderEffect::BeginEffect( )
{
	m_pEffect->SetTechnique( m_pcTechnique );
}

/**
 * To be implemented to clean up device states after an effect has rendered.
 */
void  CShaderRenderEffect::EndEffect( )
{
}


void CShaderRenderEffect::SetTechnique( const char* _kpcTechnique )
{
	STR_PRINT( m_pcTechnique, 256, "%s",  _kpcTechnique );
	//ZUtilities::StrPrint( m_pcTechnique, "%s", 256,  _kpcTechnique );
	//sprintf_s( m_pcTechnique, "%s", _kpcTechnique );
}
