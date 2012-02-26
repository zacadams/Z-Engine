/**
 *	@file Z-Engine\Z-Engine\Interfaces\RendererLib\LightManager.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _LIGHTMANAGER_H__Included_519135551
#define _LIGHTMANAGER_H__Included_519135551

#include "CoreLib/AssetManager.h"

namespace ZGE
{
	class ILight;
	class CLighDecription;

	class ILightManager : public CAssetManager< ILight >
	{
	public:
	
		ILightManager( )
		{
			m_kpcManagerId = "Lighting manager";
		}
		virtual ~ILightManager(void){}

		 /*
		 *	Creates a light using the parsed in description
		 *	Param _krLightDec : The lights description
		 */
		virtual bool CreateLight( CLighDecription& _rLightDesc, ILight*& _pAsset ) = 0;
		 
	};
}

#endif //_LIGHTMANAGER_H__Included_519135551

