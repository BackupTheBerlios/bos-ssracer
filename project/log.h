/*****************************************************************************
*
* File:  log.h 
*
* BurnOut Studios - Super Street Racer
* Module:  Core
* Author:  Jay Javier 
* Modified by:  On: 
* Date Created:  Jan 18, 2003
*
******************************************************************************
* Desc:  logging utility writes output to disk in logfiles 
* Note:  to enable logging to files you need to set active build config to debug
*   this will define "_DEBUG" in VC6 for you.  If you want to simply use DEBUG
*   instead, you will have to add "DEBUG" to the list in:
*   project->settings->c++->general->preproc defs field
* based on http://www.gamedev.net/reference/articles/article1954.asp
*****************************************************************************/
#ifndef LOG_H
#define LOG_H

// --- system includes --- //
#include "bos.h"
#include <windows.h>
#define STL_USING_ALL
#include "stl.h"  // uses STL_USING_* macro to supress stl warnings in VC++
#include <fstream>
#include <map>
//#include <ios>
#include <deque>


// --- internal library includes --- //


// --- logfile codes  OR these together to write to multiple logs at once --- //
#define LOG_APP 1
#define LOG_CLIENT 2
#define LOG_SERVER 4
#define LOG_MISC 8
#define LOG_USER 64            // display the log message to the user in a dialog box
//#define LOG_CONSOLE 1024     // display the log message to the user in the windows console
#define LOG_GAMECONSOLE 256   // display the log message to the user in the in-game console
#define LOG_ALL LOG_APP|LOG_CLIENT|LOG_SERVER|LOG_MISC|LOG_GAMECONSOLE 

#define MAX_STR_TABLE_ENTRIES 10000


class CRenderer; // forward declaration
class CCommandLineParser;


//----------------------------------------------------------------------------
// class CLog
//   logging utility for debugging and relaying status messages to in game console
//   Implemented as a singleton class so explicit instantiation is unneccessary
//----------------------------------------------------------------------------
class CLog
{
    friend CRenderer;  // renderer needs direct access to console log to display console
    friend CCommandLineParser;

  private:
    // log file streams
    std::ofstream AppLog;     // for logging most errors
    std::ofstream ClientLog;  // for logging vid, sound on player end
    std::ofstream ServerLog;  // unused at this point
    std::ofstream MiscLog;    // cleared every time the prog is executed
    std::map<unsigned int, std::string> m_kLogMap;  // where the actual predefined log strings are stored

    //$$$TODO windows console log 

    // in-game console log buffer
    std::deque< std::string > kConsoleQueue;  

    static unsigned int uiMaxConsoleLines;  // max # of lines in the console

    bool LoadStrings();  // load predefined messages 

  public:
	static CLog * GetLogPtr();  // return pointer
    static CLog & GetLog();  // return static reference to singleton
    bool Init();
    bool Shutdown();
    // writes messages to specified logs
    // variable arguement lists allow for additional fields
	void Write(int target, const char *msg, ...);
	void Write(int target, unsigned long msgID, ...);
    unsigned int GetMaxConsoleLines() { return uiMaxConsoleLines; };

    void ClearGameConsole(){ kConsoleQueue.clear(); };

  protected:
    CLog(){}
    //~CLog(){}
    static CLog m_Log;  // static instance of this singleton class


};

#endif 
//END log.h ==================================================================