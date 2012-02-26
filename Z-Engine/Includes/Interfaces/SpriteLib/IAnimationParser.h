/**
 *	@file Z-Engine\Z-Engine\Interfaces\SpriteLib\IAnimationParser.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _IANIMATIONPARSER_H__Included_594364395
#define _IANIMATIONPARSER_H__Included_594364395

namespace ZGE
{	
	/**
	 * Interface for animation parsers.
	 */
	class IAnimationParser
	{
	public:
		IAnimationParser(void);
		~IAnimationParser(void);

		/**
		 * Sets the file to read animation data from.
		 */
		void ParseFile( const char* _kpcFile ) { }
		/**
		 * Parses an animation from a file.
		 * @param _AssetId The name of the animation tp parse.
		 * @param _pAnimationSequence The animation sequence to populate.
		 * @return Success.
		 */
		bool ParseAnimation( CAssetId& _rAssetId, CAnimationSequence*& _pAnimationSequence ) = 0;
	protected:
		char8 m_pcFileName[256]; //!< The target file.
	};
}

#endif //_IANIMATIONPARSER_H__Included_594364395

