#include "cscreens.h"
#include "input.h"

#include "aimessage.h"
#include "cfrontendmanager.h"

// J's edit
#include "renderer.h"
#include "appstate.h"

// main input processor maybe overrided in some screens
//$$$TODO options screen needs a custom one
//$$$TODO garage needs a custom one

void CScreen::processInput(int key)
{
  switch(key)
  {
  case GAME_TAB:
  case GAME_RIGHT:
  case GAME_DOWN:
    DeSelectWidget(selectedScreeni); //J's add
    selectedScreeni++;
    if (selectedScreeni > maxScreeni)
        selectedScreeni =maxScreeni;

    SelectWidget(selectedScreeni); //J's add
    break;
  case GAME_LEFT:
  case GAME_UP:
    DeSelectWidget(selectedScreeni); //J's add
    selectedScreeni--;
    if (selectedScreeni < 0)
      selectedScreeni = 0;
    SelectWidget(selectedScreeni); //J's add
    break;  
  case GAME_RETURN:
  case GAME_NUMPADENTER:
    gotoScreen = screenOrder[selectedScreeni];
    if (screenOrder[selectedScreeni] == EXIT_GAME)  // after QUIT screen
        CKernel::GetKernel().KillAllTasks();  //exit the game 
  }
}

void CHome::processInput(int key)
{
  switch(key)
  {
  case GAME_TAB:
  case GAME_RIGHT:
  case GAME_DOWN:
    DeSelectWidget(selectedScreeni); //J's add
    selectedScreeni++;
    if (selectedScreeni > maxScreeni)
        selectedScreeni =maxScreeni;

    SelectWidget(selectedScreeni); //J's add
    break;
  case GAME_LEFT:
  case GAME_UP:
    DeSelectWidget(selectedScreeni); //J's add
    selectedScreeni--;
    if (selectedScreeni < 0)
      selectedScreeni = 0;
    SelectWidget(selectedScreeni); //J's add
    break;  
  case GAME_RETURN:
  case GAME_NUMPADENTER:
    gotoScreen = screenOrder[selectedScreeni];
    switch (gotoScreen)
    {
        // means we're ready to race
    case PRE_GAME:
        // send a message off to the AI with the proper game parameters
        //$$$TEMP LOAD DEFAULTS FOR NOW
        CFrontendManager::GetFrontendManager().SetRaceName("map_final");
        CFrontendManager::GetFrontendManager().SetPVName("acuransx");
        CKernel::GetKernel().DeliverMessage(new CAIMessage(CFrontendManager::GetFrontendManager().GetRaceName(),
                                                           CFrontendManager::GetFrontendManager().GetPVName(),"game"), AI_TASK);
        CAppStateManager::GetAppMan().SetAppState(STATE_IN_GAME);
        break;
    }
  }
}


// just attempt to auto arrange the widgets on screen
void CScreen::AutoArrangeWidgets(WidgetArrangment eWA )
{
    int iNumWidgets = m_vecWidgets.size();
    float i=0.0f;
    for (vector <CWidget *>::iterator it=m_vecWidgets.begin();  it!=m_vecWidgets.end(); it++ ) {
        // set the first one as selected
        if (it == m_vecWidgets.begin())  (*it)->onSelected();

        // arrenge them accordingly
        switch (eWA)  {
        case WA_LEFT_TOP_VERT:
            (*it)->setX(-1.0f);
            (*it)->setY(-1.0f+(i/(float)iNumWidgets));
            i+=1.0f;
            break;
        case WA_BOTTOM_HORIZ:
            (*it)->setX(-1.0f+(i/(float)iNumWidgets));
            (*it)->setY(1.0f - (*it)->getHeight()*2.0f);
            i+=1.0f;
            break;

        default:
            break;
        }
    }
}

// generic draw function
//   draws all widgets using their display parameters
void CScreen::draw()  {
    // draw all the widgets
    for (vector <CWidget *>::iterator it=m_vecWidgets.begin(); it!=m_vecWidgets.end(); it++ ) {
        (*it)->draw();
    }
}

