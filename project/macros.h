#ifndef MACROS_H
#define MACROS_H

#include <windows.h>
#include "dxutil.h"
#include "timer.h"
#include "log.h"



#ifdef _DEBUG
#define NEW(name, type, errorString)	{ (name) = new (type); if(!(name)) { CLog::GetLog().Write(LOG_MISC, "%s", (errorString)); return 0;}}
#else if
#define NEW(name, type, errorString)	{ (name) = new (type); if(!(name)) return 0; }
#endif

#ifdef _DEBUG
#define FREE(name, errorString)	{ if(name) { delete name; name = NULL;} else { CLog::GetLog().Write(LOG_MISC, "%s", errorString);} }
#else if
#define FREE(name, errorString)	{ if(name) { delete name; name = NULL;} }
#endif



// for tiles
#define STREET_WIDTH 80.0f // this is arbitrary for now
#define TILE_WIDTH 100.0f
#define OFFSET_FROM_CENTER_LANE 10.0f // where to position cars relative to street center 
#define STD_INDENT_INTO_STREET 40.0f // where to position car along street from tile edge
// use this as a quick way to set car's x/y position on tile [i].
// set op to '+' or '-' depending on direction car is facing
// Ex: Car.Pos = Vector3<float>(CAR_POS(2,-), CAR_POS(3,+), 0.0f);
// This says, set the cars position to the left(-) upper(+) area of tile[2,3].
#define CAR_POS(i,op) (i*TILE_WIDTH + TILE_WIDTH/2.0f op OFFSET_FROM_CENTER_LANE)
// to set car into tile i indented by n into tile i, use this:
// Used for positioning parallel to road
// suggestions for n: STD_INDENT_INTO_STREET or TILE_WIDTH - STD_INDENT_INTO_STREET
#define SET_STD_INDENT(i,n) (i*TILE_WIDTH + n)
// With the 2 macros above, use one for the x position and the
// other for the y. It doesn't matter which.
// macros for integration of outside modules
#define TIMER Timer
#define CLOCK /*(TIMER->GetCurrentTime())*/ DXUtil_Timer(TIMER_GETABSOLUTETIME) // see dxutil.h
#define INPUT CInput
#define DETECTCOLLISION(a) true 
// macros for AI class
#define WORLD_WIDTH 10
#define WORLD_LENGTH 10
// street types
#define FOURWAY 0
#define THREEWAY_NORTH 1
#define THREEWAY_EAST 2
#define THREEWAY_SOUTH 3
#define THREEWAY_WEST 4
#define CORNER_NW 5
#define CORNER_NE 6
#define CORNER_SE 7
#define CORNER_SW 8 // note: clockwise
#define VERTICLE 9
#define HORIZONTAL 10
// CTrafficLight macros
#define GREEN 0
#define YELLOW 1
#define RED 2
#define GREEN_TIME 50.0f // idunno
#define YELLOW_TIME 10.0f
#define RED_TIME (GREEN_TIME + YELLOW_TIME)
// useful for anything:
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3 // note: clockwise again

// conversion macros
#ifndef PI_BOS
#define PI_BOS	3.1415926f
#define RADIANS(a) ((PI_BOS*a)/180.0f) // convert from degrees to radians
#define DEGREES(a) ((a*180.0f)/PI_BOS) // convert from radians to degrees
#endif
#define MPS_TO_MPH_CONSTANT 2.23693629f

// for waypoint positions (add to N,E,S,W above):
#define LEAVING 0
#define COMING 4
// for TrafficVehicles:
#define STD_TRAFFIC_VELOCITY 80.0f // idunno
#define STD_TRAFFIC_ACCEL 5.0f
#define STD_CAP_DIST 10.0f
// for PlayerVehicle:
#define ROT_SCALE 10.0f
#define VEL_SCALE 10.0f
// for CWaypoint class:
#define WP_PROX_LIM 0.1f // dunno
// for vehicle types
#define MAX_VEHICLE_TYPES 10

// simple interpolation
#define LERP(a,b,c)     (((b) - (a)) * (c) + (a))

// for collision types
#define REFLECTIVE 1
#define PUSHED 2
#define SPHERE_TO_SPHERE 3

// error codes:
#define OK 0
#define GENERAL_ERROR 1
#define INDEX_OUT_OF_RANGE 2
#define NULL_POINTER 3
#define INVALID_STREET_TYPE 4
#define INVALID_TRAFFICLIGHT_STATE 5
#define NO_VEHICLE_TO_SIGNAL 6
#define INVALID_INTERSECTION_TYPE 7
#define NEGATIVE_COUNTER 8
#define RETURN_EMPTY_ARRAY 9
#define INVALID_TRAFFICLIGHT_SIDE 10
#define POINTER_OCCUPIED 11
#define NEGATIVE_MASS 12
#define INVALID_VEHICLE_TYPE 13
#define CAP_POS_NULL 14
#define CAP_NULL 15
#define BAD_COMMAND 16
#define EMPTY_VECTOR 17
#define NEGATIVE_VALUE 18
#define NO_SUCH_FONT 19
#define INVALID_COLLISION_TYPE 20

static int global_error; // for functions that don't return ints but can encounter errors
// global_error not working properly
// end error codes

#endif
