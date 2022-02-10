/*
 * HwManageThread.cpp
 *
 *  Created on: 2022 Jan 4 15:08:05
 */
#include "HwManageThread.hpp"

HwManageThread* HwManageThread::pInstance = nullptr;

HwManageThread::HwManageThread(std::string ThreadName):
    gThread()
{
    m_exit_flag = 0;
    SetThreadName(ThreadName);
}

HwManageThread::~HwManageThread()
{
}

HwManageThread* HwManageThread::getInstance(void)
{
    if(pInstance == nullptr)
    {
        pInstance = new(std::nothrow) HwManageThread(DEFAULT_THREAD_NAME);
        if(pInstance == nullptr)
        {
            std::cout<<"HwManageThread class new failed!\r\n"<<std::endl;
        }
    }
    return pInstance;
}

void HwManageThread::releaseInstance(void)
{
    if(pInstance != nullptr)
    {
        delete pInstance;
        pInstance = nullptr;
    }
}

void HwTimerHandler(void)
{
    USR_DEVICE::API2C::getInstance()->update();
    USR_DEVICE::ICMSPI::getInstance()->update();
}

bool HwManageThread::Tmain(void)
{
    gTimer *pTimer = new gTimer();
    pTimer->setAction(HwTimerHandler);
    pTimer->start(2, 2);

    while(!m_exit_flag)
    {
        USR_DEVICE::LED::getInstance()->On();
        sleep(1);
        USR_DEVICE::LED::getInstance()->Off();
        sleep(1);

        USR_DEVICE::BEEP::getInstance()->On();
        sleep(1);
        USR_DEVICE::BEEP::getInstance()->Off();
        sleep(1);

    }

    pTimer->stop();
    sleep(2);
    USR_DEVICE::LED::getInstance()->releaseInstance();
    USR_DEVICE::BEEP::getInstance()->releaseInstance();
    USR_DEVICE::API2C::getInstance()->releaseInstance();
    USR_DEVICE::ICMSPI::getInstance()->releaseInstance();

    m_finished = 1;
    return true;
}
