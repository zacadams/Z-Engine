/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9Light.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _DX9LIGHT_H__Included_67229625
#define _DX9LIGHT_H__Included_67229625

#include "RendererLib/Light.h"
#include <d3dx9.h>
struct IDirect3DDevice9;

namespace ZGE
{

	class CDX9Light : public ILight
	{
	public:
		CDX9Light( IDirect3DDevice9* _pDevice, CLighDecription& _rLightDesc );
		~CDX9Light(void);
		
		/*
		*	Sets a light at the given index on the renderer
		*/
		virtual bool Apply( const uint32 _kuIndex );
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
		virtual CLighDecription& GetLightsDecsription( ) ;

	protected:

		IDirect3DDevice9* m_pDevice;
		CLighDecription   m_LightDec;
		uint32				  m_uIndex;
		D3DLIGHT9*		  m_pD3DLight;
	};
}

#endif //_DX9LIGHT_H__Included_67229625

