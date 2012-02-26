/**
 *	@file Z-Engine\Z-Engine\Implementations\COLLADAModelParser\COLLADAMeshParser.cpp
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2011 - Zac Adams. All Rights Reserved.
 *	
 *********************************************************************************************/

#include "CoreLib/Core.h"
#include "ModelLib/Mesh.h"
#include "RendererLib/VertexBuffer.h"
#include "RendererLib/IndexBuffer.h"
#include <sstream>
#include <string>

#include "Source.h"


// Vertex
#include "RendererLib/VertexDescription.h"

// Material
#include "RendererLib/Material.h"

#include "COLLADAMeshParser.h"

inline bool ToFloat( const char* _kpcValues, ZGE::float32*& _pValues, ZGE::uint32 _kuCount )
{
	_pValues = new ZGE::float32[_kuCount];
	// Load the values
	std::istringstream iss( _kpcValues );
	ZGE::float32 fVal= 0.0f;
	for( ZGE::uint32 i = 0; i < _kuCount; ++i )
	{
		iss >> fVal;
		_pValues[i] = fVal;
	}
	return true;
}

inline bool ToFloatPreAllocated( const char* _kpcValues, ZGE::float32* _pValues, ZGE::uint32 _kuCount )
{
	//_pValues = new ZGE::float32[_kuCount];
	// Load the values
	std::istringstream iss( _kpcValues );
	ZGE::float32 fVal= 0.0f;
	for( ZGE::uint32 i = 0; i < _kuCount; ++i )
	{
		iss >> fVal;
		_pValues[i] = fVal;
	}
	return true;
}

inline bool ToUint( const char* _kpcValues, ZGE::uint32*& _pValues, ZGE::uint32 _kuCount )
{
	_pValues = new ZGE::uint32[_kuCount];
	// Load the values
	std::istringstream iss( _kpcValues );
	ZGE::uint32 uVal= 0;
	for( ZGE::uint32 i = 0; i < _kuCount; ++i )
	{
		iss >> uVal;
		_pValues[i] = uVal;
	}
	return true;
}

inline ZGE::uint32 ToUint( const char* _kpcValues )
{
	// Load the values
	std::istringstream iss( _kpcValues );
	ZGE::uint32 uVal= 0;

	iss >> uVal;

	return uVal;
}

using namespace ZGE;




CCOLLADAMeshParser::CCOLLADAMeshParser(void)
: m_kpcFileName( NULL )
{
}

CCOLLADAMeshParser::~CCOLLADAMeshParser(void)
{

}


bool CCOLLADAMeshParser::ParseFile( const char* _kpcFile )
{
	if( false == m_Document.LoadFile( _kpcFile ) )
	{
		char cBuffer[256];
		sprintf_s( cBuffer, "Failed to load : %s COLLADA file!", _kpcFile ); 
		assert_now( cBuffer );
		return false;
	}
	m_kpcFileName = _kpcFile; 
	return true;
}
//
bool CCOLLADAMeshParser::ReleaseFile( )
{
	return false;
	//m_Document.( );
}


/**
 * Returns the meshes vertices.
 * @param _pVertices To be populated with the vertice data.
 * @param _rVertexDesc To be populated with the vertices description.
 * @param _ruVertexCount To be populatedwi th the vertice count.
 * @param _kpcMeshId The name of the mesh to get the vertices from.
 * @return Success. 
 */
