/**
 *	@file Z-Engine\Z-Engine\Implementations\DInputMouseLib\DMouse.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#include "CoreLib/Core.h"
#include "InputLib/InputStateDefines.h" 
#include "DInputLib/DMouse.h"
using namespace ZGE;

#define KEYDOWN(name, key) (name[key] & 0x80)

CDMouse::CDMouse(void)
{
	HINSTANCE hInst = reinterpret_cast<HINSTANCE>(GetModuleHandle(NULL));
	// Create Direct Input.
	if(FAILED(DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL)))
	{
		// Assert if Direct Input failed to create.
		assert_now("DInput failed to create");
	}
	// Create Direct Input Device.
	if(FAILED(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDIDevice, NULL)))
	{
		// Assert if Direct Input Device failed to create.
		assert_now("DInput Mouse Device failed to create");
	}
	// Set Data Format on Device to Mouse.
	if(FAILED(m_pDIDevice->SetDataFormat(&c_dfDIMouse2)))
	{
		// Assert if failed to set Data Format
		assert_now("Failed to set data format");
	}

		// Check device by acquring it.
	if(FAILED(m_pDIDevice->Acquire()))
	{
		// Assert if failed to acquire the device.
		assert_now("Failed to Acquire device state");
	}	

	ZeroMemory( &m_CurrentMouseState, sizeof( DIMOUSESTATE2 ) );
	ZeroMemory( &m_PreviouseMouseState, sizeof( DIMOUSESTATE2 ) );

	// Set the change state keys.
	m_DownStateObserver.SetKeyState( KS_KEY_DOWN );
	m_UpStateObserver.SetKeyState( KS_KEY_UP );
	m_ChangeStateObserver.SetKeyState( KS_KEY_CHANGE );

}

CDMouse::~CDMouse(void)
{
}
/**
 * Updates the input device, this fires any registered events to imput states.
 * @return Success.
 */
