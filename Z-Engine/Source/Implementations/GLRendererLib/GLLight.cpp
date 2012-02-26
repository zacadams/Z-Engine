/**
 *	@file Z-Engine\Z-Engine\Implementations\GLRendererLib\GLLight.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"

// GL includes 

#include <gl/gl.h>
#include<gl/glu.h>

#include "GLLight.h"


using namespace ZGE;

uint32 CGLLight::sm_uLightCount = 0;

CGLLight::CGLLight( const CLighDecription& _krLightDesc )
: m_LightDesc ( _krLightDesc )
{
	m_uLightIndex = sm_uLightCount;
	++sm_uLightCount;
}

CGLLight::~CGLLight(void)
{
	--sm_uLightCount;
}

/*
*	Sets a light at the given index on the renderer
*/
bool CGLLight::Apply( const uint32 _kuIndex ) 
{
	UNUSED_VAR( _kuIndex );
	return false;
}
/*
*	Enables the light source, also updates the light with its description
*/
void CGLLight::Enable( )
{
	// Look up table for the light index
	static uint32 GLLightIndex[] = 
	{
		GL_LIGHT0,
		GL_LIGHT1,
		GL_LIGHT2, 
		GL_LIGHT3,
		GL_LIGHT4,
		GL_LIGHT5,
		GL_LIGHT6,
		GL_LIGHT7,
	};
	
	// Get the GL ligh index
	uint32 uGLLightIndex = GLLightIndex[m_uLightIndex];

	float32 fFloatArray[4];

	//W component determines light type. If it is 0, directional light, else if 1, then positional.
	if ( LT_Directional == m_LightDesc.m_eLightType )
	{
		//In this case, XYZ is the light direction.
		fFloatArray[0] = m_LightDesc.m_fDirectionX;
		fFloatArray[1] = m_LightDesc.m_fDirectionY;
		fFloatArray[2] = -m_LightDesc.m_fDirectionZ;
		fFloatArray[3] = 0.0f;
	}
	else
	{
		//Both point lights and spot lights use this. Spot light is just a specialization of a point light.
		fFloatArray[0] = m_LightDesc.m_fPositionX;
		fFloatArray[1] = m_LightDesc.m_fPositionY;
		fFloatArray[2] = m_LightDesc.m_fPositionZ;
		fFloatArray[3] = 1.0f;
	}

	//Set light position:
	glLightfv( uGLLightIndex, GL_POSITION, fFloatArray );
	
	//Update diffuse colour:
	ConvertColorToFloatRGBA( m_LightDesc.m_uDiffuse, fFloatArray );
	glLightfv( uGLLightIndex, GL_DIFFUSE, fFloatArray );			//Next 4 members (inclusive) are valid colour data. RGBA.
	
	//Update specular colour:
	ConvertColorToFloatRGBA( m_LightDesc.m_uSpecular, fFloatArray );
	glLightfv( uGLLightIndex, GL_SPECULAR, fFloatArray );			//Next 4 members (inclusive) are valid colour data. RGBA.

	//Update ambient colour:
	ConvertColorToFloatRGBA( m_LightDesc.m_uAmbient, fFloatArray );
	glLightfv( uGLLightIndex, GL_AMBIENT, fFloatArray );			//Next 4 members (inclusive) are valid colour data. RGBA.
	
	//Update attenuation.
	glLightf( uGLLightIndex, GL_CONSTANT_ATTENUATION, m_LightDesc.m_Attenuation0 );
	glLightf( uGLLightIndex, GL_LINEAR_ATTENUATION,   m_LightDesc.m_Attenuation1 );
	glLightf( uGLLightIndex, GL_QUADRATIC_ATTENUATION,m_LightDesc.m_Attenuation2 );


	//If this is a spot light, update spot light specific properties:
	if ( LT_Spot ==  m_LightDesc.m_eLightType )
	{
		//What do?
		//http://www.opengl.org/sdk/docs/man/xhtml/glLight.xml
		//GL_SPOT_EXPONENT
		//params is a single integer or floating-point value that specifies the intensity distribution of the light. 
		//Integer and floating-point values are mapped directly. Only values in the range 0 128 are accepted.

		//Effective light intensity is attenuated by the cosine of the angle between the direction of the light and the direction from the light 
		//to the vertex being lighted, raised to the power of the spot exponent. 
		//Thus, higher spot exponents result in a more focused light source, regardless of the spot cutoff angle (see GL_SPOT_CUTOFF, next paragraph).
		//The initial spot exponent is 0, resulting in uniform light distribution.

		//GL_SPOT_CUTOFF
		//params is a single integer or floating-point value that specifies the maximum spread angle of a light source.
		//Integer and floating-point values are mapped directly. Only values in the range 0 90 and the special value 180 are accepted. 
		//If the angle between the direction of the light and the direction from the light to the vertex being lighted is greater 
		//than the spot cutoff angle, the light is completely masked. Otherwise, its intensity is controlled by the spot exponent and the attenuation factors.
		//The initial spot cutoff is 180, resulting in uniform light distribution.

		//Z needs to be negated for this!
		float32* pDirection = &m_LightDesc.m_fDirectionX;
		glLightfv( uGLLightIndex, GL_SPOT_DIRECTION, pDirection );	//3 directional values, sequential in memory. More elegant this way.
		glLightf( uGLLightIndex, GL_SPOT_CUTOFF, m_LightDesc.m_fRange );
		glLightf( uGLLightIndex, GL_SPOT_EXPONENT, m_LightDesc.m_fFallOff );
	}

	//Valid for 8 lights, same as directX.
	glEnable( uGLLightIndex );
}
/*
*	Unenables the lights source
*/
void CGLLight::UnEnable( )
{
	glDisable( m_uLightIndex );
}
/*
*	Return : The lights attrubutes
*/
CLighDecription& CGLLight::GetLightsDecsription( )
{
	return m_LightDesc;
}
