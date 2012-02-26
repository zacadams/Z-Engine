/**
 *	@file Z-Engine\Z-Engine\Interfaces\MathLib\FVec2.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes
#include "CoreLib/Core.h"


#define iOS


// Library includes
#ifndef iOS
#include <windows.h>
#include <xnamath.h>
#endif

// Local includes 

#include "MathLib/FMat4x4.h"
#include "MathLib/FVec2.h"

using namespace ZGE;

#ifndef iOS
#ifdef WIN32
//Windows vector2 implementation.

CFVec2::CFVec2(void)
{
	//XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >( this );
	//vMe = XMVectorSet( 0.0f, 0.0f, 0.0f, 1.0f );

}
/*
*
*/
CFVec2::~CFVec2(void)
{
}
/*
*
*/
CFVec2::CFVec2( float32 _fX, float32 _fY )
{
	XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >( this );
	vMe = XMVectorSet( _fX, _fY, 0.0f, 1.0f );
}
/*
*
*/
CFVec2::CFVec2( CFVec2ref _kr )
{
	m_vVals = _kr.m_vVals;
	//XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >( this );
	//const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );

	//vMe = vOther;
}
/*
*
*/
CFVec2 CFVec2::operator=  ( CFVec2ref _kr )
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
bool CFVec2::operator== ( CFVec2ref _kr )
{
	XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >( this );
	const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );

	BOOL bEq = XMVector2Equal( vMe, vOther );

	return bEq ? true : false;

}
/*
*
*/
CFVec2 CFVec2::operator+  ( CFVec2ref _kr ) const
{
	CFVec2 vReturn;
	XMVECTOR& vTarget = *reinterpret_cast< XMVECTOR* >( &vReturn );

	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >( this );
	const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );

	vTarget = vMe + vOther;
	return vReturn;

}
/*
*
*/
CFVec2 CFVec2::operator-  ( CFVec2ref _kr ) const
{
	CFVec2 vReturn;
	XMVECTOR& vTarget = *reinterpret_cast< XMVECTOR* >( &vReturn );

	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >( this );
	const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );

	vTarget = vMe - vOther;
	return vReturn;
}
/*
*
*/
CFVec2 CFVec2::operator*  ( CFVec2ref _kr ) const
{
	CFVec2 vReturn;
	XMVECTOR& vTarget = *reinterpret_cast< XMVECTOR* >( &vReturn );

	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >( this );
	const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );

	vTarget = vMe - vOther;
	return vReturn;
}
/*
*
*/
void   CFVec2::operator+= ( CFVec2ref _kr )
{

	XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >( this );
	const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );

	vMe += vOther;


}
/*
*
*/
void   CFVec2::operator-= ( CFVec2ref _kr )
{
	XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >( this );
	const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );

	vMe -= vOther;
}
/*
*
*/
void   CFVec2::operator*= ( CFVec2ref _kr )
{
	XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >( this );
	const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );

	vMe *= vOther;
}
/*
*
*/
float32 CFVec2::Distance  ( CFVec2ref _kr ) const
{
	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >( this );
	const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );
	
	XMVECTOR vLenght = XMVector2Length( vMe - vOther );

	return XMVectorGetX( vLenght );
}
/*
*
*/
float32 CFVec2::SqDistance( CFVec2ref _kr ) const
{
	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >( this );
	const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );
	
	XMVECTOR vLenght = XMVector2LengthSq( vMe - vOther );

	return XMVectorGetX( vLenght );
}
/*
*
*/
float32 CFVec2::Magnitude  ( ) const
{
	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >( this );
	
	XMVECTOR vLenght = XMVector2Length( vMe );

	return XMVectorGetX( vLenght );
}
/*
*
*/
float32 CFVec2::SqMagnitude( ) const
{
	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >( this );
	
	XMVECTOR vLenght = XMVector2LengthSq( vMe );

	return XMVectorGetX( vLenght );
}
/*
*
*/
float32    CFVec2::Dot  ( CFVec2ref _kr) const
{
	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >( this );
	const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );
	
	XMVECTOR vDot = XMVector2Dot( vMe, vOther );

	return XMVectorGetX( vDot );
}
/*
*
*/
CFVec2 CFVec2::Cross( CFVec2ref _kr ) const
{
	CFVec2 vRetun;
	XMVECTOR& vTarget = *reinterpret_cast< XMVECTOR* >( &vRetun );

	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >( this );
	const XMVECTOR& vOther = *reinterpret_cast< const XMVECTOR* >( &_kr );
	
	vTarget = XMVector2Cross( vMe, vOther );

	return vRetun;
}
/*
*
*/
void   CFVec2::Normalise( )
{
	 XMVECTOR& vMe = *reinterpret_cast<  XMVECTOR* >( this );
	 vMe = XMVector2Normalize( vMe );
}
/*
*
*/
void   CFVec2::Normalise( float32& _rfMag )
{

	_rfMag = this->Magnitude( );

	 XMVECTOR& vMe = *reinterpret_cast<  XMVECTOR* >( this );
	 vMe = XMVector2Normalize( vMe );
}
/*
*
*/
CFVec2 CFVec2::GetNormal( ) const
{
	CFVec2 vReturn;
	XMVECTOR& vTarget = *reinterpret_cast< XMVECTOR* >( &vReturn );

	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >( this );
	vTarget = XMVector2Normalize( vMe );

	return vReturn;
}
/*
*
*/
CFVec2 CFVec2::GetNormal( float32& _rfMag ) const
{

	CFVec2 vNormal = GetNormal( );
	_rfMag = Magnitude( );

	return vNormal;
}
/*
*
*/
void CFVec2::RotateX( const float32 _kfRad )
{
	CFMat4x4 mRotation = CFMat4x4::CreateRotationMatrixX( _kfRad );

	XMMATRIX& xmRotation = *reinterpret_cast< XMMATRIX* >( &mRotation );

	XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >( this );

	vMe = XMVector2Transform( vMe, xmRotation );
}
/*
*
*/
void CFVec2::RotateY( const float32 _kfRad )
{
	CFMat4x4 mRotation = CFMat4x4::CreateRotationMatrixY( _kfRad );

	XMMATRIX& xmRotation = *reinterpret_cast< XMMATRIX* >( &mRotation );

	XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >( this );

	vMe = XMVector2Transform( vMe, xmRotation );
}

