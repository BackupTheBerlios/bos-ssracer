# Microsoft Developer Studio Project File - Name="ssracer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ssracer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ssracer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ssracer.mak" CFG="ssracer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ssracer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ssracer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ssracer - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D _WIN32_WINNT=0x0501 /D "WML_IMPORT_DLL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 d3dx9.lib dsound.lib dinput8.lib dxerr9.lib d3d9.lib d3dxof.lib dxguid.lib winmm.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 WildMagic2.lib Kernel32.lib d3dx9dt.lib dsound.lib dinput8.lib dxerr9.lib d3d9.lib d3dxof.lib dxguid.lib winmm.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"MSVCRTD.LIB"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ssracer - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "DEBUG" /D _WIN32_WINNT=0x0501 /D "WML_IMPORT_DLL" /FR /YX /FD /D /NODEFAULTLIB:MSVCRTD.LIB" /GZ " /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG" /d "DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 d3dx9dt.lib dsound.lib dinput8.lib dxerr9.lib d3d9.lib d3dxof.lib dxguid.lib winmm.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 WildMagic2.lib Kernel32.lib d3dx9dt.lib dsound.lib dinput8.lib dxerr9.lib d3d9.lib d3dxof.lib dxguid.lib winmm.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"MSVCRT.LIB" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "ssracer - Win32 Release"
# Name "ssracer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Core Sources"

# PROP Default_Filter ".cpp"
# Begin Group "Game Console Sources"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\ccommandlineparser.cpp
# End Source File
# Begin Source File

SOURCE=.\cinputconsole.cpp
# End Source File
# Begin Source File

SOURCE=.\consolemessage.cpp
# End Source File
# Begin Source File

SOURCE=.\consoletask.cpp
# End Source File
# End Group
# Begin Group "System Sources"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\kernel.cpp
# End Source File
# Begin Source File

SOURCE=.\task.cpp
# End Source File
# Begin Source File

SOURCE=.\timer.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\appstate.cpp
# End Source File
# Begin Source File

SOURCE=.\bosapp.cpp
# End Source File
# Begin Source File

SOURCE=.\log.cpp
# End Source File
# Begin Source File

SOURCE=.\Settings.cpp
# End Source File
# End Group
# Begin Group "Renderer Sources"

# PROP Default_Filter ".cpp"
# Begin Group "D3D Sources"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\d3denumeration.cpp
# End Source File
# Begin Source File

SOURCE=.\d3dfile.cpp
# End Source File
# Begin Source File

SOURCE=.\d3dfont.cpp
# End Source File
# Begin Source File

SOURCE=.\d3dsettings.cpp
# End Source File
# Begin Source File

SOURCE=.\d3dutil.cpp
# End Source File
# End Group
# Begin Group "Camera Sources"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\camera.cpp
# End Source File
# Begin Source File

SOURCE=.\camerafreelook.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\renderer.cpp
# End Source File
# Begin Source File

SOURCE=.\rendertask.cpp
# End Source File
# End Group
# Begin Group "Sound Sources"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\Sound.cpp
# End Source File
# Begin Source File

SOURCE=.\SoundCore.cpp
# End Source File
# Begin Source File

SOURCE=.\soundmessage.cpp
# End Source File
# Begin Source File

SOURCE=.\soundtask.cpp
# End Source File
# Begin Source File

SOURCE=.\thread.cpp
# End Source File
# End Group
# Begin Group "Input Sources"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\input.cpp
# End Source File
# Begin Source File

SOURCE=.\inputmessage.cpp
# End Source File
# Begin Source File

SOURCE=.\inputtask.cpp
# End Source File
# End Group
# Begin Group "AI Sources"

# PROP Default_Filter ".cpp"
# Begin Group "ChrisSceneConstruct Sources"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\entity.cpp
# End Source File
# Begin Source File

SOURCE=.\scene.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\aimessage.cpp
# End Source File
# Begin Source File

SOURCE=.\aitask.cpp
# End Source File
# Begin Source File

SOURCE=.\gamestatemanager.cpp
# End Source File
# End Group
# Begin Group "Physics Sources"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\physicstask.cpp
# End Source File
# End Group
# Begin Group "Front End Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cbutton.cpp
# End Source File
# Begin Source File

SOURCE=.\clabel.cpp
# End Source File
# Begin Source File

SOURCE=.\cscreens.cpp
# End Source File
# Begin Source File

SOURCE=.\ctextfield.cpp
# End Source File
# Begin Source File

