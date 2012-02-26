/**
 *	@file Z-Engine\Z-Engine\Interfaces\CoreLib\AssetId.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes
#include "CoreLib/Core.h"

// Library includes
#include <stdio.h>

// Local includes 

#include "CoreLib/AssetId.h"


using namespace ZGE;
CAssetId::CAssetId( const char* _kpcFileName )
{
	m_pFileName[0] = 0;
	STR_PRINT(  m_pFileName, 256,"%s", _kpcFileName );
	//ZUtilities::StrPrint( m_pFileName, "%s", 256, _kpcFileName );
	//sprintf_s( m_pFileName, "%s", _kpcFileName ); 
}
//
CAssetId::~CAssetId(void)
{
	
}
/*
*	Retrives the assets id file name
*/
const char* CAssetId::GetFileName( ) const
{
	return m_pFileName;
}