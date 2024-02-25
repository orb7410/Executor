#define _POSIX_C_SOURCE 199309L
#include "calcTime.h"
#include <stdio.h>
#include <time.h>
#define NANO_TO_MICRO(x) ((x) / 1000)
#define MILI_TO_MICRO(x) ((x) * 1000)
#define MILI_TO_NANO(x) ((x) * 1000000)
#define NANO_TO_SEC_FACTOR 1000000000
#define SECS_TO_MICRO(x) ((x) * 1000000)
/***********************************************************/
struct timespec GetTime(clockid_t _clk_id, size_t _period_ms)
{
    struct timespec t;
    /*printf("clock get time return val is: %d\n", );*/
    clock_gettime (_clk_id, &t);
    _period_ms = MILI_TO_NANO(_period_ms);/*convert ms to nano*/
    /*printf("piriod ms is %ld\n", _period_ms);*/
    t.tv_sec +=  (_period_ms + t.tv_nsec) /NANO_TO_SEC_FACTOR;
    t.tv_nsec =(_period_ms + t.tv_nsec) % NANO_TO_SEC_FACTOR; 
    return (t);
}
/***********************************************************/
void SleepTillTime(clockid_t _clk_id, struct timespec m_startTime)
{
    long secToWait, nanoToWait, totalTimeToWait;
    long curSec, curNano, runSec, runNano;
    struct timespec curTime;
    clock_gettime (_clk_id, &curTime);
    curSec = curTime.tv_sec; 
    curNano = curTime.tv_nsec;
    runSec = m_startTime.tv_sec;
    runNano = m_startTime.tv_nsec;

    if(curSec>runSec || (curSec==runSec && curNano>=runNano)) /*starttime need to be bigger*/
    {
        return;
    }
    if(curNano < runNano) /*get the difference*/
    {
        secToWait = runSec - curSec;
        nanoToWait = runNano - curNano;
    }
    else
    {
        secToWait = (runSec-1) - curSec;
        nanoToWait = runNano + (1 * NANO_TO_SEC_FACTOR ) - curNano; /*case negative borrow 1 sec to the caculation*/
    }
    totalTimeToWait = SECS_TO_MICRO(secToWait) + NANO_TO_MICRO(nanoToWait);/*ms*/
    /*printf("time to wait is %ld\n",totalTimeToWait);*/
    usleep(totalTimeToWait);
}
/***********************************************************/
/*
struct timespec {
               time_t   tv_sec;         seconds 
               long     tv_nsec;        nanoseconds 
           };
*/
