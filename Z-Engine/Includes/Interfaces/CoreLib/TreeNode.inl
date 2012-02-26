/**
 *	@file Z-Engine\Z-Engine\Includes\Interfaces\CoreLib\TreeNode.inl
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/

inline ChildList& CTreeNode::GetChildren( )
{ 
	return m_lChildren; 
};
inline CTreeNode* CTreeNode::GetChild( const unsigned int kuChildIndex )
{
	if( m_lChildren.size( ) <= kuChildIndex )
	{
		return NULL;
	}

	return m_lChildren.begin( ) + kuChildIndex;
}
inline uint32 CTreeNode::GetChildCount( ) const )
{
	return m_lChildren.size( ); 
}
inline void CTreeNode::SetParent( CTreeNode* _pParent ) 
{
	m_pParent = _pParent; 
}
inline CTreeNode* CTreeNode::GetParent( )const
{
	return m_pParent;
}
// Helper functions that retrieve the nodes parent / children as specified types.
// Note: tType must be a pointer to a Type;
template<typename tType>
inline void	CTreeNode::GetChildAs( tType _pType, const unsigned int kuChildIndex )
{
}
template<typename tType>
void CTreeNode::GetChildAs( tType _pType, const char* _kpcId )
{
}
template<typename tType>
inline void	CTreeNode::GetParentAs( tType _pType )
{
}