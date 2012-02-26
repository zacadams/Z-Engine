/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Implementations\XMLSpriteIO\XMLSpriteParser.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"

// Renderer
#include "RendererLib/RendererInterface.h"

// Vertex decl
#include "RendererLib/VertexElement.h"
#include "RendererLib/VertexDescription.h"
#include "RendererLib/VertexDeclaration.h"
#include "RendererLib/VertexDeclarationManager.h"

// Texture
#include "RendererLib/Texture.h"
#include "RendererLib/TextureManager.h"

// Sprite
#include "SpriteLib/Sprite.h"

#include "TinyXml.h"

#include "XMLSpriteIO/XMLSpriteParser.h"
using namespace ZGE;
CXMLSpriteParser::CXMLSpriteParser(void)
{
}

CXMLSpriteParser::~CXMLSpriteParser(void)
{
}

/**
 *	This function parses a sprite from the specified file.
 *	@param _kpcFileName.
 *	@param _pSprite To be populated with the sprite data.
 *	@return Success.
 */
bool CXMLSpriteParser::ParseSprite( const char* _kpcFileName, CSprite*& _pSprite )
{
	if( NULL == m_pTextureManager )
	{
		assert_now( "XML sprite parser does not have a valid texture manager pointer!" );
		return false;
	}
	TiXmlDocument Doc;
	if( false == Doc.LoadFile( _kpcFileName ) )
	{
		static char s_pError[256];
		sprintf_s( s_pError, "Failed to load sprite. File: %s", _kpcFileName );
		assert_now( s_pError );
		return false;
	}
	
	// Loaded the file successfully.
	TiXmlElement* pSpriteElement = Doc.FirstChildElement( "sprite" );

	//// Is this sprite lit?
	bool bLighting = false;
	const char* kpcLighting = pSpriteElement->Attribute( "lighting" );
	if( 0 == _strcmpi( kpcLighting, "true" ) )
	{
		bLighting = true;
	}

	// Parse the textures.
	ITexture** ppTextures	 = NULL;
	ParseTextures( pSpriteElement->FirstChildElement( "textures" ), ppTextures );

	// Parse the texture rect.
	SFRect sTextureRect = { 0.0f, 0.0f, 0.0f, 0.0f }; 
	ParseTextureRect( pSpriteElement->FirstChildElement( "texture_rect" ), sTextureRect );

	//// Create and initialise the sprite.
	//// Firstly enumerate the sprites vertex structure.
	_pSprite = new CSprite( );
	_pSprite->Initialise( ppTextures, sTextureRect, bLighting);
	return true;
}
/**
 *	Builds the sprites vertex declaration.
 *	@param _pVertexDeclElement	The xml documents vertex declaration element. 
 */
IVertexDeclaration* CXMLSpriteParser::ParseVertexDeclaration( TiXmlElement* _pVertexDeclElement )
{
	
	static CVertexElement::EElementSemantic pSemanticLookUp[] = 
	{
		CVertexElement::ES_POSITIONT,				//0					
		CVertexElement::ES_POSITION,				//1
		CVertexElement::ES_NORMAL,					//2
		CVertexElement::ES_TEXCOORD,				//3
		CVertexElement::ES_COLOUR,					//4
		CVertexElement::ES_BINORMAL,				//5
		CVertexElement::ES_TANGENT,					//6
		CVertexElement::ES_BLENDINDICES,			//7
		CVertexElement::ES_BLENDWEIGHTS,			//8
	};

	static CVertexElement::EElementType pSemanticTypeLookUp[] = 
	{
		CVertexElement::ET_FLOAT32, 
		CVertexElement::ET_UINT8,
	};

	// create the vertex elemnts.
	uint32 uElementCount = atoi( _pVertexDeclElement->Attribute( "element_count" ) );
	TiXmlElement* pElement = _pVertexDeclElement->FirstChildElement( "element" );
	CVertexDescription Desc;
	uint32 uValueCount	  = 0;
	uint32 uElementOffSet = 0;
	uint32 uSemantic	  = 0;
	uint32 uType		  = 0;
	uint32 uStream		  = 0;

	for( uint32 uElement = 0; uElement < uElementCount; ++uElement )
	{
		// What is this elements semantic?
		const char* kpcElementSemantic = pElement->Attribute( "semantic" );
		 uSemantic = atoi( &kpcElementSemantic[0] );

		// Get the semantics value type.
		uType = atoi( &pElement->Attribute( "type" )[0] );

		// get the number of values in the semantic.
		uValueCount = atoi( pElement->Attribute( "value_count" ) );

		// Get the offset.
		uElementOffSet = atoi( pElement->Attribute( "off_set" ) );

		// Get the stream.
		uStream = atoi( pElement->Attribute( "stream" ) );

		CVertexElement Element( uElementOffSet, pSemanticLookUp[uSemantic], 0, pSemanticTypeLookUp[uType], uValueCount, uStream );
		Desc.AddElement( Element );

		pElement = pElement->NextSiblingElement( "element" );
	}
	IVertexDeclaration* pDecl = NULL;
	if( false == ZEngine::GetRendererInterface( )->GetDeclarationManager( )->CreateDeclaration( Desc, pDecl ) )
	{
		assert_now( "Failed to create sprite vertex declaration!" );
		return NULL;
	}
	return pDecl;
}

/**
 *	Parses the sprites texture rect from file.
 *	@param _pRectElement The xml documents texture rect element.
 *	@param _rsTextureRect To be populated with the texure rect info.
 *	@return Success.
 */
bool CXMLSpriteParser::ParseTextureRect( TiXmlElement* _pRectElement, SFRect& _rsTextureRect )
{	
	_rsTextureRect.m_fX		 = static_cast<float32>( atof( _pRectElement->Attribute( "u" ) ) );	// U coordinate.
	_rsTextureRect.m_fY		 = static_cast<float32>( atof( _pRectElement->Attribute( "v" ) ) );	// V coordinate.
	_rsTextureRect.m_fWidth  = static_cast<float32>( atof( _pRectElement->Attribute( "w" ) ) );	// Width.
	_rsTextureRect.m_fHeight = static_cast<float32>( atof( _pRectElement->Attribute( "h" ) ) );	// Height.
	return  true;
}

/**
 *	Parses the sprites textures.
 *	@param _pTexturesElements The element containing the texture info. 
 *	@param _ppTextures To be populated with the sprites textures.
 *	@return Success.
 */
bool CXMLSpriteParser::ParseTextures( TiXmlElement* _pTexturesElement, ITexture**& _ppTextures )
{
	const uint32 kuTextureCount = atoi( _pTexturesElement->Attribute( "count" ) );
	_ppTextures = new ITexture*[kuTextureCount];

	TiXmlElement* pTextureElement = _pTexturesElement->FirstChildElement( "texture" );
	for( uint32 uTexture = 0; uTexture < kuTextureCount; ++uTexture )
	{
		// Get the textures file name.
		const char* kpcFile = pTextureElement->Attribute( "file" );

		// Load the texture.
		_ppTextures[uTexture] = m_pTextureManager->LoadAsset( CAssetId( kpcFile ) );
	}
	return kuTextureCount > 0;
}