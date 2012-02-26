/**
 *	@file Z-Engine\Z-Engine\Interfaces\SceneLib\SceneInterface.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "Corelib/Core.h"
#include "SceneLib/Actor.h"
#include "SpriteLib/2DActor.h"
#include "XMLSceneIO/XMLSceneIO.h"
#include "SceneLib/RTTIACtorRegistry.h"
#include "SceneLib/SceneInterface.h"

#define VALIDATE_SCENE if( NULL == m_pRootNode ) { assert_now( "Scene is not initilaised. There is no root node!" ); return false; }

using namespace ZGE;
CSceneInterface::CSceneInterface(void)
: m_pSceneIO( NULL )
{
}

CSceneInterface::~CSceneInterface(void)
{
}

	
// Initialises the scene interface.
bool CSceneInterface::Initialise( )
{
	//m_pSceneIO = new CXMLSceneIO( );
	return true;
}

// Creates an empty scene. 
CScene* CSceneInterface::CreateScene( CAssetId& _rAssetId )
{
	CScene* pScene = new CScene( );
	return pScene;
}

 // Parses a scene from file.
bool CSceneInterface::ParseScene( CAssetId& _rAssetId, CScene*& _pScene )
{		
	CActor* pRoot = NULL;
	if( m_pSceneIO->ParseScene( _rAssetId.GetFileName( ), pRoot ) )
	{
		_pScene = new CScene( );
		_pScene->InitilaiseScene( ); 

		return true;
	}
	return false;

}

// Saves a scene to file.
bool CSceneInterface::SerializeScene( CAssetId& _rAssetId, CScene* _pScene )
{
	// Save the scene.
	return m_pSceneIO->SaveScene( _rAssetId.GetFileName( ), _pScene->GetRoot( ) );
}

// Creates a registered actor.
CActor* CSceneInterface::CreateActor( const char* _kpcInstanciationId )
{
	CActor* pActor = reinterpret_cast< CActor* >( CRTTIActorRegistry::GetInstance( ).CreateInstanceOf( _kpcInstanciationId ) );	
	return pActor;
}