/**
 *	@file Z-Engine\Z-Engine\Implementations\DInputMouseLib\DMouse.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _DMOUSE_H__Included_514538642

#include "InputLib/Mouse.h"
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "MathLib/Fvec2.h"

namespace ZGE
{
	/**
	 * Direct input mouse implementetion.
	 */
	class CDMouse : public IMouse, public TAligned< 16 >
	{
	public:
		CDMouse(void);
		~CDMouse(void);

		/**
		 * Updates the input device, this fire any registered events to imput states.
		 * @return Success.
		 */
		virtual bool Update( const float32 _kfDeltaTick );
	protected:
		LPDIRECTINPUT8		  m_pDirectInput;		//!< Pointer to the instance of Direct Input.
		LPDIRECTINPUTDEVICE8  m_pDIDevice;			//!< Pointer to the Direct Input Device.
		DIMOUSESTATE2 m_CurrentMouseState;			//!< Structure containing mouse state information.
		DIMOUSESTATE2 m_PreviouseMouseState;		//!< Structure containing the previouse mouse state information.
		CFVec2		  m_vPosition;					//!< The mouses position
	};
}

#endif //_DMOUSE_H__Included_514538642

