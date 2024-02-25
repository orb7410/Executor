#define _POSIX_C_SOURCE 199309L
#include "GenericVector.h"
#include "GenericHeap.h"
#include "Executor.h"
#include "task.h"
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include "string.h"
#define MAGIC_NUM 208645311
struct PeriodicExecutor{
    char m_name[30]; /*name of what?*/
    clockid_t m_clockId;
    Vector* m_tasks;
    int m_flagRunning;
    int m_magicNum;
};

PeriodicExecutor* PeriodicExecutor_Create(const char* _name, clockid_t _clk_id)
{
    Vector* newVector;
    PeriodicExecutor* newPeriodicExecutor;
    if (NULL==_name)
    {
        return NULL;
    }
    if (NULL==(newVector= VectorCreate(10, 1)))
    {
        return NULL;
    }
    if (NULL == (newPeriodicExecutor = (PeriodicExecutor*)malloc(sizeof(PeriodicExecutor))))
    {
        VectorDestroy(&newVector, NULL);
        return NULL;
    }
    strcpy(newPeriodicExecutor -> m_name, _name);
    newPeriodicExecutor -> m_clockId = _clk_id;
    newPeriodicExecutor -> m_tasks = newVector;
    newPeriodicExecutor -> m_flagRunning = 0;
    return newPeriodicExecutor;
}
/******************************************************************/
void PeriodicExecutor_Destroy(PeriodicExecutor* _executor)
{
    if (NULL == _executor ||MAGIC_NUM != _executor->m_magicNum) 
	{
	    return;
	}

    VectorDestroy(&_executor->m_tasks, TaskDestroy);
    _executor-> m_magicNum = 0;
    free(_executor);
}
/******************************************************************/
int PeriodicExecutor_Add(PeriodicExecutor* _executor, int (*_taskFunction)(void *), void* _context, size_t _period_ms)
{
    Task* newTask;
    if (NULL == _executor || NULL == _taskFunction || 0 == _period_ms)
    {
        return 	EXECUTOR_NOT_INITIALIZED;
    } 
    if (NULL == (newTask = createTask(_taskFunction, _context, _period_ms, _executor-> m_clockId)))
    {
        return EXECUTOR_ALLOCATION_FAILED;
    }
    if (VECTOR_SUCCESS != VectorAppend(_executor->m_tasks, newTask))
    {
        return EXECUTOR_ALLOCATION_FAILED;
    }
} 
/******************************************************************/
size_t PeriodicExecutor_Run(PeriodicExecutor* _executor)
{
    size_t size, timeToRun, i, counter = 0;
    void* task;
    Heap* newHeap;
    if (NULL == _executor)
    {
        return 	0; 
    } 
    size = VectorSize(_executor -> m_tasks);
    for(i = 0; i < size; i++)/*loop-run over the the vector elements, calculate time to run to each element*/
    {
        VectorGet(_executor -> m_tasks, i, &task);
        UpdateStartTime((Task*)task);
    }
     if (NULL==(newHeap= HeapBuild(_executor -> m_tasks, LessComparatore)))/*heap build- sorted by runtime*/
    {
        return 0;
    }
    _executor-> m_flagRunning = 0;
    while(_executor->m_flagRunning == 0 && HeapSize(newHeap) > 0)
    {
        task = (Task*)HeapExtract(newHeap);
        if (TaskRun(task)== 0)
        { 
            UpdateStartTime(task);           
            if(HEAP_SUCCESS != HeapInsert(newHeap, task))
            {
                TaskDestroy(task);
                break;
            }
        }
        else
        {
            TaskDestroy(task);
        }
        counter++;
    }
    HeapDestroy(&newHeap);
    return counter;
    /*loop- while flaf==0 && heap not empty: Heapextruct, run task- if 0: insert back to heap, calculate new time to run, if not: destroy task*/
}
/******************************************************************/
size_t PeriodicExecutor_Pause(PeriodicExecutor* _executor)
{
    if (NULL == _executor)
    {
        return 	0; 
    } 
    _executor-> m_flagRunning = 1;
    return VectorSize(_executor -> m_tasks);
}
/*******************************************************************/
size_t ExGetMagicNum(PeriodicExecutor* _executor)
{
	return (_executor -> m_magicNum);
}
int ExGetReallMagicNum(void)
{
	return MAGIC_NUM;
}
size_t ExGetVectorSize(PeriodicExecutor* _executor)
{
    return VectorSize(_executor -> m_tasks);
}
char* ExGetName(PeriodicExecutor* _executor)
{
    return (_executor -> m_name);
}



