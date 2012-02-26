/**
 *	@file Z-Engine\Z-Engine\Implementations\GLRendererLib\GLMaterial.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"

// GL includes 
#include <gl\gl.h>
#include <gl\glu.h>

#include "GLMaterial.h"

using namespace ZGE;

CGLMaterial::CGLMaterial( const CMaterialDecription& _krMaterialDesc )
: m_MaterialDesc( _krMaterialDesc )
{
}

CGLMaterial::~CGLMaterial(void)
{
}

/*
*	Applys the material on teh renderer 
*/
bool CGLMaterial::Apply( )
{
	float32 pValues[4];
	// Ambient 
	ConvertColorToFloat( m_MaterialDesc.m_uAmbient,  pValues );
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT,	 pValues );

	// Diffuse
	ConvertColorToFloat( m_MaterialDesc.m_uDiffuse,  pValues );
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE,	 pValues );

	// Emissive
	ConvertColorToFloat( m_MaterialDesc.m_uEmissive,  pValues );
	glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION,	 pValues );
	
	// Specular
	ConvertColorToFloat( m_MaterialDesc.m_uSpecular,  pValues );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR,	 pValues);
	glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS,	 m_MaterialDesc.m_fSpecularPower );

	return true;
}

/*
*	Return : The materials description
*/
CMaterialDecription& CGLMaterial::GetDescription( )
{
	return m_MaterialDesc;
}
