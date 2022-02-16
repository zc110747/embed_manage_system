
#ifndef _INCLUDE_GTIMER_H
#define _INCLUDE_GTIMER_H

#include <list>
#include <vector>
#include <string>
#include <unistd.h>
#include <signal.h>
#include <time.h> 
#include <sys/time.h>

#define SYSTME_TIME_BASED_PEROID  1
typedef void (*pfunc)(void);
typedef struct 
{
  pfunc func;
  int id;
  bool allowed;
  int current_times;
  int max_times;
}TimerFunc;

class gTimer
{
public:
    gTimer();
    ~gTimer();

    void InsertAction(TimerFunc* action);
    void StartAction(int id, int times);
    void StopAction(int id);
    void start();
    void stop();
    
    static void timerHandler(int signo);
    static gTimer *getInstance(void);
    static void ReleaseInstance(void);
private:
    static std::vector<TimerFunc *> FuncList;

    static gTimer* pInstance;
};

#endif
