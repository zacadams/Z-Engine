/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Implementations\XMLSceneIO\XMLSceneIO.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"

// scene 
#include "TinyXML.h"
#include "SceneLib/Actor.h"
#include "SceneLib/RTTIActorRegistry.h"
#include "SpriteLib/2DActor.h"
#include "SceneLib/SceneInterface.h"
#include "RendererLib/RendererInterface.h"
#include "SpriteLib/SpriteInterface.h"
#include "SpriteLib/SpriteManager.h"
#include "SpriteLib/2DRenderAsset.h"
#include "SpriteLib/Sprite.h"
#include "RendererLib/RenderEffectManager.h"
#include "RendererLib/RenderEffect.h"
#include "CoreLib/AssetId.h"
#include <stdio.h>
#include <sstream>

// this
#include "XMLSceneIO/XMLSceneIO.h"

using namespace ZGE;
CXMLSceneIO::CXMLSceneIO(void)
{
}

CXMLSceneIO::~CXMLSceneIO(void)
{
}

/**
 *	Parses a scene from a XML file.
 *	@param _kpcSceneName The scene to parse.
 *  @param _pRootNode  The scenes root node.
 *	@return Success.
 */
bool CXMLSceneIO::ParseScene( const char* _kpcScene, CActor*& _pRootNode )
{
	UNUSED_VAR( _kpcScene );
	UNUSED_VAR( _pRootNode );


	// Parse the root node.
	TiXmlDocument Doc;
	if( false ==  Doc.LoadFile( _kpcScene ) )
	{
		assert_now( "Failed to load scene!" );
		return false;
	}

	// Successfully opened the file.
	TiXmlElement* pRootElement = Doc.FirstChildElement( "actor_library" )->FirstChildElement( "actor" );
	
	// Get the root nodes instanciation id and create it.
	RecursiveParse( pRootElement, _pRootNode  );

	return true;
}

/**
 *	Saves the scene to a XML file.
 *	@param _kpcFileName The name of the file to write.
 *  @param _pRootNode  The scenes root node.
 *	@return Success.
 */
bool CXMLSceneIO::SaveScene( const char* _kpcFileName, CActor* _pRootNode )
{

	TiXmlDocument Doc;
	TiXmlDeclaration* pDeclaration = new TiXmlDeclaration( "1.0", "", "" );
	Doc.LinkEndChild( pDeclaration );

	TiXmlElement* pActorLib = new TiXmlElement( "actor_library" );

	RecurseSerialize( pActorLib, _pRootNode );

	Doc.LinkEndChild( pActorLib );

	Doc.SaveFile( _kpcFileName );
	return false;
}


// Recursive.
void CXMLSceneIO::RecurseSerialize( TiXmlElement* _pParent, CActor* _pActor )
{
	// Serialize the acttor.
	TiXmlElement* pParentXML = SerializeActor( _pParent, _pActor );

	// serialize any children.
	std::list< CActor* >& rChildren = _pActor->GetChildren( );
	std::list< CActor* >::iterator iter = rChildren.begin( );

	for(iter; iter != rChildren.end( ); ++iter )
	{
		RecurseSerialize( pParentXML, *iter );
	}
}
// Recusrsive.
void CXMLSceneIO::RecursiveParse( TiXmlElement* _pElement, CActor*& _pActor )
{
	// Load me.
	ParseActor( _pElement, _pActor );
	
	// Load all children.
	for( TiXmlElement* pChildElement = _pElement->FirstChildElement( "actor" ); pChildElement; pChildElement = pChildElement->NextSiblingElement( "actor" ) )
	{
		CActor* pChild = NULL;
		RecursiveParse( pChildElement, pChild );
		_pActor->AddChild( pChild );
	}
}

// Parses a actor from file.
bool CXMLSceneIO::ParseActor( TiXmlElement* _pElement, CActor*& _pActor )
{
	// Get the actors instanciation Id and create the actor.
	const char* kpcInstanciationId = _pElement->Attribute( "instanciation_id" );
	_pActor = reinterpret_cast< CActor* >( CRTTIActorRegistry::GetInstance( ).CreateInstanceOf( kpcInstanciationId ) );
	const char* kpcName = _pElement->Attribute( "name" );
	_pActor->SetActorId( kpcName );
	return false;
}

// Writes a actor to a file.
TiXmlElement* CXMLSceneIO::SerializeActor( TiXmlElement* _pParent, CActor* _pActor )
{
	// What kind of actor is this?
	TiXmlElement* pActor = new TiXmlElement( "actor" );

	// Set the actors name
	pActor->SetAttribute( "name", _pActor->GetActorId( ) );
	pActor->SetAttribute( "instanciation_id", "CActor" ); 

	// Create the transformation element.
	TiXmlElement* pTransformElement = new TiXmlElement( "transform" );
	pActor->LinkEndChild( pTransformElement );

	// Link the actor to its parent.
	_pParent->LinkEndChild( pActor );
	return pActor;
}

