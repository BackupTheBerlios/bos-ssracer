
#include "ccommandlineparser.h"
#include "cinputconsole.h"
#include "macros.h"

#define STL_USING_STRING
#include "stl.h"
#include <algorithm>  //for lowercasing the command
#include "log.h"
#include "kernel.h"
#include "soundcore.h"
#include "soundmessage.h"
#include "gamestatemanager.h"
#include "renderer.h"
#include "settings.h"
#include "cwaypoint.h"
#include "copponentvehicle.h"
#include "copponentai.h"
#include "ccollisionmanager.h"
#include "appstate.h" 

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
    Keywords.push_back(std::string("loadpv"));  //alias

	//Keywords.push_back(std::string("clearscene"));
	//Keywords.push_back(std::string("physicstest1"));
	//Keywords.push_back(std::string("physicstest2"));
	/*** End Chris' Commands ***/

    /*** Begin J's Commands ***/
    Keywords.push_back(std::string("loadmeshtest"));
    Keywords.push_back(std::string("loadmesh"));
    Keywords.push_back(std::string("cameratest"));
    Keywords.push_back(std::string("setcamera")); // alias
    Keywords.push_back(std::string("loadmap"));
    Keywords.push_back(std::string("unloadmap"));
    Keywords.push_back(std::string("setres"));
    Keywords.push_back(std::string("showentities"));
    Keywords.push_back(std::string("setviscull"));
    Keywords.push_back(std::string("drawentbbox"));
    Keywords.push_back(std::string("drawquadtree"));
    Keywords.push_back(std::string("drawplanes"));
    Keywords.push_back(std::string("drawwaypoints"));
    Keywords.push_back(std::string("exit"));
    /*** End J's Commands ***/
    
    /** Begin Rams Commands **/
    Keywords.push_back(std::string("loadvehicleai"));
    Keywords.push_back(std::string("loadrace"));
    /*** End Rams Commands ***/

    /*** Begin Rob's Commands ***/
    Keywords.push_back(std::string("playsound"));
    Keywords.push_back(std::string("stopsound"));
    Keywords.push_back(std::string("loadsound"));
    Keywords.push_back(std::string("releasesound"));
    Keywords.push_back(std::string("pausesound"));
    Keywords.push_back(std::string("unpausesound"));

    Keywords.push_back(std::string("playstream"));
    Keywords.push_back(std::string("stopstream"));
    Keywords.push_back(std::string("loadstream"));
    Keywords.push_back(std::string("releasestream"));
    Keywords.push_back(std::string("pausestream"));
    Keywords.push_back(std::string("unpausestream"));

    Keywords.push_back(std::string("loadlist"));
    Keywords.push_back(std::string("playlist"));
    Keywords.push_back(std::string("stoplist"));
    Keywords.push_back(std::string("pauselist"));
    Keywords.push_back(std::string("unpauselist"));
    Keywords.push_back(std::string("showlist"));

    Keywords.push_back(std::string("showaudio"));
    Keywords.push_back(std::string("killsound"));

    Keywords.push_back(std::string("loadfinalmap"));
    /*** End Rob's Commands ***/

	/*** Begin Gib's commands ***/
	Keywords.push_back(std::string("loadcollisiontest"));
    Keywords.push_back(std::string("CT"));
	/*** End Gib's commands ***/

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
        // J's Mod:  lowercase the keyword
        transform (Tokens[0].begin(), Tokens[0].end(), Tokens[0].begin(), tolower);
		if (Tokens[0] == *it) break;
		it++;
	}

	if (it == Keywords.end()) return BAD_COMMAND;

/*	if (*it == "setvol") error = setvol();
	
	if (*it == "pause") error = pause();
	if (*it == "stop") error = stop();
	if (*it == "play") error = play();
    */
    if (*it == "help") error = help();
	if (*it == "clear") error = clear();
    if (*it == "echo") error = echo();	
    if (*it == "settimer") error = settimer();
	//if (*it == "loadscene") error = LoadScene();
	if (*it == "loadentity") error = LoadEntity();

	if (*it == "loadplayervehicle") error = LoadPlayerVehicle();
    if (*it == "loadpv") error = LoadPlayerVehicle();  // alias

	//if (*it == "clearscene") error = ClearScene();
	//if (*it == "physicstest1") error = PhysicsTest1();
	//if (*it == "physicstest2") error = PhysicsTest2();

    if (*it == "unloadmap") error = unloadmap();
    if (*it == "loadmap")   {
        // load the new map and scene
        //CAppStateManager::GetAppMan().SetAppState(STATE_PRE_GAME);  // set the pre game loading state (draw loading screen) kill sound buffers etc.
        error = loadmap();
    }

    if (*it == "loadmeshtest") error = loadmeshtest();
    if (*it == "loadmesh") error = loadmeshtest();
    if (*it == "cameratest") error = cameratest();
    if (*it == "setres") error = setres();
    if (*it == "showentities") error = ShowEntities();
    if (*it == "setviscull") error = SetVisCull();
    if (*it == "drawentbbox") error = SetDraw();
    if (*it == "drawquadtree") error = SetDraw();
    if (*it == "drawplanes") error = SetDraw();
    if (*it == "drawwaypoints") error = SetDraw();
    if (*it == "exit") error = SystemCommand();

    if (*it == "loadvehicleai") error = LoadVehicleAI();
    if (*it == "loadrace") error = loadrace();

    if (*it == "playsound") error = SoundEffectCommand();
    if (*it == "stopsound") error = SoundEffectCommand();
    if (*it == "loadsound") error = SoundEffectCommand();
    if (*it == "releasesound") error = SoundEffectCommand();
    if (*it == "pausesound") error = SoundEffectCommand();
    if (*it == "unpausesound") error = SoundEffectCommand();

    if (*it == "playstream") error = SoundStreamCommand();
    if (*it == "stopstream") error = SoundStreamCommand();
    if (*it == "loadstream") error = SoundStreamCommand();
    if (*it == "releasestream") error = SoundStreamCommand();
    if (*it == "pausestream") error = SoundStreamCommand();
    if (*it == "unpausestream") error = SoundStreamCommand();

    if (*it == "loadlist") error = PlaylistCommand();
    if (*it == "playlist") error = PlaylistCommand();
    if (*it == "stoplist") error = PlaylistCommand();
    if (*it == "pauselist") error = PlaylistCommand();
    if (*it == "unpauselist") error = PlaylistCommand();
    if (*it == "showlist") error = PlaylistCommand();

    if (*it == "showaudio") error = SoundCoreCommand();
    if (*it == "killsound") error = SoundCoreCommand();

	if (*it == "loadfinalmap") error = LoadFinalMap();

	if (*it == "loadcollisiontest" || *it == "CT") error = LoadCollisionTest();

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
    CLog::GetLog().Write(LOG_GAMECONSOLE, "general command syntax:  command | alias <arg> [optional arg]");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "----------------------------------------------------------------------------------------------------------------");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "HELP - Display this list.");				
	CLog::GetLog().Write(LOG_GAMECONSOLE, "ECHO <text> - echoes the text entered.");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "CLEAR - clear the console.");
