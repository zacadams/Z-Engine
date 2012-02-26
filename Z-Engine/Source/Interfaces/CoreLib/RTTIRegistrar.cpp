#include "CoreLib/Core.h" 
#include <stdio.h>
#include "CoreLib/RTTIRegistry.h"
#include "CoreLib/RTTIRegistrar.h"
using namespace ZGE;

IRTTIRegistrar::IRTTIRegistrar( const char* _kpcId, InstanciationFunction* pInstantciationFunc, IRTTIRegistry* _pRegister )
{
	STR_PRINT(  m_pcId, _MAX_REGISTRAR_ID_LENGHT,"%s" , _kpcId ); 
	//ZUtilities::StrPrint( m_pcId, "%s", _MAX_REGISTRAR_ID_LENGHT, _kpcId ); 
	//sprintf_s( m_pcId, "%s", _kpcId );
	m_pInstanciationFunction = pInstantciationFunc;
	m_pRegister = _pRegister;
	m_pRegister->Register( this );
}

IRTTIRegistrar::~IRTTIRegistrar(void)
{
}
