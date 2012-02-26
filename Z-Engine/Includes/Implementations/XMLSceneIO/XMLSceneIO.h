/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Implementations\XMLSceneIO\XMLSceneIO.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _XMLSCENEIO_H__Included_1417548001
#define _XMLSCENEIO_H__Included_1417548001

#include "SceneLib/SceneIO.h"
class TiXmlElement;
namespace ZGE
{
	class CXMLSceneIO : public ISceneIO
	{
	public:
		CXMLSceneIO(void);
		~CXMLSceneIO(void);

		/**
		 *	Parses a scene from a XML file.
		 *	@param _kpcSceneName The scene to parse.
		 *  @param _pRootNode  The scenes root node.
		 *	@return Success.
		 */
		virtual bool ParseScene( const char* _kpcScene, CActor*& _pRootNode );
		
		/**
		 *	Saves the scene to a XML file.
		 *	@param _kpcFileName The name of the file to write.
		 *  @param _pRootNode  The scenes root node.
		 *	@return Success.
		 */
		virtual bool SaveScene( const char* _kpcFileName, CActor* _pRootNode );

	protected:

		// Parses a actor from file.
		bool ParseActor( TiXmlElement* _pElement, CActor*& _pActor );

		// Writes a actor to a file.
		TiXmlElement*  SerializeActor( TiXmlElement* _pParent, CActor* _pActor );

		// Parses a 2D actor from file.
		bool Parse2DActor( TiXmlElement* _pElement, CActor* _pActor );

		// Writes a 3D actor to file.
		TiXmlElement*  Serialize2DActor( TiXmlElement* _pParent, CActor* _pActor );

		// Recursive.
		void RecurseSerialize( TiXmlElement* _pParent, CActor* _pActor );
	
		// Recusrsive.
		void RecursiveParse( TiXmlElement* _pElement, CActor*& _pParent );

		// Converts a value to a string.
		void FloatToString( float32* _pValues, char* _pCharArray ,const uint32 uElementCount = 0 );  

		template< typename t>
		void StringToValues( const char* _kcpValues, t* _pValues, const uint32 _kuCount );
	};
}

#endif //_XMLSCENEIO_H__Included_1417548001

