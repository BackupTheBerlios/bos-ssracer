#ifndef CINPUTCONSOLE_H
#define CINPUTCONSOLE_H

//using namespace Wml;
#define STL_USING_ALL
#include "stl.h"
#include "ccommandlineparser.h"

#define STD_BUF_SIZE 256
#define STD_ARC_SIZE 256

// for evaluateChar(char):
#define CONSOLE_TOGGLE 1
#define ENTER 2
#define BACKSPACE 3
#define TAB 4
#define NOT_PRINTABLE 5
#define UP_ARROW 6
#define DOWN_ARROW 7

class CInputConsole {
public:
    CInputConsole(char* str);
    static CInputConsole & GetConsole();
    static CInputConsole * GetConsolePtr();

	bool isActive() {return active;}
	void setActive(bool a) {active = a;}
	bool toggleActive() {active = !active; return active;}

	int clearBuffer();
	std::string* getBuffer() {return &buffer;}
	int addChar(char c);
	int addString(char* str); // useful for testing
	int deleteChar(); // for backspace; removes the last char entered.
	int evaluateChar(int c); // checks for specials chars
	int processCommand(CCommandLineParser* CLP); // parses buffer contents and executes command
	//int printBuffer(int where); // where = {LOG_USER, LOG_APP,...}
	int archiveCommand(); // add most recent command just executed to archives
	int arrowKeyPressed(int key);

protected:
    CInputConsole(){};
	//~CInputConsole();
    static CInputConsole * ms_pkConsole;

	static std::string buffer;
	static std::vector<std::string> archives;
	static std::vector<std::string>::iterator archiveIterator;
	static bool active;


private:

};

#endif