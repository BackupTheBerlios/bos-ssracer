#include "bosapp.h"
#include "kernel.h"
#include "timer.h"
#include "inputmessage.h"
#include "input.h"
#include "log.h"

unsigned int keymap[] = {  0x0000000000000 ,    GAME_ESCAPE ,            '1' ,            '2' , //0x00-0x03
						               '3' ,            '4' ,            '5' ,            '6' , //0x04-0x07
                                       '7' ,            '8' ,            '9' ,            '0' , //0x08-0x0B
									   '-' ,            '=' ,      GAME_BACK ,       GAME_TAB , //0x0C-0x0F
                                       'q' ,            'w' ,            'e' ,            'r' , //0x10-0x13
									   't' ,            'y' ,            'u' ,            'i' , //0x14-0x17
                                       'o' ,            'p' ,            '[' ,            ']' , //0x18-0x1B
							   GAME_RETURN ,  GAME_LCONTROL ,            'a' ,            's' , //0x1C-0x1F
                                      'd'  ,            'f' ,            'g' ,            'h' , //0x20-0x23
									   'j' ,            'k' ,            'l' ,            ';' , //0x24-0x27
                                       '\'',            '`' ,    GAME_LSHIFT ,            '\\', //0x28-0x2B
									   'z' ,            'x' ,            'c' ,            'v' , //0x2C-0x2F
                                       'b' ,            'n' ,            'm' ,            ',' , //0x30-0x33
									   '.' ,            '/' ,    GAME_RSHIFT , 0x000000000000 , //0x34-0x37
                                GAME_LMENU ,            ' ' ,  0x00000000000 ,        GAME_F1 , //0x38-0x3B
							       GAME_F2 ,        GAME_F3 ,        GAME_F4 ,        GAME_F5 , //0x3C-0x3F
                                   GAME_F6 ,        GAME_F7 ,        GAME_F8 ,        GAME_F9 , //0x40-0x43
						    0x000000000000 ,   GAME_NUMLOCK ,    GAME_SCROLL ,   GAME_NUMPAD7 , //0x44-0x47
                              GAME_NUMPAD8 ,   GAME_NUMPAD9 ,  GAME_SUBTRACT ,   GAME_NUMPAD4 , //0x48-0x4B
							  GAME_NUMPAD5 ,   GAME_NUMPAD6 ,       GAME_ADD ,   GAME_NUMPAD1 , //0x4C-0x4F
                              GAME_NUMPAD2 ,   GAME_NUMPAD3 ,   GAME_NUMPAD0 ,   GAME_DECIMAL , //0x50-0x53
							0x000000000000 , 0x000000000000 , 0x000000000000 ,       GAME_F11 , //0x54-0x57
                                  GAME_F12 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0x58-0x5B
							0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0x5C-0x5F
                            0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0x60-0x63
							0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0x64-0x67
                            0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0x68-0x6B
							0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0x6C-0x6F
                            0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0x70-0x73
							0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0x74-0x77
                            0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0x78-0x7B
							0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0x7C-0x7F
                            0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0x80-0x83
							0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0x84-0x87
                            0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0x88-0x8B
							0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0x8C-0x8F
                            0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0x90-0x93
							0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0x94-0x97
                            0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0x98-0x9B
						  GAME_NUMPADENTER ,  GAME_RCONTROL , 0x000000000000 , 0x000000000000 , //0x9C-0x9F
                            0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0xA0-0xA3
							0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0xA4-0xA7
                            0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0xA8-0xAB
							0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0xAC-0xAF
                            0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0xB0-0xB3
							0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0xB4-0xB7
                                GAME_RMENU , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0xB8-0xBB
							0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0xBC-0xBF
                            0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0xC0-0xC3
							0x000000000000 ,     GAME_PAUSE , 0x000000000000 ,      GAME_HOME , //0xC4-0xC7
                                   GAME_UP ,     GAME_PRIOR , 0x000000000000 ,      GAME_LEFT , //0xC8-0xCB
							0x000000000000 ,     GAME_RIGHT , 0x000000000000 ,       GAME_END , //0xCC-0xCF
                                 GAME_DOWN ,      GAME_NEXT ,    GAME_INSERT ,    GAME_DELETE , //0xD0-0xD3
							0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0xD4-0xD7
                            0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0xD8-0xDB
							0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0xDC-0xDF
                            0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0xE0-0xE3
							0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0xE4-0xE7
                            0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0xE8-0xEB
							0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0xEC-0xEF
                            0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0xF0-0xF3
							0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0xF4-0xF7
                            0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000 , //0xF8-0xFB
							0x000000000000 , 0x000000000000 , 0x000000000000 , 0x000000000000   //0xFC-0xFF
                    };



           
