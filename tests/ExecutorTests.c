#define _POSIX_C_SOURCE 199309L
#include "task.h"
#include "Executor.h"
#include "calcTime.h"
#include "stdio.h"
#include <time.h>
#define  MAGIC_NUM 208645311
/*CLOCK_REALTIME, CLOCK_MONOTONIC */
/*************************************************/
int TaskC(void* _value);
int TaskB(void* _value);
int TaskA(void* _value);
int TaskPouse(void* _value);
TaskFunc TaskGetFuction(Task* _task);
time_t TaskGetStartTime(Task* _task);
long TaskGetStartTimenS(Task* _task);
void* TaskGetContext(Task* _task);
/*************************************************/
char* ExGetName(PeriodicExecutor* _executor);
int ExGetReallMagicNum(void);
size_t ExGetMagicNum(PeriodicExecutor* _executor);
size_t ExGetVectorSize(PeriodicExecutor* _executor);
/********************Task*************************/
static void Test1TaskcreateOk(void);
static void Test2TaskcreateFuncionNull(void);
static void Test3TaskcreatePeriodicTimeIsZero(void);
static void Test4TaskcreateFunctionOk(void);
static void Test5TaskcreateContextOk(void);
static void Test6UpdateStartTimeOk(void);
static void Test7RunTaskReturnOk(void);
/********************EXEC*************************/
static void test1PeriodicExecutorCreateOk(void);
static void test2PeriodicExecutorCreateNameOk(void);
static void Test3ExecutorDestroyMagicNam(void);
static void Test4ExecutorDestroyDoubel(void);
static void Test5PeriodicExecutor_Add(void);
static void Test6PeriodicExecutor_AddExNull(void);
static void Test7PeriodicExecutor_AddTaskNull(void);
static void Test8PeriodicExecutor_runOneTesk(void);
static void Test9PeriodicExecutorRunTesksAndPous(void);
static void Test10PeriodicExecutorRunNoTesks(void);
int main()
{
    Test1TaskcreateOk();
    Test2TaskcreateFuncionNull();
    Test3TaskcreatePeriodicTimeIsZero();
    Test4TaskcreateFunctionOk();
    Test5TaskcreateContextOk();
    Test6UpdateStartTimeOk();
    Test7RunTaskReturnOk();

    test1PeriodicExecutorCreateOk();
    Test3ExecutorDestroyMagicNam();
    Test4ExecutorDestroyDoubel();
    Test5PeriodicExecutor_Add();
    Test6PeriodicExecutor_AddExNull();
    Test7PeriodicExecutor_AddTaskNull();
    Test8PeriodicExecutor_runOneTesk();
    Test9PeriodicExecutorRunTesksAndPous();
    Test10PeriodicExecutorRunNoTesks();
}
/**************/
int TaskA(void* _value)
{
    if (NULL == _value)
    {
        printf(" Task A\n");
        return 1;
    }
    printf("Task A- value is %s\n", ((char*)_value));
    printf("\n");
    return 1;
}
/**************/
int TaskB(void* _value)
{
    static int counter =0;
    if (NULL == _value)
    {
        printf(" Task B\n");
        return 1;
    }
    if (counter > 4)
    {
        return 1;
    }
    printf("Task B- value is %s\n", ((char*)_value));
    printf("\n");
    counter++;
    return 0;
}
/**************/
int TaskC(void* _value)
{
    if (NULL == _value)
    {
        printf("Task C\n");
        return 1;
    }
    printf("Task C- value is %s\n", ((char*)_value));
    printf("\n");
    return 0;
}
/**************/
int TaskPouse(void* _value)
{
    if(_value == NULL)
	{
		return 1;
	}
    printf("pous\n");
    return PeriodicExecutor_Pause((PeriodicExecutor*)_value);
}

/********************EXECUTOR TESTS******************************/
static void test1PeriodicExecutorCreateOk(void)
{
    PeriodicExecutor* newPeriodicExecutor = NULL;
    newPeriodicExecutor = PeriodicExecutor_Create("or", CLOCK_REALTIME);
    if (newPeriodicExecutor != NULL)
	{
		printf("%-50s %s", "Test1 PeriodicExecutor_Create OK","*PASS*\n");
	}
	else
	{	
		printf("%-50s %s", "Test1 PeriodicExecutor_Create OK","*FAIL*\n");
        
	}
    PeriodicExecutor_Destroy(newPeriodicExecutor);
}
static void test2PeriodicExecutorCreateNameOk(void)
{
    PeriodicExecutor* newPeriodicExecutor = NULL;
    char name[10]="or";
    newPeriodicExecutor = PeriodicExecutor_Create(name, CLOCK_REALTIME);
    if (ExGetName(newPeriodicExecutor) == name)
	{
		printf("%-50s %s", "Test2 PeriodicExecutor_Create NameOk","*PASS*\n");
	}
	else
	{	
		printf("%-50s %s", "Test2 PeriodicExecutor_Create NameOk","*FAIL*\n");
        PeriodicExecutor_Destroy(newPeriodicExecutor);
	}
}
static void Test3ExecutorDestroyMagicNam(void)
{
    PeriodicExecutor* newPeriodicExecutor = NULL;
    newPeriodicExecutor = PeriodicExecutor_Create("or", CLOCK_REALTIME);
    PeriodicExecutor_Destroy(newPeriodicExecutor);
	if(ExGetMagicNum(newPeriodicExecutor) != ExGetReallMagicNum())
	{
		printf("%-50s %s", "Test3 ExecutorDestroy OK","*PASS*\n");
	}
	else
	{
		printf("%-50s %s","Test3 ExecutorDestroy OK","*FAIL*\n");
	}
	
}

