/**
 *	@file Z-Engine\Z-Engine\Interfaces\MathLib\FVec3.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes
#include "CoreLib/Core.h"

#define iOS
#ifndef iOS
// Library includes
#include <windows.h>
#include <xnamath.h>
#endif
// Local includes 

#include "MathLib/FMat4x4.h"

#include "MathLib/FVec3.h"

using namespace ZGE;



#ifndef iOS
#ifdef WIN32

CFVec3::CFVec3(void)
{
	//XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >( this );
	//vMe = XMVectorSet( 0.0f, 0.0f, 0.0f, 1.0f );

}
/*
*
*/
CFVec3::~CFVec3(void)
{
}
/*
*
*/
CFVec3::CFVec3( float32 _fX, float32 _fY, float32 _fZ )
{
	XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >( this );
	vMe = XMVectorSet( _fX, _fY, _fZ, 1.0f );
}
/*
*
*/
CFVec3::CFVec3( CFVec3ref _kr )
{
	m_vVals = _kr.m_vVals;
	//XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >( this );
	//const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );

	//vMe = vOther;
}
/*
*
*/
CFVec3 CFVec3::operator=  ( CFVec3ref _kr )
{
	//XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >( this );
	//const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );

	//vMe = vOther;

	m_vVals = _kr.m_vVals;

	return *this;
}
/*
*
*/
bool CFVec3::operator== ( CFVec3ref _kr )
{
	XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >( this );
	const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );

	BOOL bEq = XMVector3Equal( vMe, vOther );

	return bEq ? true : false;

}
/*
*
*/
CFVec3 CFVec3::operator+  ( CFVec3ref _kr ) const
{
	CFVec3 vReturn;
	XMVECTOR& vTarget = *reinterpret_cast< XMVECTOR* >( &vReturn );

	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >( this );
	const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );

	vTarget = vMe + vOther;
	return vReturn;

}
/*
*
*/
CFVec3 CFVec3::operator-  ( CFVec3ref _kr ) const
{
	CFVec3 vReturn;
	XMVECTOR& vTarget = *reinterpret_cast< XMVECTOR* >( &vReturn );

	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >( this );
	const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );

	vTarget = vMe - vOther;
	return vReturn;
}
/*
*
*/
CFVec3 CFVec3::operator*  ( CFVec3ref _kr ) const
{
	CFVec3 vReturn;
	XMVECTOR& vTarget = *reinterpret_cast< XMVECTOR* >( &vReturn );

	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >( this );
	const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );

	vTarget = vMe * vOther;
	return vReturn;
}
/*
*
*/
void   CFVec3::operator+= ( CFVec3ref _kr )
{

	XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >( this );
	const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );

	vMe += vOther;


}
/*
*
*/
void   CFVec3::operator-= ( CFVec3ref _kr )
{
	XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >( this );
	const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );

	vMe -= vOther;
}
/*
*
*/
void   CFVec3::operator*= ( CFVec3ref _kr )
{
	XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >( this );
	const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );

	vMe *= vOther;
}

CFVec3 CFVec3::operator*  ( const float32 _kf ) const
{
	CFVec3 vReturn;
	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >( this );
	XMVECTOR& v = *reinterpret_cast<  XMVECTOR* >( &vReturn );

	v = vMe * _kf;
	return vReturn;
}


