
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
	//Keywords.push_back(std::string("clearscene"));
	Keywords.push_back(std::string("physicstest1"));
	/*** End Chris' Commands ***/

    /*** Begin J's Commands ***/
    Keywords.push_back(std::string("loadmeshtest"));
    Keywords.push_back(std::string("cameratest"));
    Keywords.push_back(std::string("loadmap"));
    Keywords.push_back(std::string("unloadmap"));
    /*** End J's Commands ***/
    
    /** Begin Ram & Gib Commands **/
    Keywords.push_back(std::string("loadvehicleai"));
    /*** End Ram & Gib Commands ***/

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
	//if (*it == "clearscene") error = ClearScene();
	if (*it == "physicstest1") error = PhysicsTest1();

    if (*it == "unloadmap") error = unloadmap();
    if (*it == "loadmap") error = loadmap();
    if (*it == "loadmeshtest") error = loadmeshtest();
    if (*it == "cameratest") error = cameratest();
    if (*it == "loadvehicleai") error = LoadVehicleAI();

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
	CLog::GetLog().Write(LOG_GAMECONSOLE, "-----------------------");
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
	CLog::GetLog().Write(LOG_GAMECONSOLE, "LOADPLAYERVEHICLE <params> - load a new player vehicle");
    CLog::GetLog().Write(LOG_GAMECONSOLE, "LOADMESHTEST <file> <dir> - load a mesh at some directory (leave .x extension off");
    CLog::GetLog().Write(LOG_GAMECONSOLE, "CAMERATEST <CAMERA_NAME> - change cameras to a specific one: {CAMERA_FREELOOK, CAMERA_CHASE, CAMERA_BUMPER}");
    CLog::GetLog().Write(LOG_GAMECONSOLE, "LOADMAP <file> <dir> - load a map and create a scene from a .map file");
    CLog::GetLog().Write(LOG_GAMECONSOLE, "UNLOADMAP - unload current map");
	CLog::GetLog().Write(LOG_GAMECONSOLE, "-----------------------");
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

int CCommandLineParser::LoadPlayerVehicle()
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
		if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadPlayerVehicle(&directory, &filename))) {
			CLog::GetLog().Write(LOG_GAMECONSOLE, "The scene was not loaded successfully!");
			return 0;
		}
	}
	

	CLog::GetLog().Write(LOG_GAMECONSOLE, "Command not implemented yet, please come again!");

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

int CCommandLineParser::PhysicsTest1()
{
    string sDir = CSettingsManager::GetSettingsManager().GetGameSetting(DIRDYNVEHICLES)+"mitsuEclipse\\";
	string sName = "mitsuEclipse.car";

	if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadPlayerVehicle(&sDir, &sName))) {
		CLog::GetLog().Write(LOG_GAMECONSOLE, "The scene was not loaded successfully!");
		return OK;
	}

    /*J fucken w Chris' shit*/

    //set the active camera to the chase cam
    CRenderer::GetRenderer().SetActiveCamera(CAMERA_CHASE);

    //set it to chase the vehicle we just created
    ((CCameraChase *)CRenderer::GetRenderer().GetActiveCameraPtr())->SetVehicle(CGameStateManager::GetGameStateManager().GetPlayerVehicle());

	return OK;

}
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

    if (Tokens.size() < 3)  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "not enough arguements, loading scene from debug.map");
        sName = "debug";
        sDir = CSettingsManager::GetSettingsManager().GetGameSetting(DIRMAP) + sName + "\\";
    }
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

    // load the new map and scene
    if (CGameStateManager::GetGameStateManager().GetScenePtr()->LoadMap( fp, &sDir, &sName ))  {
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
    if (Tokens.size() < 3)  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "not enough arguements, loading default mesh: pylon");
        sDir = CSettingsManager::GetSettingsManager().GetGameSetting(DIRMESH) + "static\\pylon\\";
        sName = "pylon";
    }
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
    if (Tokens.size()<2)  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "not enough arguements to cameratest");
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

// ===== End Jay's functions ==== //


// ===== Begin Ram & Gib Functions ==== //
int CCommandLineParser::LoadVehicleAI()
{
    //use defaults, all good for us
    //start pylon
    loadmeshtest();
    //end pylon
    loadmeshtest();

    //TODO Load Entities for waypoints
    //TODO Translate existing pylons to same positions as waypoints

    loadmap();
	return OK;

}

//  ===== End Ram & Gibs Functions =====//

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