static void Test4ExecutorDestroyDoubel(void)
{
	PeriodicExecutor *ptrExecutor;
    ptrExecutor = PeriodicExecutor_Create("Name", CLOCK_REALTIME);
    PeriodicExecutor_Destroy(ptrExecutor);
    PeriodicExecutor_Destroy(ptrExecutor);
	printf("%-50s %s", "Test4 ExecutorDestroyDoubelFree","*PASS*\n");
	
}
static void Test5PeriodicExecutor_Add(void)
{
    PeriodicExecutor *newExecutor;
    int result;
    newExecutor = PeriodicExecutor_Create("Name", CLOCK_REALTIME);
    PeriodicExecutor_Add(newExecutor, TaskA, "or", 2);
    result = PeriodicExecutor_Add(newExecutor, TaskA, "Ron", 3);
    if (ExGetVectorSize(newExecutor) == 2 && result == EXECUTOR_SUCCESS)
    {
       printf("%-50s %s", "Test5 PeriodicExecutor_Add OK","*PASS*\n"); 
    }
    else
	{
		printf("%-50s %s","Test5 PeriodicExecutor_Add OK","*FAIL*\n");
	}
    PeriodicExecutor_Destroy(newExecutor);
}
static void Test6PeriodicExecutor_AddExNull(void)
{
    PeriodicExecutor *newExecutor;
    int result;
    newExecutor = PeriodicExecutor_Create("Name", CLOCK_REALTIME);
    if ( PeriodicExecutor_Add(NULL, TaskA, "or", 2) == EXECUTOR_NOT_INITIALIZED)
    {
       printf("%-50s %s", "Test6 PeriodicExecutor_Add ExNull","*PASS*\n"); 
    }
    else
	{
		printf("%-50s %s","Test6 PeriodicExecutor_Add ExNull","*FAIL*\n");
	}
    PeriodicExecutor_Destroy(newExecutor);
}
static void Test7PeriodicExecutor_AddTaskNull(void)
{
    PeriodicExecutor *newExecutor;
    int result;
    newExecutor = PeriodicExecutor_Create("Name", CLOCK_REALTIME);
    if ( PeriodicExecutor_Add(newExecutor, NULL, "or", 2) == EXECUTOR_NOT_INITIALIZED)
    {
       printf("%-50s %s", "Test7 PeriodicExecutor_Add TaskNull","*PASS*\n"); 
    }
    else
	{
		printf("%-50s %s","Test7 PeriodicExecutor_Add TaskNull","*FAIL*\n");
	}
    PeriodicExecutor_Destroy(newExecutor);
}
static void Test8PeriodicExecutor_runOneTesk(void)
{
    PeriodicExecutor *newExecutor;
    size_t counter;
    int num1 = 2, num2 = 2, num3 = 3, num4 = 4;
    void *item1 = &num1, *item2 = &num2, *item3 = &num3, *item4 = &num4;
    newExecutor = PeriodicExecutor_Create("Name", CLOCK_REALTIME);
    PeriodicExecutor_Add(newExecutor, TaskA, "or", 3000);
    counter = PeriodicExecutor_Run(newExecutor);
	if(counter == 1)
    {
       printf("%-50s %s", "Test8 PeriodicExecutor_runOneTeskOnce","*PASS*\n"); 
    }
    else
	{
		printf("%-50s %s","Test8 PeriodicExecutor_runOneTeskOnce","*FAIL*\n");
	}  
    PeriodicExecutor_Destroy(newExecutor);
}
static void Test9PeriodicExecutorRunTesksAndPous(void)
{
    PeriodicExecutor *newExecutor;
    size_t counter;
    int num1 = 2, num2 = 2, num3 = 3, num4 = 4;
    void *item1 = &num1, *item2 = &num2, *item3 = &num3, *item4 = &num4;
    newExecutor = PeriodicExecutor_Create("Name", CLOCK_REALTIME);
    PeriodicExecutor_Add(newExecutor, TaskA, "or", 3000);
    PeriodicExecutor_Add(newExecutor, TaskB, "Ron", 2000);
    PeriodicExecutor_Add(newExecutor, TaskC, "Aviv", 2000);
    PeriodicExecutor_Add(newExecutor, TaskPouse, newExecutor, 20000);
    counter = PeriodicExecutor_Run(newExecutor);
    printf("counter = %ld \n", counter);
    printf("%-50s %s", "Test9 PeriodicExecutor runTesksAndPous","*PASS*\n"); 
    PeriodicExecutor_Destroy(newExecutor);
}
static void Test10PeriodicExecutorRunNoTesks(void)
{
    PeriodicExecutor *newExecutor;
    size_t counter;
    int num1 = 2, num2 = 2, num3 = 3, num4 = 4;
    void *item1 = &num1, *item2 = &num2, *item3 = &num3, *item4 = &num4;
    newExecutor = PeriodicExecutor_Create("Name", CLOCK_REALTIME);
    counter = PeriodicExecutor_Run(newExecutor);
	if(counter == 0)
    {
       printf("%-50s %s", "Test10 PeriodicExecutor runNoTesks","*PASS*\n"); 
    }
    else
	{
		printf("%-50s %s","Test10 PeriodicExecutor runNoTesks","*FAIL*\n");
	}  
    PeriodicExecutor_Destroy(newExecutor);
}
/*********************TASK******************************/
static void Test1TaskcreateOk(void)
{
    Task* newTask = NULL;
    newTask = createTask(TaskA, "or", 2, CLOCK_REALTIME);
    if (newTask != NULL)
	{
		printf("%-50s %s", "Test1 Taskcreate OK","*PASS*\n");
	}
	else
	{	
		printf("%-50s %s", "Test1 Taskcreate OK","*FAIL*\n");
        
	}
    TaskDestroy((void*)newTask);
}
static void Test2TaskcreateFuncionNull(void)
{
    Task* newTask = NULL;
    newTask = createTask(NULL, "or", 2, CLOCK_REALTIME);
    if (newTask == NULL)
	{
		printf("%-50s %s", "Test2 Taskcreate FuncionNull","*PASS*\n");
	}
	else
	{	
		printf("%-50s %s", "Test2 Taskcreate FuncionNull","*FAIL*\n");
        
	}
    TaskDestroy((void*)newTask);
}
static void Test3TaskcreatePeriodicTimeIsZero(void)
{
    Task* newTask = NULL;
    newTask = createTask(TaskA, "or", 0, CLOCK_REALTIME);
    if (newTask == NULL)
	{
		printf("%-50s %s", "Test3 Taskcreate PeriodicTimeIsZero","*PASS*\n");
	}
	else
	{	
		printf("%-50s %s", "Test3 Taskcreate PeriodicTimeIsZero","*FAIL*\n");
        
	}
    TaskDestroy((void*)newTask);
}
static void Test4TaskcreateFunctionOk(void)
{
    Task* newTask = NULL;
    newTask = createTask(TaskA, "or", 3, CLOCK_REALTIME);
    if (TaskGetFuction(newTask) == TaskA)
	{
		printf("%-50s %s", "Test4 Taskcreate FunctionOk","*PASS*\n");
	}
	else
	{	
		printf("%-50s %s", "Test4 Taskcreate FunctionOk","*FAIL*\n");
        
	}
    TaskDestroy((void*)newTask);
}
static void Test5TaskcreateContextOk(void)
{
    Task* newTask = NULL;
    int num1 = 2;
    void *item1 = &num1;
    newTask = createTask(TaskA, item1, 3, CLOCK_REALTIME);
    if (TaskGetContext(newTask) == item1)
	{
		printf("%-50s %s", "Test5 Taskcreate ContextOk","*PASS*\n");
	}
	else
	{	
		printf("%-50s %s", "Test5 Taskcreate ContextOk","*FAIL*\n");
        
	}
    TaskDestroy((void*)newTask);
}
static void Test6UpdateStartTimeOk(void)/*****/
{
    Task* newTask = NULL;
    time_t sec1, sec2;
    long nsec, nsec1;
    newTask = createTask(TaskA, NULL, 2, CLOCK_REALTIME);
    UpdateStartTime(newTask);
    sec1 = TaskGetStartTime(newTask);
    nsec = TaskGetStartTimenS(newTask);
    sleep(5);
    UpdateStartTime(newTask);    
    sec2 = TaskGetStartTime(newTask);
    nsec1 = TaskGetStartTimenS(newTask);
    printf("startTime: sec =%ld nsec =%ld \nstartTime after UpdateStartTime: sec=%ld nsec =%ld\n" , sec1, nsec, sec2, nsec1);
    if (sec2 > sec1)
	{
		printf("%-50s %s", "Test6 UpdateStartTime OK","*PASS*\n");
	}
	else
	{	
		printf("%-50s %s", "Test6 UpdateStartTime OK","*FAIL*\n");
        
	}
    TaskDestroy((void*)newTask);
}
static void Test7RunTaskReturnOk(void)
{
    Task* newTask = NULL;
    int num1 = 2;
    void *item1 = &num1;
    newTask = createTask(TaskA, item1, 3, CLOCK_REALTIME);
    if (0 != TaskRun(newTask))
	{
		printf("%-50s %s", "Test7 RunTask ReturnOk","*PASS*\n");
	}
	else
	{	
		printf("%-50s %s", "Test7 RunTask ReturnOk","*FAIL*\n");
        
	}
    TaskDestroy((void*)newTask);
}