/*
*
*/
float32 CFVec3::Distance  ( CFVec3ref _kr ) const
{
	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >( this );
	const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );
	
	XMVECTOR vLenght = XMVector3Length( vMe - vOther );

	return XMVectorGetX( vLenght );
}
/*
*
*/
float32 CFVec3::SqDistance( CFVec3ref _kr ) const
{
	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >( this );
	const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );
	
	XMVECTOR vLenght = XMVector3LengthSq( vMe - vOther );

	return XMVectorGetX( vLenght );
}
/*
*
*/
float32 CFVec3::Magnitude  ( ) const
{
	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >( this );
	
	XMVECTOR vLenght = XMVector3Length( vMe );

	return XMVectorGetX( vLenght );
}
/*
*
*/
float32 CFVec3::SqMagnitude( ) const
{
	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >( this );
	
	XMVECTOR vLenght = XMVector3LengthSq( vMe );

	return XMVectorGetX( vLenght );
}
/*
*
*/
float32    CFVec3::Dot  ( CFVec3ref _kr) const
{
	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >( this );
	const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );
	
	XMVECTOR vDot = XMVector3Dot( vMe, vOther );

	return XMVectorGetX( vDot );
}
/*
*
*/
CFVec3 CFVec3::Cross( CFVec3ref _kr ) const
{
	CFVec3 vRetun;
	XMVECTOR& vTarget = *reinterpret_cast< XMVECTOR* >( &vRetun );

	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >( this );
	const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );
	
	vTarget = XMVector3Cross( vMe, vOther );

	return vRetun;
}
/*
*
*/
void   CFVec3::Normalise( )
{
	 XMVECTOR& vMe = *reinterpret_cast<  XMVECTOR* >( this );
	vMe = XMVector3Normalize( vMe );
}
/*
*
*/
void   CFVec3::Normalise( float32& _rfMag )
{

	_rfMag = this->Magnitude( );

	 XMVECTOR& vMe = *reinterpret_cast<  XMVECTOR* >( this );
	vMe = XMVector3Normalize( vMe );
}
/*
*
*/
CFVec3 CFVec3::GetNormal( ) const
{
	CFVec3 vReturn;
	XMVECTOR& vTarget = *reinterpret_cast< XMVECTOR* >( &vReturn );

	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >( this );
	vTarget = XMVector3Normalize( vMe );

	return vReturn;
}
/*
*
*/
CFVec3 CFVec3::GetNormal( float32& _rfMag ) const
{

	CFVec3 vNormal = GetNormal( );
	_rfMag = Magnitude( );

	return vNormal;
}
/*
*
*/
void CFVec3::RotateX( const float32 _kfRad )
{
	CFMat4x4 mRotation = CFMat4x4::CreateRotationMatrixX( _kfRad );

	XMMATRIX& xmRotation = *reinterpret_cast< XMMATRIX* >( &mRotation );

	XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >( this );

	vMe = XMVector3Transform( vMe, xmRotation );
}
/*
*
*/
void CFVec3::RotateY( const float32 _kfRad )
{
	CFMat4x4 mRotation = CFMat4x4::CreateRotationMatrixY( _kfRad );

	XMMATRIX& xmRotation = *reinterpret_cast< XMMATRIX* >( &mRotation );

	XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >( this );

	vMe = XMVector3Transform( vMe, xmRotation );
}
/*
*
*/
void CFVec3::RotateZ( const float32 _kfRad )
{
	CFMat4x4 mRotation = CFMat4x4::CreateRotationMatrixZ( _kfRad );

	XMMATRIX& xmRotation = *reinterpret_cast< XMMATRIX* >( &mRotation );

	XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >( this );

	vMe = XMVector3Transform( vMe, xmRotation );
}
/*
*
*/
float32  CFVec3::GetPitch( ) const
{
	return 0.0f;
}
/*
*
*/
float32  CFVec3::GetElevation( ) const
{
	return 0.0f;
}
/*
*
*/
float32  CFVec3::GetRoll( ) const
{
	return 0.0f;
}
float32 CFVec3::x( )
{
	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >(this );
	return XMVectorGetX( vMe );
}
float32 CFVec3::y( )
{
	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >(this );
	return XMVectorGetY( vMe );
}
float32 CFVec3::z( )
{
	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >(this );
	return XMVectorGetZ( vMe );
}


float32 CFVec3::x( ) const 
{
	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >(this );
	return XMVectorGetX( vMe );
}
float32 CFVec3::y( ) const 
{
	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >(this );
	return XMVectorGetY( vMe );
}
float32 CFVec3::z( ) const
{
	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >(this );
	return XMVectorGetZ( vMe );
}



void CFVec3::x( float32 _f )
{
	XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >(this );
	vMe = XMVectorSetX( vMe, _f );
}
void CFVec3::y( float32 _f )
{
	XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >(this );
	vMe = XMVectorSetY( vMe, _f );
}
void CFVec3::z( float32 _f )
{
	XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >(this );
	vMe = XMVectorSetZ( vMe, _f );
}

#endif // WIN32
#endif

#ifdef iOS

#include <cmath>

CFVec3::CFVec3(void)
{
	m_vVals.fX = 0.0f;
	m_vVals.fY = 0.0f;
	m_vVals.fZ = 0.0f;
}
/*
*
*/
CFVec3::~CFVec3(void)
{
}
/*
*
*/
CFVec3::CFVec3( float32 _fX, float32 _fY, float32 _fZ )
{
	m_vVals.fX = _fX;
	m_vVals.fY = _fY;
	m_vVals.fZ = _fZ;
}
/*
*
*/
CFVec3::CFVec3( CFVec3ref _kr )
{
	m_vVals = _kr.m_vVals;
}
/*
*
*/
CFVec3 CFVec3::operator=  ( CFVec3ref _kr )
{
	m_vVals = _kr.m_vVals;
	return *this;
}
/*
*
*/
bool CFVec3::operator== ( CFVec3ref _kr )
{
	return m_vVals.fX == _kr.m_vVals.fX && m_vVals.fY == _kr.m_vVals.fY && m_vVals.fZ == _kr.m_vVals.fZ;
}
/*
*
*/
CFVec3 CFVec3::operator+  ( CFVec3ref _kr ) const
{
	return CFVec3( m_vVals.fX + _kr.m_vVals.fX,
				   m_vVals.fY + _kr.m_vVals.fY,
				   m_vVals.fZ + _kr.m_vVals.fZ ); 
}
/*
*
*/
CFVec3 CFVec3::operator-  ( CFVec3ref _kr ) const
{
	return CFVec3( m_vVals.fX - _kr.m_vVals.fX,
				   m_vVals.fY - _kr.m_vVals.fY,
				   m_vVals.fZ - _kr.m_vVals.fZ ); 
}
/*
*
*/
CFVec3 CFVec3::operator*  ( CFVec3ref _kr ) const
{
	return CFVec3( m_vVals.fX * _kr.m_vVals.fX,
			       m_vVals.fY * _kr.m_vVals.fY,
			       m_vVals.fZ * _kr.m_vVals.fZ ); 
}
/*
*
*/
void   CFVec3::operator+= ( CFVec3ref _kr )
{
	 m_vVals.fX += _kr.m_vVals.fX;
	 m_vVals.fY += _kr.m_vVals.fY;
	 m_vVals.fZ += _kr.m_vVals.fZ; 
}
/*
*
*/
void   CFVec3::operator-= ( CFVec3ref _kr )
{
	 m_vVals.fX -= _kr.m_vVals.fX;
	 m_vVals.fY -= _kr.m_vVals.fY;
	 m_vVals.fZ -= _kr.m_vVals.fZ; 
}
/*
*
*/
void   CFVec3::operator*= ( CFVec3ref _kr )
{
	 m_vVals.fX *= _kr.m_vVals.fX;
	 m_vVals.fY *= _kr.m_vVals.fY;
	 m_vVals.fZ *= _kr.m_vVals.fZ; 
}

