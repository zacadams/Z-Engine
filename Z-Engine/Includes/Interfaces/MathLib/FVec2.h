/**
 *	@file Z-Engine\Z-Engine\Interfaces\MathLib\FVec2.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _FVEC2_H__Included_1905374051
#define _FVEC2_H__Included_1905374051

namespace ZGE
{

	_ALIGNED_PREFIX(16)
	struct SFVec2
	{
		float32 fX;
		float32 fY;
		float32 fPad[2];
	};

	_ALIGNED_PREFIX(16)
	class CFVec2
	{
	public:

		typedef const CFVec2& CFVec2ref;

		CFVec2(void);
		~CFVec2(void);
	// Overloaded contructors

		CFVec2( float32 _fX, float32 _fY );
		CFVec2( CFVec2ref _kr );

	// Overloaded operators
		CFVec2 operator=  ( CFVec2ref _kr );
		bool   operator== ( CFVec2ref _kr );
		CFVec2 operator+  ( CFVec2ref _kr ) const;
		CFVec2 operator-  ( CFVec2ref _kr ) const;
		CFVec2 operator*  ( CFVec2ref _kr ) const;
		void   operator+= ( CFVec2ref _kr );
		void   operator-= ( CFVec2ref _kr );
		void   operator*= ( CFVec2ref _kr );

	// Static functions
		float32 Distance  ( CFVec2ref _kr ) const;
		float32 SqDistance( CFVec2ref _kr ) const;

		float32 Magnitude  ( )const ;
		float32 SqMagnitude( ) const;

	// Products
		float32    Dot  ( CFVec2ref _kr) const;
		CFVec2 Cross( CFVec2ref _kr ) const;

	// 
		void   Normalise( );
		void   Normalise( float32& _rfMag );
		CFVec2 GetNormal( ) const;
		CFVec2 GetNormal( float32& _rfMag ) const;

	//	
		void RotateX( const float32 _kfRad );
		void RotateY( const float32 _kfRad );

		float32 x( );
		float32 y( );

		float32 x( ) const;
		float32 y( ) const;

		void x( float32 _f );
		void y( float32 _f );

	protected:

		SFVec2 m_vVals;
	};
}
#endif //_FVEC2_H__Included_1905374051