bool CScreen::SelectWidget(int iWidgetVecIndex)
{
    if (iWidgetVecIndex <= m_vecWidgets.size())  {
        m_vecWidgets[iWidgetVecIndex]->onSelected();  //J's add
    }
    else
        return false;
    return true;
}


bool CScreen::DeSelectWidget(int iWidgetVecIndex)
{
    if (iWidgetVecIndex <= m_vecWidgets.size())  {
        m_vecWidgets[iWidgetVecIndex]->onDeSelected();  //J's add
    }
    else
        return false;
    return true;
}


CMainMenu::CMainMenu()
{
  newGame = new CButton();
  newGame->setText("New Game");
  newGame->setX(0.0f);
  newGame->setY(-1.0f);

  options = new CButton();
  options->setText("Options");
  options->setX(-0.1f);
  options->setY(-0.7f);

  bestTimes = new CButton();
  bestTimes->setText("Best Times");
  bestTimes->setX(-0.2f);
  bestTimes->setY(-0.5f);

  help = new CButton();
  help->setText("Help");
  help->setX(-0.3f);
  help->setY(-0.2f);

  credits = new CButton();
  credits->setText("Credits");
  credits->setX(-0.4f);
  credits->setY(0.1f);

  quit = new CButton();
  quit->setText("Quit");
  quit->setX(-0.5f);
  quit->setY(0.4f);

  int tempOrder[]={NEW_GAME, OPTIONS, BESTTIMES, HELP, CREDITS, QUIT};
  memcpy(screenOrder, tempOrder, sizeof(tempOrder));
  maxScreeni = 5;

  // put the widgets into this vector so I can just iterate through them
  m_vecWidgets.push_back( newGame );
  m_vecWidgets.push_back( options );
  m_vecWidgets.push_back( bestTimes );
  m_vecWidgets.push_back( help );
  m_vecWidgets.push_back( credits );
  m_vecWidgets.push_back( quit );

  AutoArrangeWidgets();
}


CMainMenu::~CMainMenu()
{

//do something here
}

void CMainMenu::draw()
{
    //CRenderer::GetRendererPtr()->DrawScreenText(0,0,D3DCOLOR_ARGB(255,255,255,255), "MAIN MENU");
    //$$$TEMP just draw this for now
    CRenderer::GetRendererPtr()->Draw3DTextScaled(-0.7,-0.7,0,D3DCOLOR_ARGB(100,255,255,255), "MAIN\nMENU", 0.3, 0.3);
    char tmp[100];
    sprintf(tmp, "sel screen: %d", selectedScreeni);  
    CRenderer::GetRendererPtr()->Draw3DTextScaled(-1.0,0.5,0,D3DCOLOR_ARGB(200,0,200,255), tmp, 0.05, 0.05);


    static int iFade = 255, iDir = -1;
    CRenderer::GetRendererPtr()->Draw3DTextScaled(-0.5, 0.8f,0,D3DCOLOR_ARGB(iFade,200,0,10), "Press F11 to exit the game ESC is remapped for front end -J", 0.03, 0.03);
    CRenderer::GetRendererPtr()->Draw3DTextScaled(-0.5, 0.9f,0,D3DCOLOR_ARGB(iFade,200,10,0), "Isn't this fading text annoying?", 0.03, 0.03);
    iFade += iDir*5;
    if (iFade <= 0 || iFade >= 255)  iDir *= -1;

    //Jay here's your stub function to draw the mainmenu
    /*
    newGame->draw();
    options->draw();
    bestTimes->draw();
    help->draw();
    credits->draw();
    quit->draw();
    */

    // draw all the widgets
    for (vector <CWidget *>::iterator it=m_vecWidgets.begin(); it!=m_vecWidgets.end(); it++ ) {
        (*it)->draw();
    }
}