CFVec3 CFVec3::operator*  ( const float32 _kf ) const
{
	return CFVec3( m_vVals.fX * _kf,
			       m_vVals.fY * _kf,
			       m_vVals.fZ * _kf ); 
}


/*
*
*/
float32 CFVec3::Distance  ( CFVec3ref _kr ) const
{
	CFVec3 vToTarget = _kr - (*this);
	return vToTarget.Magnitude();
}
/*
*
*/
float32 CFVec3::SqDistance( CFVec3ref _kr ) const
{
	CFVec3 vToTarget = _kr - (*this);
	return vToTarget.SqMagnitude();
}
/*
*
*/
float32 CFVec3::Magnitude  ( ) const
{
	return sqrt( (m_vVals.fX * m_vVals.fX) + (m_vVals.fY * m_vVals.fY) + (m_vVals.fZ * m_vVals.fZ) ); 
}
/*
*
*/
float32 CFVec3::SqMagnitude( ) const
{
	return (m_vVals.fX * m_vVals.fX) + (m_vVals.fY * m_vVals.fY) + (m_vVals.fZ * m_vVals.fZ); 
}
/*
*
*/
float32    CFVec3::Dot  ( CFVec3ref _kr) const
{
	return ( m_vVals.fX * _kr.m_vVals.fX ) +  ( m_vVals.fY * _kr.m_vVals.fY ) +  ( m_vVals.fZ * _kr.m_vVals.fZ );
}
/*
*
*/
CFVec3 CFVec3::Cross( CFVec3ref _kr ) const
{
	//? 
	return CFVec3();
}
/*
*
*/
void   CFVec3::Normalise( )
{
	float fMag = Magnitude( );
	if( fMag )
	{
		m_vVals.fX /= fMag;
		m_vVals.fY /= fMag;
		m_vVals.fZ /= fMag;
	}
	else
	{
		assert_now( "Normalizing vector with lenght of 0!" );
	}
}
/*
*
*/
void   CFVec3::Normalise( float32& _rfMag )
{
	_rfMag = Magnitude( );
	if( _rfMag )
	{
		m_vVals.fX /= _rfMag;
		m_vVals.fY /= _rfMag;
		m_vVals.fZ /= _rfMag;
	}
	else
	{
		assert_now( "Normalizing vector with lenght of 0!" );
	}
}
/*
*
*/
CFVec3 CFVec3::GetNormal( ) const
{
	CFVec3 vNormal = (*this);
	vNormal.Normalise( );
	return vNormal;
}
/*
*
*/
CFVec3 CFVec3::GetNormal( float32& _rfMag ) const
{
	CFVec3 vNormal = (*this);
	vNormal.Normalise( _rfMag );
	return vNormal;
}
/*
*
*/
void CFVec3::RotateX( const float32 _kfRad )
{
	//- TODO
}
/*
*
*/
void CFVec3::RotateY( const float32 _kfRad )
{
	//- TODO
}
/*
*
*/
void CFVec3::RotateZ( const float32 _kfRad )
{

}
/*
*
*/
float32  CFVec3::GetPitch( ) const
{
	//- TODO
	return 0.0f;
}
/*
*
*/
float32  CFVec3::GetElevation( ) const
{
	//- TODO
	return 0.0f;
}
/*
*
*/
float32  CFVec3::GetRoll( ) const
{
	//- TODO
	return 0.0f;
}
float32 CFVec3::x( )
{
	return m_vVals.fX;
}
float32 CFVec3::y( )
{
	return m_vVals.fY;
}
float32 CFVec3::z( )
{
	return m_vVals.fZ;
}


float32 CFVec3::x( ) const 
{
	return m_vVals.fX;
}
float32 CFVec3::y( ) const 
{
	return m_vVals.fY;
}
float32 CFVec3::z( ) const
{
	return m_vVals.fZ;
}

void CFVec3::x( float32 _f )
{
	m_vVals.fX = _f;
}
void CFVec3::y( float32 _f )
{
	m_vVals.fY  = _f;
}
void CFVec3::z( float32 _f )
{
	m_vVals.fZ = _f;
}


#endif // iOS