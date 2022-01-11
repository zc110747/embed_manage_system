/*
 * HwManageThread.cpp
 *
 *  Created on: 2022 Jan 4 15:08:05
 */
#include "HwManageThread.hpp"

HwManageThread::HwManageThread(std::string ThreadName):
    gThread()
{
    m_exit_flag = 0;
    SetThreadName(ThreadName);
}

HwManageThread::~HwManageThread()
{
}

bool HwManageThread::Tmain(void)
{
    create_device_object();

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

    release_device_object();

    m_finished = 1;
    return true;
}


void HwManageThread::create_device_object(void)
{
    prvLed = new USR_DEVICE::LED();
    prvBeep = new USR_DEVICE::BEEP();
    prvAp = new USR_DEVICE::API2C();
    prvIcm = new USR_DEVICE::ICMSPI();
}


void HwManageThread::release_device_object(void)
{
    if(prvLed){
        delete prvLed;
        prvLed = nullptr;
    }

    if(prvBeep){
        delete prvBeep;
        prvBeep = nullptr;
    }

    if(prvAp){
        delete prvAp;
        prvAp = nullptr;
    }

    if(prvIcm){
        delete prvIcm;
        prvIcm = nullptr;
    }
}