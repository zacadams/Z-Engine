/**
 *	@file Z-Engine\Z-Engine\Interfaces\MathLib\FMat4x4.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes
#include "CoreLib/Core.h"

#include "MathLib/FVec3.h"

// Library includes
#define iOS
#ifndef iOS
#include <windows.h>
#include <xnamath.h> 
#endif


// Local includes 

#include "MathLib/FMat4x4.h"

using namespace ZGE;

#ifndef iOS
#ifdef WIN32

CFMat4x4::CFMat4x4(void)
{
	//Identity( );
}

CFMat4x4::~CFMat4x4(void)
{
}
#ifdef WIN32
/*
*
*/
CFMat4x4::CFMat4x4( CFMat4x4Ref _kr )
{
	XMMATRIX& mMe = *reinterpret_cast< XMMATRIX* >( this );
	const XMMATRIX& mOther = *reinterpret_cast< const XMMATRIX* >( &_kr );

	mMe = mOther;

}
/*
*
*/
CFMat4x4::CFMat4x4( float32 _00, float32 _01, float32 _02, float32 _03, 
				    float32 _10, float32 _11, float32 _12, float32 _13, 
					float32 _20, float32 _21, float32 _22, float32 _23, 
					float32 _30, float32 _31, float32 _32, float32 _33 )
{
	XMMATRIX& mMe = *reinterpret_cast< XMMATRIX* >( this );

	mMe = XMMatrixSet(  _00, _01, _02, _03,	
				  _10, _11, _12, _13,
				  _20, _21, _22, _23,
				  _30, _31, _32, _33 ); 

}
/*
*
*/
CFMat4x4 CFMat4x4::operator=  ( CFMat4x4Ref _kr )
{
	XMMATRIX& mMe = *reinterpret_cast< XMMATRIX* >( this );
	const XMMATRIX& mOther = *reinterpret_cast< const XMMATRIX* >( &_kr );

	mMe = mOther;
	return *this;

}
/*
*
*/
CFMat4x4 CFMat4x4::operator*  ( CFMat4x4Ref _kr ) const
{
	const XMMATRIX& mMe = *reinterpret_cast< const XMMATRIX* >( this );
	const XMMATRIX& mOther = *reinterpret_cast < const XMMATRIX* >( &_kr ); 

	CFMat4x4 mReturn;
	XMMATRIX& mTarget = *reinterpret_cast< XMMATRIX* >( &mReturn );

	mTarget = mMe * mOther;
	return mReturn;

}
CFMat4x4 CFMat4x4::operator*= ( CFMat4x4Ref _kr )
{
	 XMMATRIX& mMe = *reinterpret_cast< XMMATRIX* >( this );
	const XMMATRIX& mOther = *reinterpret_cast<  const XMMATRIX* >( &_kr ); 

	mMe *= mOther;

	return *this;
}
/*
*
*/
CFMat4x4 CFMat4x4::CreateTranslationMatrix( const CFVec3& _kvTranslation )
{
	CFMat4x4 mReturn;
	XMMATRIX& mTarget = *reinterpret_cast<XMMATRIX* >( &mReturn );
	const XMVECTOR& vSource = *reinterpret_cast< const XMVECTOR* >( &_kvTranslation ); 

	mTarget = XMMatrixTranslationFromVector( vSource);
	return mReturn;
}
/*
*
*/
CFMat4x4 CFMat4x4::CreateRotationMatrix ( const CFVec3& _kvRotation )
{
	CFMat4x4 mReturn;
	XMMATRIX& mTarget = *reinterpret_cast<XMMATRIX* >( &mReturn );
	const XMVECTOR& vSource = *reinterpret_cast< const XMVECTOR* >( &_kvRotation ); 

	mTarget = XMMatrixRotationRollPitchYawFromVector( vSource );
	return mReturn;
}
/*
*
*/
CFMat4x4 CFMat4x4::CreateRotationMatrixX( const float32 _fkRads )
{
	CFMat4x4 mReturn;
	XMMATRIX& mTarget = *reinterpret_cast< XMMATRIX* >( &mReturn );

	mTarget = XMMatrixRotationX( _fkRads );

	return mReturn;
}
/*
*
*/
CFMat4x4 CFMat4x4::CreateRotationMatrixY( const float32 _fkRads )
{
	CFMat4x4 mReturn;
	XMMATRIX& mTarget = *reinterpret_cast< XMMATRIX* >( &mReturn );

	mTarget = XMMatrixRotationY( _fkRads );

	return mReturn;
}
/*
*
*/
CFMat4x4 CFMat4x4::CreateRotationMatrixZ( const float32 _kfRads )
{
	CFMat4x4 mReturn;
	XMMATRIX& mTarget = *reinterpret_cast< XMMATRIX* >( &mReturn );
	mTarget = XMMatrixRotationZ( _kfRads );
	return mReturn;
}
/*
*
*/
CFMat4x4 CFMat4x4::CreateScaleMatrix( const CFVec3& _krScale )
{
	CFMat4x4 mReturn;
	XMMATRIX& mTarget = *reinterpret_cast< XMMATRIX* >( &mReturn );
	const XMVECTOR& vSource = *reinterpret_cast< const XMVECTOR* >( &_krScale ); 

	mTarget = XMMatrixScalingFromVector( vSource );
	return mReturn;
}

