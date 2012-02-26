/**
 *	@file Z-Engine\Z-Engine\Interfaces\MathLib\FVec3.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _FVEC3_H__Included_21045915
#define _FVEC3_H__Included_21045915

namespace ZGE
{
	class CFVec3;

	struct SFVec3
	{
		float32 fX;
		float32 fY;
		float32 fZ;
			// cast to a CFVec3
	operator const CFVec3 (void) const;
	};


// Windows vector3 implementation.

	_ALIGNED_PREFIX(16)
	class CFVec3
	{
	public:

		typedef const CFVec3& CFVec3ref;

		CFVec3(void);
		~CFVec3(void);
	// Overloaded contructors

		CFVec3( float32 _fX, float32 _fY, float32 _fZ );
		CFVec3( CFVec3ref _kr );

	// Overloaded operators
		CFVec3 operator=  ( CFVec3ref _kr );
		bool   operator== ( CFVec3ref _kr );
		CFVec3 operator+  ( CFVec3ref _kr ) const;
		CFVec3 operator-  ( CFVec3ref _kr ) const;
		CFVec3 operator*  ( CFVec3ref _kr ) const;
		void   operator+= ( CFVec3ref _kr );
		void   operator-= ( CFVec3ref _kr );
		void   operator*= ( CFVec3ref _kr );
		CFVec3 operator*  ( const float32 _kf ) const;

	// Static functions
		float32 Distance  ( CFVec3ref _kr ) const;
		float32 SqDistance( CFVec3ref _kr ) const;

		float32 Magnitude  ( ) const;
		float32 SqMagnitude( ) const;

	// Products
		float32    Dot  ( CFVec3ref ) const;
		CFVec3 Cross( CFVec3ref ) const;

	// 
		void   Normalise( );
		void   Normalise( float32& _rfMag );
		CFVec3 GetNormal( ) const;
		CFVec3 GetNormal( float32& _rfMag ) const;

	//	
		void RotateX( const float32 _kfRad );
		void RotateY( const float32 _kfRad );
		void RotateZ( const float32 _kfRad );

		float32  GetPitch( ) const;
		float32  GetElevation( ) const;
		float32  GetRoll( ) const;

		float32 x( );
		float32 y( );
		float32 z( );

		float32 x( ) const;
		float32 y( ) const;
		float32 z( ) const;

		void x( float32 _f );
		void y( float32 _f );
		void z( float32 _f );

	protected:

		SFVec3 m_vVals;
	};
}

#endif //_FVEC3_H__Included_21045915