/*
*
*/

float32 CFVec2::x( )
{
	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >(this );
	return XMVectorGetX( vMe );
}
float32 CFVec2::y( )
{
	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >(this );
	return XMVectorGetY( vMe );
}
float32 CFVec2::x( ) const
{
	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >(this );
	return XMVectorGetX( vMe );
}
float32 CFVec2::y( ) const
{
	const XMVECTOR& vMe = *reinterpret_cast< const XMVECTOR* >(this );
	return XMVectorGetY( vMe );
}
void CFVec2::x( float32 _f )
{
	XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >(this );
	vMe = XMVectorSetX( vMe, _f );
}
void CFVec2::y( float32 _f )
{
	XMVECTOR& vMe = *reinterpret_cast< XMVECTOR* >(this );
	vMe = XMVectorSetY( vMe, _f );
}

#endif //WIN32
#endif // iOS

#ifdef iOS

#include <cmath>

// iPhone vector 2 implementation.

CFVec2::CFVec2(void)
{

}
/*
*
*/
CFVec2::~CFVec2(void)
{
}
/*
*
*/
CFVec2::CFVec2( float32 _fX, float32 _fY )
{
	m_vVals.fX = _fX;
	m_vVals.fY = _fY;
}
/*
*
*/
CFVec2::CFVec2( CFVec2ref _kr )
{
	m_vVals = _kr.m_vVals;
}
/*
*
*/
CFVec2 CFVec2::operator=  ( CFVec2ref _kr )
{
	m_vVals = _kr.m_vVals;
	return *this;
}
/*
*
*/
bool CFVec2::operator== ( CFVec2ref _kr )
{
	return m_vVals.fX == _kr.m_vVals.fX && m_vVals.fY == _kr.m_vVals.fY;
}
/*
*
*/
CFVec2 CFVec2::operator+  ( CFVec2ref _kr ) const
{
	return CFVec2( m_vVals.fX + _kr.m_vVals.fX,
				   m_vVals.fY + _kr.m_vVals.fY);

}
/*
*
*/
CFVec2 CFVec2::operator-  ( CFVec2ref _kr ) const
{
	return CFVec2( m_vVals.fX - _kr.m_vVals.fX,
				   m_vVals.fY - _kr.m_vVals.fY);
}
/*
*
*/
CFVec2 CFVec2::operator*  ( CFVec2ref _kr ) const
{
	return CFVec2( m_vVals.fX * _kr.m_vVals.fX,
				   m_vVals.fY * _kr.m_vVals.fY);
}
/*
*
*/
void   CFVec2::operator+= ( CFVec2ref _kr )
{
	m_vVals.fX += _kr.m_vVals.fX;
	m_vVals.fY += _kr.m_vVals.fY;
}
/*
*
*/
void   CFVec2::operator-= ( CFVec2ref _kr )
{
	m_vVals.fX -= _kr.m_vVals.fX;
	m_vVals.fY -= _kr.m_vVals.fY;
}
/*
*
*/
void   CFVec2::operator*= ( CFVec2ref _kr )
{
	m_vVals.fX *= _kr.m_vVals.fX;
	m_vVals.fY *= _kr.m_vVals.fY;
}
/*
*
*/
float32 CFVec2::Distance  ( CFVec2ref _kr ) const
{
	CFVec2 vToTarget = _kr - (*this);
	return vToTarget.Magnitude();
}
/*
*
*/
float32 CFVec2::SqDistance( CFVec2ref _kr ) const 
{
	CFVec2 vToTarget = _kr - (*this);
	return vToTarget.SqMagnitude();
}
/*
*
*/
float32 CFVec2::Magnitude  ( ) const
{
	return sqrt( (m_vVals.fX * m_vVals.fX) + (m_vVals.fY * m_vVals.fY) ); 
}
/*
*
*/
float32 CFVec2::SqMagnitude( ) const
{
	return (m_vVals.fX * m_vVals.fX) + (m_vVals.fY * m_vVals.fY); 
}
/*
*
*/
float32    CFVec2::Dot  ( CFVec2ref _kr) const
{
	return ( m_vVals.fX * _kr.m_vVals.fX ) +  ( m_vVals.fY * _kr.m_vVals.fY );
}
/*
*
*/
CFVec2 CFVec2::Cross( CFVec2ref _kr ) const
{
	return CFVec2( );
}
/*
*
*/
void   CFVec2::Normalise( )
{
	float fMag = Magnitude( );
	if( fMag )
	{
		m_vVals.fX /= fMag;
		m_vVals.fY /= fMag;
	}
	else
	{
		assert_now( "Normalizing vector with lenght of 0!" );
	}
}
/*
*
*/
void   CFVec2::Normalise( float32& _rfMag )
{
	_rfMag = Magnitude( );
	if( _rfMag )
	{
		m_vVals.fX /= _rfMag;
		m_vVals.fY /= _rfMag;
	}
	else
	{
		assert_now( "Normalizing vector with lenght of 0!" );
	}
}
/*
*
*/
CFVec2 CFVec2::GetNormal( ) const
{

	CFVec2 vNormal = *this;
	vNormal.Normalise( );
	return vNormal;
}
/*
*
*/
CFVec2 CFVec2::GetNormal( float32& _rfMag ) const
{
	CFVec2 vNormal = *this;
	vNormal.Normalise( _rfMag );
	return vNormal;
}
/*
*
*/
void CFVec2::RotateX( const float32 _kfRad )
{
}
/*
*
*/
void CFVec2::RotateY( const float32 _kfRad )
{

}

/*
*
*/

float32 CFVec2::x( )
{
	return m_vVals.fX;
}
float32 CFVec2::y( )
{
	return m_vVals.fY;
}
float32 CFVec2::x( ) const
{
	return m_vVals.fX;
}
float32 CFVec2::y( ) const
{
	return m_vVals.fY;
}
void CFVec2::x( float32 _f )
{
	m_vVals.fX = _f;
}
void CFVec2::y( float32 _f )
{
	m_vVals.fY = _f;
}


#endif 