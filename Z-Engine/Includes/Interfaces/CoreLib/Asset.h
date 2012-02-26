/**
 *	@file Z-Engine\Z-Engine\Interfaces\CoreLib\Asset.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/

#ifndef _ASSET_H__Included_1361269577
#define _ASSET_H__Included_1361269577

#include "CoreLib/AssetManager.h"

namespace ZGE
{
	template < typename t >
	class CAssetManager;
	class CAssetId;

	/*
	*	Base class for assets.
	*	Handles reference counting and detruction of an asset.
	*/
	template< typename t >
	class CAsset
	{
	public:
		
		typedef CAssetManager<t> tManager;

		CAsset( )
		: m_AssetId		 ( "NEEDS A ASSET ID" )
		, m_uRefCount	 ( 0 ) 
		, m_pAssetManager( NULL )
		, m_pNext		 ( NULL )
		, m_pPrevious	 ( NULL )
		{
		}

		virtual ~CAsset(void)
		{

		}

		// Decreases the assets reference count.
		// If the reference count becomes 0 the asset is freed.
		inline void Release( )
		{
			assert_msg( m_uRefCount != 0, "Trying to release asset with no reference count!" );
			--m_uRefCount;
			if( 0 == m_uRefCount )
			{
				m_pAssetManager->FreeAsset( reinterpret_cast< t* >( this ) );
			}
		}

		// Adds a reference to the asset
		inline void AddRef( )
		{
			++m_uRefCount;
		}

		// Returns the assets reference count
		inline uint32 GetRefCount( )
		{
			return m_uRefCount;
		}

		// Sets the assets asset manager
	
		inline void SetAssetManager( tManager* _pAssetMngr ) { m_pAssetManager = _pAssetMngr; }

		// Sets the next asset in the managers asset list
		inline void SetNextAsset( CAsset* _pAsset )
		{
			assert_msg( this, "Asset does not exist!" );
			m_pNext = _pAsset;
		}
		
		// Sets the previous asset in the managers asset list.
		inline void SetPreviousAsset( CAsset* _pAsset  )
		{
			assert_msg( this, "Asset does not exist!" );
			m_pPrevious = _pAsset;
		}

		// Returns the next asset in the list from this asset
		inline CAsset<t>* GetNext( ) { return m_pNext; }

		// Returns the previous actor in the list from this asset
		inline CAsset<t>* GetPrevious( ) { return m_pPrevious; }

		// returns the assets id 
		const CAssetId& GetAssetId( ) { return m_AssetId; };

		// Sets the assets id 
		void SetAssetId( const CAssetId& _krAssetId ) { m_AssetId = _krAssetId; }

	protected:

		CAssetId			m_AssetId;		 //!< The assets id
		uint32				m_uRefCount;	 //!< The reference count for a asset
		tManager*		    m_pAssetManager; //!< The assets manager
		CAsset*			    m_pNext;		 //!< The next	  asset in the managers asset list
		CAsset*				m_pPrevious;	 //!< The previous asset in the managers asset list
	};
}// end namespace

#endif //_ASSET_H__Included_1361269577

