#include "settings.h"


CSettingsManager * CSettingsManager::ms_pkSettingsMgr = NULL;


CSettingsManager::CSettingsManager( std::string kSettingsFileName )
{
    ms_pkSettingsMgr = this;

}

CSettingsManager::~CSettingsManager()
{
}




CSettingsManager & CSettingsManager::GetSettingsManager(){ return * ms_pkSettingsMgr; }
CSettingsManager * CSettingsManager::GetSettingsManagerPtr(){ return ms_pkSettingsMgr; }



//-----------------------------------------------------------------------------
// Name:  LoadDefaultSettings()
// Desc:  Intializes default game settings for compatibility
//-----------------------------------------------------------------------------
void CSettingsManager::LoadDefaultSettings() {
    m_settingMap[DIRMAP]   = ".\\maps\\";
    m_settingMap[DIRMEDIA] = ".\\media\\";
    m_settingMap[DIRSOUND] = m_settingMap[DIRMEDIA] + "sound\\";
    m_settingMap[DIRMUSIC] = m_settingMap[DIRMEDIA] + "music\\";
    m_settingMap[DIRMESH]  = m_settingMap[DIRMEDIA] + "meshes\\";
    m_settingMap[DIRDEBUG] = m_settingMap[DIRMEDIA] + "debug\\";

}



//END settings.cpp ============================================================