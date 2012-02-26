#ifndef __ANIMATION_TREE__
#define __ANIMATION_TREE__

class CSkeleton;
/**
 *	Defines and contains a objects complete animation bhaviours.
 */
class CAnimationTree
{
public:	
	CSkeleton*			GetSkeletalResult( void );
	void				Update( );
protected:
	CSkeleton* m_pSkeletalResult;	// The root.
};

#endif // __ANIMATION_TREE__