//New Game Screen
CNewGame::CNewGame()
{
  ok = new CButton();
  ok->setText("Ok");
  ok->setX(0.0f);
  ok->setY(0.0f);

  cancel = new CButton();
  cancel->setText("Cancel");
  cancel->setX(0.0f);
  cancel->setY(0.2f);


  name = new CTextField();


  instructions = new CLabel();
  instructions->setText("Please Enter Name:");
  instructions->setX(0.0f);
  instructions->setY(0.3f);

  int tempOrder[]={GARAGE, MAIN_MENU};
  memcpy(screenOrder, tempOrder, sizeof(tempOrder));
  maxScreeni = 1;

  // put the widgets into this vector so I can just iterate through them
  m_vecWidgets.push_back( ok );
  m_vecWidgets.push_back( cancel );
  m_vecWidgets.push_back( name );
  AutoArrangeWidgets();
  
  m_vecWidgets.push_back( instructions );
}

CNewGame::~CNewGame()
{
  //Do something here
}

void CNewGame::draw()
{
  //$$$TEMP just draw this for now
  CRenderer::GetRendererPtr()->Draw3DTextScaled(-0.7,-0.7,0,D3DCOLOR_ARGB(100,255,255,255), "NEW\nGAME", 0.3, 0.3);
  char tmp[100];
  sprintf(tmp, "sel screen: %d", selectedScreeni);  
  CRenderer::GetRendererPtr()->Draw3DTextScaled(-1.0,0.5,0,D3DCOLOR_ARGB(200,0,200,255), tmp, 0.05, 0.05);

  //Draw Screen stuff
  /*ok->draw();
  cancel->draw();
  name->draw();
  instructions->draw();
  */
  // draw all the widgets
  for (vector <CWidget *>::iterator it=m_vecWidgets.begin(); it!=m_vecWidgets.end(); it++ ) {
      (*it)->draw();
  }
}

/*void CNewGame::processInput(int key)
{CLog::GetLog().Write(LOG_DEBUGOVERLAY, 114, "in BLAH screen");
  switch(key)
  {//TODO Deal With ASCII Chars for TEXTFIELD!!!
  case GAME_TAB:
  case GAME_RIGHT:
    selectedScreeni++;
    if (selectedScreeni > maxScreeni)
    selectedScreeni =0;
    break;
  case GAME_LEFT:
    selectedScreeni--;
    if (selectedScreeni < 0)
      selectedScreeni = maxScreeni;
    break;
  case GAME_RETURN:
  case GAME_NUMPADENTER:
    gotoScreen = screenOrder[selectedScreeni];
  }
}
*/
CGarage::CGarage()
{
  select = new CButton();
  select->setText("Select");
  cancel = new CButton();
  cancel->setText("Cancel");
  instructions = new CLabel();
  instructions->setText("Change Cars By Pressing Left/Right");
  int tempOrder[]={HOME, MAIN_MENU};
  memcpy(screenOrder, tempOrder, sizeof(tempOrder));
  maxScreeni = 1;
  m_vecWidgets.push_back( select );
  m_vecWidgets.push_back( cancel );
  m_vecWidgets.push_back( instructions );
  AutoArrangeWidgets(WA_BOTTOM_HORIZ);
}

CGarage::~CGarage()
{
  //Do something here
}

void CGarage::draw()
{
  //$$$TEMP just draw this for now
  CRenderer::GetRendererPtr()->Draw3DTextScaled(-0.7,-0.7,0,D3DCOLOR_ARGB(100,255,255,255), "GARAGE", 0.3, 0.3);
  char tmp[100];
  sprintf(tmp, "sel screen: %d", selectedScreeni);  
  CRenderer::GetRendererPtr()->Draw3DTextScaled(-1.0,0.5,0,D3DCOLOR_ARGB(200,0,200,255), tmp, 0.05, 0.05);

  /*  
  select->draw();
  cancel->draw();
  instructions->draw();
  */
  // draw all the widgets
  for (vector <CWidget *>::iterator it=m_vecWidgets.begin(); it!=m_vecWidgets.end(); it++ ) {
      (*it)->draw();
  }
}

