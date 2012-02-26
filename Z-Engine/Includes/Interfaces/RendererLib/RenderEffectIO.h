/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\RendererLib\RenderEffectIO.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _RENDEREFFECTIO_H__Included_1571368886
#define _RENDEREFFECTIO_H__Included_1571368886

class TiXmlElement;
namespace ZGE
{
	class IRenderEffect;
	/**
	 *	Interface for render effect IO.
	 */
	class IRenderEffectIO
	{
	public:
		virtual ~IRenderEffectIO( ){ }
		/**
		 *	Parses render effect from file.
		 *	@param _kpcFileName The file to parse a render effect from.
		 */
		virtual bool ParseRenderEffect( const char* _kpcFileName, IRenderEffect*& _pRenderEffect ) = 0;

		/**
		 *	Serializes a render effect to file.
		 *  @param _kpcFileName The name of the file to serialize the render effect to.
		 *	@param _pRenderEffect The render effect to serialize.
		 */
		virtual bool SerializeRenderEffect( const char* _kpcFileName, IRenderEffect* _pRenderEffect ) = 0;
	};
}


#endif //_RENDEREFFECTIO_H__Included_1571368886

