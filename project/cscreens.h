#ifndef CSCREENS_H
#define CSCREENS_H

#include "clabel.h"
#include "cbutton.h"
#include "ctextfield.h"

//Main Menu
class CMainMenu 
{
  public:
    //buttons
  CButton * newGame;
  CButton * options;
  CButton * bestTimes;
  CButton * help;
  CButton * credits;
  CButton * quit;

  //functions
  CMainMenu();          //constructor where all widgets are set 
  ~CMainMenu();         //destructor
  void draw();          //Jay's stub to render screen

};

//New Game Screen
class CNewGame 
{
  public:
    //buttons
  CButton * ok;
  CButton * cancel;

  //labels
  CLabel * instructions;
    //Text Field
  CTextField * name;
  

  //functions
  CNewGame();          //constructor where all widgets are set 
  ~CNewGame();         //destructor
  void draw();          //Jay's stub to render screen

};

class CSelectCar
{
  public:
    //buttons
  CButton * select;
  CButton * cancel;

  //TODO WILL NEED 3D Widget Here to Handle Rotating Car

  //labels
  CLabel * instructions;

  //functions
  CSelectCar();          //constructor where all widgets are set 
  ~CSelectCar();         //destructor
  void draw();          //Jay's stub to render screen

};

class CWinGame
{
  public:
    //buttons
  CButton * onward;
  CButton * restartRace;
  CButton * mainMenu;


  //labels
  CLabel * congrats;
  CLabel * placement;

  //functions
  CWinGame();          //constructor where all widgets are set 
  ~CWinGame();         //destructor
  void draw();          //Jay's stub to render screen

};

class CLoseGame
{
  public:
    //buttons
  CButton * restartRace;
  CButton * mainMenu;


  //labels
  CLabel * loser;
  CLabel * placement;

  //functions
  CLoseGame();          //constructor where all widgets are set 
  ~CLoseGame();         //destructor
  void draw();          //Jay's stub to render screen

};
#endif