unsigned int extended_keymap[] = { 0x00, 0x00, '!' , '@' , '#' , '$' , '%' , '^' , //0x00-0x07
                                '&' , '*' , '(' , ')' , '_' , '+' , 0x0e, 0x0f, //0x08-0x0f
                                'Q' , 'W' , 'E' , 'R' , 'T' , 'Y' , 'U' , 'I' , //0x10-0x17
                                'O' , 'P' , '{' , '}' , 0x00, 0x00, 'A' , 'S' , //0x18-0x1f
                                'D' , 'F' , 'G' , 'H' , 'J' , 'K' , 'L' , ':' , //0x20-0x27
                                '"' , '~' , 0x00, '|' , 'Z' , 'X' , 'C' , 'V' , //0x28-0x2f
                                'B' , 'N' , 'M' , '<' , '>' , '?' , 0x00, 0x00, //0x30-0x37
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x38-0x3f
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x40-0x47
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x48-0x4f
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x50-0x57
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x58-0x5f
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x60-0x67
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x68-0x6f
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x70-0x77
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x78-0x7f
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x80-0x87
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x88-0x8f
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x90-0x97
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x98-0x9f
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0xa0-0xa7
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0xa8-0xaf
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0xb0-0xb7
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0xb8-0xbf
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0xc0-0xc7
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0xc8-0xcf
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0xd0-0xd7
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0xd8-0xdf
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0xe0-0xe7
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0xe8-0xef
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0xf0-0xf7
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  //0xf8-0xff
                         };

unsigned int joystick_map[] = { GAME_BUTTON0, GAME_BUTTON1, GAME_BUTTON2, GAME_BUTTON3,
								GAME_BUTTON4, GAME_BUTTON5, GAME_BUTTON6, GAME_BUTTON7,
								GAME_BUTTON8, GAME_BUTTON9, GAME_BUTTON10, 0x000000000,
								0x0000000000, 0x0000000000, 0x00000000000, 0x000000000,
								0x0000000000, 0x0000000000, 0x00000000000, 0x000000000,
							};


LPDIRECTINPUT8			g_joystickDI;
LPDIRECTINPUTDEVICE8	g_joystickDIDevice;
LPDIRECTINPUT8			g_keyboardDI;
LPDIRECTINPUTDEVICE8	g_keyboardDIDevice;


bool CInput::start()
{
	if(!createKeyboardDevice()) {
		return 0;
	}

    //crashes without gamepad present
    /*
	if(!createJoystickDevice()) {
		return 0;
	}
*/
	return 1;
}

bool CInput::release()
{
	HRESULT hr;

	hr = g_keyboardDIDevice->Unacquire();

	if FAILED(hr) {
		return 0;
	}	

	hr = g_keyboardDIDevice->Release();

	if FAILED(hr) {
		return 0;
	}	

	hr = g_keyboardDI->Release();
	
	if FAILED(hr) {
		return 0;
	}
	
	hr = g_joystickDIDevice->Unacquire();

	if FAILED(hr) {
		return 0;
	}	

	hr = g_joystickDIDevice->Release();

	if FAILED(hr) {
		return 0;
	}	

	hr = g_joystickDI->Release();
	
	if FAILED(hr) {
		return 0;
	}	


	return 1;
}

bool CInput::update()
{

	if(!updateKeyboard()) {
		return 0;
	}
	
	if(!updateJoystick()) {
		return 0;
	}

	return 1;

}

