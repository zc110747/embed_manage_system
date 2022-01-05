/*
 * HwManageThread.cpp
 *
 *  Created on: 2022 Jan 4 15:08:05
 */
#include "HwManageThread.hpp"
#include <iostream>

HwManageThread::HwManageThread(std::string ThreadName)
:gThread()
{
    m_exit_flag = 0;
    prvLed = new USR_DEVICE::LED();
    prvBeep = new USR_DEVICE::BEEP();
    prvAp = new USR_DEVICE::API2C();
    prvIcm = new USR_DEVICE::ICMSPI();

    SetThreadName(ThreadName);
}

HwManageThread::~HwManageThread()
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

bool HwManageThread::Tmain(void)
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