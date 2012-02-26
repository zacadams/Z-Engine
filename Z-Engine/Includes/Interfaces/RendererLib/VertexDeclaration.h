/**
 *	@file Z-Engine\Z-Engine\Interfaces\RendererLib\VertexDeclaration.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _VERTEXDECLARATION_H__Included_2059913345
#define _VERTEXDECLARATION_H__Included_2059913345

#include "CoreLib/Asset.h"

// defines a vertex structure for rendering

namespace ZGE
{
	class CVertexDescription;

	class IVertexDeclaration : public CAsset< IVertexDeclaration >
	{
	public:
		
		virtual ~IVertexDeclaration(void) {}

		/*
		*	Applys the vertex declararion on tp the renderer
		*/
		virtual bool Apply( ) = 0;

		/*
		*	Accessor to the vertex declaration description
		*/
		virtual CVertexDescription& GetDescription( ) = 0;

	protected:
		
		
	};
}// end namespace 

#endif //_VERTEXDECLARATION_H__Included_2059913345