bool CInput::createJoystickDevice()
{
	HRESULT			hr;
	DIPROPDWORD		dipdw;

	hr = DirectInput8Create(CBOSApplication::GetBOSApp().GetMainInstanceHandle(), DIRECTINPUT_VERSION,
							IID_IDirectInput8, (void**)&g_joystickDI, NULL);

	if FAILED(hr) {
		return 0;
	}

	hr = g_joystickDI->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL,
								   DIEDFL_ATTACHEDONLY);

	if FAILED(hr) {
		return 0;
	}

    hr = g_joystickDIDevice->SetDataFormat(&c_dfDIJoystick2);//

    if FAILED(hr) {
		    return 0;
    }

	hr = g_joystickDIDevice->SetCooperativeLevel( CBOSApplication::GetBOSApp().GetMainWindowHandle(), 
															  DISCL_EXCLUSIVE | DISCL_FOREGROUND );
	if FAILED(hr) {
        return 0;
	}
	
	
	

	hr = g_joystickDIDevice->EnumObjects( EnumObjectsCallback, (VOID*)CBOSApplication::GetBOSApp().GetMainWindowHandle(),
										  DIDFT_ALL);

	if FAILED(hr) {
		return 0;
	}

	dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj        = 0;
	dipdw.diph.dwHow        = DIPH_DEVICE;
	dipdw.dwData            = BUFFER_SIZE;

	hr = g_joystickDIDevice->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );

	if FAILED(hr) {
		return 0;
	}

	return 1;
}



//-----------------------------------------------------------------------------
// Name: EnumJoysticksCallback()
// Desc: Called once for each enumerated joystick. If we find one, create a
//       device interface on it so we can play with it.
//-----------------------------------------------------------------------------
BOOL CALLBACK EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance,
                                     VOID* pContext )
{
    HRESULT hr;

    // Obtain an interface to the enumerated joystick.
    hr = g_joystickDI->CreateDevice( pdidInstance->guidInstance, &g_joystickDIDevice, NULL );

    // If it failed, then we can't use this joystick. (Maybe the user unplugged
    // it while we were in the middle of enumerating it.)
    if( FAILED(hr) ) 
        return DIENUM_CONTINUE;

    // Stop enumeration. Note: we're just taking the first joystick we get. You
    // could store all the enumerated joysticks and let the user pick.
    return DIENUM_STOP;
}


//-----------------------------------------------------------------------------
// Name: EnumObjectsCallback()
// Desc: Callback function for enumerating objects (axes, buttons, POVs) on a 
//       joystick. This function enables user interface elements for objects
//       that are found to exist, and scales axes min/max values.
//-----------------------------------------------------------------------------
BOOL CALLBACK EnumObjectsCallback( const DIDEVICEOBJECTINSTANCE* pdidoi,
                                   VOID* pContext )
{
	HRESULT hr;
    HWND hDlg = (HWND)pContext;
	DIPROPRANGE diprg;

    static int nSliderCount = 0;  // Number of returned slider controls
    static int nPOVCount = 0;     // Number of returned POV controls

    // For axes that are returned, set the DIPROP_RANGE property for the
    // enumerated axis in order to scale min/max values.
    if( pdidoi->dwType & DIDFT_AXIS )
    {

        diprg.diph.dwSize       = sizeof(DIPROPRANGE); 
        diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
        diprg.diph.dwHow        = DIPH_BYID; 
		diprg.diph.dwObj        = pdidoi->dwType; // Specify the enumerated axis (X)
        diprg.lMin              = GAMEPAD_LOWER_RANGE; 
        diprg.lMax              = GAMEPAD_UPPER_RANGE;
		    
        // Set the range for the axis
        //if( FAILED( g_joystickDIDevice->SetProperty( DIPROP_RANGE, &diprg.diph ) ) ) 
        //    return DIENUM_STOP;

		hr = g_joystickDIDevice->SetProperty( DIPROP_RANGE, &diprg.diph);

		/*
		diprg.diph.dwObj        = DIJOFS_X; // Specify the enumerated axis (Y)

        // Set the range for the axis
        if( FAILED( g_joystickDIDevice->SetProperty( DIPROP_RANGE, &diprg.diph ) ) ) 
            return DIENUM_STOP; 
			*/
	}

	return 1;
}


