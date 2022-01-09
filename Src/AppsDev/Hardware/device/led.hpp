/*
 * led.hpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#pragma once
#include "device.hpp"
#include "FileProcessHw.hpp"

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

        /// \fn Status() 
        ///  - get current led status.
        /// \return led on/off status  
        uint8_t Status(void);
        
    private:
        uint8_t ledStatus{0};
        device *pdev{nullptr};
    };

    /// \fn test_led_module() 
    ///  - Called for test led module
    /// \return NULL  
    void test_led_module(void);
}