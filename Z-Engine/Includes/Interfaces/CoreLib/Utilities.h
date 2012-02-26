/**
 *	@file Z-Engine\Z-Engine\Interfaces\CoreLib\Utilities.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _UTILITIES_H__Included_518702893
#define _UTILITIES_H__Included_518702893

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

namespace ZGE
{

	#define SafeDelete(a){	if( a )	{ delete a; a = NULL; } }
	#define SafeRelease(a) { if( a ) { a->Release( ); a = NULL; } }
	#define SafeDeleteArray(a) { if( a ) { delete [] a; a = NULL; } }
	#define NULL 0
	#define UNUSED_VAR(a) { a; }
	#define _NUM_ARRAY_ELEMENTS(arg) (sizeof(arg)/sizeof(arg[0]))
#define STR_PRINT sprintf_s

	class ZUtilities
	{
	public:
	/************************
	// String helper functions
		/**
		* Returns the input as a string
		**/
		template<typename T> const char* ToString(const T& _value)
		{
			std::ostringstream TheStream; 
			TheStream << _value << std::ends; 
			return(TheStream.str()); 
		}

		/**
		* Converts a string to upper case 
		**/
		inline void string2Upper( char* str)
		{
			uint32 uStrLen = strlen( str ) + 1;
			for (uint32 i = 0; i < uStrLen; ++i)
			{
				str[i] = static_cast<char8>(toupper(str[i]));
			}
		}

	/****************************
	// Random number generators

		/**
		* Returns a random integer value between _kiLow and _kiHigh
		**/
		inline sint32 RandomI( const sint32 _kiLow, const sint32 _kiHigh)
		{
			return ((rand() % _kiHigh) + _kiLow);
		}

		/**
		* Returns a random float value between 0.0f and 1.0f
		**/
		inline float32 RandomF()
		{
			return(static_cast<float32>(rand()) / static_cast<float32>(RAND_MAX));
		}

		/**
		* Returns a random float value between _fMin and _fMax
		**/
		inline float32 RandomF( const float32 _fMin, const float32 _fMax)
		{
			return (RandomF() * (_fMax - _fMin) + _fMin);
		}

	/****************
	// Colour converter functions
		/*
		*  Optimization - multiply by this to convert colours to floats.
		*/ 
		// 1.0f / 255
#define Z_COLOUR_DIVISOR 0.003921568627f 
		
		 /*
		 *  Convert a colour from UINT32 into 4 floats
		 *  Param uColor : The color to convert.
		 *  Param pFloatArray : Array of 4 floats, populated with color values.
		 */ 
		inline static void ConvertColorToFloat( uint32 uColor, float32* pFloatArray )
		{
	 
			pFloatArray[0] = static_cast<float32>( ( ( uColor & 0xFF000000 ) >> 24 ) * Z_COLOUR_DIVISOR );
			pFloatArray[1] = static_cast<float32>( ( ( uColor & 0x00FF0000 ) >> 16 ) * Z_COLOUR_DIVISOR );
			pFloatArray[2] = static_cast<float32>( ( ( uColor & 0x0000FF00 ) >> 8 ) * Z_COLOUR_DIVISOR );
			pFloatArray[3] = static_cast<float32>( ( ( uColor & 0x000000FF ) >> 0 ) * Z_COLOUR_DIVISOR );
		}

		 /*
		 *  Convert a colour from UINT32 into 4 floats. Reverse order.
		 *  Param uColor : The color to convert.
		 *  Param pFloatArray : Array of 4 floats, populated with color values.
		 */ 
		inline static void ConvertColorToFloatRGBA( uint32 uColor, float32* pFloatArray )
		{
			pFloatArray[0] = static_cast<float32>( ( ( uColor & 0x00FF0000 ) >> 16 ) * Z_COLOUR_DIVISOR );
			pFloatArray[1] = static_cast<float32>( ( ( uColor & 0x0000FF00 ) >> 8 ) * Z_COLOUR_DIVISOR );
			pFloatArray[2] = static_cast<float32>( ( ( uColor & 0x000000FF ) >> 0 ) * Z_COLOUR_DIVISOR );
			pFloatArray[3] = static_cast<float32>( ( ( uColor & 0xFF000000 ) >> 24 ) * Z_COLOUR_DIVISOR );
		}


		 /*
		 *  Convert a colour from 4 UINT8s into 4 floats.
		 *  Param pColor The color to convert.
		 *  Param pFloatArray Array of 4 floats, populated with color values.
		 */ 
		inline static void ConvertColorToFloat( const uint32* pColor, float32* pFloatArray )
		{
			pFloatArray[3] = static_cast<float32>( pColor[0] * Z_COLOUR_DIVISOR );
			pFloatArray[2] = static_cast<float32>( pColor[1] * Z_COLOUR_DIVISOR );
			pFloatArray[1] = static_cast<float32>( pColor[2] * Z_COLOUR_DIVISOR );
			pFloatArray[0] = static_cast<float32>( pColor[3] * Z_COLOUR_DIVISOR );
		}

		/**
		 *	Performs a string comparison.
		 *	@param _kpcStringA	To be compared with string B.
		 *  @param _kpcStringB  To be compared with string A.
		 *	@return True if they are the same
		 */
		inline static bool StrCmp( const char* _kpcStringA, const char* _kpcStringB )
		{
	#ifdef Z_PLATFORM_WIN
			// We are using the windows platform.
			if( 0 == _strcmpi( _kpcStringA, _kpcStringB ) )
			{
				return true;
			}
			return false;
	#endif
		}

		/**
		 *	Prints a data into a string
		 *	@param _pcDest The string to be populated.
		 *	@param _kpcSource The string to populate the destination string
		 */
		inline static void StrPrint( char* _pcDest, const char* _kpcFormat, const uint32 _kuSize , ...)
		{
			va_list ap;
			va_start(ap, _kpcFormat);
			sint32 iChars = vsnprintf_s(_pcDest, _kuSize, _kuSize, _kpcFormat, ap);
			va_end(ap);
		}
	};
}
#endif //_UTILITIES_H__Included_518702893