//    CLog::GetLog().Write(LOG_GAMECONSOLE, "SETTIMER <n> - set game timer resolution to 1/n clicks per second");
//	CLog::GetLog().Write(LOG_GAMECONSOLE, "LOADSCENE <params> - load a new scene");
//	CLog::GetLog().Write(LOG_GAMECONSOLE, "                     <params>: -file <filename> -dir <directory>");
//	CLog::GetLog().Write(LOG_GAMECONSOLE, "                     where: <filename> is the name of the map to load");
//	CLog::GetLog().Write(LOG_GAMECONSOLE, "                                 <directory> is the directory where the map is located");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "LOADENTITY <params> - load a new entity and add it to the current scene");
//	CLog::GetLog().Write(LOG_GAMECONSOLE, "CLEARSCENE - clear the current scene");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "LOADPLAYERVEHICLE | LOADPV <file> - load a new player vehicle from file (leave .car extension off)");
    CLog::GetLog().Write(LOG_GAMECONSOLE, "LOADMESH <file> <dir> - load a mesh at some directory (leave .x extension off");
    CLog::GetLog().Write(LOG_GAMECONSOLE, "CAMERATEST <CAMERA_NAME> - change cameras to a specific one: {CAMERA_FREELOOK, CAMERA_CHASE, CAMERA_BUMPER}");
    CLog::GetLog().Write(LOG_GAMECONSOLE, "SETVISCULL <0|1> - turn on visibility culling");
    CLog::GetLog().Write(LOG_GAMECONSOLE, "DRAW{ENTBBOX|QUADTREE|PLANES|WAYPOINTS} <0|1> - draw debug information for AI");
    CLog::GetLog().Write(LOG_GAMECONSOLE, "CAMERATEST <CAMERA_NAME> - change cameras to a specific one: {CAMERA_FREELOOK, CAMERA_CHASE, CAMERA_BUMPER}");
    CLog::GetLog().Write(LOG_GAMECONSOLE, "LOADMAP <file> [dir] - load a map and create a scene from a .map file [dir] defaults to .\\maps\\ if omitted");
    CLog::GetLog().Write(LOG_GAMECONSOLE, "UNLOADMAP - unload current map and scene objects");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "LOADVEHICLEAI - runs opponent vehicle AI test");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "LOADCOLLISIONTEST - loads a scene with collidable objects and a player vehicle.");
    CLog::GetLog().Write(LOG_GAMECONSOLE, "LOADRACE - loads a race baby! (map, WPS, opponent, race cond.)");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "\n*** Sound Engine Commands ***" );
	CLog::GetLog().Write(LOG_GAMECONSOLE, "LOAD{SOUND|STREAM} <file> as <alias> - Loads a sound effect or stream and gives it the specified alias.");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "PLAY{SOUND|STREAM} [-loop] <alias> - Plays a sound effect or stream either one-shot or looping.");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "PLAY{SOUND|STREAM} [-once] <file> - Plays a sound or stream once without assigning it an alias (not recommended).");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "STOP{SOUND|STREAM} <alias> - Stops the specified sound or stream.");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "PAUSE{SOUND|STREAM} <alias> - Pauses the specified sound or stream if playing.");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "UNPAUSE{SOUND|STREAM} <alias> - Pauses the specified sound or stream.");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "RELEASE{SOUND|STREAM} <alias> - Unloads the specified sound or stream.");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "SHOWAUDIO - Shows a list of all sounds and streams registered by the console, including their status.");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "KILLSOUND -all|-sfx|-streams - Kill the specified group of sounds.");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "\n*** Playlist Commands ***" );
	CLog::GetLog().Write(LOG_GAMECONSOLE, "LOADLIST <file> - Loads the <file>.slp playlist if it exists.");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "PLAYLIST <vol%%> -[no]repeat -[no]advance - Begins playing the list with specified volume (0-1) and specified autorepeat and autoadvance.");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "PLAYLIST -next - Advance to next track.");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "PLAYLIST -prev - Back to previous track.");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "STOPLIST - Stops list playback.");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "PAUSELIST - Pauses list playback if playing.");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "UNPAUSELIST - Unpauses list playback if paused.");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "SHOWLIST - Displays the currently loaded playlist.");
    CLog::GetLog().Write(LOG_GAMECONSOLE, "----------------------------------------------------------------------------------------------------------------");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "\n\n\n");
	return OK;
}

/*** Begin Chris' Functions ***/
// Chris, the loadmap command takes care of this now...
/*int CCommandLineParser::LoadScene()
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
		return OK;
	}

	if(directorySet && filenameSet) {
		if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadScene(&directory, &filename))) {
			CLog::GetLog().Write(LOG_GAMECONSOLE, "The scene was not loaded successfully!");
			return OK;
		}
	}
    return OK;
    

}*/

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
		return OK;
	}

	if(directorySet && filenameSet) {
		if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadEntity(&directory, &filename))) {
			CLog::GetLog().Write(LOG_GAMECONSOLE, "The entity was not loaded successfully!");
			return OK;
		}
	}
    
	return OK;
}


//$$$NOTE Chris I made this function because this is basically what physicstest[1,2] does
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
	

	CLog::GetLog().Write(LOG_GAMECONSOLE, "Command not implemented yet, please come again!");

	return OK;
    */

    string sDir, sName;
    FILE *fp;

    // if only 'loadplayervehicle' was entered default to the mitsu eclipse
    if (Tokens.size() == 1)  {
        sName = "mitsuEclipse";
        CLog::GetLog().Write(LOG_GAMECONSOLE, "not enough arguements, loading default player vehicle from %s.car", sName.c_str());
        sDir = CSettingsManager::GetSettingsManager().GetGameSetting(DIRDYNVEHICLES) + sName + "\\";
    }
    // if only 'loadplayervehicle <vehiclename>' was entered
    else if (Tokens.size() == 2)  {
        sName = Tokens[1];
        // look in the .\media\meshes\dynamic\vehicles\ directory
        sDir = CSettingsManager::GetSettingsManager().GetGameSetting(DIRDYNVEHICLES) + sName + "\\";
        CLog::GetLog().Write(LOG_GAMECONSOLE, "loadmap:  looking in %s for vehicle", sDir.c_str());
    }
    // if 'loadplayervehicle <vehiclename> <dir>' was entered
    else if (Tokens[2].find(".\\", 0) == 0)  { // check if they used that .\ dir shortcut
        sName = Tokens[1];
        sDir = Tokens[2];
        sDir.replace(0, 2, CSettingsManager::GetSettingsManager().GetGameSetting(DIRCURRENTWORKING));
    }

    sName.append(".car");  // build the actual filename we want to load

    //check if the file exists
    fp = fopen( (sDir+sName).c_str(), "r");
    if (!fp)  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "loadplayervehicle Error: File does not exist: %s", (sDir+sName).c_str());
        return OK;
    }

    // load the player vehicle into the current scene
	if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadPlayerVehicle(&sDir, &sName))) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "The scene was not loaded successfully!");
		return OK;
	}

    //set the active camera to the chase cam
    CRenderer::GetRenderer().SetActiveCamera(CAMERA_CHASE);

    //set it to chase the vehicle we just created
    ((CCameraChase *)CRenderer::GetRenderer().GetActiveCameraPtr())->SetVehicle(CGameStateManager::GetGameStateManager().GetPlayerVehicle());
    
    return OK;
}


int CCommandLineParser::ClearScene()
{
	if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->ReleaseScene())) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "The scene was not cleared successfully!");
		return OK;
	}
	return OK;
}

/*
int CCommandLineParser::PhysicsTest1()
{
    string sDir = CSettingsManager::GetSettingsManager().GetGameSetting(DIRDYNVEHICLES)+"mitsuEclipse\\";
	string sName = "mitsuEclipse.car";

	if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadPlayerVehicle(&sDir, &sName))) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "The scene was not loaded successfully!");
		return OK;
	}


    //set the active camera to the chase cam
    CRenderer::GetRenderer().SetActiveCamera(CAMERA_CHASE);

    //set it to chase the vehicle we just created
    ((CCameraChase *)CRenderer::GetRenderer().GetActiveCameraPtr())->SetVehicle(CGameStateManager::GetGameStateManager().GetPlayerVehicle());

	return OK;

}

int CCommandLineParser::PhysicsTest2()
{
    string sDir = CSettingsManager::GetSettingsManager().GetGameSetting(DIRDYNVEHICLES)+"acuransx\\";
	string sName = "acuransx.car";

	if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadPlayerVehicle(&sDir, &sName))) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "The scene was not loaded successfully!");
		return OK;
	}


    //set the active camera to the chase cam
    CRenderer::GetRenderer().SetActiveCamera(CAMERA_CHASE);

    //set it to chase the vehicle we just created
    ((CCameraChase *)CRenderer::GetRenderer().GetActiveCameraPtr())->SetVehicle(CGameStateManager::GetGameStateManager().GetPlayerVehicle());

	return OK;

}
*/
/*** End Chris' Functions ***/



