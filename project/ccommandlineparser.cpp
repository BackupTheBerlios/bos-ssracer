
#include "ccommandlineparser.h"
#include "cinputconsole.h"
#include "macros.h"

#define STL_USING_STRING
#include "stl.h"
#include "log.h"
#include "kernel.h"
#include "soundcore.h"
#include "soundmessage.h"
#include "gamestatemanager.h"
#include "renderer.h"

// TO ADD COMMANDS AND FUNCTIONS, SEE initKeywords()

CCommandLineParser::CCommandLineParser()
{
	deliminators = std::string(" \t\n");

	Tokens.clear();

	initKeywords();
}

// Note: does not check for duplicate chars in string
CCommandLineParser::CCommandLineParser(std::string dels)
{
	deliminators = dels;

	Tokens.clear();

	initKeywords();

}

CCommandLineParser::~CCommandLineParser()
{
	//SAFE_DELETE(deliminators);	
}

// To add commands, type "Keywords.push_back("<your_command>");" to the list below
// Then see execute().
int CCommandLineParser::initKeywords()
{
	// define your keywords here:
/*	Keywords.push_back(std::string("setvol"));
	Keywords.push_back(std::string("loadmap"));
	Keywords.push_back(std::string("pause"));
	Keywords.push_back(std::string("stop"));
	Keywords.push_back(std::string("play"));
    */
    Keywords.push_back(std::string("help"));
	Keywords.push_back(std::string("clear"));
    Keywords.push_back(std::string("echo"));
    Keywords.push_back(std::string("settimer"));

	/*** Begin Chris' Commands ***/
	Keywords.push_back(std::string("loadscene"));
	Keywords.push_back(std::string("loadentity"));
	Keywords.push_back(std::string("loadplayervehicle"));
	Keywords.push_back(std::string("clearscene"));
	/*** End Chris' Commands ***/

    /*** Begin J's Commands ***/
    Keywords.push_back(std::string("jscript1"));
    /*** End J's Commands ***/


	return OK;
}

// Add the following to the list of if statements below:
// if (*it == "<your-command>") error = <your-function()>
// where error is some error code you define
// Note: in order to avoid error code conflicts, I suggest you choose some kind of bandwidth
// ex. Chris's codes range from [10,000 to 11,000].
// See instructions in cinputconsole.cpp to be sure your codes are processed accordingly
// Alternately, you can just print out a message to the console, and return OK.
// When done, go to the end of this file and add your function.
int CCommandLineParser::execute()
{
	int error = OK;

	if (!Tokens.size()) return EMPTY_VECTOR;

	std::vector<std::string>::iterator it = Keywords.begin();
	while (it != Keywords.end()) {
		if (Tokens[0] == *it) break;
		it++;
	}

	if (it == Keywords.end()) return BAD_COMMAND;

/*	if (*it == "setvol") error = setvol();
	if (*it == "loadmap") error = loadmap();
	if (*it == "pause") error = pause();
	if (*it == "stop") error = stop();
	if (*it == "play") error = play();
    */
    if (*it == "help") error = help();
	if (*it == "clear") error = clear();
    if (*it == "echo") error = echo();	
    if (*it == "settimer") error = settimer();
	if (*it == "loadscene") error = LoadScene();
	if (*it == "loadentity") error = LoadEntity();
	if (*it == "loadplayervehicle") error = LoadPlayerVehicle();
	if (*it == "clearscene") error = ClearScene();
    if (*it == "jscript1") error = JScript1();


	return error;
}

// Note: does not check for duplicate chars in string
int CCommandLineParser::setDeliminators(std::string dels)
{
	deliminators = dels;

	return OK;
}

int CCommandLineParser::parse(std::string command)
{
	unsigned int mark = 0;
	unsigned int index = 0;
	unsigned int token_size = 0;

	Tokens.clear();

	while (index < command.size()) {
		while (isDeliminator(command[index])) {
			index++; mark++;
		}
		if (command[index] == '\0') break;
		token_size = 0;
		while (!isDeliminator(command[index])) {
			token_size++;
			index++;
			if (command[index] == '\0') break;
		}
		if (token_size > 0)
			Tokens.push_back(std::string(command, mark, token_size));
		mark = index;
	}

	return OK;
}

bool CCommandLineParser::isDeliminator(char c)
{
	for (unsigned int i = 0; i < deliminators.size(); i++)
		if (deliminators[i] == c) return true;

	return false;
}

// Add your command function here:
// Remember, the return type = int (error code)
// Also remember to include any necessary header above.
// When finished, remember to add a prototype to ccommandlineparser.h
// Lastly, go to help() below and add a blurb about what your command does

