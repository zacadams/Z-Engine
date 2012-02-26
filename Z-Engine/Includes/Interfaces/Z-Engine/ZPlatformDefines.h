/**
 *	@file Z-Engine\Z-Engine\Includes\Interfaces\CoreLib\ZPlatformDefines.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _ZPLATFORMDEFINES_H__Included_692980818
#define _ZPLATFORMDEFINES_H__Included_692980818

// Platform 

#define Z_ENABLE_PERFORMANCE_TEST

// Hacks, if _WIN32 is defined we are using windows
#ifdef _WIN32
#define Z_PLATFORM_WIN
#else
// we are using IOS
#define Z_PLATFORM_IOS
#endif

// Render method
#define USING_DIRECT_DRAW

// Scene
#define USING_SCENE_INTERFACE
#define _2D_SCENE

// sprites
#define USING_SPRITE_INTERFACE
#define USING_XML_SPRITE_IO

// Camera
#define USING_CAMERA_INTERFACE

// Input
#define USING_INPUT_INTERFACE
// Can only use key board and mouse on Windows
#ifdef Z_PLATFORM_WIN
#define USING_KEYBOARD_INPUT
#define USING_MOUSE_INPUT
#endif

#ifdef Z_PLATFORM_IOS
//#define USING_TOUCH_INPUT
#endif
// Audio

#endif //_ZPLATFORMDEFINES_H__Included_692980818

