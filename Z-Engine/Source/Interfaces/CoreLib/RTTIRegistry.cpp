/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\CoreLib\RTTIRegistry.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "CoreLib/RTTIRegistrar.h"
#include "CoreLib/RTTIRegistry.h"
using namespace ZGE;
IRTTIRegistry::~IRTTIRegistry(void)
{
}


/** 
 *	Registers a RTTI registrar.
 */
void IRTTIRegistry::Register( IRTTIRegistrar* _pRegistrar )
{
	m_lRegistry.push_back( _pRegistrar );
}

/**
 *	Creates an instance of a registered object.
 *  @param _kpcId The id of the registered object to create.
 */
void* IRTTIRegistry::CreateInstanceOf( const char* _kpcId )
{
	// Find the registered instance with teh supplied id.
	Registry::iterator iter = m_lRegistry.begin( );
	for( iter; iter != m_lRegistry.end( ); ++iter )
	{
		if( 0 == _strcmpi( _kpcId, (*iter)->m_pcId ) )
		{
			// Found the target object, create an instance of it.
			void* pInstance =  (*iter)->m_pInstanciationFunction( );
			return pInstance;
		}
	}
	// Target object is not registered.
	assert_now( "Object not registered!" );
	return NULL;
}