int CCommandLineParser::setvol()
{
	int i = atoi(Tokens[1].begin());

	//CLog::GetLog().Write(LOG_GAMECONSOLE, "(float)i/100 = %f", (float)i/100.0f);

	CSoundCore::GetSoundCorePtr()->SetMasterVolume(i*100 - 10000);
	return OK;
}

//clear console
int CCommandLineParser::clear()
{
    CLog::GetLog().ClearGameConsole();
    return OK;
}

// print current buffer contents
int CCommandLineParser::echo()
{
	std::string strBuf = *CInputConsole::GetConsolePtr()->getBuffer();
	int i = 4;//strBuf.find("echo");
	char * cStart = &strBuf[i];
    CLog::GetLog().Write(LOG_GAMECONSOLE, "%s", cStart);//strBuf.c_str());
    return OK;
}


//set game timer resolution
int CCommandLineParser::settimer()
{
    if (Tokens.size() == 2) {
        CTimer::GetTimer().SetTimeStep(atoi(Tokens[1].c_str()));
    }
    else  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "Too few arguments to settime");   
    }
    return OK;
}


int CCommandLineParser::loadmap()
{
	return OK;
}

int CCommandLineParser::pause()
{
#ifdef _DEBUG
	CLog::GetLog().Write(LOG_GAMECONSOLE, "In CCommandLineParser::pause()");
#endif

	return OK;
}

int CCommandLineParser::play()
{

	return OK;
}

int CCommandLineParser::stop()
{


	return OK;
}


// Add a blurb about your command here.
int CCommandLineParser::help()
{
	CLog::GetLog().Write(LOG_GAMECONSOLE, "\n\n\n");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "AVAILABLE COMMANDS ARE:");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "-----------------------");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "HELP - Display this list.");				
	CLog::GetLog().Write(LOG_GAMECONSOLE, "ECHO <text> - echoes the text entered.");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "CLEAR - clear the console.");
    CLog::GetLog().Write(LOG_GAMECONSOLE, "SETTIMER <n> - set game timer resolution to 1/n clicks per second");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "LOADSCENE <params> - load a new scene");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "                     <params>: -file <filename> -dir <directory>");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "                     where: <filename> is the name of the map to load");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "                                 <directory> is the directory where the map is located");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "LOADENTITY <params> - load a new entity and add it to the current scene");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "CLEARSCENE - clear the current scene");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "LOADPLAYERVEHICLE <params> - load a new player vehicle");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "-----------------------");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "\n\n\n");
	return OK;
}

/*** Begin Chris' Functions ***/
int CCommandLineParser::LoadScene()
{
	string file = "-file";
	string dir = "-dir";

	string filename;
	string directory;

	bool filenameSet = false;
	bool directorySet = false;

	for(unsigned int i=0;i<Tokens.size();i++) {
		if(Tokens[i] == file) {
			if(++i < Tokens.size()) {
				filename = Tokens[i];
				filenameSet = true;
			}
		}
		else if(Tokens[i] == dir) {
			if(++i < Tokens.size()) {
				directory = Tokens[i];
				directorySet = true;
			}
		}
	}

	if(!directorySet && !filenameSet) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "Invalid Usage!  See help for instructions.");
		return 0;
	}

	if(directorySet && filenameSet) {
		if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadScene(&directory, &filename))) {
			CLog::GetLog().Write(LOG_GAMECONSOLE, "The scene was not loaded successfully!");
			return 0;
		}
	}
		
	return OK;
}

int CCommandLineParser::LoadEntity()
{
	string file = "-file";
	string dir = "-dir";

	string filename;
	string directory;

	bool filenameSet = false;
	bool directorySet = false;

	for(unsigned int i=0;i<Tokens.size();i++) {
		if(Tokens[i] == file) {
			if(++i < Tokens.size()) {
				filename = Tokens[i];
				filenameSet = true;
			}
		}
		else if(Tokens[i] == dir) {
			if(++i < Tokens.size()) {
				directory = Tokens[i];
				directorySet = true;
			}
		}
	}

	if(!directorySet && !filenameSet) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "Invalid Usage!  See help for instructions.");
		return 0;
	}

	if(directorySet && filenameSet) {
		if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadEntity(&directory, &filename))) {
			CLog::GetLog().Write(LOG_GAMECONSOLE, "The entity was not loaded successfully!");
			return 0;
		}
	}
    
    CLog::GetLog().Write(LOG_GAMECONSOLE, "The entity loaded successfully!");
	return OK;
}

