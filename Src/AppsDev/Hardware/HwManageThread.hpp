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

private:
    int m_exit_flag;

    USR_DEVICE::LED *prvLed;
    USR_DEVICE::BEEP *prvBeep;
    USR_DEVICE::API2C *prvAp;
    USR_DEVICE::ICMSPI *prvIcm;

    /// \fn create_device_object() 
    ///  create device used by thread
    /// \return NULL
    void create_device_object(void);

    /// \fn release_device_object() 
    ///  release device and memory
    /// \return NULL
    void release_device_object(void);
};
