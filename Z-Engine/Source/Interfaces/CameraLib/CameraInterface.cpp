/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\CameraLib\CameraInterface.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes
#include "CoreLib/Core.h"
#include "CameraLib/Camera.h"
// Library includes

// Local includes 
#include "CameraLib/CameraInterface.h"
using namespace ZGE;
CCameraInterface::CCameraInterface(void)
{
}

CCameraInterface::~CCameraInterface(void)
{
}

/**
 *	Creates a camera instance.
 *	@param _krvEye the cameras position.
 *	@param _krvUp The cameras up vector.
 *	@param _krvDirection The cameras direction.
 *	@return Camera instance.
 */
CCamera* CCameraInterface::CreateCamera( const CFVec3& _krvEye, const CFVec3& _krvUp, const CFVec3& _krvDirection )
{
	CCamera* pCamera = new CCamera( );
	pCamera->SetPosition( _krvEye );
	pCamera->SetUpVector( _krvUp );
	pCamera->SetDirection( _krvDirection );
	return pCamera;
}
