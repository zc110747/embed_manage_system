/*
 * gThread.cpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#include "gThread.hpp"
#include <cstring>
#include <iostream>

std::list<gThread*> gThread::threads;

gThread::gThread()
{
    m_running = false;
    m_finished = false;
    m_id = (pthread_t)NULL;

    SetThreadName("gThread");
}

gThread::~gThread()
{
    if(m_running)
    {
        pthread_detach(m_id);
        Stop();
        this->WaitFinished();
    }
}

bool gThread::Setup()
{
	return true;
}


bool gThread::Start(void)
{
    if (!m_running)
	{
		m_running = !(bool)pthread_create( &m_id, NULL, Entry, (void*)this );
		if (m_running)
			gThread::threads.push_back(this);
	}
	return m_running;
}

bool gThread::Stop(void)
{
    if (m_running)
	{
		for (std::list<gThread*>::iterator l = threads.begin(); l != threads.end(); l++)
        {
			if ( (*l)->GetPid() == m_id )
			{
				threads.erase(l);
				break;
			}
        }
		m_running = false;
		return true;
	}
	return false;
}

void gThread::SetThreadName(const std::string& newname )
{
    ::strncpy(m_threadname, newname.c_str(), sizeof(m_threadname));
}

const char *gThread::GetThreadName(void)
{
    return (const char *)&m_threadname[0];
}

bool gThread::WaitFinished(void)
{
    int max = 40; 
    
	while( !m_finished && max-- )
	{
		sleep(100);
	}

	return( (max > 0) ? true : false );
}

void* gThread::Entry(void* in)
{
	/// This method enables ASYNC mode and enables THREAD CANCEL.
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

	gThread* temp = (gThread*)in;
	if (temp->Setup())
	{
		temp->Tmain();
	}

	return 0;
}

pfunc gTimer::func_ptr = nullptr;
gTimer* gTimer::pInstance = nullptr;

gTimer::gTimer()
{
	signal(SIGALRM, timerHandler);
}

gTimer::~gTimer()
{
	func_ptr = nullptr;
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

void gTimer::setAction(pfunc action)
{
	func_ptr = action;
}

void gTimer::timerHandler(int signo)
{
	if(func_ptr != nullptr)
	{
		(*func_ptr)();
	}
	else
	{
		std::cout<<"timer ptr is nullptr!"<<std::endl;
	}
}

void gTimer::start(int first, int period)
{
	struct itimerval tick = {0};

    //初始执行的定时器计数值
    tick.it_value.tv_sec = first;
    tick.it_value.tv_usec = 0;

    //后续定时器执行的加载值
    tick.it_interval.tv_sec = period;
    tick.it_interval.tv_usec = 0;

	setitimer(ITIMER_REAL, &tick, NULL);
}

void gTimer::stop()
{
	//if zero, stop timer
	start(0, 0);
}

