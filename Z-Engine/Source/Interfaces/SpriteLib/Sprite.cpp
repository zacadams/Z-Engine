/**
 *	@file Z-Engine\Z-Engine\Interfaces\SpriteLib\Sprite.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes

#include "CoreLib/Core.h"
// Library includes

// Local includes 
#include "MathLib/MathsConstants.h"
#include "MathLib/FVec3.h"
#include "MathLib/FVec2.h"
#include "RendererLib/RendererInterface.h"
#include "RendererLib/Texture.h"
#include "RendererLib/VertexDeclaration.h"
#include "RendererLib/VertexDeclarationManager.h"

// Vertex
#include "RendererLib/VertexElement.h"
#include "RendererLib/VertexDescription.h"
#include "RendererLib/VertexDeclaration.h"
#include "RendererLib/VertexDeclarationManager.h"


#include "SpriteLib/Sprite.h"

using namespace ZGE;
CSprite::CSprite(void)
: m_ppTextures( NULL )
, m_uTextureCount( 0 )
, m_pVertexDeclaration( NULL )
, m_bLighting( false )
{
	//m_eRenderSourceId  = RS_SPRITE;
}

CSprite::~CSprite(void)
{
	for( uint32 uTexture = 0; uTexture < m_uTextureCount; ++uTexture )
	{
		SafeRelease( m_ppTextures[uTexture] );
	}
	SafeDeleteArray( m_ppTextures );
	SafeDeleteArray( m_pQuad );
	SafeRelease( m_pVertexDeclaration );
	//SafeDelete( m_pTexture );
}
/*
* Initialises a sprite.
* @param _pTexture : The textures for the sprite to use.
* @param _krsRect  : The rect of the texture top render.
* @param _kbLighting : Determins if the sprite will be lit using per pixel normal map lighting.
*/
bool CSprite::Initialise( ITexture** _ppTextures, const SFRect& _krsRect, const bool _kbLighting)
{
	m_ppTextures = _ppTextures;
	m_uTextureCount = sizeof( _ppTextures ) / sizeof( ITexture* );
	m_sTextureRect = _krsRect;
	m_bLighting = _kbLighting;

	// Create the sprites vertices.
	if( _kbLighting )
	{
		// This sprite is being light with normal maps.
		// Create a vertex declaration with normals, binormals and tangents.
		static const uint32 kuStride = 60;
		static CVertexElement pLightingElements[] = 
		{
			CVertexElement( 0, CVertexElement::ES_POSITION,  0, CVertexElement::ET_FLOAT32, 3 ),
			CVertexElement( 12, CVertexElement::ES_COLOUR,   0, CVertexElement::ET_UINT8,   4 ),
			CVertexElement( 16, CVertexElement::ES_TEXCOORD, 0, CVertexElement::ET_FLOAT32, 2 ),
			CVertexElement( 24, CVertexElement::ES_NORMAL  , 0, CVertexElement::ET_FLOAT32, 3 ),
			CVertexElement( 36, CVertexElement::ES_BINORMAL, 0, CVertexElement::ET_FLOAT32, 3 ),
			CVertexElement( 48, CVertexElement::ES_TANGENT , 0, CVertexElement::ET_FLOAT32, 3 ),
		};
		static CVertexDescription LightingDesc( pLightingElements, 6, kuStride, 1 );
		if( false == ZEngine::GetRendererInterface( )->GetDeclarationManager( )->CreateDeclaration( LightingDesc, m_pVertexDeclaration ) )
		{
			assert_now( "Failed to create lit sprites vertex declaration" );
		}

		// Create and initialise the ligh vertices.
		m_pQuad = new CLitSpriteVertex[4];
		CLitSpriteVertex* pQuad = reinterpret_cast< CLitSpriteVertex* >( m_pQuad );
		for( uint32 uVertex = 0 ; uVertex < 4; ++uVertex )
		{
			pQuad[0].fNormalX	 =  0.0f;
			pQuad[0].fNormalY	 = -1.0f;
			pQuad[0].fNormalZ	 =  0.0f;
			pQuad[0].fBiNormalX =	0.0f; 
			pQuad[0].fBiNormalY =	-1.0f; 
			pQuad[0].fBiNormalZ =	0.0f; 
			pQuad[0].fTangentX =	1.0f; 
			pQuad[0].fTangentX =	0.0f; 
			pQuad[0].fTangentX =	0.0f; 
		}
	}
	else
	{
		// This sprite has no lighting, create a normal vertex declaration.
		// Position, colour and UV coordinates.
		static const uint32 kuStride = 24;
		static CVertexElement pUnLitElements[] = 
		{
			CVertexElement( 0, CVertexElement::ES_POSITION,  0, CVertexElement::ET_FLOAT32, 3 ),
			CVertexElement( 12, CVertexElement::ES_COLOUR,   0, CVertexElement::ET_UINT8,   4 ),
			CVertexElement( 16, CVertexElement::ES_TEXCOORD, 0, CVertexElement::ET_FLOAT32, 2 ),
		};
		static CVertexDescription UnLitDesc( pUnLitElements, 3, kuStride, 1 );
		if( false == ZEngine::GetRendererInterface( )->GetDeclarationManager( )->CreateDeclaration( UnLitDesc, m_pVertexDeclaration ) )
		{
			assert_now( "Failed to create un lit sprites vertex declaration" );
		}
		m_pQuad = new CXyzColourUV[4];
	}

	CXyzColourUV* pQuad = reinterpret_cast< CXyzColourUV* >( m_pQuad );
	
	pQuad[0].uColour = 0xFFFFFFFF;
	pQuad[1].uColour = 0xFFFFFFFF;
	pQuad[2].uColour = 0xFFFFFFFF;
	pQuad[3].uColour = 0xFFFFFFFF;
	
	pQuad[0].fU = 0.0f;
	pQuad[0].fV = 0.0f;
	pQuad[1].fU = 1.0f;
	pQuad[1].fV = 0.0f;
	pQuad[2].fU = 1.0f;
	pQuad[2].fV = 1.0f;
	pQuad[3].fU = 0.0f;
	pQuad[3].fV = 1.0f;
	return false;
}
/*
* Renders the sprite at location.
* @param _krmPosition : The position to render the sprite.
*/
void CSprite::Draw( const CFVec3& _krvPosition, const uint32 _kuColour )
{
	// Basic sprites contain only a position and uvv coordinates.
	Transform( _krvPosition );

		CXyzColourUV* pQuad = reinterpret_cast< CXyzColourUV* >( m_pQuad );
	pQuad[0].uColour =  _kuColour;
	pQuad[1].uColour =  _kuColour;
	pQuad[2].uColour =  _kuColour;
	pQuad[3].uColour =  _kuColour;


	//Note since this sprite is not rotated, we do not need to update the binormals and tangents.

	for( uint32 uTexture = 0; uTexture < m_uTextureCount; ++uTexture )
	{
		m_ppTextures[uTexture]->Apply( uTexture );
	}
	m_pVertexDeclaration->Apply( );
	ZEngine::GetRendererInterface( )->DrawPrimitivesUP( PT_QaudList, 1, m_pVertexDeclaration->GetDescription( ).GetStride( ),m_pQuad );
}
/*
* Renders a scaled and orientated sprite.
* @param _krmPosition : The position to render the sprite.
* @param _krmScale : The scale of the sprite.
* @param _kfRotation : The orientation of the sptite( rotation around the z axis )
*/
void CSprite::DrawEx( const CFVec3& _krvPosition, const CFVec2& _krvScale, const float32 _kfOrientation, const uint32 _kuColour )
{

	// Transform the sprite. 
	TransformEx( _krvPosition, _krvScale, _kfOrientation );
	
	CXyzColourUV* pQuad = reinterpret_cast< CXyzColourUV* >( m_pQuad );
	pQuad[0].uColour =  _kuColour;
	pQuad[1].uColour =  _kuColour;
	pQuad[2].uColour =  _kuColour;
	pQuad[3].uColour =  _kuColour;

	for( uint32 uTexture = 0; uTexture < m_uTextureCount; ++uTexture )
	{
		m_ppTextures[uTexture]->Apply( uTexture );
	}
	m_pVertexDeclaration->Apply( );
	ZEngine::GetRendererInterface( )->DrawPrimitivesUP( PT_QaudList, 1, m_pVertexDeclaration->GetDescription( ).GetStride( ), m_pQuad );
}
/*
* @return the sprites texture rect
*/
SFRect& CSprite::GetTextureRect( )
{
	return m_sTextureRect;
}
/*
* @return the sprites texture rect
*/
const SFRect& CSprite::GetTextureRect( ) const
{
	return m_sTextureRect;
}
/*
* Sets the sprites texture rect
* @param _krsTextureRect : The texture rect to set
*/
void CSprite::SetTextureRect( const SFRect& _krsTextureRect )
{
	m_sTextureRect = _krsTextureRect;
}
/*
* @return the sprites texture
*/
ITexture* CSprite::GetTexture( const uint32 _kuTexture )
{
	return m_ppTextures[_kuTexture];
}

