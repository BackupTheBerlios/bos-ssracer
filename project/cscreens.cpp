#include "cscreens.h"

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


CSelectCar::CSelectCar()
{
  select = new CButton();
  select->setText("Select");
  cancel = new CButton();
  cancel->setText("Cancel");
  instructions = new CLabel();
  instructions->setText("Change Cars By Pressing Left/Right");

}

CSelectCar::~CSelectCar()
{
  //Do something here
}

void CSelectCar::draw()
{
  select->draw();
  cancel->draw();
  instructions->draw();
}


//Win Game Screen
CWinGame::CWinGame()
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
  placement->setText("You Placed First!");
}

CWinGame::~CWinGame()
{
  //Do something here
}

void CWinGame::draw()
{
  onward->draw();
  restartRace->draw();
  mainMenu->draw();
  congrats->draw();
  placement->draw();

}


//Lose Game Screen
CLoseGame::CLoseGame()
{
  restartRace = new CButton();
  restartRace->setText("Restart Race");
  mainMenu = new CButton();
  mainMenu->setText("Back to Main Menu");

  //labels
  loser = new CLabel();
  loser->setText("You got beat by Miss Daisy!..");
  placement = new CLabel();;
  placement->setText("You Placed last");
}

CLoseGame::~CLoseGame()
{
  //Do something here
}

void CLoseGame::draw()
{
  restartRace->draw();
  mainMenu->draw();
  loser->draw();
  placement->draw();

}