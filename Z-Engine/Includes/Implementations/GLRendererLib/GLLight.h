/**
 *	@file Z-Engine\Z-Engine\Implementations\GLRendererLib\GLLight.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _GLLIGHT_H__Included_350631075
#define _GLLIGHT_H__Included_350631075

#include "RendererLib/Light.h"

namespace ZGE
{
	class CGLLight : public ILight
	{
	public:
		CGLLight( const CLighDecription& _krLightDesc);
		~CGLLight(void);

		/*
		*	Sets a light at the given index on the renderer
		*/
		virtual bool Apply( const uint32 _kuIndex ) ;
		/*
		*	Enables the light source, also updates the light with its description
		*/
		virtual void Enable( );
		/*
		*	Unenables the lights source
		*/
		virtual void UnEnable( );
		/*
		*	Return : The lights attrubutes
		*/
		virtual CLighDecription& GetLightsDecsription( );

	protected:

		CLighDecription m_LightDesc;	//!< The lights description
		uint32			m_uLightIndex;	//!< This lights bound index
		static		uint32	sm_uLightCount;	//!< The current light count and index.
	
	};
}

#endif //_GLLIGHT_H__Included_350631075

