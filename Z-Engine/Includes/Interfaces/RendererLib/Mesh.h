#ifndef __MESH_H__
#define __MESH_H__

/**
 *	Encapsulates a mesh.
 */
class CMesh
{
public:
	void Initialise( const uint32 kuSizeInBytes );
	bool Lock( void*& pTarget );
	bool Unlock( );
	bool Render( );
protected:
	void				m_pVertices;			//!< The meshes vertices. This is a void* due to vertices having many declarations.
	IVertexDeclaration*	m_pVertexDeclaration;	//!< The meshes vertex declaration. Defines the meshes vertice structure. 
	uint32				m_uSize;				//!< The size in bytes of the meshes vertex buffer. 
};

#endif // __MESH_H__