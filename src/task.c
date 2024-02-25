#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include "task.h"
#include "calcTime.h"
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
struct Task{
    size_t m_piriodicTime; /*every how much time to run (sort base on that )*/
    TaskFunc m_taskFunc;
    struct timespec m_startTime;
    clockid_t m_clockId;
    void* m_context;
};
/***********************************************************/
Task* createTask(int (*TaskFunc)(void *), void* _context, size_t _period_ms, clockid_t m_clockId)
{
    Task* newTask;
    if (NULL == TaskFunc || 0 == _period_ms)
    {
        return NULL;
    } 
    if (NULL == (newTask = (Task*)malloc(sizeof(Task))))
    {
        return NULL;
    }

    newTask -> m_taskFunc = TaskFunc;
    newTask -> m_piriodicTime = _period_ms;
    newTask -> m_clockId = m_clockId;
    newTask -> m_context = _context;
    newTask -> m_startTime.tv_nsec =0;
    newTask -> m_startTime.tv_sec =0;
    
    return newTask;
}
/***********************************************************/
void TaskDestroy(void* _task)
{
    if (NULL == _task)
    {
        return;
    }
    free(_task);
}
/***********************************************************/
void UpdateStartTime(Task* _task)
{
    if (NULL == _task)
    {
        return;
    }
    _task->m_startTime = GetTime(_task->m_clockId, _task->m_piriodicTime);
}
/***********************************************************/
int LessComparatore(const void *_first, const void *_second)
{
    time_t firstSec=((Task*)_first)-> m_startTime.tv_sec;
    time_t secondSec=((Task*)_second)-> m_startTime.tv_sec;
    long firstNano = ((Task*)_first)-> m_startTime.tv_nsec;
    long secondNano = ((Task*)_second)-> m_startTime.tv_nsec;

    if(firstSec == secondSec)/*cover if the same*/
    {
        return (firstNano > secondNano);
    }
    return (firstSec > secondSec); 
}
/***********************************************************/
int TaskRun(Task* _task)
{
    if (NULL == _task)
    {
        return 1;
    }
    SleepTillTime(_task->m_clockId,_task-> m_startTime);
    /*printf("start time in sec is: %ld\n",  _task -> m_startTime.tv_sec);*/
    return(_task->m_taskFunc(_task-> m_context)); /*if return 0, want to run again*/
}
/***********************************************************/
time_t TaskGetStartTime(Task* _task)
{
    return (_task-> m_startTime.tv_sec);
}
long TaskGetStartTimenS(Task* _task)
{
    return (_task-> m_startTime.tv_nsec);
}
TaskFunc TaskGetFuction(Task* _task)
{
    return _task -> m_taskFunc;
}
void* TaskGetContext(Task* _task)
{
    return _task -> m_context;
}