/*
*
*/
CFMat4x4 CFMat4x4::CreateProjectionMatrix( const float32 _kfFOV, const float32& _kfAspectRatio, const float32& _kfNear, const float32& _kfFar )
{
	CFMat4x4 mReturn;
	XMMATRIX& mTarget = *reinterpret_cast< XMMATRIX* >( &mReturn );

	mTarget = XMMatrixPerspectiveFovLH( _kfFOV, _kfAspectRatio, _kfNear, _kfFar );

	return mReturn;
}

//CFMat4x4 CFMat4x4::CreateOffSetProjectionMatrix(	const float32 _kfLeft,
//													const float32 _kfRight,
//													const float32 _kfTop,
//													const float32 _kfBottom,
//													const float32 _kfNear,
//													const float32 _kfFar )
//{
//	
//	CFMat4x4 mReturn;
//	XMMATRIX& m = *reinterpret_cast< XMMATRIX* >( &mReturn );
//	m = XMMatrixOrthographicOffCenterLH( _kfLeft, _kfRight, _kfBottom, _kfTop, _kfNear, _kfFar );
//	return mReturn;
//}

CFMat4x4 CFMat4x4::CreateOffSetOrthoProjectionMatrix( const float32 _kfLeft, const float32 _kfRight, const float32 _kfTop, const float32 _kfBottom, const float32 _kfNear, const float32 _kfFar )
{
	CFMat4x4 mReturn;
	XMMATRIX& mTarget = *reinterpret_cast< XMMATRIX* >( &mReturn );

	mTarget = XMMatrixOrthographicOffCenterLH( _kfLeft, _kfRight, _kfBottom, _kfTop, _kfNear, _kfFar );
	return mReturn;
}

CFMat4x4 CFMat4x4::CreateOrthographicProjectionMatrix( const float32 _kfWidth, const float32 _kfHeight, const float32 _kfNear, const float32 _kfFar )
{
	CFMat4x4 mReturn;
	XMMATRIX& mTarget = *reinterpret_cast< XMMATRIX* >( &mReturn );

	mTarget = XMMatrixOrthographicLH( _kfWidth, _kfHeight, _kfNear, _kfFar );
	return mReturn;
}

