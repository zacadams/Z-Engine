/**
 *	@file Z-Engine\Z-Engine\Source\Interfaces\SceneLib\Scene.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"

// Scene
#include "SceneLib/Actor.h"

#include "SceneLib/Scene.h"
using namespace ZGE;
#define VALIDATE_SCENE if( NULL == m_pRootNode ) { assert_now( "Scene is not initilaised. There is no root node!" ); return false; }

CScene::CScene(void)
{
	m_pRootNode = new CActor( );
	m_pRootNode->SetActorId( "RootNode" );
}

CScene::~CScene(void)
{
}

// Adds an actor into the scene.
bool CScene::AddActor( CActor* _pActor, const char* _kpcParentId )
{
	// Find the target parent.
	// Is the target the root node?
	if( 0 == _strcmpi( m_pRootNode->GetActorId( ) , _kpcParentId ) )
	{
		// Yes, add the node to the root.
		return m_pRootNode->AddChild( _pActor );
	}

	// No, find the target parent.
	CActor* pTarget = NULL; 
	if( m_pRootNode->FindActor( pTarget, _kpcParentId ) )
	{
		// Found target, add actor.
		return pTarget->AddChild( _pActor ); 
	}

	// Could not find the target parent!
	return false;
}
// Removes an actor from the scene.
bool CScene::RemoveActor( CActor* _pActor )
{
	assert_msg( _pActor->GetParent( ), "Can not remove actor that has no parent!" ); 
	return _pActor->GetParent( )->RemoveChild( _pActor );
}

// Processes the scene.
bool CScene::UpdateScene( const float32 _kfDeltaTick )
{
	m_pRootNode->PreUpdate( _kfDeltaTick );
	return m_pRootNode->Update( _kfDeltaTick );
}
// Renderes the scene.
bool CScene::DrawScene( )
{
	return m_pRootNode->Draw(  );
}

// Finds the target actor.
CActor* CScene::FindActor(  const char* _kpcActorId )
{
	// Is it the root I am looking for?
	if( 0 == _strcmpi( _kpcActorId, m_pRootNode->GetActorId( ) ) )
	{
		return m_pRootNode;
	}

	CActor* pActor = NULL;
	if( m_pRootNode->FindActor( pActor, _kpcActorId ) )
	{
		return pActor;
	}
	return NULL;
}

// Recursivly initialises the scene.
void RecurseInitialise( CActor* _pActor )
{
	_pActor->Initialise( );
	std::list< CActor* >& rChildren = _pActor->GetChildren( );
	std::list< CActor* >::iterator iter = rChildren.begin( );
	for( iter; iter != rChildren.end( ); ++iter )
	{
		RecurseInitialise( *iter );
	}
}

// Initialises the scene.
bool CScene::InitilaiseScene(  )
{
	VALIDATE_SCENE
	RecurseInitialise( m_pRootNode );
	return true;
}

// Deinitialises the scene.
bool CScene::DeinitialiseScene( )
{
	SafeDelete( m_pRootNode );
	return true;
}
