/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Implementations\XMLRenderEffectIO\XMLRenderEffectIO.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "RendererLib/RendererInterface.h"
#include "RendererLib/EffectManager.h"
#include "RendererLib/Effect.h"
#include "RendererLib/TextureManager.h"
#include "RendererLib/ShaderRenderEffect.h"
#include "RendererLib/FixedFunctionRenderEffect.h"
#include "TinyXml.h"
#include "XMLRenderEffectIO/XMLRenderEffectIO.h"

using namespace ZGE;
CXMLRenderEffectIO::CXMLRenderEffectIO(void)
{
}

CXMLRenderEffectIO::~CXMLRenderEffectIO(void)
{
}

/**
 *	Parses render effect from file.
 *	@param _kpcFileName The file to parse a render effect from.
 */
bool CXMLRenderEffectIO::ParseRenderEffect( const char* _kpcFileName, IRenderEffect*& _pRenderEffect )
{
	TiXmlDocument Doc;
	if( false == Doc.LoadFile( _kpcFileName ) )
	{
		return false;
	}


	// Get the effect element.
	TiXmlElement* pEffectElement = Doc.FirstChildElement( "render_effect" );
	const char* kpcType = pEffectElement->Attribute( "type" );
	if( 0 == _strcmpi( kpcType, "Shader_effect" ) )
	{
		// Shader effect.
		return ParseShaderEffect( pEffectElement, _pRenderEffect );
	}
	else if( 0 == _strcmpi( kpcType, "fixed_function_effect" ) )
	{
		// Fixed funcion effect.
		return ParseFixedFunctionEffect( pEffectElement, _pRenderEffect );
	}
	else
	{
		assert_now( "Unknown effect type!" );
		return false;
	}

	return true;
}

/**
 *	Serializes a render effect to file.
 *  @param _kpcFileName The name of the file to serialize the render effect to.
 *	@param _pRenderEffect The render effect to serialize.
 */
bool CXMLRenderEffectIO::SerializeRenderEffect( const char* _kpcFileName, IRenderEffect* _pRenderEffect )
{
	return false;
}

/**
 * Parses a fixed funcion effect from file.
 */
bool CXMLRenderEffectIO::ParseFixedFunctionEffect( TiXmlElement* _pEffectElement, IRenderEffect*& _pRenderEffect  )
{
	CFixedFunctionRenderEffect* pRenderEffect = new CFixedFunctionRenderEffect( );
	// Get the render state element .
	TiXmlElement* pRenderStatesElement = _pEffectElement->FirstChildElement( "render_states" );
	const uint32 kuRenderStateCount = atoi( pRenderStatesElement->Attribute( "count" ) );
	TiXmlElement* pRenderStateElement = pRenderStatesElement->FirstChildElement( "render_state" );
	ERenderStates eRenderState = RS_Count;
	uint32 uValue = 0;
	uint32 uReset = 0;
	SRenderStateTarget sRenderStateTarget;
	//for( uint32 uRenderState = 0; uRenderState < kuRenderStateCount; ++uRenderState )
	for( pRenderStateElement; NULL != pRenderStateElement; pRenderStateElement = pRenderStateElement->NextSiblingElement( "render_state" ) )
	{
		eRenderState = static_cast< ERenderStates >( atoi( &(pRenderStateElement->Attribute( "render_state")[0]) ) );
		uValue = static_cast< uint32 >( atoi( pRenderStateElement->Attribute( "value" ) ) );
		uReset = static_cast< uint32 >( atoi( pRenderStateElement->Attribute( "reset_value" ) ) );
		sRenderStateTarget.uRenderState = eRenderState;
		sRenderStateTarget.uValue = uValue;
		sRenderStateTarget.uResetValue = uReset;
		pRenderEffect->AddRenderStateTarget( sRenderStateTarget );
	}
	_pRenderEffect = pRenderEffect;
	//Parse texture state targets.
	return true;
}

		/**
 * Parses a shader effect from file.
 */
bool CXMLRenderEffectIO::ParseShaderEffect( TiXmlElement* _pEffectElement, IRenderEffect*& _pRenderEffect  )
{
	// Get the shader file.
	TiXmlElement* pShaderElement = _pEffectElement->FirstChildElement( "shader" );
	IEffect* pEffect = NULL;
	const char* kpcShaderFile = pShaderElement->Attribute( "file" ); 
	pEffect = ZEngine::GetRendererInterface( )->GetEffectManager( )->LoadAsset( CAssetId( kpcShaderFile ) );
	if( NULL == pEffect )
	{
		assert_now( "Failed to load shader effect file!" );
		return false;
	}

	// Get the technique to use for this effect
	const char* kpcTechnique = pShaderElement->Attribute( "technique" );

	// Parse the render target data.
	ITexture** ppRenderTargets = NULL;
	TiXmlElement* pRenderTargetElement = pShaderElement->FirstChildElement( "render_targets" );
	const uint32 kuRenderTargetCount = (uint32)atoi( pRenderTargetElement->Attribute( "count" ) );
	if( kuRenderTargetCount )
	{
		// There are render targets.
		TiXmlElement* pRenderTarget = pRenderTargetElement->FirstChildElement( "render_target" );  
		ppRenderTargets = new ITexture*[kuRenderTargetCount];
		ESurfaceFormat eSemantic = SF_Count;
		uint32 uWidth = 0;
		uint32 uHeight = 0;
		const char* kpcName = NULL;
		bool bWriteOnly = true; // Note: This will need to be data driven!
		for( uint32 uRenderTarget = 0; uRenderTarget < kuRenderTargetCount; ++uRenderTarget )
		{
			// Create render target.
			uint32 uSemantic = (uint32)atoi(&(pRenderTarget->Attribute( "surface_type" )[0]) );  
			if( uSemantic >= SF_Count )
			{
				assert_now( "Render target specifies unknown surface format!" );
				delete [] ppRenderTargets;
				return false;
			}
			eSemantic = (ESurfaceFormat)uSemantic;
			uWidth  = (uint32)atoi( pRenderTarget->Attribute( "width" ) );
			uHeight = (uint32)atoi( pRenderTarget->Attribute( "height" ) ); 
			kpcName = pRenderTarget->Attribute( "name" );
			ppRenderTargets[uRenderTarget] = ZEngine::GetRendererInterface( )->GetTextureManager( )->CreateRenderTarget( CAssetId( kpcName ), uWidth, uHeight, eSemantic, bWriteOnly );
			pRenderTarget = pRenderTarget->NextSiblingElement( "render_target" );
		}
	}
	_pRenderEffect = new CShaderRenderEffect( );
	CShaderRenderEffect* pShaderEffect = reinterpret_cast< CShaderRenderEffect* >( _pRenderEffect );
	pShaderEffect->SetRenderTargets( ppRenderTargets, kuRenderTargetCount );
	pShaderEffect->SetEffect( pEffect );
	pShaderEffect->SetTechnique( kpcTechnique );
	return true;
}