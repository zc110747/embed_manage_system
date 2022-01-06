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

template<typename T = int>
class HwManageThread : public gThread
{
public:
    /// - 
    ///constructor
    HwManageThread(std::string ThreadName);

    /// - 
    ///constructor
    HwManageThread(std::string ThreadName, T parameter);

    /// - 
    ///destructor
    virtual ~HwManageThread();

    /// \fn Tmain() 
    ///  - main() for this thread - This method MUST be implemented in derived class
    /// \return true=success after executed, false=fail after executed
	bool Tmain();

private:
    int m_exit_flag;
    T m_parameter;

    USR_DEVICE::LED *prvLed;
    USR_DEVICE::BEEP *prvBeep;
    USR_DEVICE::API2C *prvAp;
    USR_DEVICE::ICMSPI *prvIcm;
};

template<typename T>
HwManageThread<T>::HwManageThread(std::string ThreadName):
    gThread()
{
    m_exit_flag = 0;
    prvLed = new USR_DEVICE::LED();
    prvBeep = new USR_DEVICE::BEEP();
    prvAp = new USR_DEVICE::API2C();
    prvIcm = new USR_DEVICE::ICMSPI();

    SetThreadName(ThreadName);
}

template<typename T>
HwManageThread<T>::HwManageThread(std::string ThreadName, T parameter):
    HwManageThread(ThreadName)
{
    ::memcpy((char *)m_parameter, (char *)&parameter, sizeof(m_parameter));
}

template<typename T>
HwManageThread<T>::~HwManageThread()
{
    if(prvLed){
        delete prvLed;
        prvLed = nullptr;
    }

    if(prvBeep){
        delete prvBeep;
        prvBeep = nullptr;
    }
}

template<typename T>
bool HwManageThread<T>::Tmain(void)
{
    while(!m_exit_flag)
    {
        prvLed->On();
        sleep(1);
        prvLed->Off();
        sleep(1);

        prvBeep->On();
        sleep(1);
        prvBeep->Off();
        sleep(1);

        prvAp->update();

        prvIcm->update();
    }

    m_finished = 1;
    return true;
}
