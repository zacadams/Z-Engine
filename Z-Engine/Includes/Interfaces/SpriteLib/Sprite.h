/**
 *	@file Z-Engine\Z-Engine\Interfaces\SpriteLib\Sprite.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _SPRITE_H__Included_661880917
#define _SPRITE_H__Included_661880917

#include "CoreLib/TypeDefines.h"
#include "CoreLib/Asset.h"
#include "RendererLib/Vertex.h"
#include "RendererLib/RenderSource.h"
namespace ZGE
{
	class ITexture;
	class CFVec3;
	class CFVec2;
	class IRendererInterface;
	class IVertexDeclaration;

	/*
	* A sprite, a static 2d image
	*/
	class CSprite : public CAsset< CSprite >/*, public IRenderSource*/
	{
	public:
		CSprite(void);
		~CSprite(void);

		/*
		* Initialises a sprite.
		* @param _pTexture : The textures for the sprite to use.
		* @param _krsRect  : The rect of the texture to render. 
		* @param _kbLighting : Determins if the sprite will be lit using per pixel normal map lighting.
		*/
		bool Initialise( ITexture** _ppTextures, const SFRect& _krsRect, const bool _kbLighting = false);

		/*
		* Renders the sprite at location.
		* @param _krmPosition : The position to render the sprite.
		*/
		void Draw( const CFVec3& _krvPosition, const uint32 _kuColour = 0xFFFFFFFF );

		/*
		* Renders a scaled and orientated sprite.
		* @param _krmPosition : The position to render the sprite.
		* @param _krmScale : The scale of the sprite.
		* @param _kfRotation : The orientation of the sptite( rotation around the z axis )
		*/
		void DrawEx( const CFVec3& _krvPosition, const CFVec2& _krvScale, const float32 _kfOrientation, const uint32 _kuColour = 0xFFFFFFFF );

		/*
		* Returns the sprites texture rect
		*/
		SFRect& GetTextureRect( );
		/*
		* Returns the sprites texture rect
		*/
		const SFRect& GetTextureRect( ) const;
		
		/*
		* Sets the sprites texture rect
		* Param _krsTextureRect : The texture rect to set
		*/
		void SetTextureRect( const SFRect& _krsTextureRect );

		/*
		* Returns the sprites texture
		*/
		ITexture* GetTexture(  const uint32 _kuTexture = 0 );

		// Retruns the sprites quad vertices.
		inline IVertex* GetQuad( ){ return m_pQuad; }

		// Returns the sprites texture count.
		inline uint32 GetTextureCount( ) const {return m_uTextureCount; }

		/**
		 * Transforms the sprite vertices.
		 * @param _krmPosition : The position to render the sprite.
		 */
		IVertex* Transform( const CFVec3& _krvPosition );

		/**
		 * Transforms the sprite vertices.
		 * @param _krmPosition : The position to render the sprite.
		 * @param _krmScale : The scale of the sprite.
		 * @param _kfRotation : The orientation of the sptite( rotation around the z axis )
		 */
		IVertex* TransformEx( const CFVec3& _krvPosition, const CFVec2& _krvScale, const float32 _kfOrientation );

		// Checks if the sprite is being lit.
		inline bool IsLit( ) const { return m_bLighting; }

		// Gets the sprites vertex declaration.
		inline IVertexDeclaration* GetVertexDeclaration( ) const { return m_pVertexDeclaration; }

	protected:

		ITexture**		m_ppTextures;		//!< The sprites texture sources.
		uint32          m_uTextureCount;	//!< The sprites texture count;
		SFRect			m_sTextureRect;		//!< The rect( square of the texture ) the sprite will render.
		IVertex*		m_pQuad;			//!< The sprites quad.
		IVertexDeclaration* m_pVertexDeclaration;
		bool			m_bLighting;		//!< Determins if the sprite is going to use normal map lighting.
	};
}

#endif //_SPRITE_H__Included_661880917