// ===== Begin Jay's Functions ==== ///
int CCommandLineParser::unloadmap()
{
    if (Tokens.size() != 1)  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "unloadmap:  too many arguements");
    }

    // unload the current map & scene if any
    if (CGameStateManager::GetGameStateManager().GetScenePtr()->IsLoaded() == true )  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "Releasing current scene");
        if (CGameStateManager::GetGameStateManager().GetScenePtr()->ReleaseScene()){
            CLog::GetLog().Write(LOG_GAMECONSOLE, "Scene released sucessfully");
        }
        else {
            CLog::GetLog().Write(LOG_GAMECONSOLE, "ERROR: Scene was not released sucessfully");
        }
    }
    else {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "ERROR: no map is currently loaded");
    }
    return OK;
}

int CCommandLineParser::loadmap()
{
    string sDir, sName;
    FILE *fp;

    // if only 'loadmap' was entered
    if (Tokens.size() == 1)  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "not enough arguements, loading scene from debug.map");
        sName = "debug";
        sDir = CSettingsManager::GetSettingsManager().GetGameSetting(DIRMAP) + sName + "\\";
    }
    // if only 'loadmap <mapname>' was entered
    else if (Tokens.size() == 2)  {
        sName = Tokens[1];
        // look in the .\maps directory
        sDir = CSettingsManager::GetSettingsManager().GetGameSetting(DIRMAP) + sName + "\\";
        CLog::GetLog().Write(LOG_GAMECONSOLE, "loadmap:  looking in %s for map", sDir.c_str());
    }
    // if 'loadmap <mapname> <dir>' was entered
    else if (Tokens[2].find(".\\", 0) == 0)  { // check if they used that .\ dir shortcut
        sName = Tokens[1];
        sDir = Tokens[2];
        sDir.replace(0, 2, CSettingsManager::GetSettingsManager().GetGameSetting(DIRCURRENTWORKING));
    }

    //check if the file exists
    fp = fopen( (sDir+sName+".map").c_str(), "r");
    if (!fp)  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "loadmap Error: File does not exist: %s", (sDir+sName+".map").c_str());
        return OK;
    }

    // first unload the current map & scene if any
    if (CGameStateManager::GetGameStateManager().GetScenePtr()->IsLoaded() == true )  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "Releasing current scene");
        if (CGameStateManager::GetGameStateManager().GetScenePtr()->ReleaseScene()){
            CLog::GetLog().Write(LOG_GAMECONSOLE, "Scene released sucessfully");
        }
        else {
            CLog::GetLog().Write(LOG_GAMECONSOLE, "ERROR: Scene was not released sucessfully");
        }
    }

    if (CGameStateManager::GetGameStateManager().GetScenePtr()->LoadMap( fp, &sDir, &sName ))  {
        CAppStateManager::GetAppMan().SetAppState(STATE_IN_GAME);  // set in game state so we can play
        CLog::GetLog().Write(LOG_GAMECONSOLE, "Successfully loaded map: %s%s%s", sDir.c_str(), sName.c_str(), ".map");
    }
    else  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "ERROR: Failed to load map: %s%s%s", sDir.c_str(), sName.c_str(), ".map");
    }
    return OK;
}


int CCommandLineParser::loadmeshtest()
{
    string sDir, sName;
    // if only 'loadmeshtest' was entered
    if (Tokens.size() == 1)  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "not enough arguements, loading default mesh: pylon");
        sDir = CSettingsManager::GetSettingsManager().GetGameSetting(DIRMESH) + "static\\";
        sName = "pylon";
    }
    // if only 'loadmeshtest <meshname>' was entered
    else if (Tokens.size() == 2)  {
        sName = Tokens[1];
        // look in the .\meshes\static\ directory
        sDir = CSettingsManager::GetSettingsManager().GetGameSetting(DIRMESH) + "static\\";
        CLog::GetLog().Write(LOG_GAMECONSOLE, "loadmeshtest:  looking in %s for mesh", sDir.c_str());
    }
    // if 'loadmeshtest <meshname> <dir>' was entered
    else if (Tokens[2].find(".\\", 0) == 0)  { // check if they used that .\ dir shortcut
        sName = Tokens[1];
        sDir = Tokens[2];
        sDir.replace(0, 2, CSettingsManager::GetSettingsManager().GetGameSetting(DIRCURRENTWORKING));
    }

    if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadEntity(&sDir, &sName))) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "The entity for this mesh was not loaded successfully!");
		return OK;
	}
    CLog::GetLog().Write(LOG_GAMECONSOLE, "loadmeshtest loaded the mesh %s Sucessfully!", sName.c_str() );
    return OK;
}


int CCommandLineParser::cameratest()
{
    // default to free look cam if no camera is entered
    if (Tokens.size()<2)  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "not enough arguements to cameratest loading CAMERA_FREELOOK");
        CRenderer::GetRenderer().SetActiveCamera(CAMERA_FREELOOK);
		return OK;
    }

    //check which camera is needed
    if (Tokens[1] == "CAMERA_FREELOOK")  {
        CRenderer::GetRenderer().SetActiveCamera(CAMERA_FREELOOK);
    }
    else if (Tokens[1] == "CAMERA_CHASE")  {        
        //if (!CGameStateManager::GetGameStateManager().GetPlayerVehicle())  {
            CRenderer::GetRenderer().SetActiveCamera(CAMERA_CHASE);
            CLog::GetLog().Write(LOG_GAMECONSOLE, "cameratest:  setting chase cam to track player vehicle");
            ((CCameraChase *)CRenderer::GetRenderer().GetActiveCameraPtr())->SetVehicle(CGameStateManager::GetGameStateManager().GetPlayerVehicle());
        //}
        //else  {
        //    CLog::GetLog().Write(LOG_GAMECONSOLE, "ERROR cameratest:  cannot chase a NULL vehicle");
        //}
    }
    //else if (Tokens[1] == "CAMERA_BUMPER")  {
    //    CRenderer::GetRenderer().SetActiveCamera(CAMERA_BUMPER);
    //    ((CCameraBumper *)CRenderer::GetRenderer().GetActiveCameraPtr())->SetVehicle(CGameStateManager::GetGameStateManager().GetPlayerVehicle());
    //}
    else  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "sorry, that camera is not implemented yet");
		return OK;
    }

    return OK;
}


//$$$TEMP don't use yet...
int CCommandLineParser::setres()
{
    CRenderer::GetRenderer().ToggleFullScreen(atoi(Tokens[1].c_str()), atoi(Tokens[1].c_str()));
    return OK;
}

int CCommandLineParser::ShowEntities()
{
    CLog::GetLog().Write(LOG_GAMECONSOLE, "showentities:  listing all loaded entities");
    vector<CEntity *>::iterator it;
    int i=0;
    for (it=CGameStateManager::GetGameStateManager().GetScenePtr()->m_vEntities.begin();
         it<CGameStateManager::GetGameStateManager().GetScenePtr()->m_vEntities.end();  it++,i++) {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "#%d  Name: %s  Id: %d  MeshName: %s Position: %f %f %f Rotation: %f %f %f",
             i, (*it)->GetName(), (*it)->GetId(), (*it)->GetMesh()->m_strName, 
             (*it)->GetTranslate()->X(), (*it)->GetTranslate()->Y(), (*it)->GetTranslate()->Z(),
             (*it)->GetRotate()->X(), (*it)->GetRotate()->Y(), (*it)->GetRotate()->Z());        
    }
    CLog::GetLog().Write(LOG_GAMECONSOLE, "showentities:  TOTAL # of entities %d", CGameStateManager::GetGameStateManager().GetScenePtr()->m_vEntities.size());

    return OK;
}

