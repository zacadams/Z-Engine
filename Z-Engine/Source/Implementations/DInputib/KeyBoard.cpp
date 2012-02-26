
#include "CoreLib/Core.h"

#include "DInputLib/KeyBoard.h"

using namespace ZGE;


static uint32 g_uKB_LookUpTable[KB_COUNT][2] = 
{
		KB_A,			0x1E, // A	
		KB_B,			0x30, // B
		KB_C,			0x2E, // C
		KB_D,			0x20, // D
		KB_E,			0x12, // E
		KB_F,			0x21, // F
		KB_G,			0x22, // G
		KB_H,			0x23, // H
		KB_I,			0x17, // I
		KB_J,			0x24, // J
		KB_K,			0x25, // K
		KB_L,			0x26, // L
		KB_M,			0x32, // M
		KB_N,			0x31, // N
		KB_O,			0x18, // O
		KB_P,			0x19, // P
		KB_Q,			0x10, // Q
		KB_R,			0x13, // R
		KB_S,			0x1F, // S
		KB_T,			0x14, // T
		KB_U,			0x16, // U
		KB_V,   		0x2F, // V
		KB_W,			0x11, // W
		KB_X,   		0x2D, // X
		KB_Y,			0x15, // Y
		KB_Z,			0x2C, // Z
		KB_0,			0x0B, //0	
		KB_1,   		0x02, //1
		KB_2,			0x03, //2
		KB_3,			0x04, //3
		KB_4,			0x05, //4
		KB_5,			0x06, //5
		KB_6,			0x07, //6
		KB_7,			0x08, //7
		KB_8,			0x09, //8
		KB_9,			0x0A, //9
		KB_NP_0,		0x52, // 0
		KB_NP_1,		0x4F, // 1
		KB_NP_2,		0x50, // 2
		KB_NP_3,		0x51, // 3
		KB_NP_4,		0x4B, // 4
		KB_NP_5,		0x4C, // 5
		KB_NP_6,		0x4D, // 6
		KB_NP_7,		0x47, // 7
		KB_NP_8,		0x48, // 8
		KB_NP_9,		0x49, // 9
		KB_LEFT,		0xCB,  
		KB_RIGHT,		0xCD, 
		KB_UP,			0xC8,  
		KB_DOWN,		0xD0,
		KB_ESCAPE,		0x01,
		KB_MINUS,		0x0C,  /* - on main keyboard */
		KB_PLUS,		0,// '+'
		KB_PGE_DWN,	    0,
		KB_PGE_UP,	    0,
		KB_L_SHIFT,		0x2A,
		KB_R_SHIFT,		0x36,
		KB_PERIOD,		0x34,  // '.'
		KB_COMMA,		0x33,
		KB_ENTER,    	0x1C,  /* Enter on main keyboard */
		KB_BACK,		0x0E,  /* backspace */
		KB_TAB,			0x0F,
		KB_CAPS,        0,
		KB_SPACE,		0x39,
		KB_L_ALT,		0x38,
};

		
	//	KC_EQUALS = 0x0D,
	//	
	//	KC_LBRACKET = 0x1A,
	//	KC_RBRACKET = 0x1B,
	//	KC_LCONTROL = 0x1D,
	//	KC_SEMICOLON = 0x27,
	//	KC_APOSTROPHE = 0x28,
	//	KC_BACKSLASH = 0x2B,
	//	KC_SLASH = 0x35,  /* / on main keyboard */
	//	KC_MULTIPLY = 0x37,  /* * on numeric keypad */
	//	KC_LMENU = 0x38,  /* left Alt */
	//	,
	//	KC_CAPITAL = 0x3A,
	//	KC_F1 = 0x3B,
	//	KC_F2 = 0x3C,
	//	KC_F3 = 0x3D,
	//	KC_F4 = 0x3E,
	//	KC_F5 = 0x3F,
	//	KC_F6 = 0x40,
	//	KC_F7 = 0x41,
	//	KC_F8 = 0x42,
	//	KC_F9 = 0x43,
	//	KC_F10 = 0x44,
	//	KC_NUMLOCK = 0x45,
	//	KC_SCROLL = 0x46,  /* Scroll Lock */
	//	KC_SUBTRACT = 0x4A,  /* - on numeric keypad */
	//	KC_ADD = 0x4E,  /* + on numeric keypad */
	//	KC_DECIMAL = 0x53, /* . on numeric keypad */
	//	KC_F11 = 0x57,
	//	KC_F12 = 0x58,
	//	KC_NUMPADENTER = 0x9C,  /* Enter on numeric keypad */
	//	KC_RCONTROL = 0x9D,
	//	KC_DIVIDE = 0xB5,  /* / on numeric keypad */
	//	KC_SYSRQ = 0xB7,
	//	KC_RMENU = 0xB8, /* right Alt */
	//	KC_HOME = 0xC7,  /* Home on arrow keypad */
	//	KC_PRIOR = 0xC9,  /* PgUp on arrow keypad */
	//	KC_END = 0xCF,  /* End on arrow keypad */
	//	KC_NEXT = 0xD1,  /* PgDn on arrow keypad */
	//	KC_INSERT = 0xD2,  /* Insert on arrow keypad */
	//	KC_DELETE = 0xD3,  /* Delete on arrow keypad */
	//	KC_LWIN = 0xDB,  /* Left Windows key */
	//	KC_RWIN = 0xDC,  /* Right Windows key */
	//	KC_MAX,
	//};


