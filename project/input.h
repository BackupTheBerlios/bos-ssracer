#ifndef _INPUT_H
#define _INPUT_H

#define DIRECTINPUT_VERSION		0x0800
#include <dinput.h>

#define STL_USING_ALL
#include "stl.h"

#define KEYDOWN(name, key) (name[key].dwData & 0x80)
#define BUFFER_SIZE				10

#define KEY_TIME_INTERVAL		0.05f

class CInput {

public:

	CInput() { m_caps = m_prevCaps = false; };
	~CInput() {};
	bool start();
	bool update();
	bool release();


private:

	bool createKeyboardDevice();
	bool createJoystickDevice();

	bool updateKeyboard();
	bool updateJoystick();

	void parseJoystick(DIDEVICEOBJECTDATA* buffer, int numKeysPressed);
	void parseKeyboard(DIDEVICEOBJECTDATA* buffer, int numButtonsPressed);

	bool isExtended(int i, bool lshift, bool rshift);

	bool m_caps;
	bool m_prevCaps;
};


BOOL CALLBACK EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance,
                                     VOID* pContext );

BOOL CALLBACK EnumObjectsCallback( const DIDEVICEOBJECTINSTANCE* pdidoi,
                                   VOID* pContext );

#define GAME_KEYMAP_START		0x00FF
#define NUM_BUTTONS				10
#define GAMEPAD_LOWER_RANGE		0000.0f
#define GAMEPAD_UPPER_RANGE		2000.0f

// Game keyboard value definitions
enum inputMapping {
GAME_ESCAPE = GAME_KEYMAP_START,
GAME_BACK,
GAME_TAB,
GAME_RETURN,
GAME_LCONTROL,
GAME_RSHIFT,
GAME_LSHIFT,
GAME_LMENU,
GAME_NUMLOCK,
GAME_SCROLL,
GAME_NUMPAD0,
GAME_NUMPAD1,
GAME_NUMPAD2,
GAME_NUMPAD3,
GAME_NUMPAD4,
GAME_NUMPAD5,
GAME_NUMPAD6,
GAME_NUMPAD7,
GAME_NUMPAD8,
GAME_NUMPAD9,
GAME_SUBTRACT,
GAME_ADD,
GAME_DECIMAL,
GAME_F1,
GAME_F2,
GAME_F3,
GAME_F4,
GAME_F5,
GAME_F6,
GAME_F7,
GAME_F8,
GAME_F9,
GAME_F10,
GAME_F11,
GAME_F12,
GAME_NUMPADENTER,
GAME_RCONTROL,
GAME_RMENU,
GAME_UP,
GAME_DOWN,
GAME_RIGHT,
GAME_LEFT,
GAME_PAUSE,
GAME_PRIOR,
GAME_NEXT,
GAME_INSERT,
GAME_HOME,
GAME_END,
GAME_DELETE,
GAME_BUTTON0,
GAME_BUTTON1,
GAME_BUTTON2,
GAME_BUTTON3,
GAME_BUTTON4,
GAME_BUTTON5,
GAME_BUTTON6,
GAME_BUTTON7,
GAME_BUTTON8,
GAME_BUTTON9,
GAME_BUTTON10 };


#endif