int CCommandLineParser::SetVisCull()
{
    // default to ON
    if (Tokens.size()<2)  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "setviscull: no arguments, Visibility Culling ON");
        CRenderer::GetRenderer().SetVisCulling(true);
		return OK;
    }
    else if (Tokens.size() == 2)  {
        if (Tokens[1] == "ON" || Tokens[1] == "on" || Tokens[1] == "1")  {
            CRenderer::GetRenderer().SetVisCulling(true);
        }
        else if (Tokens[1] == "OFF" || Tokens[1] == "off" || Tokens[1] == "0")  {
            CRenderer::GetRenderer().SetVisCulling(false);
        }
        else  {
            CLog::GetLog().Write(LOG_GAMECONSOLE, "setviscull: invalid syntax");
            return OK;
        }
        CLog::GetLog().Write(LOG_GAMECONSOLE, "setviscull: Visibility Culling set to %d", CRenderer::GetRenderer().IsVisCullingEnabled());
        return OK;
    }

    return OK;

}


int CCommandLineParser::SetDraw()
{
    // default to ON
    if (Tokens.size()<2)  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "draw: no arguments");
		return OK;
    }
    else if (Tokens.size() == 2)  {

        if (Tokens[1] == "ON" || Tokens[1] == "on" || Tokens[1] == "1")  {
            // drawentbbox command
            if (Tokens[0] == "drawentbbox")  {
                CRenderer::GetRenderer().SetDrawEntBBoxes(true);
            }
            else if (Tokens[0] == "drawquadtree")  {
                CRenderer::GetRenderer().SetDrawQNodeBBoxes(true);
            }
            else if (Tokens[0] == "drawplanes")  {
                CRenderer::GetRenderer().SetDrawRects(true);
            }
            else if (Tokens[0] == "drawwaypoints")  {
                CRenderer::GetRenderer().SetDrawWayPoints(true);
            }
            CLog::GetLog().Write(LOG_GAMECONSOLE, "%s: state set to %d", Tokens[0].c_str(), 1);
        }
        else if (Tokens[1] == "OFF" || Tokens[1] == "off" || Tokens[1] == "0")  {
            // drawentbbox command
            if (Tokens[0] == "drawentbbox")  {
                CRenderer::GetRenderer().SetDrawEntBBoxes(false);
            }
            else if (Tokens[0] == "drawquadtree")  {
                CRenderer::GetRenderer().SetDrawQNodeBBoxes(false);
            }
            else if (Tokens[0] == "drawplanes")  {
                CRenderer::GetRenderer().SetDrawRects(false);
            }
            else if (Tokens[0] == "drawwaypoints")  {
                CRenderer::GetRenderer().SetDrawWayPoints(false);
            }

            CLog::GetLog().Write(LOG_GAMECONSOLE, "%s: state set to %d", Tokens[0].c_str(), 0);
        }
        else  {
            CLog::GetLog().Write(LOG_GAMECONSOLE, "draw: invalid syntax");
            return OK;
        }
        return OK;
    }

    return OK;

}


int CCommandLineParser::SystemCommand()
{
    if (Tokens[0] == "exit")
        CKernel::GetKernel().KillAllTasks();  //// ****** exit the game ****** ///
    return OK;
}

// ===== End Jay's functions ==== //


// ===== Begin Ram's FunctionsFunctions ==== //

int CCommandLineParser::LoadVehicleAI()
{
    //just temporary TODO cut and paste properly 
    loadmap();

	string carDir = CSettingsManager::GetSettingsManager().GetGameSetting(DIRDYNVEHICLES)+"mitsuEclipse\\";
	string carName = "mitsuEclipse.car";
	string sDir, sName;

	//straight copy from Jays loadmeshtest to get 2 pylons up yay.
	sDir = CSettingsManager::GetSettingsManager().GetGameSetting(DIRMESH) + "static\\pylon\\";
    sName = "pylon";
	if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadEntity(&sDir, &sName))) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "The entity for this mesh was not loaded successfully!");
	}
    CLog::GetLog().Write(LOG_GAMECONSOLE, "pylon1 loaded the mesh %s Sucessfully!", sName.c_str() );

	if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadEntity(&sDir, &sName))) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "The entity for this mesh was not loaded successfully!");
	}
    CLog::GetLog().Write(LOG_GAMECONSOLE, "pylon2 loaded the mesh %s Sucessfully!", sName.c_str() );

	if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadEntity(&sDir, &sName))) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "The entity for this mesh was not loaded successfully!");
	}
    CLog::GetLog().Write(LOG_GAMECONSOLE, "pylon3 loaded the mesh %s Sucessfully!", sName.c_str() );    
    
    if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadEntity(&sDir, &sName))) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "The entity for this mesh was not loaded successfully!");
	}
    CLog::GetLog().Write(LOG_GAMECONSOLE, "pylon4 loaded the mesh %s Sucessfully!", sName.c_str() );    
    
    if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadEntity(&sDir, &sName))) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "The entity for this mesh was not loaded successfully!");
	}
    CLog::GetLog().Write(LOG_GAMECONSOLE, "pylon5 loaded the mesh %s Sucessfully!", sName.c_str() );    
    if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadEntity(&sDir, &sName))) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "The entity for this mesh was not loaded successfully!");
	}
    CLog::GetLog().Write(LOG_GAMECONSOLE, "pylon5 loaded the mesh %s Sucessfully!", sName.c_str() );    
    if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadEntity(&sDir, &sName))) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "The entity for this mesh was not loaded successfully!");
	}
    CLog::GetLog().Write(LOG_GAMECONSOLE, "pylon5 loaded the mesh %s Sucessfully!", sName.c_str() );    
    if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadEntity(&sDir, &sName))) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "The entity for this mesh was not loaded successfully!");
	}
    CLog::GetLog().Write(LOG_GAMECONSOLE, "pylon5 loaded the mesh %s Sucessfully!", sName.c_str() );    
    if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadEntity(&sDir, &sName))) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "The entity for this mesh was not loaded successfully!");
	}
    CLog::GetLog().Write(LOG_GAMECONSOLE, "pylon5 loaded the mesh %s Sucessfully!", sName.c_str() );    
    //create iterator
    std::vector<CEntity *>::iterator it = CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->TEMPGetEntities()
						->end()-1;

   //9 pylons

	//translate pylons to desired locations
	(*it)->SetTranslate(Vector3f(6.0f, 0.0f, 0.0f));
    (*--it)->SetTranslate(Vector3f(30.0f, 0.0f, -5.0f));
	(*--it)->SetTranslate(Vector3f(60.0f, 0.0f, -5.0f));
    (*--it)->SetTranslate(Vector3f(150.0f, 0.0f, -5.0f));
    (*--it)->SetTranslate(Vector3f(30.0f, 0.0f, 0.0f));
    (*--it)->SetTranslate(Vector3f(60.0f, 0.0f, 0.0f));
    (*--it)->SetTranslate(Vector3f(150.0f, 0.0f, 0.0f));
    (*--it)->SetTranslate(Vector3f(250.0f, 0.0f, 5.0f));
    (*--it)->SetTranslate(Vector3f(350.0f, 0.0f, 10.0f));
    

    //load mitsu opponent
	  if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadOpponentVehicle(&carDir, &carName))) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "The Opponent Vehicle is not loaded correctly!");
		return OK;
      }
    

    //load 2nd opponent (nsx)
    carDir = CSettingsManager::GetSettingsManager().GetGameSetting(DIRDYNVEHICLES)+"acuransx\\";
	carName = "acuransx.car";
	if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadOpponentVehicle(&carDir, &carName))) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "The Opponent Vehicle is not loaded correctly!");
		return OK;
	}

 
    COpponentVehicle * opponent = NULL;
   
    //get access to opponents and initialize waypoints for each
    vector<COpponentVehicle *>::iterator it2;
    for (it2=CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->begin();
         it2<CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->end();  it2++) {
 
        opponent = (*it2);
        opponent->setWPSequence(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->GetWaypoints());
        opponent->setWPSequence(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->GetShortCut1());
        opponent->initNext();
	    COpponentAI::GetOpponentAIPtr()->addCar(opponent);
     
    }
    opponent->setAILevel(ADVANCED_AI);
      //set Cam to last vehicle set in 
	CRenderer::GetRenderer().SetActiveCamera(CAMERA_CHASE);
    ((CCameraChase *)CRenderer::GetRenderer().GetActiveCameraPtr())->SetVehicle((*CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->begin()));
	
    return 0;
}

