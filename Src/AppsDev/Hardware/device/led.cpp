/*
 * led.cpp
 *
 *  Created on: 2021 May 11 15:08:05
 */

#include "led.hpp"

namespace USR_DEVICE
{
    using namespace USR_READER;

    LED* LED::pInstance = nullptr;

    LED::LED(void):LED(DIE_LED)
    {
    }

    LED::LED(DevInfoEnum dev)
    {
        string led_device;

        led_device = FileProcessHw::getInstance()->get_device_info(dev);
        std::cout<<led_device<<std::endl;
        pdev = new USR_DEVICE::device(led_device);
        ledStatus = FileProcessHw::getInstance()->get_default_status(dev, 0);
        pdev->write(&ledStatus, 1);

        FileProcessHw::getInstance()->releaseInstance();
    }

    LED::~LED(void)
    {
        if(pdev != nullptr)
        {
            delete pdev;
            pdev = nullptr;
        }
    }

    LED* LED::getInstance(void)
    {
        if(pInstance == nullptr)
        {
            pInstance = new(std::nothrow) LED;
            if(pInstance == nullptr)
            {
                std::cout<<"LED class new failed!\r\n"<<std::endl;
            }
        }
        return pInstance;
    }

    void LED::releaseInstance(void)
    {
        if(!pInstance)
        {
            delete pInstance;
            pInstance = nullptr;
        }
    }

    void LED::On(void)
    {
        if(pdev != nullptr)
        {
            ledStatus = 0;
            pdev->write(&ledStatus, 1);
        }

    }

    void LED::Off(void)
    {
        if(pdev != nullptr)
        {
            ledStatus = 1;
            pdev->write(&ledStatus, 0);
        }
    }

    void LED::Trigger(void)
    {
        if(pdev != nullptr)
        {
            if(ledStatus == 0)
                ledStatus = 1;
            else
                ledStatus = 0;

            pdev->write(&ledStatus, 1);
        }
    }

    uint8_t LED::Status(void)
    {
        if(pdev != nullptr)
        {
            pdev->read(&ledStatus, 1);
        }
        return ledStatus;
    }

    void LED::test(void)
    {
        USR_DEVICE::LED::getInstance()->On();
        USR_DEVICE::LED::getInstance()->Off();
        USR_DEVICE::LED::getInstance()->Trigger();
        USR_DEVICE::LED::getInstance()->releaseInstance();
    }
}