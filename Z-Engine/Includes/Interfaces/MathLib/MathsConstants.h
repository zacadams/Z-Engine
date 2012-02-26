/**
 *	@file Z-Engine\Z-Engine\Interfaces\MathLib\MathsConstants.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _MATHSCONSTANTS_H__Included_1318943118
#define _MATHSCONSTANTS_H__Included_1318943118

namespace ZGE
{
	// Constants
	const float32 g_kfPI		= 3.1415927f;
	const float32 g_kfHalfPI	= 1.5707963f;
	const float32 g_kfQuarterPI = 0.7853982f;
	const float32 g_kfEpsilon	= 0.000001f;

	/**
	* Takes a value in degrees and returns the relative value in radians.
	**/
	inline const float32 DegToRad(float32 _fDegrees)
	{
		return (_fDegrees * (g_kfPI / 180.0f));
	}

	/**
	* Takes a value in radians and returns the relative value in degrees.
	**/
	inline const float32 RadToDeg(float32 _fRadians)
	{
		return (_fRadians * (180.0f / g_kfPI));
	}

	/**
	* Returns true if the value is within range(T range) of the given compare value. 
	**/
	template<typename T> 
	bool VarianceEquals(T value, T compare, T range)
	{
		if((value > compare - range) && (value < compare + range))
		{
			return (true);
		}
		return (false);
	}

	/**
	* Returns the lesser of three values.
	**/
	template<typename T> 
	T Min3(T a, T b, T c) 
	{
		return (a<b)?((a<c)?a:c):(b<c)?b:c;
	}
	
	/**
	* Returns the greater of three values.
	**/
	template<typename T> 
	T Max3(T a, T b, T c)
	{
		return (a>b)?((a>c)?a:c):(b>c)?b:c;
	}

}
#endif //_MATHSCONSTANTS_H__Included_1318943118

