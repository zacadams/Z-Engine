/**
 *	@file Z-Engine\Z-Engine\Interfaces\InputLib\InputStateDefines.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _INPUTSTATEDEFINES_H__Included_214941386
#define _INPUTSTATEDEFINES_H__Included_214941386

#include "CoreLib/Event.h"

namespace ZGE
{
		/**
	 * Enumeration for keyboard keys.
	 */
	enum EKeyboardKeys
	{
		KB_A = 0,
		KB_B, 
		KB_C	,
		KB_D,
		KB_E,
		KB_F,
		KB_G,
		KB_H,
		KB_I,
		KB_J,
		KB_K,
		KB_L,
		KB_M,
		KB_N,
		KB_O,
		KB_P,
		KB_Q,
		KB_R,
		KB_S,
		KB_T,
		KB_U,
		KB_V,
		KB_W,
		KB_X,
		KB_Y,
		KB_Z,
		KB_0,
		KB_1,
		KB_2,
		KB_3,
		KB_4,
		KB_5,
		KB_6,
		KB_7,
		KB_8,
		KB_9,
		KB_NP_0,
		KB_NP_1,
		KB_NP_2,
		KB_NP_3,
		KB_NP_4,
		KB_NP_5,
		KB_NP_6,
		KB_NP_7,
		KB_NP_8,
		KB_NP_9,
		KB_LEFT,
		KB_RIGHT,
		KB_UP,
		KB_DOWN,
		KB_ESCAPE,
		KB_MINUS,	// '-'
		KB_PLUS,	// '+'
		KB_PGE_DWN,
		KB_PGE_UP,
		KB_L_SHIFT,
		KB_R_SHIFT,
		KB_PERIOD,	// '.'
		KB_COMMA,	
		KB_ENTER,
		KB_BACK,
		KB_TAB,
		KB_CAPS,
		KB_SPACE,
		KB_L_ALT,
		KB_COUNT,
	};

	/**
	 * Defines for mouse states.
	 */
	enum EMouseKeys
	{
		MK_XY = KB_COUNT,	//!< The mouses xy position.
		MK_L_CLICK,			//!< Mouses left click button.
		MK_R_CLICK,			//!< Mouses right click button.
		MK_SCROLL_UP,		//!< Mouses scroll wheele up.
		MK_SCROLL_DOWN,		//!< Mouses scroll wheele down. 
		MK_SCROLL_CLICK,    //!< Mouses scroll wheel click.
		MK_DELTA_XY,
		MK_COUNT,
	};

	/**
	 *	Key notifications.	
	 */
	enum EKeyState
	{
		KS_KEY_DOWN,
		KS_KEY_UP,
		KS_KEY_CHANGE,
	};

	/**
	 *	Input event.
	 */
	class CInputEvent : public IEvent
	{
	public:
		//CInputEvent( const EKeyState eKeyState )
		//	: m_eKeyState( eKeyState )
		//{
		//}
		CInputEvent( )
		{
		}
		virtual ~CInputEvent( ){}
		EKeyState m_eKeyState;
	protected:
		void operator=( const CInputEvent& _kr );
	};

	/**
	 * Mouse event. This class is passed as the IEvent instance
	 * when the MK_XY event is fired. Cast to this class to access the mouses x, y position.
	 */
	class CMouseState : public CInputEvent
	{
	public:
		CMouseState( float32 fX, float32 fY )
			: fX( fX )
			, fY( fY )
		{
			m_uEventId = MK_XY;
			m_eKeyState = KS_KEY_CHANGE;
		}
		CMouseState( )
		{
						m_uEventId = MK_XY;
			m_eKeyState = KS_KEY_CHANGE;
		}
		~CMouseState( ) { }
		float32 fX;
		float32 fY;
protected:
		void operator=( const CMouseState& _kr );
	};

}

#endif //_INPUTSTATEDEFINES_H__Included_214941386

