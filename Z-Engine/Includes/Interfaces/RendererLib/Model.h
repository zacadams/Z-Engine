#ifndef __MODEL_H__
#define __MODEL_H__

/**
 *	Visual representation of a character / object.
 *	Notes: The models skeleton has to be updated with the models animations before it is rendered.
 *		   This is because the animations deform the models meshes.
 */
class CModel 
{
public:
		CAnimationTree* GetAnimationTree( void );
		CRenderTree*	GetRenderTree( void );
		CSkeleton*		GetSkeleton( void );
protected:

	CSkeleton*		m_pSkeleton;		//!< The models skeleton.			// Skeleton is a scene graph.
	CAnimationTree* m_pAnimationTree;	//!< The models animation tree. Determins how animations are used.
										//	This is also a scene graph.
	CRenderTree*	m_pRenderTree;		//!< The models render tree.
};

// Note: Create a spacial actot class and give it the spacaial attributes.
//		 Leave the actor as the tree controller.
//		 Or create a tree node which has the tree relationships and functionality and create an actor.
//		 The scenes can just have actors.
//
//class CRenderNode : public CTreeNode<type>
//{
//public:
//		render node specific functions.
//protected:
//};

#endif // __MODEL_H__