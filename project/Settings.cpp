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

}



//END settings.cpp ============================================================