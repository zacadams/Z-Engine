/**
 *	@file Z-Engine\Z-Engine\Implementations\GLRendererLib\GLTexture.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/

#include "CoreLib/Core.h"

#include "GLTexture.h"

using namespace ZGE;

CGLTexture::CGLTexture(void)
{
}

CGLTexture::~CGLTexture(void)
{
}
/*
*	Sets the texture on the renderer at the specified index
*/
void CGLTexture::Apply( uint32 uIndex )
{
	UNUSED_VAR( uIndex );
}

/*
*	Lockes the texels lof a texture
*/
bool CGLTexture::LockTexels( uint32* _pTextels )
{
	UNUSED_VAR( _pTextels );
	return false;
}
/*
*	Unlockes a textures texels
*/
bool CGLTexture::UnlockTexels( )
{
	return false;
}
/*
*	Targets the texture for writing
*/
bool CGLTexture::Target( const uint32 _kuIndex )
{
	UNUSED_VAR( _kuIndex );
	return false;
}

/*
* Returns the textures width
*/
uint32 CGLTexture::GetWidth( ) const
{
	return m_uWidth;
}
/*
* Returns the textures height
*/
uint32 CGLTexture::GetHeight( ) const
{
	return m_uHeight;
}