// Parses a 2D actor from file.
bool  CXMLSceneIO::Parse2DActor( TiXmlElement* _pElement, CActor* _pActor )
{
	C2DActor* p2DActor = reinterpret_cast< C2DActor* >( _pActor );
	TiXmlElement* pTransform = _pElement->FirstChildElement( "transform" );
	const char* kpcTranslationValues = pTransform->Attribute( "translation" );
	const char* kpcRotation = pTransform->Attribute( "rotation" );

	float32 pValues[3];
	StringToValues<float32>( kpcTranslationValues, pValues, 3 );

	CFVec3 vLocalPosition( pValues[0], pValues[1], pValues[2] );
	float32 fLocalOrientation = (float32)atof( kpcRotation );

	p2DActor->SetLocalPosition( vLocalPosition );
	p2DActor->SetLocalOrientation( fLocalOrientation );

	// Parse the actors render effect.
	TiXmlElement* pRenderEffectElement = _pElement->FirstChildElement( "render_effect" );
	IRenderEffect* pRenderEffect = NULL;
	if( pRenderEffectElement )
	{
		const char* kpcRenderEffectFile = pRenderEffectElement->Attribute( "file" );
		pRenderEffect = reinterpret_cast< CAssetManager<IRenderEffect>* >( ZEngine::GetRendererInterface( )->GetRenderEffectManager( ))->LoadAsset( CAssetId( kpcRenderEffectFile ) );
		if( NULL == pRenderEffect )
		{
			assert_now( "failed to load render effect" );
			return false;
		}
		p2DActor->SetRenderEffect( pRenderEffect );
	}


	// Parse the actors sprite if it has one.
	TiXmlElement* pSpriteElement = _pElement->FirstChildElement( "render_asset" );
	if( pSpriteElement )
	{
		const char* kpcFileName = pSpriteElement->Attribute( "file" );
		CSprite* pSprite = ZEngine::GetSpriteInterface( )->GetSpriteManager( )->LoadAsset( CAssetId( kpcFileName ) );
		if( NULL == pSprite )
		{
			assert_now( "Failed to load actors sprite!" );
			return false;
		}
		IRenderAsset* pRenderAsset = new C2DRenderAsset( );
		pRenderAsset->m_pRenderEffect = pRenderEffect;
		reinterpret_cast< C2DRenderAsset* >( pRenderAsset )->pSprite = pSprite;
		p2DActor->SetRenderAsset( pRenderAsset );
	}
	return false;
}

// Writes a 3D actor to file.
TiXmlElement*  CXMLSceneIO::Serialize2DActor( TiXmlElement* _pParent, CActor* _pActor )
{	
	TiXmlElement* pActor = new TiXmlElement( "actor" );
	C2DActor* p2DActor = reinterpret_cast< C2DActor* >( _pActor ); 

	// Set the actors name
	pActor->SetAttribute( "name", _pActor->GetActorId( ) );
	pActor->SetAttribute( "instanciation_id", "C2DActor" ); 

	// Create the transformation element.
	TiXmlElement* pTransformElement = new TiXmlElement( "transform" ); 

	char pBuffer[256];
	CFVec3 vLocalPosition = p2DActor->GetLocalPosition( );
	float32 pfValues[3];
	pfValues[0] = vLocalPosition.x( );
	pfValues[1] = vLocalPosition.y( );
	pfValues[2] = vLocalPosition.z( );
	FloatToString( pfValues , pBuffer, 3 );
	pTransformElement->SetAttribute( "translation", pBuffer );

	float32 fLocalOrientation = p2DActor->GetLocalOrientation( );
	FloatToString( &fLocalOrientation, pBuffer, 1 );
	pTransformElement->SetAttribute( "rotation", pBuffer );
	pActor->LinkEndChild( pTransformElement );

	// Create the render effect element.
	if( p2DActor->GetRenderEffect( ) )
	{
		TiXmlElement* pRenderEffectElement = new TiXmlElement( "render_effect" );
		pRenderEffectElement->SetAttribute( "file", p2DActor->GetRenderEffect( )->GetAssetId( ).GetFileName( ) );
		pActor->LinkEndChild( pRenderEffectElement );
	}

	// Create the render asset element.
	if( p2DActor->GetRenderAsset( ) )
	{
		C2DRenderAsset* pRenderAsset = reinterpret_cast< C2DRenderAsset* >( p2DActor->GetRenderAsset( ) );
		TiXmlElement* pRenderAssetElement = new TiXmlElement( "render_asset" );
		pRenderAssetElement->SetAttribute( "file", pRenderAsset->pSprite->GetAssetId( ).GetFileName( ) );
		pActor->LinkEndChild( pRenderAssetElement );
	}

	// Link the actor to its parent.
	_pParent->LinkEndChild( pActor ); 
	return pActor;
}

// Converts a value to a string.
void CXMLSceneIO::FloatToString( float32* _pValues, char* _pCharArray, const uint32 uElementCount )
{
	_pCharArray[0] = '\0';
	for( uint32 uElement = 0; uElement < uElementCount; ++uElement )
	{
		sprintf_s( _pCharArray, 256,  "%s%f", _pCharArray, _pValues[uElement]);
	}
}
template< typename t>
void CXMLSceneIO::StringToValues( const char* _kcpValues, t* _pValues, const uint32 _kuCount )
{
	std::istringstream iss ( _kcpValues );
	for( uint32 uValue = 0; uValue < _kuCount; ++uValue)
	{
		iss >> _pValues[uValue];
	}
}
