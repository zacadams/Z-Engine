/**
 *	@file Z-Engine\Z-Engine\Interfaces\RendererLib\MaterialManager.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _MATERIALMANAGER_H__Included_1276272603
#define _MATERIALMANAGER_H__Included_1276272603

#include "CoreLib/AssetManager.h"

namespace ZGE
{
	class IMaterial;
	class CMaterialDecription;

	/*
	*	Material manager interface
	*/
	class IMaterialManager : public CAssetManager< IMaterial > 
	{
	public:

		IMaterialManager( )
		{
			m_kpcManagerId = "Material manager";
		}
		virtual ~IMaterialManager(){}

		/*
		*	Creates a material using a material description
		*	Param _rAssetyId : The materials id
		*	Param _rMaterialDesc : Containes the materials properties
		*	Param _pAsset	: To be populated with the IMaterial instance
		*/
		virtual bool CreateMaterial( CAssetId& _rAssetId, CMaterialDecription& _rMaterialDesc, IMaterial*& _pAsset ) = 0;
	
	};
}
#endif //_MATERIALMANAGER_H__Included_1276272603