SOURCE=.\cwidget.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\dxutil.cpp
# End Source File
# Begin Source File

SOURCE=.\ssracer.rc

!IF  "$(CFG)" == "ssracer - Win32 Release"

# ADD BASE RSC /l 0x1009
# ADD RSC /l 0x409

!ELSEIF  "$(CFG)" == "ssracer - Win32 Debug"

# ADD BASE RSC /l 0x1009
# ADD RSC /l 0x409
# SUBTRACT RSC /x

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\winmain.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Renderer Headers"

# PROP Default_Filter ".h"
# Begin Group "D3D Common Headers"

# PROP Default_Filter ".h"
# Begin Source File

SOURCE=.\d3denumeration.h
# End Source File
# Begin Source File

SOURCE=.\d3dfile.h
# End Source File
# Begin Source File

SOURCE=.\d3dfont.h
# End Source File
# Begin Source File

SOURCE=.\d3dsettings.h
# End Source File
# Begin Source File

SOURCE=.\d3dutil.h
# End Source File
# End Group
# Begin Group "Camera Headers"

# PROP Default_Filter ".h"
# Begin Source File

SOURCE=.\camera.h
# End Source File
# Begin Source File

SOURCE=.\camerafreelook.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\renderer.h
# End Source File
# Begin Source File

SOURCE=.\rendermessage.h
# End Source File
# Begin Source File

SOURCE=.\rendertask.h
# End Source File
# End Group
# Begin Group "Sound Headers"

# PROP Default_Filter ".h, .hpp"
# Begin Source File

SOURCE=.\SoundCore.h
# End Source File
# Begin Source File

SOURCE=.\soundmessage.h
# End Source File
# Begin Source File

SOURCE=.\soundtask.h
# End Source File
# Begin Source File

SOURCE=.\thread.h
# End Source File
# End Group
# Begin Group "Input Headers"

# PROP Default_Filter ".h"
# Begin Source File

SOURCE=.\input.h
# End Source File
# Begin Source File

SOURCE=.\inputmessage.h
# End Source File
# Begin Source File

SOURCE=.\inputtask.h
# End Source File
# End Group
# Begin Group "AI Headers"

# PROP Default_Filter ".h"
# Begin Group "ChrisSceneConstruct Headers"

# PROP Default_Filter ".h"
# Begin Source File

SOURCE=.\entity.h
# End Source File
# Begin Source File

SOURCE=.\scene.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\aimessage.h
# End Source File
# Begin Source File

SOURCE=.\aitask.h
# End Source File
# Begin Source File

SOURCE=.\gamestatemanager.h
# End Source File
# End Group
# Begin Group "Physics Headers"

# PROP Default_Filter ".h"
# Begin Source File

SOURCE=.\physicstask.h
# End Source File
# End Group
# Begin Group "Core Headers"

# PROP Default_Filter ".h"
# Begin Group "Game Console headers"

# PROP Default_Filter ".h"
# Begin Source File

SOURCE=.\ccommandlineparser.h
# End Source File
# Begin Source File

SOURCE=.\cinputconsole.h
# End Source File
# Begin Source File

SOURCE=.\consolemessage.h
# End Source File
# Begin Source File

SOURCE=.\consoletask.h
# End Source File
# End Group
# Begin Group "System Headers"

# PROP Default_Filter ".h"
# Begin Source File

SOURCE=.\kernel.h
# End Source File
# Begin Source File

SOURCE=.\task.h
# End Source File
# Begin Source File

SOURCE=.\testtask.h
# End Source File
# Begin Source File

SOURCE=.\timer.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\appstate.h
# End Source File
# Begin Source File

SOURCE=.\bosapp.h
# End Source File
# Begin Source File

SOURCE=.\log.h
# End Source File
# Begin Source File

SOURCE=.\Settings.h
# End Source File
# End Group
# Begin Group "Front End Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cbutton.h
# End Source File
# Begin Source File

SOURCE=.\clabel.h
# End Source File
# Begin Source File

SOURCE=.\cscreens.h
# End Source File
# Begin Source File

SOURCE=.\ctextfield.h
# End Source File
# Begin Source File

SOURCE=.\cwidget.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\bos.h
# End Source File
# Begin Source File

SOURCE=.\dxutil.h
# End Source File
# Begin Source File

SOURCE=.\macros.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\stl.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\DirectX.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\README.txt
# End Source File
# End Target
# End Project
