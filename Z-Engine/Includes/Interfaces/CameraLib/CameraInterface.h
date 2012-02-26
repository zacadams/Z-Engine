/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\CameraLib\CameraInterface.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _CAMERAINTERFACE_H__Included_515041071
#define _CAMERAINTERFACE_H__Included_515041071

namespace ZGE
{
	class CFVec3;
	class CCamera;
	/**
	 *	The camera interface.
	 */
	class CCameraInterface
	{
	public:
		CCameraInterface(void);
		~CCameraInterface(void);

		/**
		 *	Creates a camera instance.
		 *	@param _krvEye the cameras position.
		 *	@param _krvUp The cameras up vector.
		 *	@param _krvDirection The cameras direction.
		 *	@return Camera instance.
		 */
		CCamera* CreateCamera( const CFVec3& _krvEye, const CFVec3& _krvUp, const CFVec3& _krvDirection );
	};
}

#endif //_CAMERAINTERFACE_H__Included_515041071

