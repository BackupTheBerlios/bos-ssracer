#include "cscreens.h"
#include "input.h"

CMainMenu::CMainMenu()
{
  
  newGame = new CButton();
  newGame->setText("New Game");
  options = new CButton();
  options->setText("Options");
  bestTimes = new CButton();
  bestTimes->setText("Best Times");
  help = new CButton();
  help->setText("Help");
  credits = new CButton();
  credits->setText("Credits");
  quit = new CButton();
  quit->setText("Quit");
  int tempOrder[]={NEW_GAME, OPTIONS, BESTTIMES, HELP, CREDITS, QUIT};
  memcpy(screenOrder, tempOrder, sizeof(tempOrder));
  maxScreeni = 5;
}


CMainMenu::~CMainMenu()
{

//do something here
}

void CMainMenu::draw()

{
//Jay here's your stub function to draw the mainmenu
  newGame->draw();
  options->draw();
  bestTimes->draw();
  help->draw();
  credits->draw();
  quit->draw();
}

void CMainMenu::processInput(int key)
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
  case GAME_RETURN:
  case GAME_NUMPADENTER:
    gotoScreen = selectedScreeni;
  }
}

//New Game Screen
CNewGame::CNewGame()
{
  ok = new CButton();
  ok->setText("Ok");
  cancel = new CButton();
  cancel->setText("Cancel");
  name = new CTextField();
  instructions = new CLabel();
  instructions->setText("Please Enter Name:");
  int tempOrder[]={GARAGE, MAIN_MENU};
  memcpy(screenOrder, tempOrder, sizeof(tempOrder));
  maxScreeni = 1;

}

CNewGame::~CNewGame()
{
  //Do something here
}

void CNewGame::draw()
{

  //Draw Screen stuff
  ok->draw();
  cancel->draw();
  name->draw();
  instructions->draw();
}

void CNewGame::processInput(int key)
{
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
    gotoScreen = selectedScreeni;
  }
}

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
}

CGarage::~CGarage()
{
  //Do something here
}

void CGarage::draw()
{
  select->draw();
  cancel->draw();
  instructions->draw();
}

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
    gotoScreen = selectedScreeni;
  }
}

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
  int tempOrder[]={HOME, IN_GAME, MAIN_MENU};
  memcpy(screenOrder, tempOrder, sizeof(tempOrder));
  maxScreeni = 2;

}

CPostGame::~CPostGame()
{
  //Do something here
}

void CPostGame::draw()
{
  onward->draw();
  restartRace->draw();
  mainMenu->draw();
  congrats->draw();
  placement->draw();

}

void CPostGame::processInput(int key)
{
  switch(key)
  {
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
  case GAME_UP:
  case GAME_DOWN:
    break;
  case GAME_RETURN:
  case GAME_NUMPADENTER:
    gotoScreen = selectedScreeni;
  }
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
  int tempOrder[]={IN_GAME, IN_GAME, MAIN_MENU};
  memcpy(screenOrder, tempOrder, sizeof(tempOrder));
  maxScreeni = 2;
}


CPauseGame::~CPauseGame()
{
  //Do something here
}

void CPauseGame::draw()
{
  resume->draw();
  restartRace->draw();
  mainMenu->draw();
  instructions->draw();

}

void CPauseGame::processInput(int key)
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
    break;
  case GAME_RETURN:
  case GAME_NUMPADENTER:
    gotoScreen = selectedScreeni;
    //TODO DEAL WITH RESTART OR RESUME DEPENDENT ON CHOICE
  }
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
  int tempOrder[]={IN_GAME,PERFORMANCE, GARAGE, DEALERSHIP, MAIN_MENU};
  memcpy(screenOrder, tempOrder, sizeof(tempOrder));
  maxScreeni = 4;
}


CHome::~CHome()
{
  //Do something here
}

void CHome::draw()
{
  race->draw();
  performanceUpgrade->draw();
  garage->draw();
  dealership->draw();
  mainMenu->draw();
}

void CHome::processInput(int key)
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
    break;
  case GAME_RETURN:
  case GAME_NUMPADENTER:
    gotoScreen = selectedScreeni;
  }
}

