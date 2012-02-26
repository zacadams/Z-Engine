/**
 *	@file Z-Engine\Z-Engine\Projects\Windows\Interfaces\CoreLib\RTTIRegistrar.h
 *	@brief 
 *	
 *	Copyright()
 *		Copyright © 2010 - 2011 - Team Poly Gone. All Rights Reserved.
 *	
 *********************************************************************************************/
#ifndef _RTTIREGISTRAR_H__Included_1447015661
#define _RTTIREGISTRAR_H__Included_1447015661

namespace ZGE
{

#define REGISTER_DYNAMIC_CREATE(class_name, registry )\
void* CreateInstance_##class_name( )\
{\
	return new class_name( );\
}\
static IRTTIRegistrar s_Registrar##class_name( #class_name, &CreateInstance_##class_name, &registry::GetInstance() );\

#define _MAX_REGISTRAR_ID_LENGHT 256
	class IRTTIRegistry;
	/**
	 *	This class holds a record of a RTTI object.
	 */
	class IRTTIRegistrar
	{
	public:
		typedef void* (InstanciationFunction)(void);				// Function which creates an instance of registered object.
		char				   m_pcId[_MAX_REGISTRAR_ID_LENGHT];	//!< The record of the registered objects name.
		InstanciationFunction* m_pInstanciationFunction;			//!< The instanciation function for the registered 
		IRTTIRegistry*		   m_pRegister;							//!< The register we are registered to.
		IRTTIRegistrar( const char* _kpcId, InstanciationFunction* pInstantciationFunc, IRTTIRegistry* _pRegister ); 
		virtual ~IRTTIRegistrar(void);
	};
}

#endif //_RTTIREGISTRAR_H__Included_1447015661

