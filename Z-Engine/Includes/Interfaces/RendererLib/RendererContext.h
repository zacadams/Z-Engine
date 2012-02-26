/**
 *	@file Z-Engine\Z-Engine\Interfaces\RendererLib\RendererContext.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _RENDERERCONTEXT_H__Included_1235248611
#define _RENDERERCONTEXT_H__Included_1235248611

/*
*	Represents the main context of a game.
*	The renderer context is a intermediate that containes the
*	Renderer targets dimensions and attributes.
*/

namespace ZGE
{
	class IRendererContext
	{
	public:

		
		IRendererContext( )
		: m_uDispWidth( 800 )
		, m_uDispHeight( 600 )
		, m_uDisplayDepth( 0 )
		, m_bFullScreen( false )
		, m_pContextName( "Needs a name !" )
		, m_pWindowMenu( NULL )
		{
		}

		// Returns the render contexts width
		inline uint32 GetDisplayWidth( ) { return m_uDispWidth; }

		// Returns the render contexts height
		inline uint32 GetDisplayHeight( ) { return m_uDispHeight; }

		// Returns the display Depth
		inline uint32 GetDisplayDepth( ) { return m_uDisplayDepth; }

		// Retuns true if the context is in full screen
		inline bool IsFullScreen( ) { return m_bFullScreen; }

		// Sets the handle to the window as a void* 
		inline void SetWindowHndle( void* _pWndwHndle ) { m_pWindowHndle = _pWndwHndle; }

		// Returns the handle to the window as a void*
		inline void* GetWindowHandle( ) { return m_pWindowHndle; }

		// Sets the instance handle on the renderer context
		inline void SetInstance( void* pInstance ) { m_pHinstance = pInstance; };

		// Returns the handle 
		inline void* GetInstance( ) { return m_pHinstance; }

		//Returns the name of the context
		inline const char8* GetContextName( ) { return m_pContextName; }

		// Sets the render contexts display width
		inline void SetDisplayWidth ( uint32 _uDispWidth ) { m_uDispWidth = _uDispWidth; }
		
		// Sets the render context display height
		inline void SetDisplayHeight( uint32 _uDispHeight) { m_uDispHeight = _uDispHeight ; }

		// To be overriden to create the game loop
		virtual bool FrameUpdate( ) = 0; 

		// To be overriden to draw the game.
		virtual bool FrameDraw( ) = 0;

		// To be overriden to initialise the render context
		virtual bool Initialise( ) = 0;

		// To de overriden to deinitialise the render context
		virtual bool Deinitialise( ) = 0;

		// Sets a menu id to the window.
		void SetWindowMenu( void* _pMenu, const char* _kpcMenuId ){ m_pWindowMenu = _pMenu; m_kpcMenuId = _kpcMenuId; }

		// Gets the window menu. 
		inline void* GetWindowMenu( const char*& _kpcMenuId ){ return m_pWindowMenu; _kpcMenuId = m_kpcMenuId; }

		// Handles window commands
		virtual void OnWindowCommand( sint32 _iMessage, sint32 _iParamA, sint32 _iParamB ){ }


	protected:

		uint32 m_uDispWidth   ;//!< The screens display width.
		uint32 m_uDispHeight  ;//!< The screens display height.
		uint32 m_uDisplayDepth;	//!< Th escreens diplay depth
		bool m_bFullScreen ;	//!< Display as full screen?

		const char8* m_pContextName;

		void* m_pWindowHndle;
		void* m_pHinstance;
		void* m_pWindowMenu;
		const char* m_kpcMenuId;

	};
}// end namespace
#endif //_RENDERERCONTEXT_H__Included_1235248611

