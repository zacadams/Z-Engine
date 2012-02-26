/**
 *	@file Z-Engine\Z-Engine\Interfaces\CoreLib\AssetId.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _ASSETID_H__Included_382453560
#define _ASSETID_H__Included_382453560


namespace ZGE
{
	class CAssetId
	{
	public:
		CAssetId( const char* _kpcFileName );
		~CAssetId(void);

		/*
		*	Retrives the assets id file name
		*/
		const char* GetFileName( ) const;

	protected:

		char m_pFileName[256]; //!< The assets file name
	};
}// end namespace 
#endif //_ASSETID_H__Included_382453560

