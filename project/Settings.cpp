#include "settings.h"


CSettingsManager * CSettingsManager::ms_pkSettingsMgr = NULL;
std::map< GameSetting, std::string > CSettingsManager::m_settingMap;


CSettingsManager & CSettingsManager::GetSettingsManager(){ return * ms_pkSettingsMgr; }
CSettingsManager * CSettingsManager::GetSettingsManagerPtr(){ return ms_pkSettingsMgr; }


CSettingsManager::CSettingsManager( std::string kSettingsFileName )
{
    // // read settings from a file and put register them in the game
    ms_pkSettingsMgr = this;
}

CSettingsManager::~CSettingsManager()
{
}


//-----------------------------------------------------------------------------
// Name:  LoadDefaultSettings()
// Desc:  Intializes default game settings for compatibility
//-----------------------------------------------------------------------------
void CSettingsManager::LoadDefaultSettings() {
    TCHAR szCWD[1024];
    GetCurrentDirectory( sizeof(szCWD), szCWD);

    // get the #$!#! current working directory
    m_settingMap[DIRCURRENTWORKING] = string(szCWD) + "\\";

    // root level dirs
    m_settingMap[DIRMAP]   = m_settingMap[DIRCURRENTWORKING] + "maps\\";
    m_settingMap[DIRMEDIA] = m_settingMap[DIRCURRENTWORKING] + "media\\";

    // media level
    m_settingMap[DIRSOUND] = m_settingMap[DIRMEDIA] + "sound\\";
    m_settingMap[DIRMUSIC] = m_settingMap[DIRMEDIA] + "music\\";
    m_settingMap[DIRMESH]  = m_settingMap[DIRMEDIA] + "meshes\\";
    m_settingMap[DIRTEXTURES] = m_settingMap[DIRMEDIA] + "textures\\";

    // dynamic mesh paths
    m_settingMap[DIRDYNMESH]  = m_settingMap[DIRMESH] + "dynamic\\";
    m_settingMap[DIRDYNVEHICLES]  = m_settingMap[DIRDYNMESH] + "vehicles\\";
    m_settingMap[DIRDYNPROPS]  = m_settingMap[DIRDYNMESH] + "props\\";

    // static mesh paths
    m_settingMap[DIRSTATICMESH]  = m_settingMap[DIRMESH] + "static\\";
    m_settingMap[DIRSTATICPROPS]  = m_settingMap[DIRSTATICMESH] + "props\\";
    m_settingMap[DIRSTATICBUILDINGS]  = m_settingMap[DIRSTATICMESH] + "buildings\\";
    m_settingMap[DIRSTATICMISC]  = m_settingMap[DIRSTATICMESH] + "misc\\";

    // debug mesh path
    m_settingMap[DIRDEBUG] = m_settingMap[DIRMEDIA] + "debug\\";

    #ifdef _DEBUG
    CLog::GetLog().Write(LOG_MISC, "GSManager:  Loaded game settings");
    for (map<GameSetting, string>::iterator it = m_settingMap.begin(); it!=m_settingMap.end(); it++){
        CLog::GetLog().Write(LOG_MISC, "Setting: %d value %s", (int)it->first, it->second.c_str());
    }
    #endif

}



//END settings.cpp ============================================================