/*
*
*/
CFMat4x4 CFMat4x4::CreateLookAtMatrix( const CFVec3& _krEye, const CFVec3& _krUp, const CFVec3& _krTarget )
{
	CFMat4x4 mReturn;
	XMMATRIX& mTarget = *reinterpret_cast< XMMATRIX* >( &mReturn );

	mTarget = XMMatrixLookAtLH( *reinterpret_cast< const XMVECTOR* >( &_krEye ),
								*reinterpret_cast< const XMVECTOR* >( &_krTarget ),
								*reinterpret_cast< const XMVECTOR* >( &_krUp ) );

	return mReturn;
}
/*
*
*/
CFMat4x4 CFMat4x4::CreateLookToMatrix( const CFVec3& _krEye, const CFVec3& _krUp, const CFVec3& _krLook )
{
	CFMat4x4 mReturn;
	XMMATRIX& mTarget = *reinterpret_cast< XMMATRIX* >( &mReturn );

	mTarget = XMMatrixLookToLH( *reinterpret_cast< const XMVECTOR* >( &_krEye ),
								*reinterpret_cast< const XMVECTOR* >( &_krLook ),
								*reinterpret_cast< const XMVECTOR* >( &_krUp ) );

	return mReturn;
}
/*
*
*/
void CFMat4x4::Inverse( )
{
	XMMATRIX& mMe = *reinterpret_cast< XMMATRIX* >( this );
	
	XMVECTOR vDeterminant = XMMatrixDeterminant( mMe );
	
	mMe = XMMatrixInverse( &vDeterminant, mMe );
}
/*
*
*/
void CFMat4x4::Transpose( )
{
	XMMATRIX& mMe = *reinterpret_cast< XMMATRIX* >( this );	
	mMe = XMMatrixTranspose( mMe );
}
void CFMat4x4::Identity( )
{
	XMMATRIX& mMe = *reinterpret_cast< XMMATRIX* >( this );
	mMe = XMMatrixIdentity( );
}

void CFMat4x4::LHToRHProjection( )
{
//	mTempMatrix.Set( 2, 3, -1.0f );
//	mTempMatrix.Set( 3, 2, mTempMatrix.Get(3,2) * -1.0f );
	//m_mVals._23 = -1.0f ;
	//m_mVals._32 = ( m_mVals._32 * -1.0f );

}

CFVec3 CFMat4x4::TransformVec3( CFVec3& _rv ) const
{
	const XMMATRIX& mMe = *reinterpret_cast< const XMMATRIX* >( this );
	XMVECTOR& v   = *reinterpret_cast< XMVECTOR* >( &_rv );

	CFVec3 vReturn( 0.0f, 0.0f,0.0f );
	XMVECTOR& xvReturn = *reinterpret_cast< XMVECTOR* >( &vReturn );

	xvReturn =  XMVector3Transform( v, mMe );
	return vReturn;
}

void CFMat4x4::Decompose( CFVec3& _rvTranslation, CFVec3& _rvScale, CFVec3& _rvOrientation )
{
	XMMATRIX& mMe		   = *reinterpret_cast< XMMATRIX* >( this );
	XMVECTOR& vTranslation = *reinterpret_cast< XMVECTOR* >( &_rvTranslation );
	XMVECTOR& vScale	   = *reinterpret_cast< XMVECTOR* >( &_rvScale );
	XMVECTOR& vOrientation = *reinterpret_cast< XMVECTOR* >( &_rvOrientation );
	XMMatrixDecompose( &vScale, &vOrientation, &vTranslation, mMe );
}


void CFMat4x4::ReverseProject( const CFVec3& _krvScreenPos,
							const float32 _kfDisplayWidth,
							const float32 _kfDisplayHeight,
							const CFMat4x4& _krmWorld,
							const CFMat4x4& _krmView,
							const CFMat4x4& _krmProjection,
							const float32   _kfNear,
							const float32   _kfFar,
							CFVec3& _rmWorldPosition )
 {

	 const XMMATRIX& mWorld = *reinterpret_cast< const XMMATRIX* >( &_krmWorld );
	 const XMMATRIX& mView  = *reinterpret_cast< const XMMATRIX* >( &_krmView );
	 const XMMATRIX& mProj  = *reinterpret_cast< const XMMATRIX* >( &_krmProjection );
	 XMVECTOR& vTarget = *reinterpret_cast< XMVECTOR* >( &_rmWorldPosition );
	 XMVECTOR vScreenPos =  XMVectorSet( _krvScreenPos.x( ), _krvScreenPos.y( ), 0.0f, 0.0f ) ;
	

	 vTarget = XMVector3Unproject( vScreenPos, 0.0f, 0.0f, _kfDisplayWidth, _kfDisplayHeight, _kfNear, _kfFar, mProj, mView, mWorld ); 
 }

