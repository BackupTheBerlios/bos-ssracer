/*****************************************************************************
*
* File:  log.cpp 
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
* based on http://www.gamedev.net/reference/articles/article1954.asp
*****************************************************************************/

// --- internal library includes --- //
#include "log.h"
#include <ctime>

// --- predefined log files --- //
#define APP_LOG_FILENAME "applog.log"        // the main logfile to write to
#define CLIENT_LOG_FILENAME "clientlog.log"  //$$$DEBUG could be useful later...
#define SERVER_LOG_FILENAME "serverlog.log"  
#define MISC_LOG_FILENAME "misclog.log"  

#define MAX_CONSOLE_LINES 512;

//-----------------------------------------------------------------------------
// static member intitialization 
//-----------------------------------------------------------------------------
unsigned int CLog::uiMaxConsoleLines = MAX_CONSOLE_LINES;


//----------------------------------------------------------------------------
// GetLog ()
//   return static reference to this singleton object
//----------------------------------------------------------------------------
//CLog CLog::m_Log;
CLog & CLog::GetLog()
{
  static CLog m_Log;  // instantiate this singleton class on first use
//  assert (this.m_Log);
  return  m_Log;
}

//----------------------------------------------------------------------------
// GetLog ()
//   return pointer to this static object
//----------------------------------------------------------------------------
CLog * CLog::GetLogPtr()
{
  return &GetLog();
}


//----------------------------------------------------------------------------
// Init ()
//   Initialize logging streams
//----------------------------------------------------------------------------
bool CLog::Init()
{
    // open file streams to logs on disk
	AppLog.open(APP_LOG_FILENAME, ios::app);
	ClientLog.open(CLIENT_LOG_FILENAME, ios::app);
	ServerLog.open(SERVER_LOG_FILENAME, ios::app);
    MiscLog.open(MISC_LOG_FILENAME);
	//user errors get logged to client console

    // write an initialization message to all disk logs
    time_t rawTime;
    time( &rawTime );
    Write(LOG_ALL, "\n\n### Log Initialized on: %s", ctime( &rawTime ) );
    
	//load the strings file with predefined error messages
	if(!LoadStrings())return false;

	return true;
}

//----------------------------------------------------------------------------
// Shutdown ()
//   shutdown logging streams
//----------------------------------------------------------------------------
bool CLog::Shutdown()
{
  // close file streams to logs on disk
	AppLog.close();
	ClientLog.close();
	ServerLog.close();
    MiscLog.close();
	//user errors get logged to client console

   // shutdown console for output
    m_kLogMap.clear();
   //$$$TODO write game console to file

	return true;
}

//----------------------------------------------------------------------------
// Write ()
//   writes a plain log entry to file
//   target:  logfile to write to eg) LOG_APP
//   msg:  description of log entry 
//   ... : variable length arguement list, pass any other info about this log 
//         entry you want in here like printf in C
// ex) CLog::GetLog().Write (LOG_APP, "Rendered %d triangles", num);
//----------------------------------------------------------------------------
void CLog::Write(int target, const char *msg, ...)
{
  va_list args; va_start(args,msg);
  char szBuf[1024];
  vsprintf(szBuf,msg,args);
  
  if(target&LOG_APP)  { // write to application log
    AppLog<<szBuf<<"\n";
#ifdef DEBUG
    AppLog.flush();
#endif
  }
  if(target&LOG_CLIENT)  { // write to client log
    ClientLog<<szBuf<<"\n";
#ifdef DEBUG
    ClientLog.flush();
#endif
  }
  if(target&LOG_SERVER)  { // write to server log
    ServerLog<<szBuf<<"\n";
#ifdef DEBUG
    ServerLog.flush();
#endif
  }
  if(target&LOG_MISC)  { // write to server log
    MiscLog<<szBuf<<"\n";
#ifdef DEBUG
    MiscLog.flush();
#endif
  }
  if(target&LOG_GAMECONSOLE)  {  // write to console buffer
      //sprintf(szBuf, "%s%s", szBuf,"\n"); 
      kConsoleQueue.push_back(szBuf);  
      if (kConsoleQueue.size() > uiMaxConsoleLines)  {
          kConsoleQueue.pop_front();  // remove lines fron the buffer
      }
  }
  if(target&LOG_USER)  { // write to user display
#ifdef WIN32
    MessageBox(NULL,szBuf,"Message",MB_OK);  // display a msg box
#else
#error User-level logging is not implemented for this platform.
#endif
  }
  va_end(args);
}



//----------------------------------------------------------------------------
// Write ()
//   writes a predefined log entry to file
//   target:  logfile to write to eg) LOG_APP
//   msgID:   ID of string entry in string table eg) IDS_APP_ERROR
//   ... : variable length arguement list, pass any other info about this log 
//         entry you want in here like printf in C
// ex) CLog::GetLog().Write (LOG_APP, IDS_APP_ERROR, "cannot allocate %s", mesh.name);
//----------------------------------------------------------------------------
void CLog::Write(int target, unsigned long msgID, ...)
{
  va_list args; va_start(args, msgID);
  char logBuf[1024];       // buffer for log entry
  char strTableMsg[1024];  // buffer for string table message

  // load predefined message from string table
  //$$$DEBUG already loaded in LoadStrings() LoadString(GetModuleHandle(NULL), msgID ,strTableMsg, sizeof(strTableMsg));
   
  // combine string table message with log message
  //vsprintf(logBuf, strTableMsg, args);
  vsprintf(logBuf, m_kLogMap[msgID].c_str(), args);

  // write log entry to file
  Write(target, logBuf);
  va_end(args);
}



//----------------------------------------------------------------------------
// LoadStrings ()
//   load predefined strings for use in logging utility
// under Win32, the strings get read in from a string table resource in VC6
// strings are defined in bos.rc
//----------------------------------------------------------------------------
bool CLog::LoadStrings()
{
    unsigned int iStringTableIndex =0;
    std::map< unsigned int, std::string >::iterator it;
    char szBuf[1024];
    m_kLogMap[iStringTableIndex] = " ";

    //for ( it=m_kLogMap.begin(); it!=m_kLogMap.end(); it++, iStringTableIndex++)  {
    for(int i=0;i<MAX_STR_TABLE_ENTRIES; i++){
        //it->first = iStringTableIndex;
        if (LoadString(GetModuleHandle(NULL),iStringTableIndex ,szBuf, sizeof(szBuf)))
            m_kLogMap[iStringTableIndex] = szBuf;
        iStringTableIndex++;
//        it->second = std::string(szBuf);
    }

  
    return true;
}



//END log.cpp ==============================================================