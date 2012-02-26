/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\Physics2DLib\CollisionInfo.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "Physics2DLib/CollisionInfo.h"
using namespace ZGE;
CCollisionInfo::CCollisionInfo(void)
{
	m_ppIntersectingPrimitives[0] = NULL;
	m_ppIntersectingPrimitives[1] = NULL;
}

CCollisionInfo::~CCollisionInfo(void)
{
}
