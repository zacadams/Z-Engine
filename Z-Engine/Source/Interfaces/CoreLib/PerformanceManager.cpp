#include "CoreLib/Core.h"
#include "CoreLib/PerformanceManager.h"
using namespace ZGE;

CPerformanceManager* CPerformanceManager::sm_pInstance = NULL;

CPerformanceManager::CPerformanceManager(void)
: m_pPerformanceRoot( NULL )
{
}

CPerformanceManager::~CPerformanceManager(void)
{
	SafeDelete( m_pPerformanceRoot );
}

// Initialises the performance manager.
bool CPerformanceManager::Initialise( )
{
	return false;
}

// Adds a performance target. 
CPerformanceNode* CPerformanceManager::CreatePerformanceNode( const char* _kpcPerformanceMessage, const char* _kpcParent )
{

	// Was a parent provided? 
	CPerformanceNode* pPerfNode = new CPerformanceNode( );
	pPerfNode->SetName( _kpcPerformanceMessage );

	if( NULL == m_pPerformanceRoot )
	{
		m_pPerformanceRoot = pPerfNode;
		return pPerfNode;
	}
	if( _kpcParent )
	{
		// Yes, parent a new performance node to the parent node.
		CPerformanceNode* pParent = m_pPerformanceRoot->FindChild( _kpcParent );
		pParent->AddChild( pPerfNode );	
	}
	else
	{
		// No parent, attach to the root node.
		m_pPerformanceRoot->AddChild( pPerfNode );
	}
	return pPerfNode;
}

// Prints the performance data.
void CPerformanceManager::Print( )
{
	
	const float32 fTotalTime = ZEngine::GetClock( )->GetDeltaTick( );


	const float32 fFrameRate = ZEngine::GetClock( )->GetFrameRate( );
	static char pBuffer[256];
	STR_PRINT( pBuffer, "FPS : %0.3f\n", fFrameRate );
	OutputDebugStringA( pBuffer );

	//m_pPerformanceRoot->SetTime( fTotalTime );
	m_pPerformanceRoot->CalculatePerformance( m_pPerformanceRoot->GetPerformanceTime( ) );
	m_pPerformanceRoot->Reset( );

	OutputDebugStringA( "\n\n" );
}



CPerformanceManager* CPerformanceManager::GetInstance( )
{
	if( NULL == sm_pInstance )
	{
		sm_pInstance = new CPerformanceManager( );
		sm_pInstance->Initialise( );
	}
	return sm_pInstance;
}
void CPerformanceManager::DestroyInstance( )
{
	if( sm_pInstance )
	{
		delete sm_pInstance;
		sm_pInstance = NULL;
	}
}


CPerformanceNode::CPerformanceNode( )
: m_fPerformanceTime( 0.0f )
{
	m_Timer.Initialise( );
}
void CPerformanceNode::StartPerformance( )
{
	m_Timer.Process( );
}
void CPerformanceNode::EndPerformance( )
{
	m_Timer.Process( );
	m_fPerformanceTime += m_Timer.GetDeltaTick( );
}
float32 CPerformanceNode::GetPerformanceTime( )
{
	return m_fPerformanceTime;
}


void CPerformanceNode::Reset( )
{
	m_fPerformanceTime = 0.0f;
	ChildList::iterator iter = m_lChildren.begin( );
	for( iter; iter != m_lChildren.end( ); ++iter )
	{
		(*iter)->Reset( );
	}
}
void CPerformanceNode::CalculatePerformance( const float32 fParentTime )
{
	static uint32 suChildDepth = 0;
	if( m_fPerformanceTime == 0.0f )
	{
		assert_now( "Performance node has ZERO time!" );
		return;
	}

	const float32 fPercent =(  m_fPerformanceTime / fParentTime ) * 100.0f;
	static char pBuffer[256];
	pBuffer[0] = 0;
	for( uint32 uDepth = 0; uDepth < suChildDepth; ++uDepth )
	{
		STR_PRINT( pBuffer, 256, "%s\t", pBuffer );
	}

	STR_PRINT( pBuffer, 256, "%s%s - Percent: %0.5f - Duration: %0.7f\n", pBuffer ,m_pcName,fPercent, m_fPerformanceTime );
	OutputDebugStringA( pBuffer ); 
	
	suChildDepth++;
	ChildList::iterator iter = m_lChildren.begin( );
	for( iter; iter != m_lChildren.end( ); ++iter )
	{
		(*iter)->CalculatePerformance( m_fPerformanceTime );
	}
	suChildDepth--;
}

void CPerformanceNode::SetTime( const float32 fTime)
{
	m_fPerformanceTime = fTime;
}