/**
 * Transforms the sprite vertices.
 * @param _krmPosition : The position to render the sprite.
 */
IVertex* CSprite::Transform( const CFVec3& _krvPosition )
{
		// Basic sprites contain only a position and uvv coordinates.
	CXyzColourUV* pQuad = reinterpret_cast< CXyzColourUV* >( m_pQuad );

// Draw the sprite.
	// NOTE: with a 2d otho projection matrix the poitive y is up.
	float32 fHalfWidth  = m_sTextureRect.m_fWidth  * 0.5f;
	float32 fHalfHeight = m_sTextureRect.m_fHeight * 0.5f;
	
	pQuad[0].fX = _krvPosition.x( ) - fHalfWidth;
	pQuad[0].fY = _krvPosition.y( ) + fHalfHeight;

	pQuad[1].fX = _krvPosition.x( ) + fHalfWidth;
	pQuad[1].fY = _krvPosition.y( ) + fHalfHeight;

	pQuad[2].fX = _krvPosition.x( ) + fHalfWidth;
	pQuad[2].fY = _krvPosition.y( ) - fHalfHeight;

	pQuad[3].fX = _krvPosition.x( ) - fHalfWidth;
	pQuad[3].fY = _krvPosition.y( ) - fHalfHeight;

// Calculate the sprites UV coordinates

	const float32 fTextureWidth  = static_cast< float32 >( m_ppTextures[0]->GetWidth( ) );
	const float32 fTextureHeight = static_cast< float32 >( m_ppTextures[0]->GetHeight( ) );

	// Top left
	pQuad[0].fU = m_sTextureRect.m_fX / fTextureWidth;
	pQuad[0].fV = m_sTextureRect.m_fY / fTextureHeight;
	// Top right
	pQuad[1].fU = ( m_sTextureRect.m_fX + m_sTextureRect.m_fWidth ) / fTextureWidth;
	pQuad[1].fV = pQuad[0].fV;
	// Bottom right
	pQuad[2].fU = pQuad[1].fU;
	pQuad[2].fV = ( m_sTextureRect.m_fY + m_sTextureRect.m_fHeight ) / fTextureHeight;
	// Bottomleft
	pQuad[3].fU = pQuad[0].fU;
	pQuad[3].fV = pQuad[2].fV;

	for( uint32 i = 0; i < 4; ++i )
	{
		pQuad[i].fZ = _krvPosition.z( );
	}
	return pQuad;
}