bool CCOLLADAMeshParser::ParseVertices( void*& _pVertices, CVertexDescription& _rVertexDesc, uint32& _ruVertexCount, const char* _kpcMeshId )
{

	// Does the mesh exist?
	TiXmlElement* pMeshElement = NULL;
	if( false == DoesMeshExist( _kpcMeshId, pMeshElement ) )
	{
		return false; //mesh does not exist
	}

	// COLLADA store each vertex elements in seperate array.
	// This is used to save memory, data has to goten via look up tables.
	// Firstly we have to find the vertex element order fr this mesh.
	// Secondly we have to get each vertexs elements array od data.
	// Then we have to get the look up table and create the vertices.


	//CMesh* pMesh = new CMesh( );
	//IV//ertexBuffer* pVertexBuffer; pVertexBuffer;
	//IIndexBuffer* pIndexBuffer;   pIndexBuffer;
	CVertexDescription VertexDesc;
	uint32 uTriangleCount = 0;

	// Get the vertex element order.
	TiXmlElement* pVertexElement = pMeshElement->FirstChildElement( "triangles");
	uTriangleCount = ToUint( pVertexElement->Attribute( "count" ) );

	// Parse the meshes vertex description .
	ParseVertexDescription(  pVertexElement->FirstChildElement( ), VertexDesc );

	// Get the triangle lookup table.
	pVertexElement = pVertexElement->FirstChildElement( "p" );

	float32* pTriangles = NULL;
	ToFloat( pVertexElement->GetText( ), pTriangles, uTriangleCount * 3 * VertexDesc.GetElementCount( ) );

	// Load the data, create the sources.
	CSource* pElementSources = new CSource[VertexDesc.GetElementCount( )];
	
	// The sources are in order of children from the geometry node.
	// i.e if the description id VERTEX- NORMAL. the first child of the geometry
	// will be the position sourcesand the second the normal sources.

	TiXmlElement* pSource = pMeshElement->FirstChildElement( "source" );
	uint32 uIndex = 0;
	for( pSource; NULL!= pSource; pSource = pSource->NextSiblingElement( "source" ) )
	{
		TiXmlElement* pArray = pSource->FirstChildElement( "float_array" ); 
		// Get the array count
		
		pElementSources[uIndex].m_uSourceCount =  ToUint( pArray->Attribute( "count" ));
		// Get the foat array
		ToFloat( pArray->GetText( ), pElementSources[uIndex].m_pValues, pElementSources[uIndex].m_uSourceCount );
		// Get the index stride,accessor
		 pElementSources[uIndex].m_uStride = ToUint( pArray->NextSiblingElement( "technique_common" )->FirstChildElement( "accessor" )->Attribute( "stride" ) );
		++uIndex;
		
	}

	//							 Tri count * verts per tri * stride
	unsigned char* pVertices = new unsigned char[ uTriangleCount * 3 * VertexDesc.GetStride( )];
	unsigned char* pVertexPtr = pVertices;
	// Create the vertices.
	uint32 uSourceIndex = 0;
	// triangles
	for( uint32 uTriangle = 0; uTriangle < uTriangleCount /*/  VertexDesc.GetElementCount( )*/; ++uTriangle )
	{
		// vertices per triangle
		for( uint32 uVertex = 0; uVertex < 3 /* 3 verts per triangle */ ; ++uVertex )
		{
		// source per vertex.
			for( uint32 uSource = 0; uSource < VertexDesc.GetElementCount( ); ++uSource )
			{	
				pElementSources[uSource].MemCopy( pVertexPtr, /*uSourceIndex*/ (uint32)pTriangles[ uSourceIndex++ ] );
				pVertexPtr += 4 * pElementSources[uSource].m_uStride;
			}
		}
	}

	_pVertices = pVertices;
	_rVertexDesc = VertexDesc;
	_ruVertexCount = ( uTriangleCount * 3 );

	SafeDeleteArray( pTriangles );
	SafeDeleteArray( pElementSources );

	return false;
}

/**
 * @param _pIndices To be populated with the indice data.
 * @param _rb32BitIndices To be populated with the indices size.
 * @param _ruIndiceCount To be populated with the index count.
 * @param _kpcMeshId The name of the mesh to get the indices from.
 * @return Success. 
 */
bool CCOLLADAMeshParser::ParseIndices( void*& _pIndices, bool& _rb32BitIndices, uint32& _ruIndiceCount, const char* _kpcMeshId )
{
	UNUSED_VAR( _pIndices );
	UNUSED_VAR( _rb32BitIndices );
	UNUSED_VAR( _ruIndiceCount );
	UNUSED_VAR( _kpcMeshId );
	return false;
}

/**
 * returns the meshes material information .
 * @param _rMaterialDesc To be populated with the materials description.
 * @param _kpcMeshId The mesh to get the material information from.
 * @return Success.
 */
