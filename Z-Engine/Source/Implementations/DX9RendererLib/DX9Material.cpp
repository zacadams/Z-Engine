/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9Material.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/

#include "CoreLib/Core.h"


#include "DX9RendererLib/DX9Material.h"

using namespace ZGE;
CDX9Material::CDX9Material(IDirect3DDevice9* _pDevice, CMaterialDecription& _rMaterialDesc)
: m_pDevice( _pDevice )
, m_MaterialDesc( _rMaterialDesc )
{
	//Note: The CMaterialDecsription class is the same structure as D3DMATERIAL9
	m_pD3DMaterial = new D3DMATERIAL9(  );


	m_pD3DMaterial->Ambient.a  = (  (float32)(m_MaterialDesc.m_uAmbient >> 24 & 0xFF )/ 255 ); 
	m_pD3DMaterial->Ambient.r  = (  (float32)(m_MaterialDesc.m_uAmbient >> 16 & 0xFF )/ 255 ); 
	m_pD3DMaterial->Ambient.g  = (  (float32)(m_MaterialDesc.m_uAmbient >> 8  & 0xFF )/ 255 ); 
	m_pD3DMaterial->Ambient.b  = (  (float32)(m_MaterialDesc.m_uAmbient >> 0  & 0xFF )/ 255 ); 

	m_pD3DMaterial->Specular.a = ( (float32)(m_MaterialDesc.m_uSpecular >> 24 & 0xFF )/ 255 );   
	m_pD3DMaterial->Specular.r = ( (float32) (m_MaterialDesc.m_uSpecular >> 16 & 0xFF )/ 255 );    
	m_pD3DMaterial->Specular.g = ( (float32) (m_MaterialDesc.m_uSpecular >> 8  & 0xFF )/ 255 );  
	m_pD3DMaterial->Specular.b = ( (float32) (m_MaterialDesc.m_uSpecular >> 0  & 0xFF ) / 255 );  
								  
	m_pD3DMaterial->Diffuse.a =	( (float32) (m_MaterialDesc.m_uDiffuse >> 24 & 0xFF  ) / 255 );   
	m_pD3DMaterial->Diffuse.r = ( (float32) (m_MaterialDesc.m_uDiffuse >> 16 & 0xFF  ) / 255 );  
	m_pD3DMaterial->Diffuse.g = ( (float32) (m_MaterialDesc.m_uDiffuse >> 8  & 0xFF  ) / 255 );   
	m_pD3DMaterial->Diffuse.b = ( (float32) (m_MaterialDesc.m_uDiffuse >> 0  & 0xFF  ) / 255 ); 
								
	m_pD3DMaterial->Emissive.a = ( (float32)( m_MaterialDesc.m_uEmissive >> 24 & 0xFF  )/ 255 );
	m_pD3DMaterial->Emissive.r = ( (float32)( m_MaterialDesc.m_uEmissive >> 16 & 0xFF  )/ 255 );
	m_pD3DMaterial->Emissive.g = ( (float32)( m_MaterialDesc.m_uEmissive >> 8  & 0xFF  ) / 255 );
	m_pD3DMaterial->Emissive.b = ( (float32)( m_MaterialDesc.m_uEmissive >> 0  & 0xFF )  / 255 );
	m_pD3DMaterial->Power = m_MaterialDesc.m_fSpecularPower;
}		

CDX9Material::~CDX9Material(void)
{
}
/*
*	Applys the material on teh renderer 
*/
bool CDX9Material::Apply( )
{
	if( FAILED( m_pDevice->SetMaterial( m_pD3DMaterial ) ) )
	{
		// assert
		return false;
	}
	return true;
}
/*
*	Return : The materials description
*/
CMaterialDecription& CDX9Material::GetDescription( )
{
	return m_MaterialDesc;
}
