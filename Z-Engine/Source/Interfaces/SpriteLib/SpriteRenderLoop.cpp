/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\SpriteLib\SpriteRenderLoop.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
// Z-Engine includes
#include "CoreLib/Core.h"
#include "RendererLib/RenderEffect.h"
#include "RendererLib/VertexDescription.h"
#include "RendererLib/VertexDeclaration.h"
#include "RendererLib/Texture.h"
#include "SpriteLib/Sprite.h"
#include "SpriteLib/2DActor.h"
#include "SpriteLib/2DRenderAsset.h"

// vertex
#include "RendererLib/VertexBuffer.h"
#include "RendererLib/VertexBufferManager.h"
#include "RendererLib/RendererInterface.h"

// Library includes
#include "CoreLib/PerformanceManager.h"

// Local includes 
#include "SpriteLib/SpriteRenderLoop.h"
using namespace ZGE;
CSpriteRenderLoop::CSpriteRenderLoop(void)
: m_pVertexBuffer( NULL )
{
}

CSpriteRenderLoop::~CSpriteRenderLoop(void)
{
}

/**
 *	Overridden to update the sprite batch vertex buffer.
 *	@param _pRenderableActor The actor to add.
 *	@return Success.
 */
void CSpriteRenderLoop::AddRenderAsset( IRenderAsset* _pRenderAsset )
{
	// Add the asset.
	// We need to insert the asset into its optimal position.
	// Since 2D objects have transparency they need to be z sorted.
	// So using the insertion sort theory, we will insert the actor into its optimal place based on its z location.
	// The list is sorted from largest z distance to smallest z distance.
	C2DRenderAsset* pMe = reinterpret_cast< C2DRenderAsset* >( _pRenderAsset ); 
	float32 fMyZdepth = pMe->vWorldPosition.z( );	// My z depth.
	C2DRenderAsset* pOther = NULL;							// The other actor inthe list.
	float32	fOtherZdepth = 0.0f;						// The other actors z depth.

	// Insert this actor into its optimal position.
	LoopRenderList::iterator iter = m_lRenderList.begin( );
	for( iter ; iter != m_lRenderList.end( ); ++iter )
	{
		pOther = reinterpret_cast< C2DRenderAsset* >( (*iter) );
		fOtherZdepth = pOther->vWorldPosition.z( );
		if( fOtherZdepth <= fMyZdepth )
		{
			// Found my place.
			m_lRenderList.insert( iter, _pRenderAsset );
			return;
		}
	}
	m_lRenderList.push_back( _pRenderAsset );
	
	// If the vertex buffer does not exist, create it.
	if( NULL == m_pVertexBuffer )
	{
		CreateSpriteBatch( pMe );	
	}
}

/**
 *	Overridden to update the sprite batch vertex buffer.
 *	@param _pRenderableActor The actor to remove.
 *	@return Success.
 */
void CSpriteRenderLoop::RemoveRenderAsset( IRenderAsset* _pRenderAsset )
{
	IRenderLoop::RemoveRenderAsset( _pRenderAsset );
	// Update the batch vertex buffer.
}


/**
 *	Overridden to batch render sprites.
 *	@return Success.
 */
