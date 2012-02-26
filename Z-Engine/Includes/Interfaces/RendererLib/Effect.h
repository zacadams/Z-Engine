/**
 *	@file Z-Engine\Z-Engine\Interfaces\RendererLib\Effect.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _EFFECT_H__Included_1995631595
#define _EFFECT_H__Included_1995631595


#include "CoreLib/Asset.h"

namespace ZGE
{
	class CMesh;
	class IRendererInterface;

	/*
	* Renders meshes to achive effects.
	* Effects can be both fixed function and shader driven 
	*/
	class IEffect : public CAsset< IEffect >
	{
	public:
		
		virtual ~IEffect(void) {} 

	// Set methods
		/*
		*	Sets the active technique on shader
		*/
		virtual bool SetTechnique( const char8* _kpcTechnique ) = 0;

		/*
		*	Sets data onto a shader using a memory and size
		*	Param _kpcId  : The value to set the data on
		*	Param _pData  : The data to set
		*	Param _kuSize : The size of the  data 
		*/
		virtual bool SetValue( const char8* _kpcId, void* _pData, const uint32 _kuSize ) = 0;

	// Render techniques

		/*
		*	Beginsan effect
		*	Param _ruPassCount : The number of passes in the active technique
		*/
		virtual bool BeginEffect( uint32& _ruPassCount ) = 0; 

		/*
		*	Begins a pass on the effects active technique
		*	Param _kuPass : The effect to use
		*/
		virtual bool BeginPass( const uint32& _kuPass ) = 0;

		/*
		*	Ends a technique pass
		*/
		virtual bool EndPass( ) = 0;

		/*
		*	Ends a technique
		*/
		virtual bool EndTechnique( ) = 0;

		/*
		* Renders a mesh using an effect
		* Param _pMesh : The mesh to render
		* Param _pRenderer : The renderer 
		*/
		//virtual void DrawMesh( CMesh* _pMesh, IRendererInterface* _pRenderer ) = 0;

	};
}// end namespace 

#endif //_EFFECT_H__Included_1995631595

