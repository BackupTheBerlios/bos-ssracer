#ifndef SETTINGS_H
#define SETTINGS_H

// --- system includes --- //
#define STL_USING_ALL
#include "stl.h"

// --- internal library includes --- //
#include "bos.h"
#include "log.h"


//-----------------------------------------------------------------------------
// Name:  class CSettingsManager
// Desc:  reads in game specific settings from game settings file and initializes
// default settings for compatibility
//-----------------------------------------------------------------------------
class CSettingsManager
{
public:
    CSettingsManager( std::string kSettingsFileName );
	static CSettingsManager & GetSettingsManager();
    static CSettingsManager * GetSettingsManagerPtr();
	virtual ~CSettingsManager();
    void LoadDefaultSettings(); // loads predefined settings into map

protected:
    static CSettingsManager * ms_pkSettingsMgr;
    std::map< std::string, std::string > m_settingMap;
};



#endif 
//END settings.h ==============================================================