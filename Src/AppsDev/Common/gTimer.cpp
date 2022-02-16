
#include "gTimer.hpp"
#include <cstring>
#include <iostream>
#include <algorithm>

gTimer* gTimer::pInstance = nullptr;
std::vector<TimerFunc *> gTimer::FuncList;

gTimer::gTimer()
{
	//signal(SIGALRM, timerHandler);
}

gTimer::~gTimer()
{
	FuncList.clear();
}

gTimer* gTimer::getInstance(void)
{
	if(pInstance == nullptr)
	{
		pInstance = new(std::nothrow) gTimer;
		if(pInstance == nullptr)
		{
			std::cout<<"gTimer Create Error\r\n"<<std::endl;
		}
	}
	return pInstance;
}

void gTimer::ReleaseInstance(void)
{
	if(pInstance != nullptr)
	{
		delete pInstance;
		pInstance = nullptr;
	}
}

void gTimer::InsertAction(TimerFunc* action)
{
	uint8_t insert = true;

	std::for_each(FuncList.begin(), FuncList.end(), [&](const TimerFunc* ref){
		if(ref->id == action->id)
			insert = false;
	});

	if(insert)
	{
		std::cout<<"gTime function insert success, id:"<<action->id<<std::endl;
		FuncList.push_back(action);
	}
	else
		std::cout<<"gTime function already insert"<<std::endl;
}

void gTimer::StartAction(int id, int times)
{
	for(auto pFunc=FuncList.begin(); pFunc!=FuncList.end(); pFunc++)
	{
		if((*pFunc)->id == id)
		{
			(*pFunc)->current_times = 0;
			(*pFunc)->max_times = times;
			(*pFunc)->allowed = true;
			break;
		}
	}
}

void gTimer::StopAction(int id)
{
	for(auto pFunc=FuncList.begin(); pFunc!=FuncList.end(); pFunc++)
	{
		if((*pFunc)->id == id)
		{
			(*pFunc)->current_times = 0;
			(*pFunc)->allowed = false;
			break;
		}
	}
}

void gTimer::timerHandler(int signo)
{
	for(auto pFunc=FuncList.begin(); pFunc!=FuncList.end(); pFunc++)
	{
		if((*pFunc)->allowed && (*pFunc)->func)
		{
			(*pFunc)->current_times++;
			if((*pFunc)->current_times >= (*pFunc)->max_times)
			{
				(*((*pFunc)->func))();
				(*pFunc)->current_times = 0;
			}
			else
			{
				std::cout<<"id:"<<(*pFunc)->id<<" times_cur:"<<(*pFunc)->current_times<<std::endl;
			}
		}
	}
}

void gTimer::start()
{
	// struct itimerval tick = {0};

    // //初始执行的定时器计数值
    // tick.it_value.tv_sec = SYSTME_TIME_BASED_PEROID;
    // tick.it_value.tv_usec = 0;

    // //后续定时器执行的加载值
    // tick.it_interval.tv_sec = SYSTME_TIME_BASED_PEROID;
    // tick.it_interval.tv_usec = 0;

	// setitimer(ITIMER_REAL, &tick, NULL);
}

void gTimer::stop()
{
	//if zero, stop timer
	// struct itimerval tick = {0};

    // //初始执行的定时器计数值
    // tick.it_value.tv_sec = 0;
    // tick.it_value.tv_usec = 0;

    // //后续定时器执行的加载值
    // tick.it_interval.tv_sec = 0;
    // tick.it_interval.tv_usec = 0;

	// setitimer(ITIMER_REAL, &tick, NULL);
}
