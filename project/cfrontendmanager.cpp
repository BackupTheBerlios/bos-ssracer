#include "cfrontendmanager.h"
#include "cfrontendmessage.h"
#include "log.h"
#include "appstate.h"

// Singleton stuff
CFrontendManager * CFrontendManager::m_pkFrontendManager = NULL; 
CFrontendManager & CFrontendManager::GetFrontendManager() {  return *m_pkFrontendManager; } 
CFrontendManager * CFrontendManager::GetFrontendManagerPtr() {  return m_pkFrontendManager;  } 
// end Singleton stuff

CFrontendManager::CFrontendManager()
{
	m_nTaskType = FRONTEND_TASK;

	m_curScreen = NULL;
	m_iState = NO_STATE;

	m_MainMenu = NULL;
	m_NewGame = NULL;
	m_Garage = NULL;
	m_PostGame = NULL;
	m_PauseGame = NULL;
	m_Home = NULL;

	m_pkFrontendManager = this;
}

CFrontendManager::~CFrontendManager()
{
	//SAFE_DELETE(m_curScreen);
	SAFE_DELETE(m_MainMenu);
	SAFE_DELETE(m_NewGame);
	SAFE_DELETE(m_Garage);
	SAFE_DELETE(m_PostGame);
	SAFE_DELETE(m_PauseGame);
	SAFE_DELETE(m_Home);
}

bool CFrontendManager::Start()
{
	m_MainMenu = new CMainMenu();
	m_NewGame = new CNewGame();
	m_Garage = new CGarage();
	m_PostGame = new CPostGame();
	m_PauseGame = new CPauseGame();
	m_Home = new CHome();

	m_curScreen = m_MainMenu;
	m_iState = MAIN_MENU;

	return true;
}

void CFrontendManager::Update()
{
	if (m_iState == NO_STATE || m_iState == IN_GAME || m_iState == PRE_GAME)
		return;

	// special cases: if IN_GAME or PREGAME and player does something to exit this state.
	// must use setState(STATE) manually from outside. 
	// Then this function will set curScreen accordingly.
	if (m_iState == PAUSE && !m_curScreen) {
		m_curScreen = m_PauseGame;
		return;
	}
	if (m_iState == POST_GAME && !m_curScreen) {
		m_curScreen = m_PostGame;
		return;
	}

	// just being cautious here:
	if (!m_curScreen) return;

	// If we must goto another screen, call transition function.
	// Else process message for current screen
	if (m_curScreen->getGotoScreen() != 0)
		Transition();
	else HandleMessages();
}

void CFrontendManager::DoMessageHandle(ITaskMessage *cMsg)
{
	if (!cMsg || !m_curScreen) return;

	CFrontendMessage* cFMsg = (CFrontendMessage*)cMsg;
	m_curScreen->processInput(cFMsg->Key());

}

int CFrontendManager::processInput(int c)
{
	m_curScreen->processInput(c);	
	return OK;
}

int CFrontendManager::Transition()
{
	int next_screen = m_curScreen->getGotoScreen();
	// Ramit, uncomment this when you have it implemented
	//m_curScreen->resetGotoScreen();

	switch(next_screen) {
	case MAIN_MENU: 
		m_curScreen = m_MainMenu; m_iState = MAIN_MENU; break;
	case NEW_GAME:
		m_curScreen = m_NewGame; m_iState = NEW_GAME; break;
	case GARAGE:
		m_curScreen = m_Garage; m_iState = GARAGE; break;
	case POST_GAME:
		m_curScreen = m_PostGame; m_iState = POST_GAME; break;
	case PAUSE:
		m_curScreen = m_PauseGame; m_iState = PAUSE; break;
	case HOME:
		m_curScreen = m_Home; m_iState = HOME; break;
	case OPTIONS:
	case BESTTIMES:
	case HELP:
	case CREDITS:
	case QUIT:
	case PERFORMANCE:
	case DEALERSHIP:
#ifdef _DEBUG
		CLog::GetLog().Write(LOG_MISC, "case %i not implemented in CFrontendManager::Transition()", 
			next_screen);
#endif
		break;
	case PRE_GAME:
		m_curScreen = NULL; m_iState = PRE_GAME;
		CAppStateManager::GetAppMan().SetAppState(STATE_PRE_GAME);
		break;
	case IN_GAME:
		m_curScreen = NULL; m_iState = IN_GAME; 
		CAppStateManager::GetAppMan().SetAppState(STATE_IN_GAME);
		break;
	default:
#ifdef _DEBUG
		CLog::GetLog().Write(LOG_MISC, "case %i out of range in CFrontendManager::Transition()",
			next_screen);
#endif
	}

	return OK;
}

// careful, this function does not synchronize state with curWidget
int CFrontendManager::setState(int state)
{
	if (state < NO_STATE || state > MAX_STATES)
		return INDEX_OUT_OF_RANGE;
	m_iState = state;
}

CScreen* CFrontendManager::Screen(int which)
{
	switch(which) {
	case MAIN_MENU:
		return m_MainMenu;
	case NEW_GAME:
		return m_NewGame;
	case GARAGE:
		return m_Garage;
	case POST_GAME:
		return m_PostGame;
	case PAUSE:
		return m_PauseGame;
	case HOME:
		return m_Home;
	// not yet implemented:
	case OPTIONS:
	case BESTTIMES:
	case HELP:
	case CREDITS:
	case QUIT:
	case PERFORMANCE:
	case DEALERSHIP:
	default:
		return NULL;
	}
}