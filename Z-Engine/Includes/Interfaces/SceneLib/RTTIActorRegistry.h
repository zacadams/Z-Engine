/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\SceneLib\RTTIActorRegistry.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _RTTIACTORREGISTRY_H__Included_558279231
#define _RTTIACTORREGISTRY_H__Included_558279231

#include "CoreLib/RTTIRegistry.h"

namespace ZGE
{
	/**
	 *	The actor registr.
	 *	Contains all the dynamicly declared actors.
	 */
	class CRTTIActorRegistry : public IRTTIRegistry
	{
	public:
		
		~CRTTIActorRegistry(void);

		/**
		 *
		 */
		static CRTTIActorRegistry& GetInstance( );
		
	protected:
		CRTTIActorRegistry(void);
	};
}
#endif //_RTTIACTORREGISTRY_H__Included_558279231

