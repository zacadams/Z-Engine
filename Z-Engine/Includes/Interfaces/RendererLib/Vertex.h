/**
 *	@file Z-Engine\Z-Engine\Interfaces\RendererLib\Vertex.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _VERTEX_H__Included_273009028
#define _VERTEX_H__Included_273009028

namespace ZGE
{
	
	// Vertex format for position and colour
	struct SXyzColour
	{
		float32 fX;
		float32 fY;
		float32 fZ;
		uint32	uColour;
	};

	// Represents a coloured and textured vertex
	struct SXyzColourUV
	{
		float32 fX;
		float32 fY;
		float32 fZ;
		uint32	uColour;
		float32 fU;
		float32 fV;
	};

	// Vertex format for position, colour and normals 
	struct SXyzColourNorm
	{
		float32 fX;
		float32 fY;
		float32 fZ;
		uint32	uColour;
		float32	fNormalX;
		float32	fNormalY;
		float32	fNormalZ;
	};

	struct SXyzNorm
	{
		float32 fX;
		float32 fY;
		float32 fZ;
		float32	fNormalX;
		float32	fNormalY;
		float32	fNormalZ;
	};

	/*
	*	Basic skinned vertex
	*/
	struct SXyzColorSkin
	{
		float32 fX;
		float32 fY;
		float32 fZ;
		uint32	uColour;

		//bones

		float32 fBone0;
		float32 fBone1;

		float32 fWeight0;
		float32 fWeight1;
	};

	/**
	 *	The base class for a vertex, all vertices need a position.
	 */
	class IVertex
	{
	public:
		// members made public.
		float32		fX;	//!< The vertexes x position.
		float32		fY;	//!< The vertexes y position.
		float32		fZ;	//!< The vertexes z position. 
	};

	class CXyzColour : public IVertex
	{
	public:
		uint32		uColour;	//!< The vertex colour.
	};

	/**
	 *	Vertex declaration with UV coordinates.
	 */
	class CXyzColourUV : public CXyzColour
	{
	public:
		float32 fU;	//!< The vertexes U coordinate.
		float32	fV;	//!< The vertexes V coordinate.
	};

	/**
	 *	Vertex declaration with UV coordinates.
	 */
	class CXyzUV : public IVertex
	{
	public:
		float32 fU;	//!< The vertexes U coordinate.
		float32	fV;	//!< The vertexes V coordinate.
	};

	/**
	 *	Vertex declaration for sprite lit by normal maps.
	 */
	class CLitSpriteVertex : public CXyzColourUV
	{
	public:	
		float32 fNormalX;	//!< The sprites normal x direction.
		float32 fNormalY;	//!< The sprites normal y direction.
		float32 fNormalZ;	//!< The sprites notmal z direction.
		float32 fBiNormalX;	//!< The sprites binormal x direction.
		float32 fBiNormalY; //!< The sprites binormal y direction.
		float32 fBiNormalZ; //!< The sprites binormal z direction.
		float32 fTangentX;	//!< The sprites tangent x direction.
		float32 fTangentY;	//!< The sprites tangent y direction.
		float32 fTangentZ;	//!< The sprites tangent z direction.
	};


}
#endif //_VERTEX_H__Included_273009028

