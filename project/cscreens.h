#ifndef CSCREENS_H
#define CSCREENS_H

#include "clabel.h"
#include "cbutton.h"
#include "ctextfield.h"

//Hey Gibran, heres my SCREEN MACROS that you can use
#define NO_STATE 0
#define MAIN_MENU 1
#define NEW_GAME 2
#define GARAGE 3
#define POST_GAME 4
#define IN_GAME 5
#define OPTIONS 6
#define BESTTIMES 7
#define HELP 8
#define CREDITS 9
#define QUIT 10
#define PAUSE 11
#define PERFORMANCE 12
#define HOME 13
#define DEALERSHIP 14
#define PRE_GAME 15
#define MAX_STATES 15

class CScreen
{
public:
  virtual void draw()=0;
  //virtual void processInput(int key)=0;
  int getGotoScreen(){return gotoScreen;};
  void resetGotoScreen(){gotoScreen=0;};
  //not much else in base class for now
  CScreen(){gotoScreen=0; maxScreeni = 1000; selectedScreeni =0;};
  ~CScreen(){};
  void processInput(int key);

protected:
  //CWidget * selectedWidget;
  int selectedScreeni;
  int maxScreeni;
  int gotoScreen;  
  int screenOrder[20];

};


//Main Menu
class CMainMenu : public CScreen 
{
  public:
    //buttons
  CButton * newGame;
  CButton * options;
  CButton * bestTimes;
  CButton * help;
  CButton * credits;
  CButton * quit;
  //int screenOrder[6];

  //functions
  CMainMenu();          //constructor where all widgets are set 
  ~CMainMenu();         //destructor
  void draw();          //Jay's stub to render screen
  


};

//New Game Screen
class CNewGame : public CScreen
{
  public:
    //buttons
  CButton * ok;
  CButton * cancel; 
  //int screenOrder[2];

  //labels
  CLabel * instructions;
    //Text Field
  CTextField * name;
  

  //functions
  CNewGame();          //constructor where all widgets are set 
  ~CNewGame();         //destructor
  void draw();          //Jay's stub to render screen
  void processInput(int key);
  

};

class CGarage : public CScreen
{
  public:
    //buttons
  CButton * select;
  CButton * cancel;
  //int screenOrder[2];

  //TODO WILL NEED 3D Widget Here to Handle Rotating Car

  //labels
  CLabel * instructions;

  //functions
  CGarage();          //constructor where all widgets are set 
  ~CGarage();         //destructor
  void draw();          //Jay's stub to render screen
  void processInput(int key);

};

class CPostGame : public CScreen
{
  public:
    //buttons
  CButton * onward;
  CButton * restartRace;
  CButton * mainMenu;
  //int screenOrder[3];

  //labels
  CLabel * congrats;
  CLabel * placement;
  CLabel * winnings;

  //functions
  CPostGame();          //constructor where all widgets are set 
  ~CPostGame();         //destructor
  void draw();          //Jay's stub to render screen
  

};

class CPauseGame : public CScreen
{
  public:
    //buttons
  CButton * resume;
  CButton * restartRace;
  CButton * mainMenu;
  CButton * options;
  //int screenOrder[3];

  //labels
  CLabel * instructions;

  //functions
  CPauseGame();          //constructor where all widgets are set 
  ~CPauseGame();         //destructor
  void draw();          //Jay's stub to render screen
  

};

class CHome : public CScreen
{
  public:
    //buttons
  CButton * race;
  CButton * performanceUpgrade;
  CButton * garage;
  CButton * dealership;
  CButton * mainMenu;

  //int screenOrder[5];

  //labels
  CLabel * home;

  //functions
  CHome();          //constructor where all widgets are set 
  ~CHome();         //destructor
  void draw();          //Jay's stub to render screen
  void processInput(int key);

};

class CQuit : public CScreen
{
  public:
    //buttons
  CButton * quit;
  CButton * mainMenu;

  //int screenOrder[2];

  //functions
  CQuit();          //constructor where all widgets are set 
  ~CQuit();         //destructor
  void draw();          //Jay's stub to render screen


};

class CPreGame : public CScreen
{
  public:
    //buttons
  CButton * onward;
  CButton * mainMenu;
  //int screenOrder[2];

  //labels
  CLabel * ready;
  
  //functions
  CPreGame();          //constructor where all widgets are set 
  ~CPreGame();         //destructor
  void draw();          //Jay's stub to render screen
  //void processInput(int key);

};

class COptions : public CScreen
{
  public:
    //buttons
  CButton * option1;
  CButton * option2;
  CButton * option3;
  CButton * mainMenu;
  //int screenOrder[3];

  //labels
  CLabel * instructions;

  //functions
  COptions();          //constructor where all widgets are set 
  ~COptions();         //destructor
  void draw();          //Jay's stub to render screen
  

};

class CBestTimes : public CScreen
{
  public:
    //buttons
  CButton * mainMenu;

  //labels
  CLabel * bestTime;
  
  //functions
  CBestTimes();          //constructor where all widgets are set 
  ~CBestTimes();         //destructor
  void draw();          //Jay's stub to render screen
  //void processInput(int key);

};

class CHelp : public CScreen
{
  public:
    //buttons
  CButton * mainMenu;

  //labels
  CLabel * help;
  
  //functions
  CHelp();          //constructor where all widgets are set 
  ~CHelp();         //destructor
  void draw();          //Jay's stub to render screen
  //void processInput(int key);

};

class CCredits : public CScreen
{
  public:
    //buttons
  CButton * mainMenu;

  //labels
  CLabel * credits;
  
  //functions
  CCredits();          //constructor where all widgets are set 
  ~CCredits();         //destructor
  void draw();          //Jay's stub to render screen
  //void processInput(int key);

};

class CPerformance : public CScreen
{
  public:
    //buttons
  CButton * engineUp;
  CButton * tireUp;
  CButton * weightRed;
  CButton * home;
  //int screenOrder[3];

  //labels
  CLabel * instructions;

  //functions
  CPerformance();          //constructor where all widgets are set 
  ~CPerformance();         //destructor
  void draw();          //Jay's stub to render screen
  

};

class CDealership : public CScreen
{
  public:
    //buttons
  CButton * select;
  CButton * cancel;
  //int screenOrder[2];

  //TODO WILL NEED 3D Widget Here to Handle Rotating Car

  //labels
  CLabel * instructions;

  //functions
  CDealership();          //constructor where all widgets are set 
  ~CDealership();         //destructor
  void draw();          //Jay's stub to render screen
  void processInput(int key);

};

#endif