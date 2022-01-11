/*
 * led.cpp
 *
 *  Created on: 2021 May 11 15:08:05
 */

#include "led.hpp"

namespace USR_DEVICE
{
    using namespace USR_READER;

    LED::LED(void)
    {
        string led_device;
        FileProcessHw *pReader = new FileProcessHw(HARDWART_JSON_DEFINE);

        if(pReader->get_led_device(&led_device))
        {
            std::cout<<led_device<<std::endl;
            pdev = new USR_DEVICE::device(led_device);
            if(pReader->get_led_status(&ledStatus))
            {
                pdev->write(&ledStatus, 1);
            }
        }
        else
            pdev = nullptr;

        delete pReader;
        pReader = nullptr;
    }

    LED::LED(const string& device)
    {
        string led_device;
        FileProcessHw *pReader = new FileProcessHw(HARDWART_JSON_DEFINE);

        if(pReader->get_device_info(&led_device, device))
        {
            std::cout<<led_device<<std::endl;
            pdev = new USR_DEVICE::device(led_device);
            if(pReader->get_default_status(&ledStatus, device))
            {
                pdev->write(&ledStatus, 1);
            }
        }
        else
            pdev = nullptr;

        delete pReader;
        pReader = nullptr;
    }

    LED::~LED(void)
    {
        if(pdev != nullptr)
        {
            delete pdev;
            pdev = nullptr;
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

    void test_led_module(void)
    {
        USR_DEVICE::LED *pdev = new USR_DEVICE::LED();
        pdev->Trigger();
        pdev->On();
        delete pdev;
        pdev = nullptr;

        pdev = new USR_DEVICE::LED("Led0");
        pdev->Trigger();
        pdev->Off();
        delete pdev;
        pdev = nullptr;
    }
}