#endif
#endif
#endif

#ifdef iOS
#include <cmath>

CFMat4x4::CFMat4x4(void)
{
	Identity( );
}

CFMat4x4::~CFMat4x4(void)
{
}

/*
*
*/
CFMat4x4::CFMat4x4( CFMat4x4Ref _kr )
{
	// TODO Test if I need to deep copy this.
	m_mVals = _kr.m_mVals;
}
/*
*
*/
CFMat4x4::CFMat4x4( float32 _00, float32 _01, float32 _02, float32 _03, 
				    float32 _10, float32 _11, float32 _12, float32 _13, 
					float32 _20, float32 _21, float32 _22, float32 _23, 
					float32 _30, float32 _31, float32 _32, float32 _33 )
{
	m_mVals.m_fVal[0][0] = _00;
	m_mVals.m_fVal[0][1] = _01;
	m_mVals.m_fVal[0][2] = _02;
	m_mVals.m_fVal[0][3] = _03;

	m_mVals.m_fVal[1][0] = _10;
	m_mVals.m_fVal[1][1] = _11;
	m_mVals.m_fVal[1][2] = _12;
	m_mVals.m_fVal[1][3] = _13;

	m_mVals.m_fVal[2][0] = _20;
	m_mVals.m_fVal[2][1] = _21;
	m_mVals.m_fVal[2][2] = _22;
	m_mVals.m_fVal[2][3] = _23;

	m_mVals.m_fVal[3][0] = _30;
	m_mVals.m_fVal[3][1] = _31;
	m_mVals.m_fVal[3][2] = _32;
	m_mVals.m_fVal[3][3] = _33;
}
/*
*
*/
void CFMat4x4::operator=  ( CFMat4x4Ref _kr )
{
	m_mVals = _kr.m_mVals;
}
/*
*
*/
CFMat4x4 CFMat4x4::operator*  ( CFMat4x4Ref _kr ) const
{
	CFMat4x4 mReturn = *this;
	mReturn *= _kr;
	return mReturn;
}
void CFMat4x4::operator*= ( CFMat4x4Ref _kr )
{
	for( uint32 uRow = 0 ; uRow < 4; ++uRow )
	{
		for( uint32 uColoumn = 0; uColoumn < 4; ++uColoumn )
		{
			m_mVals.m_fVal[uRow][uColoumn] *= _kr.m_mVals.m_fVal[uRow][uColoumn];
		}
	}
}
/*
*
*/
void CFMat4x4::CreateTranslationMatrix( const CFVec3& _krvTranslation, CFMat4x4& _rOut )
{
	_rOut.Identity();
	_rOut.m_mVals.m_fVal[3][0] = _krvTranslation.x();
	_rOut.m_mVals.m_fVal[3][1] = _krvTranslation.y();
	_rOut.m_mVals.m_fVal[3][2] = _krvTranslation.z();
}
/*
*
*/
void CFMat4x4::CreateRotationMatrix ( const CFVec3& _kvRotation, CFMat4x4& _rOut )
{
	// Create the x rotation matrix
	CFMat4x4 mRotationX;  
	CreateRotationMatrixX( _kvRotation.x( ), mRotationX );
	
	// Create the y rotation matrix
	CFMat4x4 mRotationY;
	CreateRotationMatrixX( _kvRotation.x( ), mRotationY );
	
	// Create the z rotation matrix.
	CFMat4x4 mRotationZ;
	CreateRotationMatrixX( _kvRotation.x( ), mRotationZ );
	
	_rOut =  mRotationX;
	_rOut *= mRotationY;
	_rOut *= mRotationZ;
}
/*
*
*/
void CFMat4x4::CreateRotationMatrixX( const float32 _kfRads, CFMat4x4& _rOut )
{

	// 1	0		0		0
	// 0	cos(x)	-sin(x)	0
	// 0	sin(x)	cos(x)	0
	_rOut.Identity();
	_rOut.m_mVals.m_fVal[1][1] = cosf( _kfRads );
	_rOut.m_mVals.m_fVal[1][2] = -sinf( _kfRads );
	_rOut.m_mVals.m_fVal[2][1] = sinf( _kfRads );
	_rOut.m_mVals.m_fVal[2][2] = cosf( _kfRads );
}
/*
*
*/
void CFMat4x4::CreateRotationMatrixY( const float32 _kfRads, CFMat4x4& _rOut )
{
	// cos(x)	0	-sin(x)
	// 0		1	0
	// sin(x)	0	cos(x)
	_rOut.Identity( );
	_rOut.m_mVals.m_fVal[0][0] = cosf( _kfRads );
	_rOut.m_mVals.m_fVal[0][2] = -sinf( _kfRads );
	_rOut.m_mVals.m_fVal[2][0] = sinf( _kfRads );
	_rOut.m_mVals.m_fVal[2][2] = cosf( _kfRads );
}
/*
*
*/
void CFMat4x4::CreateRotationMatrixZ( const float32 _kfRads, CFMat4x4& _rOut )
{
	// cos(x)	0	sin(x)
	// -sin(x)	0	cos(x)
	// 0		0	0
	_rOut.Identity( );
	_rOut.m_mVals.m_fVal[0][0] = cosf( _kfRads );
	_rOut.m_mVals.m_fVal[0][1] = sinf( _kfRads );
	_rOut.m_mVals.m_fVal[1][0] = -sinf( _kfRads );
	_rOut.m_mVals.m_fVal[1][1] = cosf( _kfRads );
}
/*
*
*/
void CFMat4x4::CreateScaleMatrix( const CFVec3& _krScale, CFMat4x4& _rOut )
{
	// sx	0	0
	// 0	sy	0
	// 0	0	sz
	_rOut.Identity( );
	_rOut.m_mVals.m_fVal[0][0] = _krScale.x();
	_rOut.m_mVals.m_fVal[1][1] = _krScale.y();
	_rOut.m_mVals.m_fVal[2][2] = _krScale.z();
}

