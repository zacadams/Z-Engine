/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\Physics2DLib\IntersectionInfo.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "Physics2DLib/IntersectionInfo.h"

using namespace ZGE;
CIntersectionInfo::CIntersectionInfo(void)
: m_bIntersected( false )
, m_vIntersectionPoint( CFVec3( .0f, 0.0f, 0.0f ) )
, m_vIntersectionNormal( CFVec3( 0.0f, 0.0f, 0.0f ) )
{
}

CIntersectionInfo::~CIntersectionInfo(void)
{
}
