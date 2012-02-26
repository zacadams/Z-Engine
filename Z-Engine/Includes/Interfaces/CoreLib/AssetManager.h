/**
 *	@file Z-Engine\Z-Engine\Interfaces\CoreLib\AssetManager.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _ASSETMANAGER_H__Included_1582135954
#define _ASSETMANAGER_H__Included_1582135954

#include "stdio.h"

#include "CoreLib/Asset.h"

namespace ZGE
{
	class CAssetId;

	/*
	*	The base to the asset system.
	*	The asset manager uses the flyweight design.
	*	Contains the all the assets for a manager and the asset count. 
	*/
	template< typename t >
	class CAssetManager
	{
	public:

		//typedef CAssetManager<t> tManager;
		typedef t tAsset;

		CAssetManager< t >( )
			: m_pAssetList	 ( NULL )
			, m_pAssetListEnd( m_pAssetList )
			, m_uAssetCount	 ( 0 )
			, m_kpcManagerId ( " Asset manager ?" )
		{

		}

		virtual ~CAssetManager< t >( )
		{
			if( m_uAssetCount )
			{
				static char pBuffer[256];
				STR_PRINT( pBuffer, 256,"%s%d assets remaining!", m_kpcManagerId, m_uAssetCount );
				assert_now( pBuffer );
			}
		}

		/*
		*	Retrives an asset by id
		*	Return : Asset
		*/
		inline tAsset* GetAssetById( CAssetId& _rAssetId )
		{
			UNUSED_VAR( _rAssetId );

			// Does the asset exist?
			
			const char* kpcTarget     = _rAssetId.GetFileName( );
			const char* kpcContained = NULL;

			tAsset* pAsset = m_pAssetList;
			for( pAsset; NULL != pAsset; pAsset = reinterpret_cast< tAsset* >( pAsset->GetNext( ) ) )
			{
				kpcContained = pAsset->GetAssetId( ).GetFileName( );
				if( 0 == _strcmpi( kpcTarget, kpcContained ) )
				{
					// Found the asset.
					return pAsset;
				}
			}
			return NULL;
		}

		// Adds an asset to the asset list
		// _pAsset : The asset to add
		void AddToAssetList( tAsset* _pAsset )
		{
			if( NULL == m_pAssetList )
			{
				m_pAssetList = _pAsset;
				m_pAssetListEnd = m_pAssetList;
				return;
			}

			m_pAssetListEnd->SetNextAsset( _pAsset );
			_pAsset->SetPreviousAsset( m_pAssetListEnd );
			m_pAssetListEnd = _pAsset;
		}

		// Removes the asset from the list
		// _pAsset : The asset to remove
		void RemoveAssetFromList( tAsset* _pAsset )
		{
			tAsset* pPrevious = reinterpret_cast< tAsset* >( _pAsset->GetPrevious( ) );
			tAsset* pNext	  = reinterpret_cast< tAsset* >( _pAsset->GetNext( ) );

			pPrevious ? pPrevious->SetNextAsset( pNext )     : NULL;
			pNext     ? pNext->SetPreviousAsset( pPrevious ) : NULL;
			//--m_uAssetCount;

			// is this asset at the end of the list?
			if( m_pAssetListEnd == _pAsset )
			{
				m_pAssetListEnd = reinterpret_cast< tAsset* >( _pAsset->GetPrevious( ) );
			}
		}

		
		/**
		 *	Loades an asset and adds it to the managers list
		 *	Param _rAssetId : The assets id, ( could be the file name ).
		 *	Return : The created asset.
		 */
		tAsset* LoadAsset( CAssetId& _rAssetId )
		{
			
			tAsset* pAsset = NULL;
			// Does the asset already exist?
			pAsset = GetAssetById( _rAssetId );
			if( pAsset )
			{
				// Yes, increase its reference count and return the asset
				pAsset->AddRef( );
				return pAsset;
			}

			if( false == LoadAssetImplementation( _rAssetId, pAsset ) )
			{
				// Failed to laod the asset, rell the user
				static char pBuffer[256];
				//sprintf_s( pBuffer, "Failed to load asset : %s", _rAssetId.GetFileName( ) );
				STR_PRINT( pBuffer, 256,"Failed to load asset: %s", _rAssetId.GetFileName( ) );
				//ZUtilities::StrPrint( pBuffer, "Failed to load asset: %s", 256, _rAssetId.GetFileName( ) );
				assert_now( pBuffer );
				return NULL;
			}

			// Successfully loaded the asset
			++m_uAssetCount;
			pAsset->SetAssetManager( this );
			pAsset->SetAssetId( _rAssetId );
			AddToAssetList( pAsset );
			pAsset->AddRef( );
			return pAsset;
		}

		/**
		 *	To be overidden to release a managers assets.
		 *	Param _pAsset : The asset to release.
		 *	Return : Success.
		 */
		bool FreeAsset( tAsset* _pAsset )
		{
			// Remove the asset from the list
			RemoveAssetFromList( _pAsset );

			// Release the asset
			if( false == ReleaseAsset( _pAsset ) )
			{
				// Failed to release the asset
				static char pBuffer[256];
				STR_PRINT( pBuffer, 256, "Failed to free asset : %s" ,_pAsset->GetAssetId( ).GetFileName( ) );
				assert_now( pBuffer );
				return false;
			}
			// Succesfully released
			--m_uAssetCount;
			
			return true;
		}


	protected:


		/**
		 *	To be overriden to load assets of a derived manager.
		 *	Param _rAssetId : The assets id, ( could be the file name ).
		 *	Param _pAsset   : To be populated with the loaded asset.
		 *	Return : Success.
		 */
		virtual bool LoadAssetImplementation( CAssetId& _rAssetId, tAsset*& _pAsset ) = 0;

		/**
		 *	To be overidden to release a managers assets.
		 *	Param _pAsset : The asset to release.
		 *	Return : Success.
		 */
		virtual bool ReleaseAsset( tAsset* _pAsset ) = 0;

		/**
		 * Adds a pre created assets to the managers list
		 * Param _krAssetId : The assets id
		 * Param _pAsset : The asset to add
		 */
		void AddPreCreatedAsset( const CAssetId& _krAssetId, tAsset* _pAsset )
		{
			AddToAssetList( _pAsset );
			_pAsset->SetAssetId( _krAssetId );
			_pAsset->SetAssetManager( this );
			_pAsset->AddRef( );
			++m_uAssetCount;
		}

	protected:

		tAsset* m_pAssetList;    	//!< The managers asset list
		tAsset* m_pAssetListEnd;		//!< The last asset in the list 
		uint32  m_uAssetCount;	//!< The number off assets the manager contains
		const char*	m_kpcManagerId; //!< The name of the asset manager
	};
}// end namespace 

#endif //_ASSETMANAGER_H__Included_1582135954

