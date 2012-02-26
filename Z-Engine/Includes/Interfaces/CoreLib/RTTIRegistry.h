/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\CoreLib\RTTIRegistry.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _RTTIREGISTRY_H__Included_2130189372
#define _RTTIREGISTRY_H__Included_2130189372

#include <list>
namespace ZGE
{
	class IRTTIRegistrar;
	/**
	 * Base class for a registry. 
	 */
	class IRTTIRegistry
	{
	public:
		virtual ~IRTTIRegistry(void);
	
		/** 
		 *	Registers a RTTI registrar. 
		 */
		void Register( IRTTIRegistrar* _pRegistrar );

		/**
		 *	Creates an instance of a registered object.
		 *  @param _kpcId The id of the registered object to create.
		 */
		void* CreateInstanceOf( const char* _kpcId ); 


	protected: 
		typedef std::list< IRTTIRegistrar* > Registry;
		Registry m_lRegistry;
	};
}

#endif //_RTTIREGISTRY_H__Included_2130189372