/*
void CGarage::processInput(int key)
{
  switch(key)
  {
  case GAME_TAB:
  case GAME_DOWN:
    selectedScreeni++;
    if (selectedScreeni > maxScreeni)
    selectedScreeni =0;
    break;
  case GAME_UP:
    selectedScreeni--;
    if (selectedScreeni < 0)
      selectedScreeni = maxScreeni;
    break;
  case GAME_LEFT:
  case GAME_RIGHT:
//TODO CHANGE 3D Widget CAR  and SELECT CAR IF ENTER
    break;
  case GAME_RETURN:
  case GAME_NUMPADENTER:
    gotoScreen = screenOrder[selectedScreeni];
  }
}
*/

//PostGame Game Screen
CPostGame::CPostGame()
{
  onward = new CButton();
  onward->setText("Onward!");
  restartRace = new CButton();
  restartRace->setText("Restart Race");
  mainMenu = new CButton();
  mainMenu->setText("Back to Main Menu");

  //labels
  congrats = new CLabel();
  congrats->setText("Congratulations! You Rocked the House");
  placement = new CLabel();;
  placement->setText("You Finished the Race in Some Place");
  winnings = new CLabel();
  winnings->setText("Good For you buddy, You won a Gazillion Dollars");
  int tempOrder[]={HOME, PRE_GAME, MAIN_MENU};
  memcpy(screenOrder, tempOrder, sizeof(tempOrder));
  maxScreeni = 2;

  // put the widgets into this vector so I can just iterate through them
  m_vecWidgets.push_back( onward );
  m_vecWidgets.push_back( restartRace );
  m_vecWidgets.push_back( congrats );
  m_vecWidgets.push_back( placement );
  m_vecWidgets.push_back( winnings );
  AutoArrangeWidgets();

}

CPostGame::~CPostGame()
{
  //Do something here
}

void CPostGame::draw()
{
//$$$TEMP just draw this for now
CRenderer::GetRendererPtr()->Draw3DTextScaled(-0.7,-0.7,0,D3DCOLOR_ARGB(100,255,255,255), "POST\nGAME", 0.3, 0.3);  
char tmp[100];
  sprintf(tmp, "sel screen: %d", selectedScreeni);  
  CRenderer::GetRendererPtr()->Draw3DTextScaled(-1.0,0.5,0,D3DCOLOR_ARGB(200,0,200,255), tmp, 0.05, 0.05);

  onward->draw();
  restartRace->draw();
  mainMenu->draw();
  congrats->draw();
  placement->draw();

}

//Pause Game Screen
CPauseGame::CPauseGame()
{
  resume = new CButton();
  resume->setText("Resume Game");
  restartRace = new CButton();
  restartRace->setText("Restart Race");
  mainMenu = new CButton();
  mainMenu->setText("Back to Main Menu");

  //labels
  instructions = new CLabel();
  instructions->setText("Pause Menu");
  int tempOrder[]={IN_GAME, PRE_GAME, MAIN_MENU};
  memcpy(screenOrder, tempOrder, sizeof(tempOrder));
  maxScreeni = 2;

  m_vecWidgets.push_back( resume );
  m_vecWidgets.push_back( restartRace );
  m_vecWidgets.push_back( mainMenu );
  m_vecWidgets.push_back( instructions );
  AutoArrangeWidgets();
}


CPauseGame::~CPauseGame()
{
  //Do something here
}

void CPauseGame::draw()
{
  //$$$TEMP just draw this for now
  CRenderer::GetRendererPtr()->Draw3DTextScaled(-0.7,-0.7,0,D3DCOLOR_ARGB(100,255,255,255), "PAUSE", 0.3, 0.3); 
  char tmp[100];
  sprintf(tmp, "sel screen: %d", selectedScreeni);  
  CRenderer::GetRendererPtr()->Draw3DTextScaled(-1.0,0.5,0,D3DCOLOR_ARGB(200,0,200,255), tmp, 0.05, 0.05);

  resume->draw();
  restartRace->draw();
  mainMenu->draw();
  instructions->draw();

}

