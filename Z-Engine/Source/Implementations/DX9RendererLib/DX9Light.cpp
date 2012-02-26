/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9Light.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/


#include "CoreLib/Core.h"

#include <d3dx9.h>

#include "DX9RendererLib/DX9Light.h"

using namespace ZGE;

CDX9Light::CDX9Light( IDirect3DDevice9* _pDevice, CLighDecription& _rLightDesc )
: m_pDevice( _pDevice )
, m_LightDec( _rLightDesc )
, m_uIndex ( 0 )
{

	// Note: The CLight desc is the same as the d3d light structure 
		//0xFFFF0000, d
		//0xFFFFFFFF, s
		//0xFF000000, a



	m_pD3DLight = new D3DLIGHT9( );

	m_pD3DLight->Ambient.a  = ( (float32)( m_LightDec.m_uAmbient >> 24 & 0xFF )/ 255 ); 
	m_pD3DLight->Ambient.r  = ( (float32)( m_LightDec.m_uAmbient >> 16 & 0xFF )/ 255 ); 
	m_pD3DLight->Ambient.g  = ( (float32)( m_LightDec.m_uAmbient >> 8  & 0xFF )/ 255 ); 
	m_pD3DLight->Ambient.b  = ( (float32)( m_LightDec.m_uAmbient >> 0  & 0xFF )/ 255 ); 
								
	m_pD3DLight->Specular.a = ( (float32)( m_LightDec.m_uSpecular >> 24 & 0xFF )/ 255 );   
	m_pD3DLight->Specular.r = ( (float32)( m_LightDec.m_uSpecular >> 16 & 0xFF )/ 255 );    
	m_pD3DLight->Specular.g = ( (float32)( m_LightDec.m_uSpecular >> 8  & 0xFF )/ 255 );  
	m_pD3DLight->Specular.b = ( (float32)( m_LightDec.m_uSpecular >> 0  & 0xFF )/ 255 );  
								
	m_pD3DLight->Diffuse.a =  ( (float32)( m_LightDec.m_uDiffuse >> 24 & 0xFF  )/ 255 );   
	m_pD3DLight->Diffuse.r =  ( (float32)( m_LightDec.m_uDiffuse >> 16 & 0xFF  )/ 255 );  
	m_pD3DLight->Diffuse.g =  ( (float32)( m_LightDec.m_uDiffuse >> 8  & 0xFF  )/ 255 );   
	m_pD3DLight->Diffuse.b =  ( (float32)( m_LightDec.m_uDiffuse >> 0  & 0xFF  )/ 255 ); 

	m_pD3DLight->Attenuation0 = m_LightDec.m_Attenuation0;
	m_pD3DLight->Attenuation1 = m_LightDec.m_Attenuation1;
	m_pD3DLight->Attenuation2 = m_LightDec.m_Attenuation2;

	m_pD3DLight->Range	  = m_LightDec.m_fRange;
	m_pD3DLight->Falloff  = m_LightDec.m_fFallOff;
	m_pD3DLight->Theta    = m_LightDec.m_fTheta;
	m_pD3DLight->Phi      = m_LightDec.m_fPhi;

	m_pD3DLight->Position = D3DXVECTOR3( m_LightDec.m_fPositionX,  m_LightDec.m_fPositionY,  m_LightDec.m_fPositionZ );
	m_pD3DLight->Direction = D3DXVECTOR3( m_LightDec.m_fDirectionX,  m_LightDec.m_fDirectionY,  m_LightDec.m_fDirectionZ );

	static D3DLIGHTTYPE pLightTypes[] = 
	{
		D3DLIGHT_DIRECTIONAL,
		D3DLIGHT_SPOT,
		D3DLIGHT_POINT,
	};

	m_pD3DLight->Type = pLightTypes[m_LightDec.m_eLightType];


}

CDX9Light::~CDX9Light(void)
{
	SafeDelete( m_pD3DLight );
}
/*
*	Sets a light at the given index on the renderer
*/
bool CDX9Light::Apply( const uint32 _kuIndex )
{
	m_uIndex = _kuIndex;
	if( FAILED( m_pDevice->SetLight( m_uIndex, m_pD3DLight ) ) )
	{
		// assert
		return false;
	}
	return true;
}
/*
*	Enables the light source, also updates the light with its description
*/
void CDX9Light::Enable( )
{
	if( FAILED( m_pDevice->LightEnable( m_uIndex , TRUE ) ) )
	{
		// assert
		int i = 0;i;
	}
}
/*
*	Unenables the lights source
*/
void CDX9Light::UnEnable( )
{
	if( FAILED( m_pDevice->LightEnable( m_uIndex , FALSE ) ) )
	{
		// assert 
		int i = 0; i;
	}
}
/*
*	Return : The lights attrubutes
*/
CLighDecription& CDX9Light::GetLightsDecsription( )
{
	return m_LightDec;
}
