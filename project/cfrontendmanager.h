#ifndef CFRONTENDMANAGER_H
#define CFRONTENDMANAGER_H

#include "task.h"
#include "cscreens.h"

class CFrontendManager : public ITask {
public:
	CFrontendManager();
	~CFrontendManager();

	int Transition();
	int processInput(int c);

	// virtual inherited functions
	bool Start();
	void Update();
	//void OnSuspend(){};
	//void OnResume(){};
	//void Stop(){};

	// access methods
	int State() {return m_iState;}
	CScreen* CurScreen() {return m_curScreen;}
	CScreen* Screen(int which); // gets screen corresponding to which
	int setState(int state); // careful, this function does not synchronize state with curWidget

	// For use as Singleton:
	static CFrontendManager & GetFrontendManager();
    static CFrontendManager * GetFrontendManagerPtr();

protected:
	// more virtual inherited functions
	void DoMessageHandle( ITaskMessage *cMsg );

	CScreen* m_curScreen;
	int m_iState;

	// for use as Singleton:
	static CFrontendManager* m_pkFrontendManager;

private:
	CMainMenu* m_MainMenu;
	CNewGame* m_NewGame;
	CGarage* m_Garage;
	CPostGame* m_PostGame;
	CPauseGame* m_PauseGame;
	CHome* m_Home;
    CQuit* m_Quit;
    COptions * m_Options;
    CPreGame * m_PreGame;
    CBestTimes * m_BestTimes;
	CHelp * m_Help;
	CCredits * m_Credits;
	CPerformance * m_Performance;
	CDealership * m_Dealership;
};

#endif