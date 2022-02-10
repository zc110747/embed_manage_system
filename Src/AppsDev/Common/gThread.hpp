/*
 * gThread.hpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#pragma once

#include <list>
#include <pthread.h>
#include <string>
#include <unistd.h>
#include <signal.h>
#include <time.h> 
#include <sys/time.h>

class gThread
{
public:
    /// - 
    ///constructor
    gThread();

    /// - 
    ///destructor
    virtual ~gThread();

    /// \fn Setup() 
    ///  - Get current thread work status
    /// \return true=thread is running, false=thread is not running
    virtual bool Setup(void);

    /// \fn Start() 
    ///  - called for create thread and append to thread pool.
    /// \return true=create success, false=create failed
    bool Start(void);

    /// \fn Stop() 
    ///  - called for release thread and delete from thread pool.
    /// \return true=release success, false=release failed
    bool Stop(void);

    /// \fn GetPid() 
    ///  - get current thread id
    /// \return thread id
    pthread_t GetPid(){return m_id;}
    
    /// \fn SetThreadName() 
    ///  - Update current thread name
    /// \return NULL
		void SetThreadName(const std::string& newname );

    /// \fn GetThreadName() 
    ///  - Get Current thread name
    /// \return thread name for current thread
    const char *GetThreadName(void);

    /// \fn WaitFinished() 
    ///  - Wait for thread finished
    /// \return true=thread finished success, false=thread finsined timeout
    bool WaitFinished(void);

    /// \fn Running() 
    ///  - Get current thread work status
    /// \return true=thread is running, false=thread is not running
    bool Running(void){return m_running;}
protected:

    /// \fn Tmain() 
    ///  - main() for this thread - This method MUST be implemented in derived class
    /// \return true=success after executed, false=fail after executed
		virtual bool Tmain() = 0;

		/// - local thread state \n
		/// \b false = thread is NOT running \n
		/// \b true = thread is running 
		bool      m_running;

    /// - local thread finished \n
		/// \b false = thread is NOT finished \n
		/// \b true = thread is finished 
		bool      m_finished;
private:
    /// \fn Entry() 
    ///  - the entry for the thread
    /// \return buffer while the thread exit
		static void* Entry (void* in);

    /// -
    /// thread id
    pthread_t m_id;

    /// -
    /// thread name
    char m_threadname[128];

    /// -
    /// thread list
    static std::list<gThread *> threads;
};

typedef void (*pfunc)(void);

class gTimer
{
public:
    gTimer();
    ~gTimer();

    void setAction(pfunc action);
    void start(int first, int period);
    void stop();
private:
    static void timerHandler(int signo);
    static pfunc func_ptr;
};