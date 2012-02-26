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

namespace ZGE
{
	/*
	* The base class for all objects.
	* Represents the base  scene graph object.
	*/
	class CActor
	{
	public:
		CActor(void);
		~CActor(void);

		// Sets the actors id.
		inline SetActorId( const char* _kpcId ) { m_pcActorId = _kpcId; }

		// Returns the actors id as a string.
		inline const char8* GetActorId( ) const { return m_pActorId; }

		// Sets the actors parent.
		inline void SetParent( CActor* _pParent ) { m_pParent = _pParent; }

		// Returns the actors parent.
		inline CActor* GetParent( )const { return m_pParent; }

		// Adds a child to the actor.
		bool AddChild( CActor* _pChild );

		// Removes a child from the actor.
		bool RemoveChild( CActor* _pChild );

		// returns the actors children.
		inline zList& GetChildren( ) { return m_lChildren; }

		// Empty process function, to be overidden by derived classes.
		bool Process( const float32 _kfDeltaTick ) { UNUSED_VAR( _kfDeltaTick );  }

		// Empty draw function, to be overidden by derived classes.
		bool Draw( const CFMat4x4& _krmParentTransform ) { UNUSED_VAR( _krmParentTransform ); }

	protected:

		char8*  m_pcActorId;			//!< The actors id / name.
		CActor* m_pParent;				//!< The actors parent.
		zList< CActor* > m_lChildren;	//!< The actors child list.
	};
}// end namespace 

#endif //_ACTOR_H__Included_547649318