//Kinda like loadmap... but different :)
int CCommandLineParser::loadrace()
{
    string sDir, sName;
    FILE *fp;

    // if only 'loadrace' was entered
    if (Tokens.size() == 1)  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "not enough arguements, loading race from debug.race");
        sName = "debug";
        sDir = CSettingsManager::GetSettingsManager().GetGameSetting(DIRMAP) + sName + "\\";
    }
    // if only 'loadrace <racename>' was entered
    else if (Tokens.size() == 2)  {
        sName = Tokens[1];
        // look in the .\maps directory
        sDir = CSettingsManager::GetSettingsManager().GetGameSetting(DIRMAP) + sName + "\\";
        CLog::GetLog().Write(LOG_GAMECONSOLE, "loadrace:  looking in %s for race", sDir.c_str());
    }
    // if 'loadrace <racename> <dir>' was entered
    else if (Tokens[2].find(".\\", 0) == 0)  { // check if they used that .\ dir shortcut
        sName = Tokens[1];
        sDir = Tokens[2];
        sDir.replace(0, 2, CSettingsManager::GetSettingsManager().GetGameSetting(DIRCURRENTWORKING));
    }

    //check if the file exists
    fp = fopen( (sDir+sName+".race").c_str(), "r");
    if (!fp)  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "loadrace Error: File does not exist: %s", (sDir+sName+".race").c_str());
        return OK;
    }

    // first unload the current map & scene if any
    if (CGameStateManager::GetGameStateManager().GetScenePtr()->IsLoaded() == true )  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "Releasing current scene");
        if (CGameStateManager::GetGameStateManager().GetScenePtr()->ReleaseScene()){
            CLog::GetLog().Write(LOG_GAMECONSOLE, "Scene released sucessfully");
        }
        else {
            CLog::GetLog().Write(LOG_GAMECONSOLE, "ERROR: Scene was not released sucessfully");
        }
    }

    // load the new map and scene
    if (CGameStateManager::GetGameStateManager().GetScenePtr()->LoadRace( fp, &sDir, &sName ))  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "Successfully loaded Race: %s%s%s", sDir.c_str(), sName.c_str(), ".race");
    }
    else  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "ERROR: Failed to load race: %s%s%s", sDir.c_str(), sName.c_str(), ".race");
    }
    CLog::GetLog().Write(LOG_MISC, "Done Command Line");
	            
    return OK;
}

//  ===== End Rams Functions =====//


// ===== Begin Rob's Functions ==== ///
int CCommandLineParser::SoundCoreCommand()
{
	std::string sSoundFile;
	std::string sSoundID;
	CSoundMessage *cSMsg = NULL;

	// ** LISTAUDIO command ** //
	if ( strcmp( Tokens[0].c_str(), "showaudio" ) == 0 ) {
		switch( Tokens.size() ) {
		case 1:
			// Send the sound message
			cSMsg = new CSoundMessage();
			cSMsg->ListAudio();
			CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
			break;

		default:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "showaudio - invalid syntax (command takes no arguments)." );
			return BAD_COMMAND;
			break;

		}
	}
	else if ( strcmp( Tokens[0].c_str(), "killsound" ) == 0 ) {
		switch( Tokens.size() ) {
		case 2:
			// Send the sound message
			cSMsg = new CSoundMessage();

			if ( Tokens[1] == "-all" ) cSMsg->KillSound();
			if ( Tokens[1] == "-sfx" ) cSMsg->KillSoundEffects();
			if ( Tokens[1] == "-streams" ) cSMsg->KillSoundStreams();

			CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
			break;

		default:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "killsound - invalid syntax (command takes no arguments)." );
			return BAD_COMMAND;
			break;

		}
	}

    return OK;
}


int CCommandLineParser::PlaylistCommand()
{
	std::string sSoundFile;
	int nVol = 100;
	bool bAutoRep = true;
	bool bAutoAdv = true;

	CSoundMessage *cSMsg = NULL;

	// ** LOAD command ** //
	if ( strcmp( Tokens[0].c_str(), "loadlist" ) == 0 ) {
		switch( Tokens.size() ) {
		case 2:
			// Send the sound message
			cSMsg = new CSoundMessage();
			cSMsg->LoadList( Tokens[1].c_str() );
			CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
			break;

		default:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "playlist - invalid syntax." );
			return BAD_COMMAND;
			break;

		}
	}

	// ** PLAY command ** //
	else if ( strcmp( Tokens[0].c_str(), "playlist" ) == 0 ) {
		switch( Tokens.size() ) {
		case 2:
			// ** NEXT command ** //
			if ( Tokens[1] == "-next" ) {
				// Send the sound message
				cSMsg = new CSoundMessage();
				cSMsg->ListNext();
				CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
				break;
			}

			// ** PREV command ** //
			if ( Tokens[1] == "-prev" ) {
				// Send the sound message
				cSMsg = new CSoundMessage();
				cSMsg->ListPrev();
				CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
				break;
			}

			return BAD_COMMAND;
			break;

		case 4:
			nVol = atoi( Tokens[1].c_str() );

			// Ensure the volume is within the valid range
			if ( (nVol > 100) || (nVol < 0) ) return BAD_COMMAND;

			// Autorepeat?
			if ( Tokens[2] == "-repeat" ) {
				bAutoRep = true;
			}
			else if ( Tokens[2] == "-norepeat" ) {
				bAutoRep = false;
			}
			else return BAD_COMMAND;

			// Autoadvance?
			if ( Tokens[3] == "-advance" ) {
				bAutoRep = true;
			}
			else if ( Tokens[3] == "-noadvance" ) {
				bAutoRep = false;
			}
			else return BAD_COMMAND;

			// Send the sound message
			cSMsg = new CSoundMessage();
			cSMsg->PlayList( (float) nVol / (float) 100, bAutoRep, bAutoAdv );
			CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
			break;

		default:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "playlist - invalid syntax." );
			return BAD_COMMAND;
			break;

		}
	}

	// ** STOP command ** //
	else if ( strcmp( Tokens[0].c_str(), "stoplist" ) == 0 ) {
		switch( Tokens.size() ) {
		case 1:
			// Send the sound message
			cSMsg = new CSoundMessage();
			cSMsg->StopList();
			CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
			break;

		default:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "stoplist - invalid syntax." );
			return BAD_COMMAND;
			break;

		}
	}

	// ** PAUSE command ** //
	else if ( strcmp( Tokens[0].c_str(), "pauselist" ) == 0 ) {
		switch( Tokens.size() ) {
		case 1:
			// Send the sound message
			cSMsg = new CSoundMessage();
			cSMsg->PauseList();
			CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
			break;

		default:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "pauselist - invalid syntax." );
			return BAD_COMMAND;
			break;

		}
	}

	// ** UNPAUSE command ** //
	else if ( strcmp( Tokens[0].c_str(), "unpauselist" ) == 0 ) {
		switch( Tokens.size() ) {
		case 1:
			// Send the sound message
			cSMsg = new CSoundMessage();
			cSMsg->UnpauseList();
			CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
			break;

		default:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "unpauselist - invalid syntax." );
			return BAD_COMMAND;
			break;

		}
	}

	// ** SHOW command ** //
	else if ( strcmp( Tokens[0].c_str(), "showlist" ) == 0 ) {
		switch( Tokens.size() ) {
		case 1:
			// Send the sound message
			cSMsg = new CSoundMessage();
			cSMsg->ShowList();
			CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
			break;

		default:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "showlist - invalid syntax." );
			return BAD_COMMAND;
			break;

		}
	}


    return OK;
}



