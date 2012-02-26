/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\SceneLib\SceneIO.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _SCENEIO_H__Included_1092822146
#define _SCENEIO_H__Included_1092822146

namespace ZGE
{
	class CActor;

	/** 
	 *	This is an interface for scene IO.
	 */
	class ISceneIO
	{
	public:
		/**
		 *	Parses a scene from file.
		 *	@param _kpcSceneName The scene to parse.
		 *  @param _pRootNode  The scenes root node.
		 *	@return Success.
		 */
		virtual bool ParseScene( const char* _kpcScene, CActor*& _pRootNode ) = 0;
		
		/**
		 *	Saves the scene to a file.
		 *	@param _kpcFileName The name of the file to write.
		 *  @param _pRootNode  The scenes root node.
		 *	@return Success.
		 */
		virtual bool SaveScene( const char* _kpcFileName, CActor* _pRootNode ) = 0;
	};
}

#endif //_SCENEIO_H__Included_1092822146

