/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\SceneLib\RTTIActorRegistry.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "SceneLib/RTTIActorRegistry.h"
using namespace ZGE;
CRTTIActorRegistry::CRTTIActorRegistry(void)
{
}

CRTTIActorRegistry::~CRTTIActorRegistry(void)
{
}

/**
 *
 */
CRTTIActorRegistry& CRTTIActorRegistry::GetInstance( )
{
	static CRTTIActorRegistry registry;
	return registry;
}