bool CInput::createKeyboardDevice()
{
	HRESULT			hr;
	DIPROPDWORD		dipdw;

	hr = DirectInput8Create(CBOSApplication::GetBOSApp().GetMainInstanceHandle(), DIRECTINPUT_VERSION,
							IID_IDirectInput8, (void**)&g_keyboardDI, NULL);

	if FAILED(hr) {
		return 0;
	}	

	hr = g_keyboardDI->CreateDevice(GUID_SysKeyboard, &g_keyboardDIDevice, NULL);

	if FAILED(hr) {
		return 0;
	}	

	hr = g_keyboardDIDevice->SetDataFormat(&c_dfDIKeyboard);

	if FAILED(hr) {
		return 0;
	}	

	hr = g_keyboardDIDevice->SetCooperativeLevel(CBOSApplication::GetBOSApp().GetMainWindowHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	if FAILED(hr) {
		return 0;
	}

	// Setup buffered keyboard input
    dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj        = 0;
    dipdw.diph.dwHow        = DIPH_DEVICE;
    dipdw.dwData            = BUFFER_SIZE;

	hr = g_keyboardDIDevice->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );
    
	if FAILED(hr) {
		return 0;
    }

	return 1;

}

bool CInput::updateJoystick()
{
	HRESULT     hr;
	DIDEVICEOBJECTDATA	bufferedData[ BUFFER_SIZE ];  // Receives buffered data 
	DWORD		numButtonsPressed =  BUFFER_SIZE;

    if( NULL == g_joystickDIDevice ) 
        return 0;

    // Poll the device to read the current state
    hr = g_joystickDIDevice->Poll(); 
    if( FAILED(hr) )  
    {
        // DInput is telling us that the input stream has been
        // interrupted. We aren't tracking any state between polls, so
        // we don't have any special reset that needs to be done. We
        // just re-acquire and try again.
        hr = g_joystickDIDevice->Acquire();
        while( hr == DIERR_INPUTLOST ) 
            hr = g_joystickDIDevice->Acquire();

        // hr may be DIERR_OTHERAPPHASPRIO or other errors.  This
        // may occur when the app is minimized or in the process of 
        // switching, so just try again later 
        return 0; 
    }

	hr = g_joystickDIDevice->GetDeviceData( sizeof(DIDEVICEOBJECTDATA),
										bufferedData, &numButtonsPressed, 0 );

	parseJoystick(bufferedData, numButtonsPressed);

	return 1;
}

void CInput::parseJoystick(DIDEVICEOBJECTDATA *buffer, int numButtonsPressed)
{
	CInputTaskMessage *cIMsg;
	bool keyState;


	for(int i=0;i<numButtonsPressed;i++) {
		

		for(int j=0;j<NUM_BUTTONS;j++) {
			if(buffer[i].dwOfs == DIJOFS_BUTTON(j)) {
				keyState = bool(buffer[i].dwData & 0x80);
				cIMsg = new CInputTaskMessage(joystick_map[j], keyState);
				CKernel::GetKernel().DeliverMessage(cIMsg, AI_TASK);
			}
		}

		if(buffer[i].dwOfs == DIJOFS_X) {
			if(buffer[i].dwData > (GAMEPAD_UPPER_RANGE * 0.8f)) {
				cIMsg = new CInputTaskMessage(GAME_RIGHT, true);
				CKernel::GetKernel().DeliverMessage(cIMsg, AI_TASK);
			}
			else if(buffer[i].dwData < (GAMEPAD_LOWER_RANGE + GAMEPAD_UPPER_RANGE * 0.2f)) {
				cIMsg = new CInputTaskMessage(GAME_LEFT, true);
				CKernel::GetKernel().DeliverMessage(cIMsg, AI_TASK);
			}
			else {
				cIMsg = new CInputTaskMessage(GAME_LEFT, false);
				CKernel::GetKernel().DeliverMessage(cIMsg, AI_TASK);
				cIMsg = new CInputTaskMessage(GAME_RIGHT, false);
				CKernel::GetKernel().DeliverMessage(cIMsg, AI_TASK);
			}
		}

		if(buffer[i].dwOfs == DIJOFS_Y) {
			if(buffer[i].dwData > (GAMEPAD_UPPER_RANGE * 0.8f)) {
				cIMsg = new CInputTaskMessage(GAME_UP, true);
				CKernel::GetKernel().DeliverMessage(cIMsg, AI_TASK);
			}
			else if(buffer[i].dwData < (GAMEPAD_LOWER_RANGE + GAMEPAD_UPPER_RANGE * 0.2f)) {
				cIMsg = new CInputTaskMessage(GAME_DOWN, true);
				CKernel::GetKernel().DeliverMessage(cIMsg, AI_TASK);
			}
			else {
				cIMsg = new CInputTaskMessage(GAME_UP, false);
				CKernel::GetKernel().DeliverMessage(cIMsg, AI_TASK);
				cIMsg = new CInputTaskMessage(GAME_DOWN, false);
				CKernel::GetKernel().DeliverMessage(cIMsg, AI_TASK);
			}
		}
	}
}

