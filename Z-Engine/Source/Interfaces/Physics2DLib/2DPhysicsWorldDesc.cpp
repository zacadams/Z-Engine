/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\Physics2DLib\2DPhysicsWorldDesc.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "Physics2DLib/2DPhysicsWorldDesc.h"
using namespace ZGE;
C2DPhysicsWorldDesc::C2DPhysicsWorldDesc( const CFVec2& _krvGravity )
: m_vGravity( _krvGravity )
{
}

C2DPhysicsWorldDesc::~C2DPhysicsWorldDesc(void)
{
}

