/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9Material.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _DX9MATERIAL_H__Included_1874348488
#define _DX9MATERIAL_H__Included_1874348488

#include "RendererLib/Material.h"
#include <d3dx9.h>

struct IDirect3DDevice9;

namespace ZGE
{
	class CDX9Material : public IMaterial
	{
	public:
		CDX9Material( IDirect3DDevice9* _pDevice, CMaterialDecription& _rMaterialDesc );
		~CDX9Material(void);

		/*
		*	Applys the material on teh renderer 
		*/
		virtual bool Apply( );

		/*
		*	Return : The materials description
		*/
		virtual CMaterialDecription& GetDescription( );

	protected:

		IDirect3DDevice9* m_pDevice;
		CMaterialDecription m_MaterialDesc;
		D3DMATERIAL9*     m_pD3DMaterial;
	};
}// end namespace 

#endif //_DX9MATERIAL_H__Included_1874348488