bool CInput::updateKeyboard()
{
    DIDEVICEOBJECTDATA	bufferedData[ BUFFER_SIZE ];  // Receives buffered data 
    HRESULT				hr;
	DWORD		numKeysPressed =  BUFFER_SIZE;
    
	if (!g_keyboardDIDevice) {
		return 0;
	}

	hr = g_keyboardDIDevice->Acquire();
	
	if FAILED(hr) {
		// If it failed, the device has probably been lost. 
		// Check for (hr == DIERR_INPUTLOST) 
		// and attempt to reacquire it here. 
		return 0; 
	}

	hr = g_keyboardDIDevice->GetDeviceData( sizeof(DIDEVICEOBJECTDATA),
										bufferedData, &numKeysPressed, 0 );

	if( hr != DI_OK ) 
    {
        hr = g_keyboardDIDevice->Acquire();
        while( hr == DIERR_INPUTLOST ) 
            hr = g_keyboardDIDevice->Acquire();
	}

	if FAILED(hr) {
		return 0;
	}

	parseKeyboard(bufferedData, (int)numKeysPressed);
	
	return 1;
}

void CInput::parseKeyboard(DIDEVICEOBJECTDATA* buffer, int numKeysPressed)
{
	static bool lshift = false;
	static bool rshift = false;
	bool extended = false;
	bool keyDown = false;
	CInputTaskMessage *cIMsg;

	for(int i=0;i<numKeysPressed;i++) {
		// Check to see if the left shift is pressed
		if(buffer[i].dwOfs == DIK_LSHIFT ) {
			lshift ^= true;
		}

		// Check to see if the right shift is pressed
		else if(buffer[i].dwOfs == DIK_RSHIFT ) {
			rshift ^= true;
		}

		// Check to see if the caps lock button is pressed
		else if(buffer[i].dwOfs == DIK_CAPSLOCK && KEYDOWN(buffer, i)) {
			// Toggle the caps variable
		//	if(m_prevCaps == false) {
				m_caps ^= true;
				m_prevCaps = true;
			//}
		}

		extended = isExtended(buffer[i].dwOfs, lshift, rshift);

		if(KEYDOWN(buffer, i)) {
			keyDown = true;
		}
			
		if(extended) {
			// create a new message
			cIMsg = new CInputTaskMessage(extended_keymap[buffer[i].dwOfs], keyDown);
			// send message with extended keycode: extended_keymap[buffer[i]]
			CKernel::GetKernel().DeliverMessage(cIMsg, AI_TASK);
			
		}
		else {
			// create a new message
			cIMsg = new CInputTaskMessage(keymap[buffer[i].dwOfs], keyDown);
			// send message with regular keycode: keymap[buffer[i]];
			CKernel::GetKernel().DeliverMessage(cIMsg, AI_TASK);
		}

		keyDown = false;
	
	}
}

bool CInput::isExtended(int i, bool lshift, bool rshift)
{
	if( (i >= DIK_1 && i <= DIK_EQUALS)			 ||
		(i >= DIK_LBRACKET && i <= DIK_RBRACKET) ||
		(i >= DIK_SEMICOLON && i <= DIK_GRAVE)	 ||
		(i >= DIK_COMMA && i <= DIK_SLASH) ) {
		
		if( (!lshift && rshift) || (lshift && !rshift)) {
			return true;
		}
	}
	else if( (i >= DIK_Q && i <= DIK_P) ||
			 (i >= DIK_A && i <= DIK_L) ||
			 (i >= DIK_Z && i <= DIK_M) ) {

		bool temp = false;
		
		temp = lshift;

		if(rshift) {
			temp ^= rshift;
		}
		if(m_caps) {
			temp ^= m_caps;
		}

		return temp;
	}

	return false;
}
