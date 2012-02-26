/**
 *	@file Z-Engine\Z-Engine\Implementations\COLLADAModelParser\COLLADAMeshParser.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _COLLADAMESHPARSER_H__Included_1020509142
#define _COLLADAMESHPARSER_H__Included_1020509142

#include "TinyXml/tinyxml.h"
#include "ModelParserLib/MeshParser.h"


namespace ZGE
{
	class CCOLLADAMeshParser : public IMeshParser
	{
	public:
		CCOLLADAMeshParser(void);
		~CCOLLADAMeshParser(void);

		bool ParseFile( const char* _kpcFile );
		bool ReleaseFile( );

			/**
	 	 * Returns the meshes vertices.
		 * @param _pVertices To be populated with the vertice data.
		 * @param _rVertexDesc To be populated with the vertices description.
		 * @param _ruVertexCount To be populatedwi th the vertice count.
		 * @param _kpcMeshId The name of the mesh to get the vertices from.
		 * @return Success. 
		 */
		virtual bool ParseVertices( void*& _pVertices, CVertexDescription& _rVertexDesc, uint32& _ruVertexCount, const char* _kpcMeshId ) ;

		/**
		 * @param _pIndices To be populated with the indice data.
		 * @param _rb32BitIndices To be populated with the indices size.
		 * @param _ruIndiceCount To be populated with the index count.
		 * @param _kpcMeshId The name of the mesh to get the indices from.
		 * @return Success. 
		 */
		virtual bool ParseIndices( void*& _pIndices, bool& _rb32BitIndices, uint32& _ruIndiceCount, const char* _kpcMeshId );

		/**
		 * returns the meshes material information .
		 * @param _rMaterialDesc To be populated with the materials description.
		 * @param _kpcMeshId The mesh to get the material information from.
		 * @return Success.
		 */
		virtual bool ParseMaterial( CMaterialDecription& _rMaterialDesc, const char* _kpcMeshId );

		/**
		 * Parses the meshes textures from file.
		 */

	protected:

		/**
		 * Creats the meshes vertexdescription.
		 * @param _pElement the vertexelement section.
		 * @param _rVertexDesc The vertex description to populate.
		 * @return Success.
		 */
		bool ParseVertexDescription( TiXmlElement* _pElement, CVertexDescription& _rDesc ); 

		/**
		 * Validates the mesh exist.
		 * @param _kpcMeshId The id of the mesh to validate
		 * @param _pMeshElement To be populated with the meshes element if it exist.
		 * @retrurn Mesh Exist
		 */
		bool DoesMeshExist( const char * _kpcMeshId, TiXmlElement*& _pMeshElement );

		/**
		 * Validates the material exist.
		 * @param _kpcMaterial The id of the mesh to validate
		 * @param _pMaterialElement To be populated with the materials element if it exist.
		 * @retrurn Mesh Exist
		 */
		bool DoesMaterialExist( const char * _kpcMaterialId, TiXmlElement*& _pMaterialElement );

		/**
		 * Validates the material exist.
		 * @param _kpcMaterial The id of the effect to validate
		 * @param _pMaterialElement To be populated with the effect element if it exist.
		 * @retrurn Effect Exist
		 */
		bool DoesEffectExist( const char * _kpcEffectId, TiXmlElement*& _pEffectElement );



	protected:

		TiXmlDocument m_Document;   //!< The document to parse.
		const char*	  m_kpcFileName; //!< The documents file name.
	};
}// end namespace 

#endif //_COLLADAMESHPARSER_H__Included_1020509142

