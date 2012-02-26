/**
 *	@file Z-Engine\Z-Engine\Interfaces\RendererLib\EffectManager.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _EFFECTMANAGER_H__Included_1251350893
#define _EFFECTMANAGER_H__Included_1251350893

#include "CoreLib/AssetManager.h"

namespace ZGE
{
	class IEffect;
	
	/*
	* Manages loaded shader files.
	* Derived effects will have to 
	*/
	class IEffectManager : public CAssetManager< IEffect >
	{
	public:
		IEffectManager( )
		{
			m_kpcManagerId = "Effect manager";
		}
		virtual ~IEffectManager(void) {}

		/*
		* Returns the default rendering effect.
		* Defualts to rendering a mesh with diffuse textures
		* and materials using the fixed function pipeline.
		*/
		virtual IEffect* GetDefaultEffect( ) = 0;

		/*
		* Creates a user defined effect.
		*/
		template< typename t >
		void CreateEffect( t* _pEffect, const CAssetId& _rAssetId  )
		{
			//_pEffect = new t( );
			//AddPreCreatedAsset( _rAssetId, reinterpret_cast< IEffect* >( _pEffect ) );
		}
	};
}

#endif //_EFFECTMANAGER_H__Included_1251350893

