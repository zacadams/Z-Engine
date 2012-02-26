/**
 *	@file Z-Engine\Z-Engine\Interfaces\MathLib\FMat4x4.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _FMAT4X4_H__Included_1312119448
#define _FMAT4X4_H__Included_1312119448

#include "CoreLib/MemoryAlignment.h"
#include "MathLib/FVec3.h"



namespace ZGE
{
	class CFMat4x4;
		// these types are used to pass by value, on some platforms
	// passing by reference would be preferred, hence these
	// defines will be different...
	typedef const class CFVec3& CFVec3Arg;
	typedef const class CFVec4& CFVec4Arg;

	struct SFMat4x4
	{
		float32	m_fVal[4][4];
		operator const CFMat4x4 (void) const;
	};

// Windows Math library implementation.
	_ALIGNED_PREFIX( 16 )
	class CFMat4x4 : public TAligned<16>
	{
	public:

		typedef const CFMat4x4& CFMat4x4Ref;

		CFMat4x4(void);
		~CFMat4x4(void);

	// Overloaded constructors 

		CFMat4x4( CFMat4x4Ref _kr );
		CFMat4x4( float32 _00, float32 _01, float32 _02, float32 _03, 
				  float32 _10, float32 _11, float32 _12, float32 _13, 
				  float32 _20, float32 _21, float32 _22, float32 _23, 
				  float32 _30, float32 _31, float32 _32, float32 _33 ); 

	// Overloaded operators

		void	 operator=  ( CFMat4x4Ref _kr );
		CFMat4x4 operator*  ( CFMat4x4Ref _kr ) const;
		void	 operator*= ( CFMat4x4Ref _kr );

	// Static functions

		static void CreateTranslationMatrix( const CFVec3& _kvTranslation, CFMat4x4& _rOut );
		static void CreateRotationMatrix ( const CFVec3& _kvRotation, CFMat4x4& _rOut );
		static void CreateRotationMatrixX( const float32 _fkRads, CFMat4x4& _rOut );
		static void CreateRotationMatrixY( const float32 _fkRads, CFMat4x4& _rOut );
		static void CreateRotationMatrixZ( const float32 _kfRads, CFMat4x4& _rOut );
		static void CreateScaleMatrix( const CFVec3& _krScale, CFMat4x4& _rOut );

		static void CreatePersepectiveProjectionMatrix( const float32 _kfFOV,
												const float32& _kfAspectRatio,
												const float32& _kfNear,
												const float32& _kfFar, CFMat4x4& _rOut );

		static void CreateOffSetOrthoProjectionMatrix( const float32 _kfLeft, const float32 _kfRight, const float32 _kfTop, const float32 _kfBottom, const float32 _kfNear, const float32 _kfFar, CFMat4x4& _rOut ); 
		static void CreateOrthographicProjectionMatrix( const float32 _kfWidth, const float32 _kfHeight, const float32 _kfNear, const float32 _kfFar, CFMat4x4& _rOut ); 
	// Creates view matrix
		static void CreateLookAtMatrix( const CFVec3& _krEye, const CFVec3& _krUp, const CFVec3& _krTarget, CFMat4x4& _rOut );
		static void CreateLookToMatrix( const CFVec3& _krEye, const CFVec3& _krUp, const CFVec3& _krLook, CFMat4x4& _rOut );


		void Inverse( );
		void Transpose( );
		void Identity( );
		void LHToRHProjection( );

		// Vector operations.
		void TransformVec3( CFVec3& _rv, CFVec3& _rOut )  const;
		void Decompose( CFVec3& _rvTranslation, CFVec3& _rvScale, CFVec3& _rvOrientation );

		static void  ReverseProject( const CFVec3& _krvScreenPos,
									const float32 _kfDisplayWidth,
									const float32 _kfDisplayHeight,
									const CFMat4x4& _krmWorld,
									const CFMat4x4& _krmView,
									const CFMat4x4& _krmProjection,
									const float32   _kfNear,
									const float32   _kfFar,
									CFVec3& _rmWorldPosition );

	protected:

		SFMat4x4 m_mVals;

	};
}

#endif //_FMAT4X4_H__Included_1312119448