//HOME SCREEN
CHome::CHome()
{
  race = new CButton();
  race->setText("RACE!");
  performanceUpgrade = new CButton();
  performanceUpgrade->setText("Tune Your Ride");
  dealership = new CButton();
  dealership->setText("Dealership");
  garage = new CButton();
  garage->setText("Garage");
  mainMenu = new CButton();
  mainMenu->setText("Back to Main Menu");

  //labels
  home = new CLabel();
  home->setText("Home");
  int tempOrder[]={PRE_GAME,PERFORMANCE, GARAGE, DEALERSHIP, MAIN_MENU};
  memcpy(screenOrder, tempOrder, sizeof(tempOrder));
  maxScreeni = 4;

  // put the widgets into this vector so I can just iterate through them
  m_vecWidgets.push_back( race );
  m_vecWidgets.push_back( performanceUpgrade );
  m_vecWidgets.push_back( dealership );
  m_vecWidgets.push_back( garage );
  m_vecWidgets.push_back( mainMenu );
  AutoArrangeWidgets();

  m_vecWidgets.push_back( home );
}


CHome::~CHome()
{
  //Do something here
}

void CHome::draw()
{
  //$$$TEMP just draw this for now
  CRenderer::GetRendererPtr()->Draw3DTextScaled(-0.7,-0.7,0,D3DCOLOR_ARGB(100,255,255,255), "HOME", 0.3, 0.3);
  char tmp[100];
  sprintf(tmp, "sel screen: %d", selectedScreeni);  
  CRenderer::GetRendererPtr()->Draw3DTextScaled(-1.0,0.5,0,D3DCOLOR_ARGB(200,0,200,255), tmp, 0.05, 0.05);

  race->draw();
  performanceUpgrade->draw();
  garage->draw();
  dealership->draw();
  mainMenu->draw();
}


//Quit Screen SCREEN
CQuit::CQuit()
{
  quit = new CButton();
  quit->setText("Quit");
  quit->setX(0.0f);
  quit->setY(0.5f);


  mainMenu = new CButton();
  mainMenu->setText("Back to Main Menu");
  mainMenu->setX(-0.5f);
  mainMenu->setY(0.0f);

  // exit game isn't actually a screen, its so we know when to exit the game after the quit screen
  int tempOrder[]={MAIN_MENU, EXIT_GAME};  
  memcpy(screenOrder, tempOrder, sizeof(tempOrder));
  maxScreeni = 1;

  m_vecWidgets.push_back( mainMenu );
  m_vecWidgets.push_back( quit );
  AutoArrangeWidgets();
}


CQuit::~CQuit()
{
  //Do something here
}

void CQuit::draw()
{
  //$$$TEMP just draw this for now
  CRenderer::GetRendererPtr()->Draw3DTextScaled(-0.7,-0.7,0,D3DCOLOR_ARGB(100,255,255,255), "QUIT", 0.3, 0.3);
  char tmp[100];
  sprintf(tmp, "sel screen: %d", selectedScreeni);  
  CRenderer::GetRendererPtr()->Draw3DTextScaled(-1.0,0.5,0,D3DCOLOR_ARGB(200,0,200,255), tmp, 0.05, 0.05);

  //quit->draw();
  //mainMenu->draw();
  // draw all the widgets
  for (vector <CWidget *>::iterator it=m_vecWidgets.begin(); it!=m_vecWidgets.end(); it++ ) {
      (*it)->draw();
  }
}

//PreGame Game Screen
CPreGame::CPreGame()
{
    CAppStateManager::GetAppMan().SetAppState(STATE_PRE_GAME);
  onward = new CButton();
  onward->setText("Onward!");
  mainMenu = new CButton();
  mainMenu->setText("Back to Main Menu");

  //labels
  ready = new CLabel();
  ready->setText("Get Ready to Race");
  int tempOrder[]={IN_GAME, MAIN_MENU};
  memcpy(screenOrder, tempOrder, sizeof(tempOrder));
  maxScreeni = 1;

  m_vecWidgets.push_back( onward );
  m_vecWidgets.push_back( mainMenu );
  AutoArrangeWidgets();

  m_vecWidgets.push_back( ready );

}

