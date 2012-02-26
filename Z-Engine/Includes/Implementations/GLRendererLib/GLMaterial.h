/**
 *	@file Z-Engine\Z-Engine\Implementations\GLRendererLib\GLMaterial.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _GLMATERIAL_H__Included_540936950
#define _GLMATERIAL_H__Included_540936950

#include "RendererLib/Material.h"

namespace ZGE
{
	class CGLMaterial : public IMaterial
	{
	public:
		CGLMaterial( const CMaterialDecription& _krMaterialDesc );
		~CGLMaterial(void);

		/*
		*	Applys the material on teh renderer 
		*/
		virtual bool Apply( );

		/*
		*	Return : The materials description
		*/
		virtual CMaterialDecription& GetDescription( ) ;

	protected:

		CMaterialDecription m_MaterialDesc; //!< The materials description

	};
}

#endif //_GLMATERIAL_H__Included_540936950