bool CSpriteRenderLoop::Render( )
{

	CPerformanceNode* pPerfNode = NULL;
	CREATE_PERFORMANCE_TIMER( pPerfNode, "CSpriteRenderLoop::Render( )", NULL );
	START_PERFORMANCE_TIMER( pPerfNode );

	// Pre transform the sprites.
	void* pData = NULL;
	if( false == m_pVertexBuffer->Lock( Z_MAX_SPRITE_BATCH * 6, 0, pData, false ) )
	{
		END_PERFORMANCE_TIMER( pPerfNode );
		assert_now( "Failed to lock the sprite render loops prite batch!" );
		return false;
	}
	LoopRenderList::iterator iter = m_lRenderList.begin( );
	C2DRenderAsset* pAsset = NULL;
	
	// There are two types of sprites. Lit sprites and unlit sprites.
	if( m_bContainsLitSprites )
	{
		CPerformanceNode* pLiteSpritePerfNode = NULL;
		CREATE_PERFORMANCE_TIMER( pLiteSpritePerfNode, "Batch_lit_sprites", "CSpriteRenderLoop::Render( )" );
		START_PERFORMANCE_TIMER( pLiteSpritePerfNode );
		
		// We are working with lit sprites.
		CLitSpriteVertex* pVertex = NULL;
		CLitSpriteVertex* pDataPtr = reinterpret_cast< CLitSpriteVertex* >( pData );
		for( iter; iter != m_lRenderList.end( ); ++iter )
		{
			pAsset = reinterpret_cast< C2DRenderAsset* >( (*iter) );
			pVertex = reinterpret_cast< CLitSpriteVertex* >( pAsset->pSprite->TransformEx( pAsset->vWorldPosition, CFVec2( pAsset->vScale.x( ), pAsset->vScale.y( ) ), pAsset->fWorldOrientation ) );
			*pDataPtr = pVertex[0];
			pDataPtr++;
			*pDataPtr = pVertex[1];
			pDataPtr++;
			*pDataPtr = pVertex[2];
			pDataPtr++;
			*pDataPtr = pVertex[0];
			pDataPtr++;
			*pDataPtr = pVertex[2];
			pDataPtr++;
			*pDataPtr = pVertex[3];
			pDataPtr++;
		}
		END_PERFORMANCE_TIMER( pLiteSpritePerfNode );
	}
	else
	{
		
		CPerformanceNode* pUnLiteSpritePerfNode = NULL;
		CREATE_PERFORMANCE_TIMER( pUnLiteSpritePerfNode, "Batch_UnLit_sprites", "CSpriteRenderLoop::Render( )" );
		START_PERFORMANCE_TIMER( pUnLiteSpritePerfNode );
		
		// We are working with lit sprites.
		CXyzColourUV* pVertex = NULL;
		CXyzColourUV* pDataPtr = reinterpret_cast< CXyzColourUV* >( pData );
		for( iter; iter != m_lRenderList.end( ); ++iter )
		{
			pAsset = reinterpret_cast< C2DRenderAsset* >( (*iter) );
			pVertex = reinterpret_cast< CXyzColourUV* >( pAsset->pSprite->TransformEx( pAsset->vWorldPosition, CFVec2( pAsset->vScale.x( ), pAsset->vScale.y( ) ), pAsset->fWorldOrientation ) );
			*pDataPtr = pVertex[0];
			pDataPtr++;
			*pDataPtr = pVertex[1];
			pDataPtr++;
			*pDataPtr = pVertex[2];
			pDataPtr++;
			*pDataPtr = pVertex[0];
			pDataPtr++;
			*pDataPtr = pVertex[2];
			pDataPtr++;
			*pDataPtr = pVertex[3];
			pDataPtr++;
		}
		END_PERFORMANCE_TIMER( pUnLiteSpritePerfNode );
	}

	// Unlock the vertex buffer
	if( false == m_pVertexBuffer->Unlock( ) )
	{
		assert_now( "Failed To unlock the sprite batch buffer!" );
	}

	// Render the vertex buffer.
	CSprite* pSprite = pAsset->pSprite;
	for( uint32 uTexture = 0; uTexture < pSprite->GetTextureCount( ); ++uTexture )
	{
		pSprite->GetTexture( uTexture )->Apply( uTexture );
	}

	CPerformanceNode* pSpriteBatchRender = NULL;
	CREATE_PERFORMANCE_TIMER( pSpriteBatchRender, "Sprite_Batch_Render", "CSpriteRenderLoop::Render( )" );
	START_PERFORMANCE_TIMER( pSpriteBatchRender );

	m_pRenderEffect->BeginEffect( );
	m_pRenderEffect->Render( PT_TriangleList, m_pVertexBuffer, m_lRenderList.size( ) * 2 );

	END_PERFORMANCE_TIMER( pSpriteBatchRender );

	// End the batch render.
	m_pRenderEffect->EndEffect( );

	END_PERFORMANCE_TIMER( pPerfNode );
	return false;
}