int CCommandLineParser::SoundEffectCommand()
{
	std::string sSoundFile;
	std::string sSoundID;
	CSoundMessage *cSMsg = NULL;

	// ** PLAYSOUND command ** //
	if ( strcmp( Tokens[0].c_str(), "playsound" ) == 0 ) {
		switch( Tokens.size() ) {
		case 1:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "SYNTAX: playsound -once (soundname)" );
			CLog::GetLog().Write(LOG_GAMECONSOLE, "OR: playsound [-loop] (ID)" );
			CLog::GetLog().Write(LOG_GAMECONSOLE, "  (soundname) - name of sound file (not including .wav extension!)" );
			CLog::GetLog().Write(LOG_GAMECONSOLE, "  (ID) - alias of sound to play." );
			break;

		case 2:
			sSoundID = Tokens[1].begin();

			// Send the sound message
			cSMsg = new CSoundMessage();
			cSMsg->PlaySoundEffect( sSoundID, false );
			CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
			break;

		case 3:
			// Ensure the middle argument is an AS statement
			if ( strcmp( Tokens[1].c_str(), "-once" ) == 0 ) {
				sSoundFile = Tokens[2].begin();

				// Send the sound message
				cSMsg = new CSoundMessage();
				cSMsg->PlaySoundEffectOnce( sSoundFile );
				CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
			}
			else if ( strcmp( Tokens[1].c_str(), "-loop" ) == 0 ) {
				sSoundID = Tokens[2].begin();

				// Send the sound message
				cSMsg = new CSoundMessage();
				cSMsg->PlaySoundEffect( sSoundID, true );
				CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );

			}
			else {
				return BAD_COMMAND;

			}
			break;

		default:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "playsound - invalid syntax." );
			return BAD_COMMAND;
			break;

		}
	}

	// ** LOADSOUND command ** //
	else if ( strcmp( Tokens[0].c_str(), "loadsound" ) == 0 ) {
		switch( Tokens.size() ) {
		case 1:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "SYNTAX: loadsound (soundname) as (ID)" );
			CLog::GetLog().Write(LOG_GAMECONSOLE, "  (soundname) - name of sound file (not including .wav extension!)" );
			CLog::GetLog().Write(LOG_GAMECONSOLE, "  (ID) - unique identifier string to use as alias for loaded sound." );
			break;

		case 4:
			sSoundFile = Tokens[1].begin();
			sSoundID = Tokens[3].begin();

			// Ensure the middle argument is an AS statement
			if ( strcmp( Tokens[2].c_str(), "as" ) != 0 ) return BAD_COMMAND;

			// Send the sound message
			cSMsg = new CSoundMessage();
			cSMsg->LoadSoundEffect( sSoundFile, sSoundID );
			CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
			break;

		default:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "loadsound - invalid syntax." );
			return BAD_COMMAND;
			break;

		}
	}

	// ** STOPSOUND command ** //
	else if ( strcmp( Tokens[0].c_str(), "stopsound" ) == 0 ) {
		switch( Tokens.size() ) {
		case 1:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "SYNTAX: stopsound (ID)" );
			CLog::GetLog().Write(LOG_GAMECONSOLE, "  (ID) - Alias of sound to be stopped." );
			break;

		case 2:
			sSoundID = Tokens[1].begin();

			// Send the sound message
			cSMsg = new CSoundMessage();
			cSMsg->StopSoundEffect( sSoundID );
			CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
			break;

		default:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "stopsound - invalid syntax." );
			return BAD_COMMAND;
			break;

		}
	}

	// ** RELEASESOUND command ** //
	else if ( strcmp( Tokens[0].c_str(), "releasesound" ) == 0 ) {
		switch( Tokens.size() ) {
		case 1:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "SYNTAX: releasesound (ID)" );
			CLog::GetLog().Write(LOG_GAMECONSOLE, "  (ID) - Alias of sound to be released." );
			break;

		case 2:
			sSoundID = Tokens[1].begin();

			// Send the sound message
			cSMsg = new CSoundMessage();
			cSMsg->ReleaseSoundEffect( sSoundID );
			CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
			break;

		default:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "releasesound - invalid syntax." );
			return BAD_COMMAND;
			break;

		}
	}

	// ** PAUSESOUND command ** //
	else if ( strcmp( Tokens[0].c_str(), "pausesound" ) == 0 ) {
		switch( Tokens.size() ) {
		case 1:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "SYNTAX: pausesound (ID)" );
			CLog::GetLog().Write(LOG_GAMECONSOLE, "  (ID) - Alias of sound to be paused." );
			break;

		case 2:
			sSoundID = Tokens[1].begin();

			// Send the sound message
			cSMsg = new CSoundMessage();
			cSMsg->PauseSoundEffect( sSoundID );
			CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
			break;

		default:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "pausesound - invalid syntax." );
			return BAD_COMMAND;
			break;

		}
	}

	// ** UNPAUSESOUND command ** //
	else if ( strcmp( Tokens[0].c_str(), "unpausesound" ) == 0 ) {
		switch( Tokens.size() ) {
		case 1:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "SYNTAX: unpausesound (ID)" );
			CLog::GetLog().Write(LOG_GAMECONSOLE, "  (ID) - Alias of sound to be unpaused." );
			break;

		case 2:
			sSoundID = Tokens[1].begin();

			// Send the sound message
			cSMsg = new CSoundMessage();
			cSMsg->UnpauseSoundEffect( sSoundID );
			CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
			break;

		default:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "unpausesound - invalid syntax." );
			return BAD_COMMAND;
			break;

		}
	}

    return OK;
}