/**
 * Transforms the sprite vertices.
 * @param _krmPosition : The position to render the sprite.
 * @param _krmScale : The scale of the sprite.
 * @param _kfRotation : The orientation of the sptite( rotation around the z axis )
 */
IVertex* CSprite::TransformEx( const CFVec3& _krvPosition, const CFVec2& _krvScale, const float32 _kfOrientation )
{
		// Basic sprites contain only a position and uvv coordinates.
	CXyzColourUV* pQuad = reinterpret_cast< CXyzColourUV* >( m_pQuad );

	// Scales the sprite around the origin.
	// Rotates the sprite around the origin.
	// Translates the sprite to its screen coordinates
	// Scale * rotation * translation

	float32 fHalfWidth  = ( m_sTextureRect.m_fWidth  * _krvScale.x( ) ) * 0.5f;
	float32 fHalfHeight = ( m_sTextureRect.m_fHeight * _krvScale.y( ) ) * 0.5f;

	// Calculate the points position around the origin ( 0, 0 )

	// Note: with a 2d ortho projection the y axis is up+ .
	pQuad[0].fX =  - fHalfWidth;
	//pQuad[0].fY =  - fHalfHeight;
	pQuad[0].fY =  + fHalfHeight;
	
	pQuad[1].fX =  + fHalfWidth;
	//pQuad[1].fY =  - fHalfHeight;
	pQuad[1].fY =  + fHalfHeight;
	
	pQuad[2].fX =  + fHalfWidth;
	//pQuad[2].fY =  + fHalfHeight;
	pQuad[2].fY =  - fHalfHeight;
	
	pQuad[3].fX =  - fHalfWidth;
	//pQuad[3].fY =  + fHalfHeight;
	pQuad[3].fY =  - fHalfHeight;

// rotate the sprite

	const float32 kfOrientation = DegToRad( _kfOrientation );
	for( uint32 i = 0; i < 4; ++i )
	{
		CFVec3 vPoint = CFVec3( pQuad[i].fX,  pQuad[i].fY,  _krvPosition.z( ) );
		vPoint.RotateZ( kfOrientation );

		pQuad[i].fX = vPoint.x( );
		pQuad[i].fY = vPoint.y( );
		pQuad[i].fZ = vPoint.z( );
	}

	// Translate the sprite
	pQuad[0].fX += _krvPosition.x( );
	pQuad[0].fY += _krvPosition.y( );
	pQuad[1].fX += _krvPosition.x( );
	pQuad[1].fY += _krvPosition.y( );
	pQuad[2].fX += _krvPosition.x( );
	pQuad[2].fY += _krvPosition.y( );
	pQuad[3].fX += _krvPosition.x( );
	pQuad[3].fY += _krvPosition.y( );

	// Calculate the sprites UV coordinates

	const float32 fTextureWidth  = static_cast< float32 >( m_ppTextures[0]->GetWidth( ) );
	const float32 fTextureHeight = static_cast< float32 >( m_ppTextures[0]->GetHeight( ) );

	// Top left
	pQuad[0].fU = m_sTextureRect.m_fX / fTextureWidth;
	pQuad[0].fV = m_sTextureRect.m_fY / fTextureHeight;
	// Top right
	pQuad[1].fU = ( m_sTextureRect.m_fX + m_sTextureRect.m_fWidth ) / fTextureWidth;
	pQuad[1].fV = pQuad[0].fV;
	// Bottom right
	pQuad[2].fU = pQuad[1].fU;
	pQuad[2].fV = ( m_sTextureRect.m_fY + m_sTextureRect.m_fHeight ) / fTextureHeight;
	// Bottomleft
	pQuad[3].fU = pQuad[0].fU;
	pQuad[3].fV = pQuad[2].fV;

	if( m_bLighting )
	{
		// Transform the sprites normals, binormals and tangents.
	}
	return pQuad;
}