#ifndef __CALCTIME_H__
#define __CALCTIME_H__
#include <stddef.h>
#include <time.h>

/**  
 * @brief get the current time to run the task  
 * @param[in] _period_ms - the periodic time to run the function
 * @param[in] _clk_id - specify the id of the system clock to be used 
 * @return current time as struct timespec
 */
struct timespec GetTime(clockid_t _clk_id, size_t _period_ms);
/**  
 * @brief calculate time to sleep till running, and sleep for the sleep time 
 * @param[in] m_startTime - the start time of the task
 * @param[in] _clk_id - specify the id of the system clock to be used 
 * @return -no
 */
void SleepTillTime(clockid_t _clk_id, struct timespec m_startTime);
#endif /*__CALCTIME_H__*/
