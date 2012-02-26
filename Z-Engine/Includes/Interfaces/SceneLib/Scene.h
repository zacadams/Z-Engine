/**
 *	@file Z-Engine\Z-Engine\Includes\Interfaces\SceneLib\Scene.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _SCENE_H__Included_1245132922
#define _SCENE_H__Included_1245132922

namespace ZGE
{
	class CActor;
	class CScene
	{
	public:

		CScene( );
		~CScene( );

		// Adds an actor into the scene.
		bool AddActor( CActor* _pActor, const char* _kpcParentId );

		// Removes an actor from the scene.
		bool RemoveActor( CActor* _pActor );

		// Processes the scene.
		bool UpdateScene( const float32 _kfDeltaTick );

		// Renderes the scene.
		bool DrawScene( );

		// Initialises the scene.
		bool InitilaiseScene(  );

		// Deinitialises the scene.
		bool DeinitialiseScene( );

		// Finds the target actor.
		CActor* FindActor( const char* _kpcActorId );

		// returns the scenes root node.
		inline CActor* GetRoot( ) const { return m_pRootNode; }

	protected:
		CActor*   m_pRootNode;	//!< The scenes root.
	};
}
#endif //_SCENE_H__Included_1245132922