/*
*
*/
void CFMat4x4::CreatePersepectiveProjectionMatrix( const float32 _kfFOV, const float32& _kfAspectRatio, const float32& _kfNear, const float32& _kfFar, CFMat4x4& _rOut )
{
	// http://msdn.microsoft.com/en-gb/library/bb205350.aspx
	//xScale     0          0               0
	//0        yScale       0               0
	//0          0       zf/(zf-zn)         1
	//0          0       -zn*zf/(zf-zn)     0
	//where:
	//yScale = cot(fovY/2)
	//xScale = yScale / aspect ratio
	float32 zn = _kfNear;
	float32 zf = _kfFar;
	float32 yScale = 1/tanf(_kfFOV/2);// cot( _kfFOV/2);
	float32 xScale = yScale / _kfAspectRatio;
	_rOut =  CFMat4x4( xScale ,		0,			0,			0,
					  0,			yScale,		0,			0,
					  0,			0,			zf/(zf-zn),	1,
					  0,			0,			-zn/(zf-zn),0 );

	//return mReturn;
}

//CFMat4x4 CFMat4x4::CreateOffSetProjectionMatrix(	const float32 _kfLeft,
//													const float32 _kfRight,
//													const float32 _kfTop,
//													const float32 _kfBottom,
//													const float32 _kfNear,
//													const float32 _kfFar )
//{
//	
//	CFMat4x4 mReturn;
//	XMMATRIX& m = *reinterpret_cast< XMMATRIX* >( &mReturn );
//	m = XMMatrixOrthographicOffCenterLH( _kfLeft, _kfRight, _kfBottom, _kfTop, _kfNear, _kfFar );
//	return mReturn;
//}

