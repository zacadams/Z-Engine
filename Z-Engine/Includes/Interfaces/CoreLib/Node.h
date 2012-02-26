/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\CoreLib\Node.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _NODE_H__Included_839010843
#define _NODE_H__Included_839010843


#include <list>
namespace ZGE
{
	template< typename t>
	class CNode
	{
	public:
		typedef CNode<t> tThis;

		CNode( )
		{
		}
		~CNode( )
		{
		}

		// Sets the nodes parent.
		void SetParent( t* _pParent )
		{
			m_pParent = _pParent;
		}

		// Adds a child to the node.
		void AddChild(  t* _pChild )
		{
			m_lChildren.push_back( _pChild );
		}
		
		// Get the parent.
		tThis* GetParent( )
		{
			return m_pParent;
		}

		// Get a childs node at the given index.
		tThis* GetChild( const uint32 _kuIndex )
		{
			const uint32 kuChildCount = GetChildCount( );
			if( kuChildCount > _kuIndex )
			{
				ChildList::iterator iter = m_lChildren.begin( );
				for( uint32 uChild = 0; uChild < _kuIndex; ++uChild )
				{
					iter++;
				}
				return *iter;
			}
			else
			{
				assert_now( "Invalid index" );
				return NULL;
			}

		}

		// Gets a child node by name.
		t* FindChild( const char* _kpcName )
		{
			t* pChild = NULL;
			ChildList::iterator iter = m_lChildren.begin( );
			for( iter; iter != m_lChildren.end( ); ++iter )
			{
				if( ZUtilities::StrCmp( (*iter)->GetName( ), _kpcName ) )
				{
					return *iter;
				}
			}

			iter = m_lChildren.begin( );
			for( iter; iter != m_lChildren.end( ); ++iter )
			{
				pChild = (*iter)->FindChild( _kpcName );
				if( pChild )
				{
					return pChild;
				}
			}
			return pChild;
		}


		// Gets the nodes child count
		const uint32 GetChildCount( ) const
		{
			return m_lChildren.size( );
		}

		// Sets the nodes name.
		void SetName( const char* _kpcName )
		{
			STR_PRINT( m_pcName, "%s", _kpcName );
		}

		const char* GetName( ) const 
		{
			return m_pcName;
		}

	protected:
		t* m_pParent;
		
		typedef std::list<  t* > ChildList;
		ChildList m_lChildren;
		char m_pcName[256];

	};
}

#endif //_NODE_H__Included_839010843