bool CCOLLADAMeshParser::ParseMaterial( CMaterialDecription& _rMaterialDesc, const char* _kpcMeshId )
{
	UNUSED_VAR( _rMaterialDesc );
	UNUSED_VAR( _kpcMeshId );

	TiXmlElement* pMeshElement = NULL;
	if( false == DoesMeshExist( _kpcMeshId, pMeshElement ) )
	{
		assert_now( "Failed to parse material!" );
	}

	// Get the meshes material target.
	// Mesh's triangle elemnts material attribure.
	const char* kpcMaterialTarget =  pMeshElement->FirstChildElement( "triangles" )->Attribute( "material" );
	char pMaterialTarget[256];
	sprintf_s( pMaterialTarget, "%s", kpcMaterialTarget );

	// This is the materials symbol. The target is the symbols name with out the _SG
	// Find the last _ and delete the rest of the line.
	//
	for( char* p = pMaterialTarget; p != NULL; ++p )
	{
		if( '_' == ( *p ) )
		{
			*p = '\0'; // Null terminating string.
		}
	}

	// Get the material library and find the target material.
	TiXmlElement* pMaterialElement = NULL;
	if( false == DoesMaterialExist( pMaterialTarget, pMaterialElement ) )
	{
		assert_now( "Failed to parse material!" );
	}

	// Get the materials effect instance.
	const char* kpcEffectId = pMaterialElement->FirstChildElement( "instance_effect" )->Attribute( "name" );

	// Get the effect instance in the effect library.
	TiXmlElement* pEffectElement = NULL;
	if( false == DoesEffectExist( kpcEffectId, pEffectElement ) )
	{
		assert_now( "Effect does not exist!" );
	}

	// pTechniqueNode can be phong, blinn or lambert
	// enumerate the effect.
	TiXmlElement* pTechnique = pEffectElement->FirstChildElement( "profile_common" )->FirstChildElement("technique")->FirstChildElement("phong");
	if( NULL == pTechnique )
	{
		pTechnique = pEffectElement->FirstChildElement( "profile_common" )->FirstChildElement("technique")->FirstChildElement("blin");
	}
	if( NULL == pTechnique )
	{
		pTechnique = pEffectElement->FirstChildElement("profile_common" )->FirstChildElement("technique")->FirstChildElement("lambert");
	}

	// Get the materials diffuse properties.
	float32 pColour[4];
	TiXmlElement* pDiffuse = pTechnique->FirstChildElement( "diffuse" );
	if( pDiffuse )
	{
		ToFloatPreAllocated( pDiffuse->FirstChildElement( "color" )->GetText( ), pColour, 4 );
		//_rMaterialDesc.m_uDiffuse = 
	}
	else
	{
	}

	// Get the materials emmisive properties.
		TiXmlElement* pAmbient = pTechnique->FirstChildElement( "ambient" );
	if( pAmbient )
	{
		ToFloatPreAllocated( pAmbient->FirstChildElement( "color" )->GetText( ), pColour, 4 );
		//_rMaterialDesc.m_uDiffuse = 
	}
	else
	{
	}
	// Get the materials ambient properties.
			TiXmlElement* pEmissive = pTechnique->FirstChildElement( "emission" );
	if( pEmissive )
	{
		ToFloatPreAllocated( pEmissive->FirstChildElement( "color" )->GetText( ), pColour, 4 );
		//_rMaterialDesc.m_uDiffuse = 
	}
	else
	{
	}
	// Get the materials transparent properties.
		TiXmlElement* pTransparent = pTechnique->FirstChildElement( "transparent" );
	if( pEmissive )
	{
		ToFloatPreAllocated( pTransparent->FirstChildElement( "color" )->GetText( ), pColour, 4 );
		//_rMaterialDesc.m_uDiffuse = 
	}
	else
	{
	}



	return false;
}

/**
* Creats the meshes vertexdescription.
* @param _pElement the vertexelement section.
* @param _rVertexDesc The vertex description to populate.
* @return Success.
*/
bool CCOLLADAMeshParser::ParseVertexDescription( TiXmlElement* _pElement, CVertexDescription& _rDesc )
{
	uint32 uOffSet = 0;
	for( _pElement; NULL != _pElement; _pElement = _pElement->NextSiblingElement( "input" ) )
	{
		// Get the elements name
		const char* kpcElementName = _pElement->Attribute( "semantic" );
		// enumerate the semantic

		CVertexElement Element;
		if( 0 == _stricmp( "VERTEX", kpcElementName ) )
		{
			Element = CVertexElement( uOffSet, CVertexElement::ES_POSITION, 0, CVertexElement::ET_FLOAT32, 3 );
			uOffSet += 12;
		}
		if( 0 == _stricmp( "NORMAL", kpcElementName ) )
		{
			Element = CVertexElement( uOffSet, CVertexElement::ES_NORMAL, 0, CVertexElement::ET_FLOAT32, 3 );
			uOffSet += 12;
		}
		if( 0 == _stricmp( "TEXCOORD", kpcElementName ) )
		{
			Element = CVertexElement( uOffSet, CVertexElement::ES_TEXCOORD, 0, CVertexElement::ET_FLOAT32, 2 );
			uOffSet += 8;
		}

		_rDesc.AddElement( Element );
	}
	return true;
}

