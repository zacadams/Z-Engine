/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\CameraLib\Camera.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _CAMERA_H__Included_2099896868
#define _CAMERA_H__Included_2099896868

#include "MathLib/FMat4x4.h"
#include "MathLib/FVec3.h"

namespace ZGE
{
	/**
	 *	This class is used to manipulate view matrix.
	 */
	class CCamera 
#ifdef Z_PLATFORM_WIN
		: public TAligned<16>
#endif
	{
	public:
		CCamera(void);
		~CCamera(void);

		// Updates the camera.
		bool Update( const float32 _kfDeltaTick );

		// Sets the cameras position.
		inline void SetPosition( const CFVec3& _krvPosition ){ m_vPosition = _krvPosition; }

		// @return The cameras position.
		inline const CFVec3& GetPosition( ) const { return m_vPosition; }

		// Sets the cameras direction.
		inline void SetDirection( const CFVec3& _krvDirection ){ m_vDirection = _krvDirection; }

		// Sets the up vector.
		inline void SetUpVector( const CFVec3& _krvUp ){ m_vUp = _krvUp; }

		// @return The up vector
		inline const CFVec3& GetUpVector( ) const { return m_vUp; }

		// @return The cameras direction.
		inline const CFVec3& GetDirection( ) const { return m_vDirection; }

		// @returns the view matrix.
		inline const CFMat4x4& GetViewMatrix( ) const { return m_mViewMatrix; }

		// Rotates the camera.
		void Rotate( const float32 _kfYaw, const float32 _kfPitch, const float32 _kfRoll );

		// Translates the camera.
		void Translate( const float32 _kfX, const float32 _kfY, const float32 _kfZ );

	protected:
		CFMat4x4 m_mViewMatrix;	//!< The cameras view matrix;
		CFVec3   m_vPosition;	//!< The cameras position.
		CFVec3   m_vDirection;	//!< The cameras position.
		CFVec3   m_vUp;

		// 
		CFVec3 m_vTranslation;	//!< The cameras translation for a frame.
		CFVec3 m_vRotation;	    //!< The cameras rotation for a frame. 
	};
}

#endif //_CAMERA_H__Included_2099896868