CKeyBoard::CKeyBoard(void)
{
	// Create Direct Input.
	if(FAILED(DirectInput8Create(reinterpret_cast<HINSTANCE>(GetModuleHandle(NULL)), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL)))
	{
		// Assert if Direct Input failed to create.
		assert_now("DInput failed to create");
	}
	// Create Direct Input Device.
	if(FAILED(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDIDevice, NULL)))
	{
		// Assert if Direct Input Device failed to create.
		assert_now("DInput Device failed to create");
	}
	// Set Data Format on Device to Keyboard.
	if(FAILED(m_pDIDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		// Assert if failed to set Data Format
		assert_now("Failed to set data format");
	}

	// Initialise all key states.
	for( uint32 i =0 ; i  < KB_COUNT; ++i )
	{
		m_bObserverdKeys[i] = false;
	}

	// Initialse the buffers
	for( uint32 i = 0; i < KB_COUNT; ++i )
	{
		m_pCurrentKeyStates[i] = 0;
		m_pPreviousKeyStates[i] = 0;
	}

	
	// Set the change state keys.
	m_DownStateObserver.SetKeyState( KS_KEY_DOWN );
	m_UpStateObserver.SetKeyState( KS_KEY_UP );
	m_ChangeStateObserver.SetKeyState( KS_KEY_CHANGE );


	// Aquire the device.
	m_pDIDevice->Acquire( );
	// Get the initial key states.
	// Gets the current state of all keys on the keyboard.
	if (FAILED(m_pDIDevice->GetDeviceState(sizeof(m_pCurrentKeyStates),(LPVOID)&m_pCurrentKeyStates))) 
    { 
		// If failed to get the current key states, try to acquire the keyboard device.
		if FAILED(m_pDIDevice->Acquire())
		{
			// Unable to acquire the keyboard device. Assert.
			assert_now("Failed to acquire device state on update");
		}
		// Unable to process rest of function. Return.

    }
	for( uint32 i = 0; i < 256; ++i )
	{
		m_pPreviousKeyStates[i] = m_pCurrentKeyStates[i];
	}
}

CKeyBoard::~CKeyBoard(void)
{
}


#define KEYDOWN(name, key) (name[key] & 0x80)

/**
 * Updates the input device, this fire any registered events to imput states.
 * @return Success.
 */
bool CKeyBoard::Update( const float32 _kfDeltaTick )
{
	// Unused variables.
	UNUSED_VAR( _kfDeltaTick );

	// Gets the current state of all keys on the keyboard.
	if (FAILED(m_pDIDevice->GetDeviceState(sizeof(m_pCurrentKeyStates),(LPVOID)&m_pCurrentKeyStates))) 
    { 
		// If failed to get the current key states, try to acquire the keyboard device.
		if FAILED(m_pDIDevice->Acquire())
		{
			// Unable to acquire the keyboard device. Assert.
			assert_now("Failed to acquire device state on update");
		}
		// Unable to process rest of function. Return.
        return false; 
    }

	CInputEvent Evnt;

	// Iterate through all keys, and update the stored states to the new states.
	for( uint32 i = 0; i < KB_COUNT; ++i )
	{
		Evnt.m_uEventId = i;
		// Chheck the current state of key.
		if( KEYDOWN( m_pCurrentKeyStates, g_uKB_LookUpTable[i][1] ) )
		{
			// This key is down, has this state changed?
			if( false == KEYDOWN( m_pPreviousKeyStates, g_uKB_LookUpTable[i][1] ) )
			{
				// This key was not not donw previously, notify this keys observers
				// for a down event or change event.
				
				m_DownStateObserver.IsStateObserved( i ) ? m_DownStateObserver.FireStateChange( &Evnt, i ) : NULL;
				m_ChangeStateObserver.IsStateObserved( i ) ? m_ChangeStateObserver.FireStateChange( &Evnt, i ) : NULL;
			}
		}else
		{
			// This key is up, has this state changed?
			if( KEYDOWN( m_pPreviousKeyStates, g_uKB_LookUpTable[i][1] ) )
			{
				// This key was not up previously, notify this keys observers
				// for a up event or change state event.
				m_UpStateObserver.IsStateObserved( i ) ? m_DownStateObserver.FireStateChange( &Evnt, i ) : NULL;
				m_ChangeStateObserver.IsStateObserved( i ) ? m_ChangeStateObserver.FireStateChange( &Evnt, i ) : NULL;
			}
		}
	}
	// Set the previous states to be this state.
	for( uint32 i = 0; i < 256; ++i )
	{
		m_pPreviousKeyStates[i] = m_pCurrentKeyStates[i];
	}
	return true;
}