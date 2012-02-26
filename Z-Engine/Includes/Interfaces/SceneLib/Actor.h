/**
 *	@file Blarg\blarg\Actor.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010-2011 Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _ACTOR_H__Included_547649318
#define _ACTOR_H__Included_547649318

#include<list>
#include "MathLib/FMat4x4.h"
#include "CoreLib/Observer.h"
#include "RendererLib/RenderableActor.h"
#include "CoreLib/MemoryAlignment.h"
namespace ZGE
{


	//
	// Make a CTreeNode<template> class to handle the tree functionality.
	// Make the actor contain spacial information and actor functions.
	//
	//



	/**
	 * The base class for all objects.
	 * Represents the base  scene graph object.
	 */
	_ALIGNED_PREFIX( 16 )
	class CActor : public IObserver
#ifdef Z_PLATFORM_WIN
		,  public TAligned< 16 >
#endif
	{
	public:
		CActor(void);
		~CActor(void);

		typedef std::list<CActor*> ChildList;

		// Initialises the actor
		virtual bool Initialise( ){ return true; }

		// Sets the actors id.
		void SetActorId( const char* _kpcId );

		// Returns the actors id as a string.
		inline const char8* GetActorId( ) const { return m_pcActorId; }

		// Sets the actors parent.
		inline void SetParent( CActor* _pParent ) { m_pParent = _pParent; }

		// Returns the actors parent.
		inline CActor* GetParent( )const { return m_pParent; }

	/* Parenting functionas */

		// Adds a child to the actor.
		bool AddChild( CActor* _pChild );

		// Removes a child from the actor.
		bool RemoveChild( CActor* _pChild );

		// returns the actors children.
		inline ChildList& GetChildren( ){ return m_lChildren; }; 

	/* Actor processes and draw */

		// This is a pre update.
		virtual bool PreUpdate( const float32 _kfDeltaTick );

		// Empty process function, to be overidden by derived classes.
		virtual bool Update( const float32 _kfDeltaTick );

		// Empty draw function, to be overidden by derived classes.
		virtual bool Draw( );

	/* Children functionality */

		// PreUpdates the actors children.
		bool PreUpdateChildren( const float32 _kfDeltaTick );

		// Udates the actors children.
		bool UpdateChildren( const float32 _kfDeltaTick );
		
		// Draws the actors children.
		bool DrawChildren(  );


		// Gets a child by id.
		bool GetChild( CActor*& _pActor, const char* _kpcActorId );

		// Get the actors child count.
		inline uint32 GetChildCount( ) const { return m_lChildren.size( ); }

		// Search function to find an actor in the scene.
		bool FindActor( CActor*& _pActor, const char* _kpcActorId ); 

	/*	member accessors */
		
		// Retunrs the actors position.
		inline CFVec3 GetWorldPosition( ) const { return m_vWorldPosition; }

		// Gets the actors local positition.
		inline CFVec3 GetLocalPosition( ) const { return m_vLocalPosition; }

		// Sets the actors world position.
		inline CFVec3 SetWorldPosition(  const CFVec3& _krvPosition ){ m_vWorldPosition = _krvPosition; }

		// Sets the actors poition
		inline void SetLocalPosition( const CFVec3& _krvPosition ){ m_vLocalPosition = _krvPosition; }

		// Sets the actor scale.
		inline void SetScale( const CFVec3& _krvScale ){ m_vScale = _krvScale; }

		// Gets the actors scale.
		inline const CFVec3& GetScale( ) const { return m_vScale; }

		// Sets the actors local up vector.

	/* Events and runtime type information */

		/**
		 * To be overridden by a derived class
		 */
		 virtual void OnEvent( IEvent* _pEvent, const uint32 _kuMessage, const uint32 _kuEventDomain  ){ }

		 inline void SetRenderFlag( bool _b ){ m_bRenderFlag = _b; } 

	protected:
		CActor*			   m_pParent;			//!< The actors parent.	
		uint32			   m_uPadding[1];		
		CFVec3			   m_vWorldPosition;	//!< The actors world space position.
		CFVec3			   m_vLocalPosition;	//!< The actors local space position. This can be considered as the local transforms translation.
		CFVec3			   m_vScale;			//!< The actors scale.
		char8			   m_pcActorId[256];	//!< The actors id / name.			// 256
		ChildList		   m_lChildren;			//!< The actors children.	
		bool			   m_bRenderFlag;		//!< Determins if the actor will render.
		CFMat4x4	       m_mWorldTransform;	//!< The actors world transform.
		CFMat4x4		   m_mLocalTransform;	//!< The actors local transform.
	};
}// end namespace 

#endif //_ACTOR_H__Included_547649318
