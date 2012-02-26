/**
 *	@file Z-Engine\Z-Engine\Interfaces\ModelParser\MeshParser.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _MESHPARSER_H__Included_1561927334
#define _MESHPARSER_H__Included_1561927334

namespace ZGE
{
	class CVertexDescription;
	class CMaterialDecription;

	/**
	 * Interface for mesh parsers.
	 */
	class IMeshParser
	{
	public:

		virtual 	bool ParseFile( const char* _kpcFile )= 0;
		virtual bool ReleaseFile( ) = 0;

		

		/**
	 	 * Returns the meshes vertices.
		 * @param _pVertices To be populated with the vertice data.
		 * @param _rVertexDesc To be populated with the vertices description.
		 * @param _ruVertexCount To be populatedwi th the vertice count.
		 * @param _kpcMeshId The name of the mesh to get the vertices from.
		 * @return Success. 
		 */
		virtual bool ParseVertices( void*& _pVertices, CVertexDescription& _rVertexDesc, uint32& _ruVertexCount, const char* _kpcMeshId ) = 0;

		/**
		 * @param _pIndices To be populated with the indice data.
		 * @param _rb32BitIndices To be populated with the indices size.
		 * @param _ruIndiceCount To be populated with the index count.
		 * @param _kpcMeshId The name of the mesh to get the indices from.
		 * @return Success. 
		 */
		virtual bool ParseIndices( void*& _pIndices, bool& _rb32BitIndices, uint32& _ruIndiceCount, const char* _kpcMeshId ) = 0;

		/**
		 * returns the meshes material information .
		 * @param _rMaterialDesc To be populated with the materials description.
		 * @param _kpcMeshId The mesh to get the material information from.
		 * @return Success.
		 */
		virtual bool ParseMaterial( CMaterialDecription& _rMaterialDesc, const char* _kpcMeshId ) = 0;

	protected:

		/**
		 * Calculates index data from vertices. 
		 * @param _kpVertices The vertex data.
		 * @param _krVertexDesc The vertexdescription.
		 * @param _pIndices To be poulated with the index data.
		 * @param _ruIndexCount To be poulated with the index count. 
		 * @return Suceess.
		 */
		bool GenerateIndexData(const void* _pVertices, const CVertexDescription& _krVertexDesc, void*& pIndices, uint32& _ruIndexCount  );

	protected:
	};
}// end namespace 

#endif //_MESHPARSER_H__Included_1561927334

