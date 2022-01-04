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
        FileReaderHw *pReader = new FileReaderHw(HARDWART_JSON_DEFINE);

        if(pReader->get_led_device(&led_device))
        {
            std::cout<<led_device<<std::endl;
            pled = new USR_DEVICE::device(led_device);
            if(pReader->get_led_status(&ledStatus))
            {
                pled->write(&ledStatus, 1);
            }
        }
        else
            pled = nullptr;



        delete pReader;
        pReader = nullptr;

    }

    LED::LED(const string& device)
    {
        string led_device;
        FileReaderHw *pReader = new FileReaderHw(HARDWART_JSON_DEFINE);

        if(pReader->get_device_info(&led_device, device))
        {
            std::cout<<led_device<<std::endl;
            pled = new USR_DEVICE::device(led_device);
            if(pReader->get_default_status(&ledStatus, device))
            {
                pled->write(&ledStatus, 1);
            }
        }
        else
            pled = nullptr;

        delete pReader;
        pReader = nullptr;
    }

    LED::~LED(void)
    {
        if(pled != nullptr)
        {
            delete pled;
            pled = nullptr;
        }
    }

    void LED::On(void)
    {
        if(pled != nullptr)
        {
            ledStatus = 0;
            pled->write(&ledStatus, 1);
        }

    }

    void LED::Off(void)
    {
        if(pled != nullptr)
        {
            ledStatus = 1;
            pled->write(&ledStatus, 1);
        }
    }

    void LED::Trigger(void)
    {
        if(pled != nullptr)
        {
            if(ledStatus == 0)
                ledStatus = 1;
            else
                ledStatus = 0;

            pled->write(&ledStatus, 1);
        }
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