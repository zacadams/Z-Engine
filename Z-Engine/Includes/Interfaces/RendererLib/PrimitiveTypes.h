/**
 *	@file Z-Engine\Z-Engine\Interfaces\RendererLib\PrimitiveTypes.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _PRIMITIVETYPES_H__Included_1223194050
#define _PRIMITIVETYPES_H__Included_1223194050

namespace ZGE
{
	/*
	*	An enumeration of supported rendering primitive 
	*/
	enum EPrimitiveTypes
	{
		// Triangles 
		PT_TriangleList = 0,
		PT_TriangleStrip,
		PT_TriangleFan,

		// Lines 
		PT_LineList,
		PT_LineStrip,
		PT_Points,

		// Quads
		PT_QaudList,
		PT_QuadStrip,

		// Points
		
	};                               
}
#endif //_PRIMITIVETYPES_H__Included_1223194050