CPreGame::~CPreGame()
{
  //Do something here
}

void CPreGame::draw()
{
//$$$TEMP just draw this for now
CRenderer::GetRendererPtr()->Draw3DTextScaled(-0.7,-0.7,0,D3DCOLOR_ARGB(100,255,255,255), "PRE\nGAME", 0.3, 0.3);

  onward->draw();
  mainMenu->draw();
  ready->draw();

}

//Option Screen
COptions::COptions()
{
  option1 = new CButton();
  option1->setText("option1");
  option2 = new CButton();
  option2->setText("option2");
  option3 = new CButton();
  option3->setText("option3");
  mainMenu = new CButton();
  mainMenu->setText("Back to Main Menu");

  //labels
  instructions = new CLabel();
  instructions->setText("Options");
  int tempOrder[]={MAIN_MENU};
  memcpy(screenOrder, tempOrder, sizeof(tempOrder));
  maxScreeni = 0;

  //TODO ADD OPTIONS
  m_vecWidgets.push_back( mainMenu );
  m_vecWidgets.push_back( option1 );
  m_vecWidgets.push_back( option2 );
  m_vecWidgets.push_back( option3 );
  AutoArrangeWidgets();
  m_vecWidgets.push_back( instructions );
}

//$$$NOTE OPTIONS SCREEN NEEDS SPECIAL INPUT HANDLER

COptions::~COptions()
{
  //Do something here
}

void COptions::draw()
{
  //$$$TEMP just draw this for now
  CRenderer::GetRendererPtr()->Draw3DTextScaled(-0.7,-0.7,0,D3DCOLOR_ARGB(100,255,255,255), "OPTIONS", 0.3, 0.3);

  option1->draw();
  option2->draw();
  option3->draw();
  mainMenu->draw();
  instructions->draw();

}

//Best Times Screen
CBestTimes::CBestTimes()
{
  mainMenu = new CButton();
  mainMenu->setText("Back to Main Menu");

  //labels
  bestTime = new CLabel();
  bestTime->setText("blah blah blah");
  int tempOrder[]={MAIN_MENU};
  memcpy(screenOrder, tempOrder, sizeof(tempOrder));
  maxScreeni = 0;

  m_vecWidgets.push_back( mainMenu );
  AutoArrangeWidgets();

  m_vecWidgets.push_back( bestTime );

}

CBestTimes::~CBestTimes()
{
  //Do something here
}

void CBestTimes::draw()
{
//$$$TEMP just draw this for now
CRenderer::GetRendererPtr()->Draw3DTextScaled(-0.7,-0.7,0,D3DCOLOR_ARGB(100,255,255,255), "BEST\nTIMES", 0.3, 0.3);
  mainMenu->draw();
  bestTime->draw();

}

//Help Screen
CHelp::CHelp()
{
  mainMenu = new CButton();
  mainMenu->setText("Back to Main Menu");

  //labels
  help = new CLabel();
  help->setText("blah blah blah");
  int tempOrder[]={MAIN_MENU};
  memcpy(screenOrder, tempOrder, sizeof(tempOrder));
  maxScreeni = 0;

  m_vecWidgets.push_back( mainMenu );
  AutoArrangeWidgets();

  m_vecWidgets.push_back( help );

}

CHelp::~CHelp()
{
  //Do something here
}

void CHelp::draw()
{
//$$$TEMP just draw this for now
CRenderer::GetRendererPtr()->Draw3DTextScaled(-0.7,-0.7,0,D3DCOLOR_ARGB(100,255,255,255), "HELP", 0.3, 0.3);
  mainMenu->draw();
  help->draw();

}

