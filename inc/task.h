#ifndef __TASK_H__
#define __TASK_H__

#include <stddef.h>
#include <time.h>
typedef struct Task Task;
typedef int	(*TaskFunc)(void *_task);
/**  
 * @brief Dynamically create a new Task  
 * @param[in] TaskFunc - the function we want to save in the task
 * @param[in] _context - the function parametrs to run, can be Null
 * @param[in] _period_ms - the period time to run the function
 * @param[in] m_clockId - - specify the id of the system clock to be used 
 * @return Task* -  success
 * @retval NULL - fail  
 */
 Task* createTask(int (*TaskFunc)(void *), void* _context, size_t _period_ms, clockid_t m_clockId);
/**  
 * @brief Dynamically deallocate a previously allocated Task  
 * @param[in] _task - Task to be deallocated.
 * @return -
 */
void TaskDestroy(void* _task);
/**  
 * @brief Update the function's time to start runing. 
 * @param[in] _task - the Task to update its time.
 * @return - 
 */
 void UpdateStartTime(Task* _task);

/**  
 * @brief compare between two Task's start runing times.
 * @param[in] _first - first task to compare
 * @param[in] _second - second task to compare
 * @return True if the first task start runing time is bigger than the second 
 * @return False if the second task start runing time is bigger than the first 
 */
 int LessComparatore(const void *_first, const void *_second);
 /**  
 * @brief run the task, while waiting for the required time
 * @param[in] _task - the task tht should be run.
 * @return 1 if task NULL
 * @return the context of the function that runs.
 */
 int TaskRun(Task* _task);








#endif /*__TASK_H__*/