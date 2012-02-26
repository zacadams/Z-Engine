#ifndef __SKELETAL_ANIMATION_POSE_H__
#define __SKELETAL_ANIMATION_POSE_H__

/**
 *	Represents a skeletal pose. Otherwise known as a key frame in a skeletal animation.
 *	This is the bare bones of a skeleton.
 *	For memory conservation and speed, the pose only contains the transformation matricies of the poses bones.
 *	The transformations are in the form of an explicit tree array which directly matches to the target skeletons explicit tree array.
 */
class CSkeletalAnimationPose
{
public:
	CSkeletalAnimationPose();
	~CSkeletalAnimationPose();
	
	/**
	 * Performs a linear interpolation over time between two poses.
	 * @param kpOther			: The pose to interpolate with.
	 * @param pResult			: To be populated with the resulting pose.
	 * @param kfAnimationTime	: The interpolation time.
	 */
	void LinearInterpolateWith( const CAnimationPose* kpOther, CAnimationPose* pResult, const float kfAnimationTime ); 
protected:
	CFMat4x4* m_pBoneTransform;	

};


#endif // __SKELETAL_ANIMATION_POSE_H__