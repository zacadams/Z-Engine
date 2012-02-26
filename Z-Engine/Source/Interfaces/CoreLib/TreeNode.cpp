/**
 *	@file Z-Engine\Z-Engine\Source\Interfaces\CoreLib\TreeNode.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes

// Library includes

// Local includes 
#include "CoreLi


bool GetChild( CTreeNode*& _pNode, const char* _kpcId );
bool FindNode( CTreeNode*& _pNode, const char* _kpcId );

void AddChild( CTreeNode* _pChild );
bool RemoveChild( CTreeNode* _pChild );

void SetId( const char* _kpcId );
const char*			GetId( );