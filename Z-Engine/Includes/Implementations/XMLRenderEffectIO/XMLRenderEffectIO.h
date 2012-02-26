/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Implementations\XMLRenderEffectIO\XMLRenderEffectIO.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _XMLRENDEREFFECTIO_H__Included_220910925
#define _XMLRENDEREFFECTIO_H__Included_220910925

#include "RendererLib/RenderEffectIO.h"
namespace ZGE
{
	/**
	 * XML render effect IO implentation.
	 */
	class CXMLRenderEffectIO : public IRenderEffectIO
	{
	public:
		CXMLRenderEffectIO(void);
		~CXMLRenderEffectIO(void);

				/**
		 *	Parses render effect from file.
		 *	@param _kpcFileName The file to parse a render effect from.
		 */
		virtual bool ParseRenderEffect( const char* _kpcFileName, IRenderEffect*& _pRenderEffect );

		/**
		 *	Serializes a render effect to file.
		 *  @param _kpcFileName The name of the file to serialize the render effect to.
		 *	@param _pRenderEffect The render effect to serialize.
		 */
		virtual bool SerializeRenderEffect( const char* _kpcFileName, IRenderEffect* _pRenderEffect );

	protected:
		/**
		 * Parses a fixed funcion effect from file.
		 */
		bool ParseFixedFunctionEffect( TiXmlElement* _pEffectElement, IRenderEffect*& _pRenderEffect  );

				/**
		 * Parses a shader effect from file.
		 */
		bool ParseShaderEffect( TiXmlElement* _pEffectElement, IRenderEffect*& _pRenderEffect  );
	};
}

#endif //_XMLRENDEREFFECTIO_H__Included_220910925