/**
 * Validates the mesh exist.
 * @param _kpcMeshId The idof the mesh to validate
 * @param _pMeshElement To be populated with the meshes element if it exist.
 * @retrurn Mesh Exist
 */
bool CCOLLADAMeshParser::DoesMeshExist( const char * _kpcMeshId, TiXmlElement*& _pMeshElement )
{
	// Find the mesh mesh in the geometry library.
	TiXmlElement* pGeopmetryLib = m_Document.RootElement( )->FirstChildElement( "library_geometries" );
	assert_msg( NULL != pGeopmetryLib, "Failed to get the geometry library in the collada file " );

	// We have the geomtery library, loop and find the specified mesh.
	bool bMeshExist = false;
	TiXmlElement* pGeometry = pGeopmetryLib->FirstChildElement( "geometry" );
	for( pGeometry; NULL != pGeometry; pGeometry = pGeometry->NextSiblingElement( "geometry" ) )
	{
		if( 0 == _stricmp( _kpcMeshId, pGeometry->Attribute( "name" ) ) )
		{
			// Found the mesh
			bMeshExist = true;
			_pMeshElement = pGeometry->FirstChildElement( "mesh" );
			break;
		}
	}

	char cBuffer[256 ];
	sprintf_s( cBuffer, "Failes to find mesh : %s in COLLADA FILE %s : ", _kpcMeshId, m_kpcFileName );
	assert_msg( bMeshExist, cBuffer );

	return bMeshExist;
}

/**
 * Validates the material exist.
 * @param _kpcMaterial The id of the mesh to validate
 * @param _pMaterialElement To be populated with the materials element if it exist.
 * @retrurn Material Exist
 */
bool CCOLLADAMeshParser::DoesMaterialExist( const char * _kpcMaterialId, TiXmlElement*& _pMaterialElement )
{
	// Find the material in the material library.
	TiXmlElement* pMaterialLib = m_Document.RootElement( )->FirstChildElement( "library_materials" );
	assert_msg( NULL != pMaterialLib, "Failed to get the material library in the collada file " );

	// We have the geomtery library, loop and find the specified mesh.
	bool bMaterialExist = false;
	TiXmlElement* pMaterial = pMaterialLib->FirstChildElement( "material" );
	for( pMaterial; NULL != pMaterial; pMaterial = pMaterial->NextSiblingElement( "material" ) )
	{
		if( 0 == _stricmp( _kpcMaterialId, pMaterial->Attribute( "name" ) ) )
		{
			// Found the mesh
			bMaterialExist = true;
			_pMaterialElement = pMaterial->FirstChildElement( "mesh" );
			break;
		}
	}

	char cBuffer[256 ];
	sprintf_s( cBuffer, "Failes to find material : %s in COLLADA FILE %s : ", _kpcMaterialId, m_kpcFileName );
	assert_msg( bMaterialExist, cBuffer );

	return bMaterialExist;
}

/**
 * Validates the material exist.
 * @param _kpcMaterial The id of the effect to validate
 * @param _pMaterialElement To be populated with the effect element if it exist.
 * @retrurn Effect Exist
 */
bool CCOLLADAMeshParser::DoesEffectExist( const char * _kpEffectId, TiXmlElement*& _pEffectElement )
{
	// Find the material in the material library.
	TiXmlElement* pEffectLib = m_Document.RootElement( )->FirstChildElement( "library_effects" );
	assert_msg( NULL != pEffectLib, "Failed to get the effects library in the collada file " );

	// We have the geomtery library, loop and find the specified mesh.
	bool bEffectExist = false;
	TiXmlElement* pEffect = pEffectLib->FirstChildElement( "effect" );
	for( pEffect; NULL != pEffect; pEffect = pEffect->NextSiblingElement( "effect" ) )
	{
		if( 0 == _stricmp( _kpEffectId, pEffect->Attribute( "name" ) ) )
		{
			// Found the mesh
			bEffectExist = true;
			_pEffectElement = pEffect->FirstChildElement( "mesh" );
			break;
		}
	}

	char cBuffer[256 ];
	sprintf_s( cBuffer, "Failes to find effect : %s in COLLADA FILE %s : ", _kpEffectId, m_kpcFileName );
	assert_msg( bEffectExist, cBuffer );

	return bEffectExist;
}