/**
 *	@file Z-Engine\Z-Engine\Implementations\GLRendererLib\GLLightManager.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _GLLIGHTMANAGER_H__Included_1573250220

#include "RendererLib/LightManager.h"

namespace ZGE
{
	class CGLLightManager : public ILightManager
	{
	public:
		CGLLightManager(void);
		~CGLLightManager(void);

				 /*
		 *	Creates a light using the parsed in description
		 *	Param _krLightDec : The lights description
		 */
		virtual bool CreateLight( CLighDecription& _rLightDesc, ILight*& _pAsset );

				/*
		*	To be overriden to load assets of a derived manager.
		*	Param _rAssetId : The assets id, ( could be the file name ).
		*	Param _pAsset   : To be populated with the loaded asset.
		*	Return : Success.
		*/
		virtual bool LoadAsset( CAssetId& _rAssetId, ILight*& _pAsset );

		/*
		*	To be overidden to release a managers assets.
		*	Param _pAsset : The asset to release.
		*	Return : Success.
		*/
		virtual bool ReleaseAsset( ILight* _pAsset );
	};
}

#endif //_GLLIGHTMANAGER_H__Included_1573250220

