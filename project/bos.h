/*****************************************************************************
*
* File:  bos.h 
*
* BurnOut Studios - Super Street Racer
* Module:  All - internal declarations and includes
* Author:  Jay Javier
* Modified by:  On: 
* Date Created:  Jan 18, 2003
*
******************************************************************************
* Desc:  general include file for common headers
*****************************************************************************/
#ifndef BOS_H
#define BOS_H    

#ifndef DIRECT3D_VERSION
#define DIRECT3D_VERSION         0x0900
#endif  //DIRECT3D_VERSION

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION      0x0800
#endif

#ifndef DIRECTSOUND_VERSION
#define DIRECTSOUND_VERSION      0x0900
#endif

#define BOSAPPVERSION "BETA 3.0"

/*
 * Disable following warnings when including Windows headers
 *
 * warning C4115: named type definition in parentheses
 * warning C4116: unnamed type definition in parentheses
 * warning C4127: conditional expression is constant
 * warning C4201: nonstandard extension used : nameless struct/union
 * warning C4214: nonstandard extension used : bit field types other than int
 * warning C4514: unreferenced inline function has been removed
 * warning C4786: symbol names being too long for the debug information
 */
#pragma warning( disable : 4115 4116 4127 4201 4214 4514 4786 4100)

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN

// include project resources
#include "resource.h" 

#endif
//END bos.h ==============================================================