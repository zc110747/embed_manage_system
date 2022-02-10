/*
 * HwManageThread.hpp
 *
 *  Created on: 2022 Jan 4 15:08:05
 */
#pragma once

#include "gThread.hpp"
#include "beep.hpp"
#include "led.hpp"
#include "ApI2c.hpp"
#include "IcmSpi.hpp"

#define DEFAULT_THREAD_NAME "Instance"


class HwManageThread : public gThread
{
public:
    /// - 
    ///constructor
    HwManageThread(std::string ThreadName);

    /// - 
    ///destructor
    virtual ~HwManageThread();

    /// \fn Tmain() 
    ///  - main() for this thread - This method MUST be implemented in derived class
    /// \return true=success after executed, false=fail after executed
	bool Tmain();

    /// \fn getInstance() 
    ///  - get the default Instance of the class
    /// \return the point for the Instance
    static HwManageThread *getInstance(void);
    
    /// \fn releaseInstance() 
    ///  - release the Instance of the class
    /// \return null
    void releaseInstance(void);
private:
    int m_exit_flag;

    static HwManageThread* pInstance;
};
