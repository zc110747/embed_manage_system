/*
 * beep.cpp
 *
 *  Created on: 2021 May 11 15:08:05
 */

#include "beep.hpp"

namespace USR_DEVICE
{
    using namespace USR_READER;

    BEEP::BEEP(void):BEEP(DIE_BEEP)
    {
    }

    BEEP::BEEP(DevInfoEnum dev)
    {
        string beep_device;
        FileProcessHw *pReader = new FileProcessHw(HARDWART_JSON_DEFINE);

        beep_device = pReader->get_device_info(dev);
        std::cout<<beep_device<<std::endl;
        pdev = new USR_DEVICE::device(beep_device);
        beepStatus = pReader->get_default_status(dev);
        pdev->write(&beepStatus, 1);

        delete pReader;
        pReader = nullptr;
    }

    BEEP::~BEEP(void)
    {
        if(pdev != nullptr)
        {
            delete pdev;
            pdev = nullptr;
        }
    }

    void BEEP::On(void)
    {
        if(pdev != nullptr)
        {
            beepStatus = 0;
            pdev->write(&beepStatus, 1);
        }

    }

    void BEEP::Off(void)
    {
        if(pdev != nullptr)
        {
            beepStatus = 1;
            pdev->write(&beepStatus, 1);
        }
    }

    void BEEP::Trigger(void)
    {
        if(pdev != nullptr)
        {
            if(beepStatus == 0)
                beepStatus = 1;
            else
                beepStatus = 0;

            pdev->write(&beepStatus, 1);
        }
    }

    uint8_t BEEP::Status(void)
    {
        if(pdev != nullptr)
        {
            pdev->read(&beepStatus, 1);
        }
        return beepStatus;
    }

    void test_beep_module(void)
    {
        USR_DEVICE::BEEP *pdev = new USR_DEVICE::BEEP();
        pdev->Trigger();
        pdev->On();
        delete pdev;
        pdev = nullptr;

        pdev = new USR_DEVICE::BEEP(DIE_BEEP0);
        pdev->Trigger();
        pdev->Off();
        delete pdev;
        pdev = nullptr;
    }
}