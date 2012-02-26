/**
 *	@file Z-Engine\Z-Engine\Interfaces\SceneLib\SceneInterface.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _SCENEINTERFACE_H__Included_683690354
#define _SCENEINTERFACE_H__Included_683690354

#include "SceneLib/Scene.h"

namespace ZGE
{
	class ISceneIO;
	class CActor;
	class CScene;
	/**
	 * ZEngines scene representation.
	 */
	class CSceneInterface
	{
	public:
		CSceneInterface(void);
		~CSceneInterface(void);
	
		// Initialises the scene interface.
		bool Initialise( );

		// Creates an empty scene. 
		CScene* CreateScene( CAssetId& _rAssetId );

		 // Parses a scene from file.
		bool ParseScene( CAssetId& _rAssetId, CScene*& _pScene );

		// Saves a scene to file.
		bool SerializeScene( CAssetId& _rAssetId, CScene* _pScene );

		// Creates a registered actor.
		static CActor* CreateActor( const char* _kpcInstanciationId );
	protected:
		ISceneIO* m_pSceneIO;	//!< The scene IO interface.

	};
}// end namespace

#endif //_SCENEINTERFACE_H__Included_683690354

