/**
 *	@file Z-Engine\Z-Engine\Interfaces\RendererLib\Material.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _MATERIAL_H__Included_1718817945
#define _MATERIAL_H__Included_1718817945

#include "CoreLib/Asset.h"

namespace ZGE
{
	class IEffect;

	/*
	*	Defines a materials properties
	*/
	class CMaterialDecription
	{
	public:
		 uint32 m_uDiffuse;			//!< Materials diffuse colour
		 uint32 m_uAmbient;			//!< Materials amibient colour
		 uint32 m_uSpecular;		//!< Materials specular colour
	     uint32 m_uEmissive;		//!< Materials emissive colour
		 float32 m_fSpecularPower;	//!< Materials specular power

		 bool m_bNormalMapped;		//!< Normal mapped
		 bool m_bSpecularCMapped;	//!< Specular colour mapped
		 bool m_bSpecularPMapped;	//!< Speculat power  mapped
		 bool m_bAlphaMapped;		//!< Alpha mapped

		 IEffect* m_pEffect;		//!< The materials shader

		 /*
		 *	Initilaises the material to be zero
		 */
		 void ZeroMaterial( )
		 {
			m_uDiffuse        = 0x00000000;		
			m_uAmbient		  = 0x00000000;			
			m_uSpecular		  = 0x00000000;			
			m_uEmissive		  = 0x00000000;			
			m_fSpecularPower  = 0.0f;

			m_bNormalMapped    = false;
			m_bSpecularCMapped = false;
			m_bSpecularPMapped = false;
			m_bAlphaMapped	   = false;

			m_pEffect = NULL;
		 }
	};

	/*
	*	Interface for a meaterial
	*/
	class IMaterial : public CAsset< IMaterial >
	{
	public:

		/*
		*	Applys the material on teh renderer 
		*/
		virtual bool Apply( ) = 0;

		/*
		*	Return : The materials description
		*/
		virtual CMaterialDecription& GetDescription( ) = 0; 
	};
}

