/**
 *	@file Z-Engine\Z-Engine\Interfaces\RendererLib\RendererTypes.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _RENDERERTYPES_H__Included_1543868015
#define _RENDERERTYPES_H__Included_1543868015

namespace ZGE
{
	/*
	*	Defines for the types of matrice transfromations
	*	Fames of references
	*/
	enum ETransforms
	{
		TM_World = 0,	//!< Denotes a world  frame of reference 
		TM_View,		//!< Denotes a camera frame of reference 
		TM_Projection,	//!< Denotes a screen frame of reference
	};


	/*
	*	Defines the render states supported 
	*/
	enum ERenderStates
	{
		RS_Lighting,	//!< Lighting ( on , off )
		RS_ZTest,		//!< Used to set the depth test parametres when testing rendered primitives
		RS_AphaBlend,	//!< Specifies alpha blend operations
		RS_CULLMODE,
		RS_FILLMODE,
		RS_Count,
	};

	// Deines for render modes
	enum EFillMode
	{
		FM_WIREFRAME = 0,	//!< Render as wire frame.
		FM_SOLID,			//!< Render normaly.
		FM_POINTS,			//!< Render as points.
		
	};

	///**
	// * Defines cull mode states 
	// */
	enum ECullMode
	{
		CM_NOCULL =0 ,  //!< Does no culling rendering all faces.
		CM_CW,		 //!< Culls all back faced triangles.
		CM_CCW,		 //!< Culls all front faced triangles. 
	};


	/*	
	*	Defines the depth test a supported 
	*/
	enum EDepthTests
	{
	};

	/*
	*	Enimeration supported render target formats
	*/
	enum ESurfaceFormat
	{
		SF_float32, // Floating point format
		SF_uARGB,
		SF_uDepth, // Depth format 
		SF_Count,
	};

	  // DX TSS
	  //D3DTSS_COLOROP                 = 1,
	  //D3DTSS_COLORARG1               = 2,
	  //D3DTSS_COLORARG2               = 3,
	  //D3DTSS_ALPHAOP                 = 4,
	  //D3DTSS_ALPHAARG1               = 5,
	  //D3DTSS_ALPHAARG2               = 6,
	  //D3DTSS_BUMPENVMAT00            = 7,
	  //D3DTSS_BUMPENVMAT01            = 8,
	  //D3DTSS_BUMPENVMAT10            = 9,
	  //D3DTSS_BUMPENVMAT11            = 10,
	  //D3DTSS_TEXCOORDINDEX           = 11,
	  //D3DTSS_BUMPENVLSCALE           = 22,
	  //D3DTSS_BUMPENVLOFFSET          = 23,
	  //D3DTSS_TEXTURETRANSFORMFLAGS   = 24,
	  //D3DTSS_COLORARG0               = 26,
	  //D3DTSS_ALPHAARG0               = 27,
	  //D3DTSS_RESULTARG               = 28,
	  //D3DTSS_CONSTANT                = 32,



	/*
	* texture stage states
	*/
	//enum ETextureStageStates
	//{
	//	TSS_ADD,
	//}
	//enum ETextureOperation
	//{

	//}

	// dot3 
	// texure factor 
	//colour args
	// texture stage states
	
}// end namespace 
#endif //_RENDERERTYPES_H__Included_1543868015

