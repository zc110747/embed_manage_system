/*
 * led.hpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#pragma once
#include "device.hpp"
#include "FileReaderHw.hpp"

namespace USR_DEVICE
{
    class LED
    {
    public:
        /// - 
        ///constructor
        LED(void);

        /// - 
        ///constructor
        LED(const string& device);

        /// - 
        ///destructor
        ~LED(void);

      	/// \fn On() 
        ///  - Called for Set LED On.
        /// \return NULL
        void On(void);

        /// \fn Off() 
        ///  - Called for Set LED Off.
        /// \return NULL
        void Off(void);

        /// \fn Trigger() 
        ///  - Called for Trigger the Led, Switch On or Off.
        /// \return NULL  
        void Trigger(void);
    private:
        uint8_t ledStatus;
        device *pled;
    };

    /// \fn test_led_module() 
    ///  - Called for test led module
    /// \return NULL  
    void test_led_module(void);
}