/**
 *	@file Z-Engine\Z-Engine\Includes\Interfaces\CoreLib\TreeNode.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _TREENODE_H__Included_1834731984
#define _TREENODE_H__Included_1834731984
#ifndef __TREE_NODE__
#define __TREE_NODE__

/**
 *	The base class for a tree node. 
 *	This class handles all parent child relationships.
 */
class CTreeNode
{
public:
	typedef std::list< CTreeNode* > ChildList;
	
	CTreeNode( );
	virtual ~CTreeNode( );

	inline CTreeNode*	GetChild( const unsigned int kuChildIndex );
	bool				GetChild( CTreeNode*& _pNode, const char* _kpcId );
	bool				FindNode( CTreeNode*& _pNode, const char* _kpcId );
	inline uint32		GetChildCount( ) const { return m_lChildren.size( ); }

	inline void			SetParent( CTreeNode* _pParent ) { m_pParent = _pParent; }
	inline CTreeNode*	GetParent( )const { return m_pParent; }
	void				AddChild( CTreeNode* _pChild );
	bool				RemoveChild( CTreeNode* _pChild );
	inline ChildList&   GetChildren( ){ return m_lChildren; };


	// Helper functions that retrieve the nodes parent / children as specified types.
	// Note: tType must be a pointer to a Type;
	template<typename tType>
	inline void			GetChildAs( tType _pType, const unsigned int kuChildIndex );
	template<typename tType>
	void				GetChildAs( tType _pType, const char* _kpcId );
	template<typename tType>
	inline void			GetParentAs( tType _pType );

	void				SetId( const char* _kpcId );
	const char*			GetId( );
protected:
	CTreeNode*	m_pParent;		//!< The nodes parent.
	ChildList	m_lChildren;	//!< The nodes childen.
	char		m_pcId[256];
};

#endif // __TREE_NODE__
#endif //_TREENODE_H__Included_1834731984