bool CDMouse::Update( const float32 _kfDeltaTick )
{
	// Unused Variables.
	UNUSED_VAR( _kfDeltaTick );

	// Get the mouse states.
	if( m_pDIDevice->GetDeviceState( sizeof(DIMOUSESTATE2), &m_CurrentMouseState) != DI_OK )
	{
		// Failed to get the mouse states.
		// Try acquiring the mouse
		m_pDIDevice->Acquire();
		return false;
	}

	if( m_ChangeStateObserver.IsStateObserved( MK_XY ) || 
		m_UpStateObserver.IsStateObserved( MK_XY ) ||
		m_DownStateObserver.IsStateObserved( MK_XY ) )
	{
		// Check the new mouse states, fire events where needed.
		// Has the mouses position change?
		float32 fMouseX = static_cast< float32 >( m_CurrentMouseState.lX );
		float32 fMouseY = static_cast< float32 >( m_CurrentMouseState.lY );

		// Update the mouses position.
		m_vPosition += CFVec2( fMouseX, fMouseY );
		
		if( fMouseX || fMouseY )
		{		

			POINT pt;
			GetCursorPos( &pt );
			m_vPosition = CFVec2( static_cast<float32>( pt.x ),
 								 static_cast< float32 >( pt.y ) );

			// Convert the the point into the windows screen coordinates.
			RECT Rect;
			HWND hWnd = GetForegroundWindow();
			GetWindowRect( hWnd, &Rect );

			uint32 uXFrame = GetSystemMetrics(SM_CXFRAME);
			uint32 uYFrame = GetSystemMetrics(SM_CYFRAME);
			uint32 uYCaption = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME);
			float32 fRealX = (float32)pt.x - (Rect.left + uXFrame);
			float32 fRealY = (float32)pt.y - (Rect.top + uYCaption);
			fRealX = max(fRealX, 0.0f);
			fRealX = min(fRealX, Rect.right - Rect.left - (uXFrame * 2));
			fRealY = max(fRealY, 0.0f);
			fRealY = min(fRealY, Rect.bottom - Rect.top - (uYFrame + uYCaption));

			m_vPosition = CFVec2( fRealX, fRealY );

			// The mouse has moved, fire the mouse moved event.
			CMouseState MousePos( m_vPosition.x( ), m_vPosition.y( ) );
			m_ChangeStateObserver.IsStateObserved( MK_XY ) ? m_ChangeStateObserver.FireStateChange( &MousePos, MK_XY ) : NULL;
		}
	}



	// Is there an observer for delta mouse changes?
	if( m_ChangeStateObserver.IsStateObserved( MK_DELTA_XY ) )
	{
		// Yes, sent the change.
		CMouseState MouseDelta( static_cast<float32>( m_CurrentMouseState.lX ),
								static_cast<float32>( m_CurrentMouseState.lY ) );
		MouseDelta.m_uEventId = MK_DELTA_XY;
		m_ChangeStateObserver.FireStateChange( &MouseDelta, MK_DELTA_XY );

	}
	
	/**
	 *	Look up table for key events.
	 */
	static EMouseKeys eKeyEvents[] = 
	{
		MK_L_CLICK,
		MK_R_CLICK,
		MK_SCROLL_CLICK,
	};
	const uint32 kuKeyEventCount = 3; 
	CInputEvent Evnt;

	// Process all keys.
	for( uint32 uKeyEvent = 0; uKeyEvent < kuKeyEventCount; ++uKeyEvent )
	{
		Evnt.m_uEventId = eKeyEvents[uKeyEvent];
		if( m_CurrentMouseState.rgbButtons[uKeyEvent] & 0x80 )
		{
			// Key down, has this state changed?
			if( false == ( m_PreviouseMouseState.rgbButtons[uKeyEvent] & 0x80 ) )
			{
				// State has changed, notify the down and change observers.
				m_DownStateObserver.IsStateObserved( eKeyEvents[uKeyEvent] ) ? m_DownStateObserver.FireStateChange( &Evnt, eKeyEvents[uKeyEvent] ) : NULL;
				m_ChangeStateObserver.IsStateObserved( eKeyEvents[uKeyEvent] ) ? m_ChangeStateObserver.FireStateChange( &Evnt, eKeyEvents[uKeyEvent] ) : NULL;
			}
		}else
		{
			// Key is up, has this state changed?
			if( m_PreviouseMouseState.rgbButtons[uKeyEvent] & 0x80 )
			{
				// State has changed, notify the up and change state observers.
				m_UpStateObserver.IsStateObserved(  eKeyEvents[uKeyEvent] ) ? m_UpStateObserver.FireStateChange( &Evnt,  eKeyEvents[uKeyEvent] ) : NULL;
				m_ChangeStateObserver.IsStateObserved(  eKeyEvents[uKeyEvent] ) ? m_ChangeStateObserver.FireStateChange( &Evnt,  eKeyEvents[uKeyEvent] ) : NULL;
			}
		}

	}

	//// Has the left click button changed?
	//if( m_CurrentMouseState.rgbButtons[0] & 0x80 ) // KEYDOWN( m_CurrentMouseState.rgbButtons,0 ) )
	//{
	//	// Left button down, has this state changed?
	//	if( false == ( m_PreviouseMouseState.rgbButtons[0] & 0x80 ) )
	//	{
	//		// State has changed, notify the down and change observers.
	//		m_DownStateObserver.IsStateObserved( MK_L_CLICK ) ? m_DownStateObserver.FireStateChange( &Evnt, MK_L_CLICK ) : NULL;
	//		m_ChangeStateObserver.IsStateObserved( MK_L_CLICK ) ? m_ChangeStateObserver.FireStateChange( &Evnt, MK_L_CLICK ) : NULL;
	//	}
	//}else
	//{
	//	// Left button up, has this state changed?
	//	if( m_PreviouseMouseState.rgbButtons[0] & 0x80 )
	//	{
	//		// State has changed, notify the up and change state observers.
	//		m_UpStateObserver.IsStateObserved( MK_L_CLICK ) ? m_UpStateObserver.FireStateChange( &Evnt, MK_L_CLICK ) : NULL;
	//		m_ChangeStateObserver.IsStateObserved( MK_L_CLICK ) ? m_ChangeStateObserver.FireStateChange( &Evnt, MK_L_CLICK ) : NULL;
	//	}
	//}

	//Evnt.m_uEventId = MK_R_CLICK;
	//	// Has the right click button changed?
	//if( m_CurrentMouseState.rgbButtons[1] & 0x80 )
	//{
	//	// Right button down, has this state changed?
	//	if( false == ( m_PreviouseMouseState.rgbButtons[1] & 0x80 ) )
	//	{
	//		// State has changed, notify the down and change observers.
	//		m_DownStateObserver.IsStateObserved( MK_R_CLICK ) ? m_DownStateObserver.FireStateChange( &Evnt, MK_R_CLICK ) : NULL;
	//		m_ChangeStateObserver.IsStateObserved( MK_R_CLICK ) ? m_ChangeStateObserver.FireStateChange( &Evnt, MK_R_CLICK ) : NULL;
	//	}
	//}else
	//{
	//	// Right button up, has this state changed?
	//	if( m_PreviouseMouseState.rgbButtons[1] & 0x80 )
	//	{
	//		// State has changed, notify the up and change state observers.
	//		m_UpStateObserver.IsStateObserved( MK_R_CLICK ) ? m_UpStateObserver.FireStateChange( &Evnt, MK_R_CLICK ) : NULL;
	//		m_ChangeStateObserver.IsStateObserved( MK_R_CLICK ) ? m_ChangeStateObserver.FireStateChange( &Evnt, MK_R_CLICK ) : NULL;
	//	}
	//}


	//Evnt.m_uEventId = MK_SCROLL_CLICK;

	m_PreviouseMouseState = m_CurrentMouseState;
	return true;
}