/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\Physics2DLib\IntersectionInfo.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _INTERSECTIONINFO_H__Included_872209080
#define _INTERSECTIONINFO_H__Included_872209080

#include "MathLib/FVec3.h"

namespace ZGE
{
	/**
	 *	Containes the result of explicit intersection test. 
	 *  i.e. ray casts, or other intersection test performed out side of the physics scene. 
	 */
	class CIntersectionInfo
	{
	public:
		CIntersectionInfo(void);
		~CIntersectionInfo(void);
		bool	m_bIntersected;		  //!< Determins if an intersection occured.
		CFVec3	m_vIntersectionPoint; //!< The point of intersection.
		CFVec3  m_vIntersectionNormal;//!< The intersection normal.
	};
}

#endif //_INTERSECTIONINFO_H__Included_872209080