void CFMat4x4::CreateOffSetOrthoProjectionMatrix( const float32 _kfLeft, const float32 _kfRight, const float32 _kfTop, const float32 _kfBottom, const float32 _kfNear, const float32 _kfFar, CFMat4x4& _rOut )
{

}

void CFMat4x4::CreateOrthographicProjectionMatrix( const float32 _kfWidth, const float32 _kfHeight, const float32 _kfNear, const float32 _kfFar, CFMat4x4& _rOut )
{
}

/*
*
*/
void CFMat4x4::CreateLookAtMatrix( const CFVec3& _krEye, const CFVec3& _krUp, const CFVec3& _krTarget, CFMat4x4& _rOut )
{
	// http://msdn.microsoft.com/en-us/library/windows/desktop/bb205342(v=vs.85).aspx
	//zaxis = normal(At - Eye)
	//xaxis = normal(cross(Up, zaxis))
	//yaxis = cross(zaxis, xaxis)
	//    
	// xaxis.x           yaxis.x           zaxis.x          0
	// xaxis.y           yaxis.y           zaxis.y          0
	// xaxis.z           yaxis.z           zaxis.z          0
	//-dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  1

	CFVec3 zaxis = (_krTarget - _krEye).GetNormal( );
	CFVec3 xaxis = _krUp.Cross( zaxis ).GetNormal( );
	CFVec3 yaxis = zaxis.Cross(xaxis);

	 _rOut = CFMat4x4( xaxis.x(),           yaxis.x(),           zaxis.x(),           0,
					  xaxis.y(),           yaxis.y(),           zaxis.y(),           0,
					  xaxis.z(),           yaxis.z(),           zaxis.z(),           0,
					  -xaxis.Dot(_krEye),  -yaxis.Dot(_krEye),	-zaxis.Dot(_krEye),	 1);

//	return mReturn;





}
/*
*
*/
void CFMat4x4::CreateLookToMatrix( const CFVec3& _krEye, const CFVec3& _krUp, const CFVec3& _krLook, CFMat4x4& _rOut )
{

}
/*
*
*/
void CFMat4x4::Inverse( )
{
	
}
/*
*
*/
void CFMat4x4::Transpose( )
{
	
}
void CFMat4x4::Identity( )
{
	// Note this could be faster with a zero mem call. Though is there one on iOS?
	for( uint32 uRow = 0; uRow < 4; ++uRow )
	{
		for( unsigned uColoumn = 0; uColoumn < 4; ++uColoumn )
		{
			m_mVals.m_fVal[uRow][uColoumn] = 0.0f;
		}
	}
	m_mVals.m_fVal[0][0] = 1.0f;
	m_mVals.m_fVal[1][1] = 1.0f;
	m_mVals.m_fVal[2][2] = 1.0f;
}

void CFMat4x4::LHToRHProjection( )
{
//	mTempMatrix.Set( 2, 3, -1.0f );
//	mTempMatrix.Set( 3, 2, mTempMatrix.Get(3,2) * -1.0f );
	//m_mVals._23 = -1.0f ;
	//m_mVals._32 = ( m_mVals._32 * -1.0f );

}

void CFMat4x4::TransformVec3( CFVec3& _rv, CFVec3& _rOut ) const
{

}

void CFMat4x4::Decompose( CFVec3& _rvTranslation, CFVec3& _rvScale, CFVec3& _rvOrientation )
{

}


void CFMat4x4::ReverseProject( const CFVec3& _krvScreenPos,
							const float32 _kfDisplayWidth,
							const float32 _kfDisplayHeight,
							const CFMat4x4& _krmWorld,
							const CFMat4x4& _krmView,
							const CFMat4x4& _krmProjection,
							const float32   _kfNear,
							const float32   _kfFar,
							CFVec3& _rmWorldPosition )
 {

 }

#endif