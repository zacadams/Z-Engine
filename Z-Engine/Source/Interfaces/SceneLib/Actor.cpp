/**
 *	@file Z-Engine\Z-Engine\Source\Interfaces\SceneLib\Actor.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "SceneLib/RTTIActorRegistry.h"
#include "CoreLib/RTTIRegistrar.h"
#include "SceneLib/Actor.h"

using namespace ZGE;

CActor::CActor(void)
: m_pParent	 ( NULL ) 
, m_vWorldPosition( 0.0f, 0.0f, 0.0f )
, m_vLocalPosition( 0.0f, 0.0f, 0.0f )
, m_bRenderFlag( true )
{
	m_pcActorId[0] = '\0';
}

CActor::~CActor(void)
{
	//Delete the actors children
	std::list<CActor*>::iterator iter = m_lChildren.begin( );
	for( iter; iter != m_lChildren.end( ); ++iter )
	{
		delete (*iter);
		       (*iter) = NULL;
	}
	m_lChildren.clear( );
}


// This is a pre update.
bool CActor::PreUpdate( const float32 _kfDeltaTick )
{
	// Calculate the actors world transforms.
	return PreUpdateChildren( _kfDeltaTick );
}

// Empty process function, to be overidden by derived classes.
bool CActor::Update( const float32 _kfDeltaTick )
{
	// This actr has no logic.
	return UpdateChildren( _kfDeltaTick );
}

// Empty draw function, to be overidden by derived classes.
bool CActor::Draw( )
{
	// This actor has no render function.
	return DrawChildren( );
}


// Sets the actors id.
void CActor::SetActorId( const char* _kpcId )
{
	STR_PRINT( m_pcActorId, 256,"%s", _kpcId );
	//ZUtilities::StrPrint( m_pcActorId, "%s", 256, _kpcId );
	//sprintf_s( m_pcActorId, "%s", _kpcId );
}
// Adds a child to the actor.
bool CActor::AddChild( CActor* _pChild )
{
	m_lChildren.push_back( _pChild );
	_pChild->SetParent( this );
	return true;
}

// Removes a child from the actor.
bool CActor::RemoveChild( CActor* _pChild )
{
	m_lChildren.remove( _pChild );
	return true;
}

// Gets a child by id.
bool CActor::GetChild( CActor*& _pActor, const char* _kpcActorId )
{
	ChildList::iterator iter = m_lChildren.begin( );
	for( iter; iter != m_lChildren.end( ); ++iter )
	{
		if( 0 == _strcmpi( _kpcActorId, (*iter)->GetActorId( ) ) )
		{
			_pActor = (*iter);
			return true;
		}
	}
	return false;
}

// Search function to find an actor in the scene.
bool CActor::FindActor( CActor*& _pActor, const char* _kpcActorId )
{
	// Do I contain the target actor.
	if( GetChild( _pActor, _kpcActorId ) )
	{
		// Found the actor.
		return true;
	}

	// No, do my children?
	ChildList::iterator iter = m_lChildren.begin( );
	for( iter; iter != m_lChildren.end( ); ++iter )
	{
		if( (*iter)->FindActor( _pActor, _kpcActorId ) )
		{
			return true;
		}
	}
	return false;
}

// PreUpdates the actors children.
bool CActor::PreUpdateChildren( const float32 _kfDeltaTick )
{
	bool bSuccess = true;
	ChildList::iterator iter = m_lChildren.begin( );
	for( iter; iter != m_lChildren.end( ); ++iter )
	{
		if( false == (*iter)->PreUpdate( _kfDeltaTick  ) )
		{
			bSuccess = false;
		}
	}
	return bSuccess;
}



// Udates the actors children.
bool CActor::UpdateChildren( const float32 _kfDeltaTick )
{
	bool bSuccess = true;
	ChildList::iterator iter = m_lChildren.begin( );
	for( iter; iter != m_lChildren.end( ); ++iter )
	{
		if( false == (*iter)->Update( _kfDeltaTick ) )
		{
			bSuccess = false;
		}
	}
	return bSuccess;
}

// Draws the actors children.
bool CActor::DrawChildren(  )
{
	bool bSuccess = true;
	ChildList::iterator iter = m_lChildren.begin( );
	for( iter; iter != m_lChildren.end( ); ++iter )
	{
		if( false == (*iter)->Draw( ) )
		{
			bSuccess = false;
		}
	}
	return bSuccess;
}

