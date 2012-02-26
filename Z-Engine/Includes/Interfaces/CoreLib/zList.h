/**
 *	@file Z-Engine\Z-Engine\Interfaces\CoreLib\zList.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _ZLIST_H__Included_1198806517
#define _ZLIST_H__Included_1198806517
#pragma once

namespace ZGE
{


	/*
	* Defines a node for a list
	*/
	template < typename t > class zNode
	{
	public:

		typedef t tElement;
		typedef zNode<t> tNode;

		zNode<t>(  )
		: m_pNext( NULL )
		, m_pPrevious( NULL )
		{

		}

		zNode<t>( t _tData )
		: m_tData( _tData )
		, m_pNext( NULL )
		, m_pPrevious( NULL )
		{

		}

		// Overloaded dereference operator,
		// to return the nodes data.
		tElement* operator*( )
		{
		}

		// Overloadded assignment operator.
		// Assignes the nodes data.
		void operator= ( const tNode* _kr )
		{
			m_pData = *_kr;
		}

		// Overloaded assignment operator.
		// Sets the nodes data
		void operator= ( const t* _kr )
		{
			m_pData = _kr;
		}

		// Overloaded indirection operator
		// Returns the element data.
		tElement* operator->( )
		{
			return m_tData;
		}

		// Overloadded addition operator.
		// Increases the 
		
		zNode<t>* m_pNext;		//!< The next node in th list
		zNode<t>* m_pPrevious;	//!< The previous node in the list
		tElement  m_tData;

	};

	/*
	* Supplies ab implementation for traversing a list 
	*/
	template <typename t> class zItterator
	{
	public:

		// Overloaded constructor

		// Overloaded post increment operator
		// Make the itteratort point to the next element in a list
		void operator++( )
		{
			m_pNode = m_pNode->m_pNext;
		}

		// Overloaded post decrement operator
		// Makes the iterrator point to the previous element in the list
		void operator--( )
		{
			m_pNode = m_pNode->m_pPrevious;
		}

		// Overloaded dereference operator
		// Returns the data at the iterrator
		t operator*( )
		{
			return *m_pNode;
		}

		// Overlloadded assignment operator.
		// Points the itterator at the node
		void operator =( const zNode<t>* _kr )
		{
			m_pNode = _kr;
 		}

		// Overloaded indirection operator
		// Returns a pointer to the data the iterrator is pointing to 
		t* operator->( )
		{
			return;
		}

		// Overloaded equality operator.
		// Checks if the iterrator is equvalent to the consition
		bool operator==( zNode<t>* _pElement )
		{
			if( m_pNode == _pElement )
			{
				return true;
			}
			return false;
		}
		// Overloaded in-equality operator.
		// Checks if the iterrator is not equvalent to the consition
		bool operator!=( zNode<t>* _pElement )
		{
			if( m_pNode != _pElement )
			{
				return true;
			}
			return false;
		}

	protected:
		zNode<t>* m_pNode;
	};


	/*
	* Wrapper for a list implementation.
	* By wrapping the list a new implementation can be written when porting
	* to other platforms.
	*/
	template< typename t > class zList
	{
	public:

		typedef t tElement;
		typedef zNode<t> tNode;

		zList<t>(void)
		{
			// Create a dummy node at the start and end
			m_pListStart = new tNode( );
			m_pListEnd   = new tNode( );
		}
		~zList<t>(void)
		{
			delete m_pListStart;
			delete m_pListEnd;
		}

		// Adds  the defined element
		// Removes it from the list, does not delete the data
		// Returns success
		bool AddElement( tElement* _pElement )
		{
			tNode* pNode = new tNode( _pElement );

			m_pListEnd->m_pPrevious->m_pNext = _pElement;
			m_pListEnd->m_pPrevious =
		}

		// Removes the defined element
		// Removes it from the list, does not delete the data
		// Returns success
		bool RemoveElement( tElement* _pElement)
		{
		}

		// Returns the beginning node
		// The bigging node is the dummies next node
		zItterator<tNode*> Start( ) const
		{
			return zItterator<tNode>( m_pListStart->m_pNext );
		}

		// Returns the end of a list
		// The last node is the end dummies previous node
		tNode* End( ) const 
		{
			return m_pListEnd->m_pPrevious;
		}
			
	protected:

		tNode* m_pListStart;
		tNode* m_pListEnd;
	};
}

#endif //_ZLIST_H__Included_1198806517

