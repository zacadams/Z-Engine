/**
 *	@file Z-Engine\Z-Engine\Implementations\DX9RendererLib\DX9Effect.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _DX9EFFECT_H__Included_1520336364
#define _DX9EFFECT_H__Included_1520336364

#include "RendererLib/Effect.h"

struct IDirect3DDevice9;
struct ID3DXEffect;

namespace ZGE
{
	class CDX9Effect : public IEffect
	{
	public:
		CDX9Effect( IDirect3DDevice9* _pDevice, ID3DXEffect* _pEffect );
		~CDX9Effect(void);

			// Set methods
		/*
		*	Sets the active technique on shader
		*/
		virtual bool SetTechnique( const char8* _kpcTechnique );

		/*
		*	Sets data onto a shader using a memory and size
		*	Param _kpcId  : The value to set the data on
		*	Param _pData  : The data to set
		*	Param _kuSize : The size of the  data 
		*/
		virtual bool SetValue( const char8* _kpcId, void* _pData, const uint32 _kuSize );

	// Render techniques

		/*
		*	Beginsan effect
		*	Param _ruPassCount : The number of passes in the active technique
		*/
		virtual bool BeginEffect( uint32& _ruPassCount ); 

		/*
		*	Begins a pass on the effects active technique
		*	Param _kuPass : The effect to use
		*/
		virtual bool BeginPass( const uint32& _kuPass );

		/*
		*	Ends a technique pass
		*/
		virtual bool EndPass( );

		/*
		*	Ends a technique
		*/
		virtual bool EndTechnique( );

	protected:

		IDirect3DDevice9* m_pDevice;
		ID3DXEffect* m_pD3DEffect;	//!< DirectX effect instance

	};
}

#endif //_DX9EFFECT_H__Included_1520336364