int CCommandLineParser::SoundStreamCommand()
{
	std::string sSoundFile;
	std::string sSoundID;
	CSoundMessage *cSMsg = NULL;

	// ** PLAYSTREAM command ** //
	if ( strcmp( Tokens[0].c_str(), "playstream" ) == 0 ) {
		switch( Tokens.size() ) {
		case 1:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "SYNTAX: playstream -once (streamname)" );
			CLog::GetLog().Write(LOG_GAMECONSOLE, "OR: playsound [-loop] (ID)" );
			CLog::GetLog().Write(LOG_GAMECONSOLE, "  (streamname) - name of stream file (not including .wav extension!)" );
			CLog::GetLog().Write(LOG_GAMECONSOLE, "  (ID) - alias of stream to play." );
			break;

		case 2:
			sSoundID = Tokens[1].begin();

			// Send the sound message
			cSMsg = new CSoundMessage();
			cSMsg->PlayStream( sSoundID, false );
			CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
			break;

		case 3:
			// Ensure the middle argument is an AS statement
			if ( strcmp( Tokens[1].c_str(), "-once" ) == 0 ) {
				sSoundFile = Tokens[2].begin();

				// Send the sound message
				cSMsg = new CSoundMessage();
				cSMsg->PlayStreamOnce( sSoundFile );
				CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
			}
			else if ( strcmp( Tokens[1].c_str(), "-loop" ) == 0 ) {
				sSoundID = Tokens[2].begin();

				// Send the sound message
				cSMsg = new CSoundMessage();
				cSMsg->PlayStream( sSoundID, true );
				CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );

			}
			else {
				return BAD_COMMAND;

			}
			break;

		default:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "playstream - invalid syntax." );
			return BAD_COMMAND;
			break;

		}
	}

	// ** LOADSTREAM command ** //
	else if ( strcmp( Tokens[0].c_str(), "loadstream" ) == 0 ) {
		switch( Tokens.size() ) {
		case 1:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "SYNTAX: loadstream (streamname) as (ID)" );
			CLog::GetLog().Write(LOG_GAMECONSOLE, "  (streamname) - name of stream file (not including .wav extension!)" );
			CLog::GetLog().Write(LOG_GAMECONSOLE, "  (ID) - unique identifier string to use as alias for loaded stream." );
			break;

		case 4:
			sSoundFile = Tokens[1].begin();
			sSoundID = Tokens[3].begin();

			// Ensure the middle argument is an AS statement
			if ( strcmp( Tokens[2].c_str(), "as" ) != 0 ) return BAD_COMMAND;

			// Send the sound message
			cSMsg = new CSoundMessage();
			cSMsg->LoadStream( sSoundFile, sSoundID );
			CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
			break;

		default:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "loadstream - invalid syntax." );
			return BAD_COMMAND;
			break;

		}
	}

	// ** STOPSTREAM command ** //
	else if ( strcmp( Tokens[0].c_str(), "stopstream" ) == 0 ) {
		switch( Tokens.size() ) {
		case 1:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "SYNTAX: stopstream (ID)" );
			CLog::GetLog().Write(LOG_GAMECONSOLE, "  (ID) - Alias of stream to be stopped." );
			break;

		case 2:
			sSoundID = Tokens[1].begin();

			// Send the sound message
			cSMsg = new CSoundMessage();
			cSMsg->StopStream( sSoundID );
			CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
			break;

		default:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "stopstream - invalid syntax." );
			return BAD_COMMAND;
			break;

		}
	}

	// ** RELEASESTREAM command ** //
	else if ( strcmp( Tokens[0].c_str(), "releasestream" ) == 0 ) {
		switch( Tokens.size() ) {
		case 1:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "SYNTAX: releasestream (ID)" );
			CLog::GetLog().Write(LOG_GAMECONSOLE, "  (ID) - Alias of stream to be released." );
			break;

		case 2:
			sSoundID = Tokens[1].begin();

			// Send the sound message
			cSMsg = new CSoundMessage();
			cSMsg->ReleaseStream( sSoundID );
			CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
			break;

		default:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "releasestream - invalid syntax." );
			return BAD_COMMAND;
			break;

		}
	}

	// ** PAUSESTREAM command ** //
	else if ( strcmp( Tokens[0].c_str(), "pausestream" ) == 0 ) {
		switch( Tokens.size() ) {
		case 1:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "SYNTAX: pausestream (ID)" );
			CLog::GetLog().Write(LOG_GAMECONSOLE, "  (ID) - Alias of stream to be paused." );
			break;

		case 2:
			sSoundID = Tokens[1].begin();

			// Send the sound message
			cSMsg = new CSoundMessage();
			cSMsg->PauseStream( sSoundID );
			CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
			break;

		default:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "pausestream - invalid syntax." );
			return BAD_COMMAND;
			break;

		}
	}

	// ** UNPAUSESOUND command ** //
	else if ( strcmp( Tokens[0].c_str(), "unpausestream" ) == 0 ) {
		switch( Tokens.size() ) {
		case 1:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "SYNTAX: unpausestream (ID)" );
			CLog::GetLog().Write(LOG_GAMECONSOLE, "  (ID) - Alias of stream to be unpaused." );
			break;

		case 2:
			sSoundID = Tokens[1].begin();

			// Send the sound message
			cSMsg = new CSoundMessage();
			cSMsg->UnpauseStream( sSoundID );
			CKernel::GetKernel().DeliverMessage( cSMsg, SOUND_TASK );
			break;

		default:
			CLog::GetLog().Write(LOG_GAMECONSOLE, "unpausestream - invalid syntax." );
			return BAD_COMMAND;
			break;

		}
	}

    return OK;
}


int CCommandLineParser::LoadFinalMap()
{
	// Execute a series of commands

	// Turn on culling
	parse( "setviscull 1" );
	execute();

	// Load the final map
	parse( "loadmap map_final" );
	execute();

	// Load a player vehicle
	parse( "loadpv acuransx" );
	execute();

	return OK;
}
// ===== End Rob's functions ==== //

// ===== Begin Gib's functions === //
int CCommandLineParser::LoadCollisionTest()
{
// 	sDir = CSettingsManager::GetSettingsManager().GetGameSetting(DIRMESH) + "static\\pylon\\";

	string carDir = CSettingsManager::GetSettingsManager().GetGameSetting(DIRDYNVEHICLES)+"mitsuEclipse\\";
	string carName = "mitsuEclipse.car";
	string oppDir1 = CSettingsManager::GetSettingsManager().GetGameSetting(DIRDYNVEHICLES)+"mitsuEclipse\\";
	string oppName1 = "mitsuEclipse.car";
	string oppDir2 = CSettingsManager::GetSettingsManager().GetGameSetting(DIRDYNVEHICLES)+"mitsuEclipse\\";
	string oppName2 = "mitsuEclipse.car";
	string planesDir = CSettingsManager::GetSettingsManager().GetGameSetting(DIRMAP) + "debug\\";
	string planesName = "debug";
	string pylonDir, pylonName;

	//straight copy from Jays loadmeshtest to get 2 pylons up yay.
	pylonDir = CSettingsManager::GetSettingsManager().GetGameSetting(DIRMESH) + "static\\pylon\\";
    pylonName = "pylon";

	// Load planes
	CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadPlanes(&planesDir, &planesName);

	
	// Load Player Vehicle
	if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadPlayerVehicle(&carDir, &carName))) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "Player Vehicle not loaded correctly!");
		return GENERAL_ERROR;
	}
	CVehicle * PV = (CVehicle *)CGameStateManager::GetGameStateManagerPtr()->GetPlayerVehicle();
	PV->IsPlayer() = true;
	PV->SetPositionLC(Vector3f(0.0f, 0.0f, 0.0f));

	// Set its bounding box
	PV->GetBoundingBox()->Extent(0) = 1.5f;
	PV->GetBoundingBox()->Extent(1) = 0.5f;
	PV->GetBoundingBox()->Extent(2) = 0.6f;
	PV->GetBoundingBox()->Axis(0) = Vector3f(1.0f, 0.0f, 0.0f);
	PV->GetBoundingBox()->Axis(1) = Vector3f(0.0f, 1.0f, 0.0f);
	PV->GetBoundingBox()->Axis(2) = Vector3f(0.0f, 0.0f, 1.0f);
	PV->GetBoundingBox()->Center() = PV->GetPositionLC();

	/*** set bbox for tires ***/
	// First, initialize their extents and axis
	for (int i = 0; i < 4; i++) {
		PV->GetTire(i)->GetBoundingBox()->Extent(0) = 0.2f;
		PV->GetTire(i)->GetBoundingBox()->Extent(1) = 0.2f;
		PV->GetTire(i)->GetBoundingBox()->Extent(2) = 0.1f;
		PV->GetTire(i)->GetBoundingBox()->Axis(0) = Vector3f(1.0f, 0.0f, 0.0f);
		PV->GetTire(i)->GetBoundingBox()->Axis(1) = Vector3f(0.0f, 1.0f, 0.0f);
		PV->GetTire(i)->GetBoundingBox()->Axis(2) = Vector3f(0.0f, 0.0f, 1.0f);
	}

	// Now, prepare a vector that points from the car center to one of the tire centers
	// and use it to set each tire