//Help Screen
CCredits::CCredits()
{
  mainMenu = new CButton();
  mainMenu->setText("Back to Main Menu");

  //labels
  credits = new CLabel();
  credits->setText("blah blah blah");
  int tempOrder[]={MAIN_MENU};
  memcpy(screenOrder, tempOrder, sizeof(tempOrder));
  maxScreeni = 0;

  m_vecWidgets.push_back( mainMenu );
  AutoArrangeWidgets();
}

CCredits::~CCredits()
{
  //Do something here
}

void CCredits::draw()
{
//$$$TEMP just draw this for now
CRenderer::GetRendererPtr()->Draw3DTextScaled(-0.7,-0.7,0,D3DCOLOR_ARGB(100,255,255,255), "CREDITS", 0.3, 0.3);
  mainMenu->draw();
  credits->draw();

}

//Performance Upgrade Screen
CPerformance::CPerformance()
{
  tireUp = new CButton();
  tireUp->setText("Upgrade Tires");
  engineUp = new CButton();
  engineUp->setText("Upgrade Engine");
  weightRed = new CButton();
  weightRed->setText("Weight Reduction");
  home = new CButton();
  home->setText("Back to Home");

  //labels
  instructions = new CLabel();
  instructions->setText("Performance");
  int tempOrder[]={MAIN_MENU};
  memcpy(screenOrder, tempOrder, sizeof(tempOrder));
  maxScreeni = 0;
  //TODO ADD CURRENT LEVELS OF TUNE

  m_vecWidgets.push_back( tireUp );
  m_vecWidgets.push_back( engineUp );
  m_vecWidgets.push_back( weightRed );
  m_vecWidgets.push_back( home );
  AutoArrangeWidgets();

  m_vecWidgets.push_back( instructions );
}


CPerformance::~CPerformance()
{
  //Do something here
}

void CPerformance::draw()
{
  //$$$TEMP just draw this for now
  CRenderer::GetRendererPtr()->Draw3DTextScaled(-0.7,-0.7,0,D3DCOLOR_ARGB(100,255,255,255), "PERFORMANCE", 0.3, 0.3);

  tireUp->draw();
  engineUp->draw();
  weightRed->draw();
  home->draw();
  instructions->draw();

}


CDealership::CDealership()
{
  select = new CButton();
  select->setText("Purchase");
  cancel = new CButton();
  cancel->setText("Cancel");
  instructions = new CLabel();
  instructions->setText("Change Cars By Pressing Left/Right");
  int tempOrder[]={HOME, MAIN_MENU};
  memcpy(screenOrder, tempOrder, sizeof(tempOrder));
  maxScreeni = 1;

  m_vecWidgets.push_back( select );
  m_vecWidgets.push_back( cancel );
  AutoArrangeWidgets();

  m_vecWidgets.push_back( instructions );
}

CDealership::~CDealership()
{
  //Do something here
}

void CDealership::draw()
{
  //$$$TEMP just draw this for now
  CRenderer::GetRendererPtr()->Draw3DTextScaled(-0.7,-0.7,0,D3DCOLOR_ARGB(100,255,255,255), "Dealership", 0.3, 0.3);

  select->draw();
  cancel->draw();
  instructions->draw();
}


/*
void CDealership::processInput(int key)
{
  switch(key)
  {
  case GAME_TAB:
  case GAME_RIGHT:
  case GAME_DOWN:
    selectedScreeni++;
    if (selectedScreeni > maxScreeni)
    selectedScreeni = maxScreeni;  //do not wrap
    break;
  case GAME_LEFT:
  case GAME_UP:
    selectedScreeni--;
    if (selectedScreeni < 0)
      selectedScreeni = 0;  //do not wrap
    break;
  case GAME_RETURN:
  case GAME_NUMPADENTER:
    gotoScreen = screenOrder[selectedScreeni];
    if (screenOrder[gotoScreen] == QUIT)  // QUIT screen
        CKernel::GetKernel().KillAllTasks();  //exit the game 
  }
}
*/