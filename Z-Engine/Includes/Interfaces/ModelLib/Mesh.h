/**
 *	@file Z-Engine\ModelLib\Mesh.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _MESH_H__Included_322828744
#define _MESH_H__Included_322828744

#include "RendererLib/PrimitiveTypes.h"

namespace ZGE
{
	class IVertexBuffer;
	class IMaterial;
	class IVertexDeclaration;
	class IRendererInterface;
	class CFMat4x4;
	class ITexture;

	// Represents a mesh
	class CMesh
	{
	public:
		CMesh(void);
		~CMesh(void);

		// Sets the meshes material
		void SetMaterial( IMaterial* _kpMaterial );

		// Sets the meshes vertex declaration
		void SetVertexDeclaration( IVertexDeclaration* _kpVertexDeclaration  );

		// Sets the meshes vertex buffer
		void SetVertexBuffer( IVertexBuffer* _kpVertexBuffer );

		// Sets the meshes textures.
		inline void SetTextures( ITexture** _ppTextures, const uint32 _kuTextureCount ) { m_ppTextures = _ppTextures; m_uTextureCount = _kuTextureCount; };

		// Sets the meshes primitive count.
		inline void SetPrimitiveCount( const uint32 _kuPrimitiveCount ) { m_uPrimitiveCount = _kuPrimitiveCount; }

		// Sets the meshes primitive type.
		inline void SetPrimitiveType( const EPrimitiveTypes _kePrimitiveType ) { m_ePrimitiveType = _kePrimitiveType; }

		// Gets the meshes material
		IMaterial* GetMaterial( ) const;

		// Gets the meshes vertex declaration
		IVertexDeclaration* GetVertexDeclaration( ) const;

		// Gets the meshes vertex buffer
		IVertexBuffer* GetVertexBuffer( ) const;

		// Returns the meshes textures.
		inline ITexture** GetTextures( uint32& _ruTextureCount ) { _ruTextureCount = m_uTextureCount; return m_ppTextures; }

		// Returns the meshes p[rimitive count.
		inline uint32 GetPrimitiveCount( ) { return m_uPrimitiveCount; }

		// Returns the meshes primitive type.
		inline EPrimitiveTypes GetPrimitiveType( ) { return m_ePrimitiveType; }
		
		// Draws the mesh
		void Draw( IRendererInterface* _pRenderer, const CFMat4x4& _krmWorld );

	protected:

		IVertexBuffer* m_pVertexBuffer;     //!< The meshes vertex buffer
		IMaterial*	   m_pMaterial;		    //!< The meshes material
		IVertexDeclaration* m_pDecl;	    //!< The meahes vertex declaration
		ITexture**     m_ppTextures;		//!< The meshes textures.
		uint32		   m_uTextureCount;	    //!< The meshes texture count.
		uint32		   m_uPrimitiveCount;   //!< the meshes primitive count.
		EPrimitiveTypes m_ePrimitiveType;	//!< The meshes p[rimitive type.
	};
}

#endif //_MESH_H__Included_322828744

