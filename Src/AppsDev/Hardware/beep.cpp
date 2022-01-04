/*
 * beep.cpp
 *
 *  Created on: 2021 May 11 15:08:05
 */

#include "beep.hpp"

namespace USR_DEVICE
{
    using namespace USR_READER;

    BEEP::BEEP(void)
    {
        string beep_device;
        FileReaderHw *pReader = new FileReaderHw(HARDWART_JSON_DEFINE);

        if(pReader->get_beep_device(&beep_device))
        {
            std::cout<<beep_device<<std::endl;
            pbeep = new USR_DEVICE::device(beep_device);
            if(pReader->get_beep_status(&beepStatus))
            {
                pbeep->write(&beepStatus, 1);
            }
        }
        else
            pbeep = nullptr;

        delete pReader;
        pReader = nullptr;
    }

    BEEP::BEEP(const string& device)
    {
        string beep_device;
        FileReaderHw *pReader = new FileReaderHw(HARDWART_JSON_DEFINE);

        if(pReader->get_device_info(&beep_device, device))
        {
            std::cout<<beep_device<<std::endl;
            pbeep = new USR_DEVICE::device(beep_device);
            if(pReader->get_default_status(&beepStatus, device))
            {
                pbeep->write(&beepStatus, 1);
            }
        }
        else
            pbeep = nullptr;

        delete pReader;
        pReader = nullptr;
    }

    BEEP::~BEEP(void)
    {
        if(pbeep != nullptr)
        {
            delete pbeep;
            pbeep = nullptr;
        }
    }

    void BEEP::On(void)
    {
        if(pbeep != nullptr)
        {
            beepStatus = 0;
            pbeep->write(&beepStatus, 1);
        }

    }

    void BEEP::Off(void)
    {
        if(pbeep != nullptr)
        {
            beepStatus = 1;
            pbeep->write(&beepStatus, 1);
        }
    }

    void BEEP::Trigger(void)
    {
        if(pbeep != nullptr)
        {
            if(beepStatus == 0)
                beepStatus = 1;
            else
                beepStatus = 0;

            pbeep->write(&beepStatus, 1);
        }
    }

    uint8_t BEEP::Status(void)
    {
        if(pbeep != nullptr)
        {
            pbeep->read(&beepStatus, 1);
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

        pdev = new USR_DEVICE::BEEP("Beep0");
        pdev->Trigger();
        pdev->Off();
        delete pdev;
        pdev = nullptr;
    }
}