/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\RendererLib\RenderEffectManager.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _RENDEREFFECTMANAGER_H__Included_484725879
#define _RENDEREFFECTMANAGER_H__Included_484725879

#include "CoreLib/AssetManager.h"
namespace ZGE
{
	class IRenderEffectIO;
	class IRenderEffect;
	class CRenderEffectManager : public CAssetManager< IRenderEffect >
	{
	public:
		CRenderEffectManager(void);
		~CRenderEffectManager(void);

		//bool Initialise( IRenderEffectIO* _pRenderEffectIO );

protected:
				/**
		 *	To be overriden to load assets of a derived manager.
		 *	Param _rAssetId : The assets id, ( could be the file name ).
		 *	Param _pAsset   : To be populated with the loaded asset.
		 *	Return : Success.
		 */
		virtual bool LoadAssetImplementation( CAssetId& _rAssetId, tAsset*& _pAsset );

		/**
		 *	To be overidden to release a managers assets.
		 *	Param _pAsset : The asset to release.
		 *	Return : Success.
		 */
		virtual bool ReleaseAsset( tAsset* _pAsset );

	protected:
		//IRenderEffectIO* m_pRenderEffecIO; // The renderer effect instance.
	};
}

#endif //_RENDEREFFECTMANAGER_H__Included_484725879

