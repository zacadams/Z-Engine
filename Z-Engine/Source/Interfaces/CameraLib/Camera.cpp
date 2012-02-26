/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\CameraLib\Camera.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes
#include "CoreLib/Core.h"
#include "MathLib/MathsConstants.h"
#include "RendererLib/RendererInterface.h"
// Library includes

// Local includes 
#include "CameraLib/Camera.h"
using namespace ZGE;
CCamera::CCamera(void)
{
	m_vRotation = CFVec3( 0.0f, 0.0f, 0.0f );
	m_vTranslation = CFVec3( 0.0f, 0.0f, 0.0f );
}

CCamera::~CCamera(void)
{
}

// Updates the camera.
bool CCamera::Update( const float32 _kfDeltaTick )
{

	// Rotate the cameras direction.
	CFMat4x4 mRotation;
	CFMat4x4::CreateRotationMatrix( CFVec3( DegToRad( m_vRotation.z( ) ),
													             DegToRad( m_vRotation.y( )),
																  DegToRad( m_vRotation.x( )) ),
																  mRotation);
	mRotation.TransformVec3( m_vUp, m_vUp );
	mRotation.TransformVec3( m_vDirection, m_vDirection );

	m_vPosition += m_vTranslation;
	//// translate my position.
	//CFVec3 vDisplacement =  m_vDirection * m_vTranslation;
	//m_vPosition += vDisplacement;

	CFMat4x4::CreateLookToMatrix( m_vPosition, m_vUp, m_vDirection, m_mViewMatrix ); 	
	// Set the view matrix on the renderer.
	ZEngine::GetRendererInterface( )->SetTransform( m_mViewMatrix, TM_View, 0 );

	m_vRotation = CFVec3( 0.0f, 0.0f, 0.0f );
	m_vTranslation = CFVec3( 0.0f, 0.0f, 0.0f );
	return true;
}


// Rotates the camera.
void CCamera::Rotate( const float32 _kfYaw, const float32 _kfPitch, const float32 _kfRoll )
{
	m_vRotation.x( _kfYaw );
	m_vRotation.y( _kfPitch );
	m_vRotation.z( _kfRoll );
}

// Translates the camera.
void CCamera::Translate( const float32 _kfX, const float32 _kfY, const float32 _kfZ )
{
	m_vTranslation.x( _kfX );
	m_vTranslation.y( _kfY );
	m_vTranslation.z( _kfZ );
	//CFMat4x4 mTranslation = CFMat4x4::CreateTranslationMatrix( CFVec3( _kfX, _kfY, _kfZ ) );
	//m_vPosition = mTranslation.TransformVec3( m_vPosition );
}