int CCommandLineParser::LoadPlayerVehicle()
{
	/*
	string file = "-file";
	string dir = "-dir";

	string filename;
	string directory;

	bool filenameSet = false;
	bool directorySet = false;

	for(unsigned int i=0;i<Tokens.size();i++) {
		if(Tokens[i] == file) {
			if(++i < Tokens.size()) {
				filename = Tokens[i];
				filenameSet = true;
			}
		}
		else if(Tokens[i] == dir) {
			if(++i < Tokens.size()) {
				directory = Tokens[i];
				directorySet = true;
			}
		}
	}

	if(!directorySet && !filenameSet) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "Invalid Usage!  See help for instructions.");
		return 0;
	}

	if(directorySet && filenameSet) {
		if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadPlayerVehicle(&directory, &filename))) {
			CLog::GetLog().Write(LOG_GAMECONSOLE, "The scene was not loaded successfully!");
			return 0;
		}
	}
	*/

	CLog::GetLog().Write(LOG_GAMECONSOLE, "Command not implemented yet, please come again!");

	return OK;
}

int CCommandLineParser::ClearScene()
{
	if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->ReleaseScene())) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "The scene was not cleared successfully!");
		return 0;
	}
	return OK;
}

/*** End Chris' Functions ***/



int CCommandLineParser::JScript1()
{
    if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadEntity(new string("."), new string("nsx")))) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "The entity was not loaded successfully!");
		return 0;
	}
}




// SAVING THIS; IT'S USEFUL:
/*
	CLog::GetLog().Write(LOG_MISC, "\n\n\n\n\n\n");
	CLog::GetLog().Write(LOG_MISC, "command:\n|%s|\n ------------------------------------\n", command.begin());
	for (int i = 0; i < Tokens.size(); i++) {
		CLog::GetLog().Write(LOG_MISC, "Token[%i]=%s, size=%i", i, Tokens[i].begin(), Tokens[i].size());
		CLog::GetLog().Write(LOG_MISC, "index=%i, mark=%i, token_size=%i\n", index, mark, token_size);
	}
	CLog::GetLog().Write(LOG_MISC, "\n\n\n\n\n\n");
	*/


	/*
	// Attempt to retrieve sound effect
	SC->GetSoundEffect(Tokens[1].begin(), &SFX_ref);
	if (!SFX_ref)
#ifdef _DEBUG
		CLog::GetLog().Write(LOG_GAMECONSOLE, 
		"\nIn CCommandLineParser::play():\n\tSFX_ref = NULL after SC->GetSoundEffect(Tokens[1].begin(), &SFX_ref);\n");
#endif

	// play it!
	error = SFX_ref->Play(false, false);
*/

/*
	if (error != NO_ERROR) { 
		if (error == 21) { // would like to use macro instead of 21. Is there one?
		// it might be a music file


			// "IF" PART COPIED DIRECTLY FROM ALPHA 0.0 RELEASE
			CSoundStream *cSStrm = NULL;
			if( CSoundCore::GetSoundCorePtr()->GetSoundStream( Tokens[1].begin(), &cSStrm ) == NO_ERROR ) {
				cSStrm->SetVolume(0.85f);
				//cSStrm->Play( TRUE );
				cSStrm->FadeIn( TRUE, 0.4f, 0.02f );
			}
			else { // THEN it doesn't exist
#ifdef _DEBUG
					CLog::GetLog().Write(LOG_GAMECONSOLE, "%s: so such file", Tokens[1].begin());
#endif
					// any other values for error? Put your if statement here.
					return OK;
			}

*/
			// THIS WHOLE SECTION DOES WORK WITH STREAM FILES

			/*
			// attempt to get the song
			SC->GetSoundStream(Tokens[1].begin(), &SS_ref);
			if (!SS_ref) 
#ifdef _DEBUG
				CLog::GetLog().Write(LOG_GAMECONSOLE, 
				"\nIn CCommandLineParser::play():\n\tSS_ref = NULL after SC->GetSoundStream(Tokens[1].begin(), &SS_ref);\n");
#endif

			error = SS_ref->Play(false, false);

			if (error != NO_ERROR) {
				if (error == 21) {
					// THEN it doesn't exist
#ifdef _DEBUG
					CLog::GetLog().Write(LOG_GAMECONSOLE, "%s: so such file", Tokens[1].begin());
#endif
					// any other values for error? Put your if statement here.
					return OK;

				// end inner if statements:
				} // end if (error == 21)
			} // end if (error != NO_ERROR)



		// end outer if statements:
		} // end if (error == 21)
	} // end if (error != NO_ERROR)
*/