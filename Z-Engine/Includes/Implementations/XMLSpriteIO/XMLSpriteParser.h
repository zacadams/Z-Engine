/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Implementations\XMLSpriteIO\XMLSpriteParser.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _XMLSPRITEPARSER_H__Included_1075413154
#define _XMLSPRITEPARSER_H__Included_1075413154

#include "SpriteLib/ISpriteParser.h"
class TiXmlElement;

namespace ZGE
{
	struct SFRect;
	class IVertexDeclaration;
	class ITexture;
	/**
	 *	This class parses a sprite from xml files.
	 */
	class CXMLSpriteParser : public ISpriteParser
	{
	public:
		CXMLSpriteParser(void);
		~CXMLSpriteParser(void);

		/**
		 *	This function parses a sprite from the specified file.
		 *	@param _kpcFileName.
		 *	@param _pSprite To be populated with the sprite data.
		 *	@return Success.
		 */
		virtual bool ParseSprite( const char* _kpcFileName, CSprite*& _pSprite );
	protected:
		/**
		 *	Builds the sprites vertex declaration.
		 *	@param _pVertexDeclElement	The xml documents vertex declaration element.
		 *	@return The sprites vertex declaration, NULL if there is no declaration. 
		 */
		IVertexDeclaration* ParseVertexDeclaration( TiXmlElement* _pVertexDeclElement );

		/**
		 *	Parses the sprites texture rect from file.
		 *	@param _pRectElement The elements that contains the sprites texture rect info.
		 *	@param _rsTextureRect To be populated with the texture rect info.
		 *	@return Success.
		 */
		bool ParseTextureRect( TiXmlElement* _pRectElement, SFRect& _rsTextureRect );

		/**
		 *	Parses the sprites textures.
		 *	@param _pTexturesElement The documents texture element.
		 *	@param _ppTextures To be populated with the sprites textures.
		 *	@return Success.
		 */
		bool ParseTextures(  TiXmlElement* _pTexturesElement , ITexture**& _ppTextures);


	};
}

#endif //_XMLSPRITEPARSER_H__Included_1075413154

