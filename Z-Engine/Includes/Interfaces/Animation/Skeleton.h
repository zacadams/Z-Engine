
#ifndef __SKELETON_H__
#define __SKELETON_H__

class CBone;

/**
 * Representa an objects skeleton.
 */
class CSkeleton : public CActor
{
public:
	CSkeleton( );
	virtual ~CSkeleton( );

	/**
	 *	Initialises the skeleton.
	 *	@param pBones		: The bones the skeleton will contain.
	 *	@param kuBoneCount	: The number of bones contained by the skeleton. 
	 */
	void	Initialise( CBone* pBones, const uint32 kuBoneCount );
	
	/**
	 *	Returns the target bone.
	 *	@param kuBone : The bones index into the tree.
	 *	@return CBone, NULL if the index does not exist.
	 */
	CBone*	GetBone( const uint32 kuBoneIndex );
	
	/**
	 *	Returns the target bone.
	 *	@param kpcBoneName : The name of the wanted bone.
	 *	@return CBone* , NULL if the bone does note exist.
	 */
	CBone*	GetBoneByName( const char* kpcBoneName );
	
	/**
	 *	Manipulates the skeleton into the target pose.
	 *	@param kpPose : The pose to form.
	 */
	void	FormPose( const CSkeletalAnimationPose* kpPose );

protected:
	CBone* m_pBones;	//!< This is a explicit three in the form of an array. This makes skeletal iteration quicker.
	uint32 m_uBoneCount;//!< The number of bones contained in this skeleton.
};

#endif // __SKELETON_H__