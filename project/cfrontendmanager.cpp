#include "cfrontendmanager.h"
#include "cfrontendmessage.h"
#include "log.h"
#include "appstate.h"
#include "kernel.h"

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
    m_PreGame = NULL;
    m_Options = NULL;
	m_PostGame = NULL;
	m_PauseGame = NULL;
	m_Home = NULL;
    m_Quit = NULL;
    m_BestTimes = NULL;
	m_Help=NULL;
	m_Credits=NULL;
	m_Performance=NULL;
	m_Dealership=NULL;

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
    SAFE_DELETE(m_PreGame);
    SAFE_DELETE(m_Options);
	SAFE_DELETE(m_Home);
    SAFE_DELETE(m_Quit);
    SAFE_DELETE(m_BestTimes);
    SAFE_DELETE(m_Help);
    SAFE_DELETE(m_Credits);
    SAFE_DELETE(m_Performance);
    SAFE_DELETE(m_Dealership);
}

bool CFrontendManager::Start()
{
	m_MainMenu = new CMainMenu();
	m_NewGame = new CNewGame();
	m_Garage = new CGarage();
    m_PreGame = new CPreGame();
	m_PostGame = new CPostGame();
	m_PauseGame = new CPauseGame();
    m_Options = new COptions();
    m_Home = new CHome();
    m_Quit = new CQuit();
    m_BestTimes = new CBestTimes();
	m_Help = new CHelp();
    m_Credits= new CCredits();
	m_Performance= new CPerformance();
	m_Dealership= new CDealership();


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
	m_curScreen->resetGotoScreen();

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
        m_curScreen = m_Options; m_iState = OPTIONS; break;
	case BESTTIMES:
        m_curScreen = m_BestTimes; m_iState = BESTTIMES; break;
	case HELP:
      m_curScreen = m_Help; m_iState = HELP; break;
	case CREDITS:
      m_curScreen = m_Credits; m_iState = CREDITS; break;
	case QUIT:
        m_curScreen = m_Quit; m_iState = QUIT; 
        break;
	case PERFORMANCE:
      m_curScreen = m_Performance; m_iState = PERFORMANCE; break;
	case DEALERSHIP:
      m_curScreen = m_Dealership; m_iState = DEALERSHIP; break;
#ifdef _DEBUG
		CLog::GetLog().Write(LOG_MISC, "case %i not implemented in CFrontendManager::Transition()", 
			next_screen);
#endif
		break;
	case PRE_GAME:
		m_curScreen = m_PreGame/*NULL*/; m_iState = PRE_GAME; //or Change ot pregame
		CAppStateManager::GetAppMan().SetAppState(STATE_PRE_GAME);
		break;
	case IN_GAME:
		m_curScreen = NULL; m_iState = IN_GAME; 
		CAppStateManager::GetAppMan().SetAppState(STATE_IN_GAME);
		break;
	default:
        #ifdef _DEBUG
		CLog::GetLog().Write(LOG_MISC, "case %i out of range in CFrontendManager::Transition()",next_screen);
        #endif
        break;
	}

	return OK;
}

// careful, this function does not synchronize state with curWidget
int CFrontendManager::setState(int state)
{
	if (state < NO_STATE || state > MAX_STATES)
		return INDEX_OUT_OF_RANGE;
	m_iState = state;
    return OK;
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
	case OPTIONS:
        return m_Options;
	case BESTTIMES:
        return m_BestTimes;
	case HELP:
        return m_Help;
	case CREDITS:
        return m_Credits;
	case QUIT:
        return m_Quit;
	case PERFORMANCE:
        return m_Performance;
	case DEALERSHIP:
        return m_Dealership;
    case PRE_GAME:
        return m_PreGame;
	default:
		return NULL;
	}
}