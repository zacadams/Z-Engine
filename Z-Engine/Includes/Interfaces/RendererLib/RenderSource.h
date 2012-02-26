/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\RendererLib\RenderSource.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _RENDERSOURCE_H__Included_1163346275
#define _RENDERSOURCE_H__Included_1163346275

namespace ZGE
{
	enum ERenderSourceId
	{
		RS_SPRITE = 0, //!< Sprite render source id.
		RS_MODEL,	   //!< Model render source id.
	};

	class IRenderSource
	{
	public:
		virtual ~IRenderSource( ){ }

		// Gets the render sources id.
		ERenderSourceId GetSourceId( ) const { return m_eRenderSourceId; }
	protected:
		ERenderSourceId m_eRenderSourceId;	//!< The render sources runtime id.
	};
}

#endif //_RENDERSOURCE_H__Included_1163346275

