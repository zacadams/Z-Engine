/**
 *	@file Z-Engine\Z-Engine\Interfaces\RendererLib\Light.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _LIGHT_H__Included_38277623
#define _LIGHT_H__Included_38277623

#include "CoreLib/Asset.h"
#include "MathLib/FVec3.h"

namespace ZGE
{

	/*
	*	Enumeration of lights types 
	*/
	enum ELightType
	{
		LT_Directional,	//!< Directonal, lighsts every thing evenly, sun.
		LT_Spot,		//!< Spot light, lights as a cone, tourche.
		LT_Point,		//!< Point light, has a position and lights objects in a 360 range over a set range.
		LT_NONE,		//!< If a light has a type of none, it will be unable to be set on the renderer or enabled.
	};

	/*
	*	Represents a lights descriptions and properties 
	*/
	class CLighDecription
	{
	public:

		ELightType     m_eLightType;	//!< The light type. 
		uint32		   m_uDiffuse;		//!< The lights diffuse colour.
		uint32         m_uSpecular;		//!< The lights specular colour.
		uint32         m_uAmbient;		//!< The lights ambient colour.
		float32		   m_fPositionX;
		float32		   m_fPositionY;
		float32		   m_fPositionZ;
		float32		   m_fDirectionX;
		float32		   m_fDirectionY;
		float32		   m_fDirectionZ;
		float32        m_fRange;		//!< The lights range.
		float32	       m_fFallOff;		//!< How fast the lights intensioty falls off over range.
		float32        m_Attenuation0;	//!< Value specifying how the light intensity changes over distance.
		float32	       m_Attenuation1;	//!< Value specifying how the light intensity changes over distance.
		float32	       m_Attenuation2;	//!< Value specifying how the light intensity changes over distance.
		float32        m_fTheta;		//!< The angle of a spot lights outter cone 
		float32	       m_fPhi;			//!< The angle of a spot lights inner  cone

		/*
		*	Initilaises all the veariables to be zer0 
		*/
		void ZeroLight( )
		{
		
			m_eLightType     = LT_NONE;	
			m_uDiffuse		 = 0x00000000;		
			m_uSpecular		 = 0x00000000;		
			m_uAmbient		 = 0x00000000;
			m_fPositionX     = 0.0f;
			m_fPositionY     = 0.0f;
			m_fPositionZ	 = 0.0f;
			m_fDirectionX	 = 0.0f;	
			m_fDirectionY	 = 0.0f;	
			m_fDirectionZ	 = 0.0f;	
			m_fRange		 = 0.0f;
			m_fFallOff		 = 0.0f;
			m_Attenuation0   = 0.0f;	
			m_Attenuation1	 = 0.0f;	
			m_Attenuation2	 = 0.0f;	
			m_fTheta		 = 0.0f;
			m_fPhi			 = 0.0f;			
		}
	};


	/*
	*	An abstracted light interface
	*/
	class ILight : public CAsset< ILight >
	{
	public:
		
		virtual ~ILight(void){}

		/*
		*	Sets a light at the given index on the renderer
		*/
		virtual bool Apply( const uint32 _kuIndex ) = 0;
		/*
		*	Enables the light source, also updates the light with its description
		*/
		virtual void Enable( ) = 0;
		/*
		*	Unenables the lights source
		*/
		virtual void UnEnable( ) = 0;
		/*
		*	Return : The lights attrubutes
		*/
		virtual CLighDecription& GetLightsDecsription( ) = 0;

	};
}// end namespace

#endif //_LIGHT_H__Included_38277623