// enum { FLTIRE, FRTIRE, RLTIRE, RRTIRE };
	Vector3f TireCenter = Vector3f (0.85f, -0.25f, 0.5f); // guestimate for FLTIRE
	PV->SetFLTirePosition(TireCenter);
	PV->GetTire(FLTIRE)->GetBoundingBox()->Center() = TireCenter + PV->GetBoundingBox()->Center();
	TireCenter.Z() *= -1.0f; // front-right
	PV->GetTire(FRTIRE)->GetBoundingBox()->Center() = TireCenter + PV->GetBoundingBox()->Center();
	TireCenter.X() *= -1.0f; // rear-right
	PV->GetTire(RRTIRE)->GetBoundingBox()->Center() = TireCenter + PV->GetBoundingBox()->Center();
	TireCenter.Z() *= -1.0f; // rear-left
	PV->GetTire(RLTIRE)->GetBoundingBox()->Center() = TireCenter + PV->GetBoundingBox()->Center();
	
	// Now, set its bounding sphere
	Vector3f RadiusVec;
	if (PV->GetBoundingSphere()) {
		PV->GetBoundingSphere()->Center() = PV->GetBoundingBox()->Center();
		RadiusVec = Vector3f(PV->GetBoundingBox()->Extent(0),
							 PV->GetBoundingBox()->Extent(1),
							 PV->GetBoundingBox()->Extent(2));
		PV->GetBoundingSphere()->Radius() = RadiusVec.Length();
	}
	else CLog::GetLog().Write(LOG_DEBUGOVERLAY, 60, "Vehicle %s has no bounding sphere", PV->GetName());

	/***************** Load a couple opponent vehicles *************************/

	// Opponent Vehicle 1
	if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadOpponentVehicle(&oppDir1, &oppName1))) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "Opponent Vehicle 1 not loaded correctly!");
		return GENERAL_ERROR;
	}	

	// Opponent Vehicle 2
	if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadOpponentVehicle(&oppDir2, &oppName2))) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "Opponent Vehicle 2 not loaded correctly!");
		return GENERAL_ERROR;
	}

	std::vector<COpponentVehicle*>::iterator OV = CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->begin();

	float sign = 1.0f;
	do {

	// sign = 1 --> ahead and to the right
	// sign = -1 --> ahead and to the left
	(*OV)->SetPositionLC(Vector3f(10.0f*sign, 10.0f*sign, 0.0f)); 

	// Set opponent vehicle's bounding box
	(*OV)->GetBoundingBox()->Extent(0) = 1.5f;
	(*OV)->GetBoundingBox()->Extent(1) = 0.5f;
	(*OV)->GetBoundingBox()->Extent(2) = 0.6f;
	(*OV)->GetBoundingBox()->Axis(0) = Vector3f(1.0f, 0.0f, 0.0f);
	(*OV)->GetBoundingBox()->Axis(1) = Vector3f(0.0f, 1.0f, 0.0f);
	(*OV)->GetBoundingBox()->Axis(2) = Vector3f(0.0f, 0.0f, 1.0f);
	(*OV)->GetBoundingBox()->Center() = (*OV)->GetPositionLC();

	/*** set bbox for tires ***/
	// First, initialize their extents and axis
	for (i = 0; i < 4; i++) {
		(*OV)->GetTire(i)->GetBoundingBox()->Extent(0) = 0.2f;
		(*OV)->GetTire(i)->GetBoundingBox()->Extent(1) = 0.2f;
		(*OV)->GetTire(i)->GetBoundingBox()->Extent(2) = 0.1f;
		(*OV)->GetTire(i)->GetBoundingBox()->Axis(0) = Vector3f(1.0f, 0.0f, 0.0f);
		(*OV)->GetTire(i)->GetBoundingBox()->Axis(1) = Vector3f(0.0f, 1.0f, 0.0f);
		(*OV)->GetTire(i)->GetBoundingBox()->Axis(2) = Vector3f(0.0f, 0.0f, 1.0f);
	}

	// Set opponent vehicle's tire positions
// enum { FLTIRE, FRTIRE, RLTIRE, RRTIRE };
	TireCenter = Vector3f (0.85f, -0.25f, 0.5f); // guestimate for FLTIRE
	(*OV)->SetFLTirePosition(TireCenter);
	(*OV)->GetTire(FLTIRE)->GetBoundingBox()->Center() = TireCenter + PV->GetBoundingBox()->Center();
	TireCenter.Z() *= -1.0f; // front-right
	(*OV)->GetTire(FRTIRE)->GetBoundingBox()->Center() = TireCenter + PV->GetBoundingBox()->Center();
	TireCenter.X() *= -1.0f; // rear-right
	(*OV)->GetTire(RRTIRE)->GetBoundingBox()->Center() = TireCenter + PV->GetBoundingBox()->Center();
	TireCenter.Z() *= -1.0f; // rear-left
	(*OV)->GetTire(RLTIRE)->GetBoundingBox()->Center() = TireCenter + PV->GetBoundingBox()->Center();
	
	// Now, set opponent vehicle's bounding sphere
	//Vector3f RadiusVec;
	if ((*OV)->GetBoundingSphere()) {
		(*OV)->GetBoundingSphere()->Center() = (*OV)->GetBoundingBox()->Center();
		RadiusVec = Vector3f((*OV)->GetBoundingBox()->Extent(0),
							 (*OV)->GetBoundingBox()->Extent(1),
							 (*OV)->GetBoundingBox()->Extent(2));
		(*OV)->GetBoundingSphere()->Radius() = RadiusVec.Length();
	}
	else CLog::GetLog().Write(LOG_DEBUGOVERLAY, 60, "Vehicle %s has no bounding sphere", (*OV)->GetName());

	OV++;
	sign = -sign;

	} while(OV != CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->end());

	/************* SET SOME WAYPOINTS *********************/

	CWaypoint* WP = new CWaypoint();
	WP->SetTranslate(Vector3f(100.0f, 0.0f, 40.0f));
	std::vector<CWaypoint*>* WP_vector = new std::vector<CWaypoint*>;
	WP_vector->push_back(WP);
	OV--;
	(*OV)->setWPSequence(WP_vector);
	(*OV)->initNext();

	COpponentAI::GetOpponentAIPtr()->addCar(*OV);
	
	CWaypoint* WP2 = new CWaypoint();
	WP->SetTranslate(Vector3f(100.0f, 0.0f, -40.0f));
	std::vector<CWaypoint*>* WP_vector2 = new std::vector<CWaypoint*>;
	WP_vector2->push_back(WP2);	
	OV--;
	(*OV)->setWPSequence(WP_vector2);
	(*OV)->initNext();

	COpponentAI::GetOpponentAIPtr()->addCar(*OV);

	/****** OTHER MISCELLANEOUS STUFF **********/

	// Make planes visible
	string drawplanes = "drawplanes 1";
	parse(drawplanes);
	execute();

	// Make bounding boxes visible
	string drawentbbox = "drawentbbox 1";
	parse(drawentbbox);	
	execute();

	// set camera
	CRenderer::GetRenderer().SetActiveCamera(CAMERA_FREELOOK);
    ((CCameraChase *)CRenderer::GetRenderer().GetActiveCameraPtr())->SetVehicle(CGameStateManager::GetGameStateManager().GetPlayerVehicle());

	return OK;
}

