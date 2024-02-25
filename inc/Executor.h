#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__
#include <time.h>
#include <stddef.h>
#include <features.h>
#include <sys/types.h>
typedef enum ExecutorResultCode {
	EXECUTOR_SUCCESS = 0,
	EXECUTOR_NOT_INITIALIZED,
    EXECUTOR_ALLOCATION_FAILED
} ExecutorResultCode;


typedef struct PeriodicExecutor PeriodicExecutor;
/**********************************************************************************************************************/
/**  
 * @brief Create a periodic executor that will measure time using given clock 
 * @param[in] _name - specify the id of the system clock to be used
 * @param[in] _clk_id - specify the id of the system clock to be used

 * @return 
 * @retval 
 *
 */
PeriodicExecutor* PeriodicExecutor_Create(const char* _name, clockid_t _clk_id);
/**********************************************************************************************************************/
 /**  
 * @brief Destroy previously created executor.
 * @param[in] _executor - previously created executor
 * @warning  
 */   
void PeriodicExecutor_Destroy(PeriodicExecutor* _executor);
/**********************************************************************************************************************/
 /* @brief Adding task to the executor
 * @param[in] _executor - previously created executor
 * @param[in] _context-
 * @param[in] _period_ms-
 * @return 
 * @retval 
 *
*/
int PeriodicExecutor_Add(PeriodicExecutor* _executor, int (*_taskFunction)(void *), void* _context, size_t _period_ms);
/**********************************************************************************************************************/
 /* @brief Start running the tasks previously added to the executor or resume a previously paused Executor
 * @param[in] _executor - previously created executor
 * @return 
 * @retval 
 *
*/
size_t PeriodicExecutor_Run(PeriodicExecutor* _executor);
/**********************************************************************************************************************/
 /* @brief Pause the execution of the executor. 
 * @param[in] _executor - previously created executor
 * @return 
 * @retval 
 * @commend: If a task is currently being executed then pause after it has completed the current cycle.
*/
size_t PeriodicExecutor_Pause(PeriodicExecutor* _executor);
/**********************************************************************************************************************/
#endif /*__EXECUTOR_H__*/