/**
 *	Checks if the render loop is designed for the renderable actor.
 *	@param _pRenderableActor The actor to check compatibily with the render loop.
 *	@return Compatibility.
 */
bool CSpriteRenderLoop::IsCompatibleWith( IRenderAsset* _pRenderAsset )
{	
	CPerformanceNode* pPerfNode = NULL;
	CREATE_PERFORMANCE_TIMER( pPerfNode, "IsCompatibleWith( )", "AddRenderAsset( )" );
	START_PERFORMANCE_TIMER( pPerfNode );

	if( m_lRenderList.size( ) == 0 )
	{
		// We can claim it.
		END_PERFORMANCE_TIMER( pPerfNode );
		return true;
	}

	// Are the render effects compatible?
	if( IRenderLoop::IsCompatibleWith( _pRenderAsset ) )
	{

		// The list is not empty, check if the contained actors have the same textures.
		CSprite* pMe = reinterpret_cast< C2DRenderAsset* >( (*m_lRenderList.begin( ) ) )->pSprite;
		CSprite* pOther = reinterpret_cast< C2DRenderAsset* >( _pRenderAsset )->pSprite;

		// Quick check, if they have different texture counts, they have different textures.
		uint32 uMyTextureCount = pMe->GetTextureCount( );
		uint32 uTheirTextureCount = pOther->GetTextureCount( );
		if( uMyTextureCount != uTheirTextureCount )
		{
			END_PERFORMANCE_TIMER( pPerfNode );
			return false;
		}

		// They have the same texture count, check if they contain the same textures.
		for( uint32 uMyTexture = 0; uMyTexture < uMyTextureCount; ++uMyTexture )
		{
			for( uint32 uTheirTexture = 0; uTheirTexture < uTheirTextureCount; ++uTheirTexture )
			{
				if( pMe->GetTexture( uMyTexture ) != pOther->GetTexture( uTheirTexture ) )
				{
					// Textures are not the same, we can reject the render actor.
					END_PERFORMANCE_TIMER( pPerfNode );
					return false;
				}
			}
		}
	}
	else
	{
		END_PERFORMANCE_TIMER( pPerfNode );
		return false;
	}

	// If we have not retured, we are compatible.
	END_PERFORMANCE_TIMER( pPerfNode );
	return true;
}

/**
 * Creates the loops vertex buffer.
 */
void CSpriteRenderLoop::CreateSpriteBatch( IRenderAsset* _pRenderAsset )
{
	C2DRenderAsset* pAsset = reinterpret_cast< C2DRenderAsset* >( _pRenderAsset );
	m_bContainsLitSprites = pAsset->pSprite->IsLit( );

	uint32 uStride = 0;
	if( m_bContainsLitSprites )
	{
		uStride = sizeof( CLitSpriteVertex );
	}
	else
	{
		uStride = sizeof( CXyzColourUV );
	}
	static uint32 suBatch = 0;
	char pcBuffer[256];
	//sprintf_s( pcBuffer, "SpriteBatch_%d", suBatch++ );
	STR_PRINT( pcBuffer, 256,"SpriteBatch_%d", suBatch++ );
	//ZUtilities::StrPrint( pcBuffer, "SpriteBatch_%d",255, suBatch++ );
	m_pVertexBuffer = ZEngine::GetRendererInterface( )->GetVertexBufferManager( )->CreateVertexBuffer( CAssetId( pcBuffer ) );
	m_pVertexBuffer->Initialise( Z_MAX_SPRITE_BATCH * 6, uStride, pAsset->pSprite->GetVertexDeclaration( ), true );
}
