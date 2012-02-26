/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\SpriteLib\ISpriteParser.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _ISPRITEPARSER_H__Included_1038128469
#define _ISPRITEPARSER_H__Included_1038128469

namespace ZGE
{
	class CSprite;
	class ITextureManager;
	class ISpriteParser
	{
	public:

		/**
		 *	Initilaises the sprite parser.
		 *	@param _pTextureManager Used to create textures.
		 */
		inline void Initialise( ITextureManager* _pTextureManager )
		{
			m_pTextureManager = _pTextureManager;
		}


		/**
		 *	This function parses a sprite from the specified file.
		 *	@param _kpcFileName.
		 *	@param _pSprite To be populated with the sprite data.
		 *	@return Success.
		 */
		virtual bool ParseSprite( const char* _kpcFileName, CSprite*& _pSprite ) = 0;
	protected:
		ITextureManager* m_pTextureManager;
	};
}

#endif //_ISPRITEPARSER_H__Included_1038128469

