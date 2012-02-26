#ifndef _PERFORMANCEMANAGER_H__Included_1840393078
#define _PERFORMANCEMANAGER_H__Included_1840393078

#include "CoreLib/Clock.h"
#include "CoreLib/Node.h"
#include <list>
namespace ZGE
{

	/**
	 *
	 */
	class CPerformanceNode : public CNode<CPerformanceNode>
	{
	public:
		CPerformanceNode( );
		void StartPerformance( );
		void EndPerformance( );
		float32 GetPerformanceTime( );
		void Reset( );
		void CalculatePerformance( const float32 fParentTime );
		void SetTime( const float32 fTime);
	protected:
		CClock	m_Timer;
		float32 m_fPerformanceTime;
	};

	/**
	 *	The performance manager. 
	 */
	class CPerformanceManager
	{
	public:

		// Initialises the performance manager.
		bool Initialise( );

		// Adds a performance target. 
		CPerformanceNode* CreatePerformanceNode( const char* _kpcPerformanceMessage, const char* _kpcParent );
		
		// Prints the performance data.
		void Print( );

		static CPerformanceManager* GetInstance( );
		static void DestroyInstance( );

	protected:
		// Constuctor made private.
		CPerformanceManager(void);
		~CPerformanceManager(void);
	protected:
		static CPerformanceManager* sm_pInstance;
		CPerformanceNode* m_pPerformanceRoot;
	};
}

#ifdef Z_ENABLE_PERFORMANCE_TEST
	#define CREATE_PERFORMANCE_TIMER( performanceNode, performanceMessage, parent )\
	static CPerformanceNode* _##performanceNode = CPerformanceManager::GetInstance( )->CreatePerformanceNode( performanceMessage, parent );\
	performanceNode = _##performanceNode;\

	#define START_PERFORMANCE_TIMER( performanceNode )\
		performanceNode->StartPerformance( );\

	#define END_PERFORMANCE_TIMER( performanceNode )\
		performanceNode->EndPerformance( );

#else

	#define CREATE_PERFORMANCE_TIMER( performanceNode, performanceMessage, parent )
	#define START_PERFORMANCE_TIMER( performanceNode )
	#define END_PERFORMANCE_TIMER( performanceNode )

#endif

#endif //_PERFORMANCEMANAGER_H__Included_1840393078