#endif //_MATERIAL_H__Included_1718817945
//
//
///**
// *	A surface represents the current visual apprance of a section of a model.
// *	pMesh			The physical form of the model section.
// *	pMaterial		The surfaces properties i.e shiny / dull - this is appart of the process that defines its look.
// *	ppTextures		The surfaces texture. Defines its look.
// *	pRenderEffect	Determins the final result. Uses all of the above to produce an output result.
// */
//class CRenderSurface : public CActor
//{
//public:
//	CMesh*			pMesh;
//	CMaterial*		pMaterial;
//	CTextures**		ppTextures;
//	IRenderEffect*  pRenderEffect;
//};
//
///**
// *	Visual representation of a character / object.
// *	Notes: The models skeleton has to be updated with the models animations before it is rendered.
// *		   This is because the animations deform the models meshes.
// */
//class CModel : public CActor
//{
//public:
//		CRenderSurface* GetRenderSurface( unsigned int kuIndex );
//		CRenderSurface* GetRenderSurfaceByName( const char* kpcName );
//		CSkeleton*		GetSkeleton( void );
//protected:
//
//	CSkeleton*		m_pSkeleton;		//!< The models skeleton.			// Skeleton is a scene graph.
//	CAnimationTree* m_pAnimationTree;	//!< The models animation tree. Determins how animations are used.
//										//	This is also a scene graph.
//	CRenderTree*	m_pRenderTree;		//!< The models render tree.
//};
//
///**
// * A tree that defines the behaviour of a characters animations.
// */
//class CAnimationTree
//{
//}
//
///**
// *	The base class for a animation result generator.
// *	Animation result generatots take multiple animations and generate a final result.
// *  * animation in -> result out.
// */
//class IAnimationResultGenerator
//{
//};
//
///**
// *	This animation result generator blends multiple animations together.
// *	It does this by interpolating between animation weights.
// */
//class CAnimationBlender
//{
//};
//
///**
// *	This animation result generator overlays one animation over another. This is used to create different body states.
// *	i.e upper body animations will overlay full body animations to enable a character to run and shoot etc.
// */
//class CAnimationLayerer
//{
//};
//
///**
// *	This is used to filter animations so as they only effect the filters targets. This is used to ensure animations only effect certain bones / vertices
// *	This enables for body states to be created. i.e making a filter that targets upper body bone generates an upper body targeted state.
// */
//class CAnimatoionTargetFilter
//{
//};
//
///**
// *	This is used to encapsulate an animation state. A state is a tangeable description of an action.
// *	i.e a state would be running, jumping, attacking etc. Each state has can have a skletal animation and a vertex animation.
// */
//class CAnimationState
//{
//};
//
///** 
// *	 This is used to group animations into collective states. i.e using a target filter with this can create a body target that can be in x defined states.
// *   Setting the traget state on the state machine will handle the transitions from animation to animation.
// */
//class CAnimationStateMachine
//{
//};
//
///**
// *	This is used to encapsulate the transition process between animations.
// */
//class CAnimationTransition
//{
//};
//
//
///**
// *	
// */
//class CSkeletalAnimationSequence
//{
//public:
//protected:
//	std::vector< CAnimationPose* > m_vecAnimation;
//};
//
//
//
//
///**
// * Representa an objects skeleton.
// */
//class CSkeleton : public CActor
//{
//public:
//protected:
//};
//
//
///**
// *	Represents a skeletal pose. Otherwise known as a key frame in a skeletal animation.
// */
//class CAnimationPose
//{
//public:
//	CAnimationPose();
//	~CAnimationPose();
//	
//	/**
//	 * Performs a linear interpolation over time between two poses.
//	 * @param kpOther			: The pose to interpolate with.
//	 * @param pResult			: To be populated with the resulting pose.
//	 * @param kfAnimationTime	: The interpolation time.
//	 */
//	void LinearInterpolateWith( const CAnimationPose* kpOther, CAnimationPose* pResult, const float kfAnimationTime ); 
//protected:
//	CBone* m_pBones;	//!< The poses use a an inplace array representation of a tree.
//						//   This is to make pose interpolation quicker by reducing tree traversion with memory jumoing between functions.
//};
//
///**
// *	Animates a meshes verticies.
// */
//class CVertexAnimation : public IAnimation
//{
//public:
//	void SetSourceMesh( CMesh* pMeshTarget );
//protected:
//	CMesh* m_pSourceMesh; //!< The source mesh 
//
//	/**
//	 *	An enumeration of the vertex elements that can be targeted.
//	 */
//	enum EVertexElementTarget
//	{
//		VET_POSITION,		//!< This animates the mesh's vertices positions.
//		VET_NORMAL,			//!< This animates the mesh's normals.
//		VET_UV_COORD,		//!< This animates the mesh's UV coordinates.
//	};
//};
//
//class IVertexTransformAnimation
//{
//public:
//	// Key frame data ? 
//};
//
///**
// *	 A vertex animation with key frames.
// */
//class CVertexFrameAnimation
//{
//public:
//protected:
//};
//
///**
// * A transform animation, for animated textures, scrolling animations etc.
// */
//class CVertexTransformAnimation
//{
//public:
//protected:
//};
//
//
///**
// * A morph vertex animation, also kmown as tweening.
// */
//class CVertexMorphAnimation
//{
//	void SetTargetMesh( CMesh* pTargetMesh );
//protected:
//	CMesh* m_pTarget;	//!< The target mesh to blend to.
//	CMesh* m_pResult;
//};
//
///**
// *	Controls playback of animations.
// */
//class IAnimationController : IAnimationResultGenerator
//{	
//public: 
//	void Update( const float fTimeDelta );
//protected:
//	float32			m_fAnimTime;		//!< The current duration the animation has been playing for.
//	unsigned int	m_fAnimationFrame;	//!< The index of the current animation frame being played.
//
//	/**
//	 *
//	 */
//	enum EAnimationPlaybackState
//	{
//		AS_PAUSED = 0,
//		AS_PLAYING_FORWARD,
//		AS_PLAYING_BACKWARDS,
//		AS_STOPED,
//	};
//
//	enum EAnimationPlaybackDetails
//	{
//		ASD_LOOPING,
//		ASD_PLAYING_ONCE,
//	};
//};
//
//
///**
// *	Controls the play back of skeletal animations.
// */
//class CSkeletalAnimationController
//{
//}
