/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\RendererLib\RenderAssets.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _RENDERASSETS_H__Included_1671444435
#define _RENDERASSETS_H__Included_1671444435

#include "RendererLib/RenderEffect.h"
namespace ZGE
{
	class IRenderEffect;
	/**
	 *	This class is used as a container to store a renderabl actors assets.
	 */
#ifdef Z_PLATFORM_WIN
_ALIGNED_PREFIX(16)
#endif
	class IRenderAsset
#ifdef Z_PLATFORM_WIN
		: public TAligned<16>
#endif
	{
	public:
		IRenderAsset( )
			:m_pRenderEffect( NULL )
		{
		}
		virtual ~IRenderAsset(){ SafeRelease( m_pRenderEffect ); }
		IRenderEffect* m_pRenderEffect;	//!< The effect used to render the asset.
	};
}

#endif //_RENDERASSETS_H__Included_1671444435

