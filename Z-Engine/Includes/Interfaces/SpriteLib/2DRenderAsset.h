/**
 *	@file Z-Engine\Z-Engine\Includes\Interfaces\SpriteLib\2DRenderAssets.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _2DRENDERASSETS_H__Included_326544304
#define _2DRENDERASSETS_H__Included_326544304

#include "RendererLib/RenderAsset.h"
#include "MathLib/FVec3.h"

namespace ZGE
{
	class CSprite;
	/**
	 *	Container for 2D rendered assets.
	 */
	class C2DRenderAsset : public IRenderAsset
	{
	public:
		C2DRenderAsset( );
		~C2DRenderAsset(void);
		CSprite* pSprite;
		CFVec3   vWorldPosition;	 //!< The world position to render the sprite.
		CFVec3   vScale;			 //!< The sprites scale.
		float32  fWorldOrientation; //!< The sprites world orientation.
		
	};
}

#endif //_2DRENDERASSETS_H__Included_326544304

