#include "cinputconsole.h"
#include "log.h"
#include "macros.h"
#include "input.h"

// If you've just added a command to ccommandlineparser.cpp
// see processCommand() below

//#undef _DEBUG

CInputConsole * CInputConsole::ms_pkConsole		 = NULL;
std::string CInputConsole::buffer				 = "";
bool CInputConsole::active						 = false;
std::vector<std::string> CInputConsole::archives;
std::vector<std::string>::iterator CInputConsole::archiveIterator;

CInputConsole & CInputConsole::GetConsole() {  return *ms_pkConsole; }
CInputConsole * CInputConsole::GetConsolePtr() {  return ms_pkConsole;  }


CInputConsole::CInputConsole(char* str)
{
	// assumes str is null terminated
	buffer.reserve(STD_BUF_SIZE);
	if (str) buffer.append(str);
	else buffer.erase();

	archives.reserve(STD_ARC_SIZE);
	archives.clear();
	archiveIterator = archives.end();

	active = false;
}

/*
CInputConsole::~CInputConsole()
{
	// nothing to do here
}
*/

int CInputConsole::clearBuffer()
{
	buffer.erase();
	return OK;
}

// question: will InputConsoleTask be sending in a char, or the key code?
int CInputConsole::addChar(char c)
{
	// must check for special chars first (backspace, enter, etc)
	buffer.append(&c, 1);
	return OK;
}

// good for testing purposes
int CInputConsole::addString(char* str)
{
	// assuming str is null terminated
	buffer.append(str);
	return OK;
}

int CInputConsole::evaluateChar(int c)
{
	switch(c) {
    case '`':
	case '~': 
        return CONSOLE_TOGGLE;

	case GAME_RETURN:
	case GAME_NUMPADENTER:
        return ENTER; 

	case GAME_BACK:
        return BACKSPACE;
	
	case GAME_TAB:
        return TAB;

	case GAME_UP: 
		return UP_ARROW;

	case GAME_DOWN: 
		return DOWN_ARROW;

	case GAME_LSHIFT:
	case GAME_RSHIFT: 
		return NOT_PRINTABLE;
	
    default:
//		if (c < 32 || c > 126) // not a printable character
//			return NOT_PRINTABLE;
 //       else
            return OK;
	}

}

int CInputConsole::deleteChar()
{
	if (buffer.size() > 0)
		buffer.erase(buffer.end()-1);
	return OK;
}

// If you've just added a command to ccommandlineparser.cpp, 
// this is where your error code gets processed.
// Simply at your case number to the switch statement.
// Ex. case RAMITS_ERROR: return RAMITS_ERROR;
int CInputConsole::processCommand(CCommandLineParser* CLP)
{
	int error = OK;

	if (!CLP) return NULL_POINTER;

	if (CLP->parse(buffer) == NULL_POINTER) // if buffer empty
		return NULL_POINTER;

	// If Tokens empty after parsing, don't bother executing
	if (CLP->getTokens()->size() == 0) return OK;
	else error = CLP->execute();

	// archive the command just executed
	if (error != EMPTY_VECTOR) archiveCommand();

	// return error status of execution
	switch(error) {
	case OK: return OK;
	case EMPTY_VECTOR: return EMPTY_VECTOR;
	case BAD_COMMAND: return BAD_COMMAND;
	default:
		return GENERAL_ERROR; 
	}

}

int CInputConsole::archiveCommand()
{
	archives.push_back(buffer);
	archiveIterator = archives.end();
	return OK;
}

int CInputConsole::arrowKeyPressed(int key)
{
	if (key != UP_ARROW && key != DOWN_ARROW) 
		return GENERAL_ERROR;

	// go up through archives
	if (key == UP_ARROW && archiveIterator != archives.begin()) {
		archiveIterator--;
		buffer.erase();
		buffer = *archiveIterator;
	}
	
	// go down through archives
	if (key == DOWN_ARROW && archiveIterator != archives.end()) {
		archiveIterator++;
		buffer.erase();
		if (archiveIterator != archives.end()) // archives.end() is empty
			buffer = *archiveIterator;
	}

	return OK;
}

/*
int CInputConsole::printBuffer(int where)
{
#ifdef _DEBUG
	CLog::GetLog().Write(where, "buffer = %s", buffer.begin());
#endif
	return OK;
}
*/

//#define _DEBUG







// SAVING THIS CRAP:
	/*
	CLog::GetLog().Write(LOG_MISC, "\n\n\niterating\n");
	for (archiveIterator = archives.begin(); archiveIterator != archives.end(); archiveIterator++)
		CLog::GetLog().Write(LOG_MISC, "archiveIterator = %s", (*archiveIterator).begin());  
	CLog::GetLog().Write(LOG_MISC, "\nend iterating\n\n\n");
*/