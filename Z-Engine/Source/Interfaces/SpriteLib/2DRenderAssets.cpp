/**
 *	@file Z-Engine\Z-Engine\Source\Interfaces\SpriteLib\2DRenderAssets.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes
#include "CoreLib/Core.h"
#include "SpriteLib/Sprite.h"
// Library includes

// Local includes 
#include "SpriteLib/2DRenderAsset.h"

using namespace ZGE;
C2DRenderAsset::C2DRenderAsset(void)
: pSprite ( NULL )
{
}

C2DRenderAsset::~C2DRenderAsset(void)
{
	SafeRelease( pSprite );
}
