Super Street Racer
BETA 3.0 Release Documentation -- Readme.txt
https://developer.berlios.de/projects/bos-ssracer/


BETA 3.0 *********** CURRENT VERSION PLEASE FILL THIS IN **************
--------
[DD.MM.2004]

Changes / Additions :
Added LOG_DEBUGOVERLAY
Added loadmap console command
Added unloadmap console command
Added loadmeshtest console command

Bug Fixes:
- no longer crashes if no gamepad connected

Known Bugs: 
- older gamepads keep sending input to console


BETA 2.0
--------
[10.3.2004]

Changes / Additions :
- Total restructuring of project
- All game specific tasks are disabled
- only essential tasks are running

Bug Fixes:
- no longer crashes on release mode


BETA 1.1 
--------
[9.3.2004]

Changes / Additions :
- Added gamepad support

Bug Fixes:
- wheels are now rendered properly

Known Bugs: 
- game crashes if no gamepad is connected


BETA 1.0 
--------
[8.3.2004]

Changes / Additions :
- Added chase camera
- Added camera selection

Known Bugs: 
- map scale is way off
- wheels cannot render properly


ALPHA 4.0 (Internal Release)
--------
[7.3.2004]

Changes / Additions :
- buffered input
- Added various misc console commands
- Added dynamic map loading command
- Renderer is now a singleton

Bug Fixes:

Known Bugs:
- physics engine is wack
- meshes have to be edited outside program to be oriented properly
- memory leak when map is unloaded


ALPHA 3.0 (Internal Release)
--------
[5.3.2004]

Changes / Additions :
* new input module
- Added in game console input buffer
- Added basic debugging camera

Bug Fixes:
- memory leak in messaging system causing crashes
- input only sends scancodes

Known Bugs:
- needs to be re-integrated with features from old input module
- needs buffered input
- tasks need to change input message handling 
- .X meshes need to be manually edited so textures can be found on system


ALPHA 3.0a (Internal Release)
--------
[4.3.2004]

Changes / Additions :
- Added console tasking
- game timer now operates in "Real Time"
- Added Map Loading
- Added Map Rendering

Bug Fixes:
- fixed game console multi-line drawing

Known Bugs:
- game crashes on rapid and simultaneous keypresses
- input sending wrong keys in messages
- loose thread in sound core causes game to hang in release mode



ALPHA 2.0 (BROKEN on CVS)
--------
[3.3.2004]

Changes / Additions :
* project is now using multi-threaded DLLs + static libraries
* game AI now integrated
- basic communication between modules via messaging system
- Added toggle keys

Bug Fixes:
- game timer now returns correct values



ALPHA 1.0
--------
[2.29.2004]

Changes / Additions :
- CTimer now a singleton class
- Added mesh loading and rendering
- Added basic camera model
- Added new LOG_GAMECONSOLE (press ~ to view)
- full keyboard input handler
- Added messaging service to kernel
- Changed renderer task to use messaging system
- Changed game directory structure for /media


Bug Fixes:
- message deletion after sending doesn't result in VC6 debug error
- mesh rendering fixed



ALPHA 0.0
--------
[2.23.2004]

Features :
- multithreaded windows application layer
- application state manager
- game kernel with task management
- all system tasks are running (timer, input, sound, renderer)
- logging utility with new log LOG_MISC cleared on each run
- game timer has a variable timestep
- DirectSound sound core plays music and sound effects with fading
- basic DirectInput handler
- basic D3D renderer supports windowed/fullscreen with font rendering
- game settings manager (not fully functional yet)


Known Bugs:
- game hangs in release mode




-------------------- notes ---------------------------------
make sure you have the /media directory present with the sound files and meshes



------------------ credits ---------------------------------


THE BURNOUT STUDIOS TEAM
------------------------


Jay Javier
Project Lead, Core/Application Programmer, Graphics Programmer


Christian Meredith
Game AI Programmer, Game Utility Programmer


Rob Diaz
Sound Programmer, Communication Programmer, Webmaster


Ramit Karr
3D Modeler, Input Programmer


Gibran Shah
Opponent/Traffic AI Programmer, Utility Programmer



Project Webpage on berliOS:  https://developer.berlios.de/projects/bos-ssracer/
Official Website:  http://cpsc585.draggor.com/
