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
    class BEEP
    {
    public:
        /// - 
        ///constructor
        BEEP(void);

        /// - 
        ///constructor
        BEEP(const string& device);

        /// - 
        ///destructor
        ~BEEP(void);

      	/// \fn On() 
        ///  - Called for Set Beep On.
        /// \return NULL
        void On(void);

        /// \fn Off() 
        ///  - Called for Set Beep Off.
        /// \return NULL
        void Off(void);

        /// \fn Trigger() 
        ///  - Called for Trigger the Led, Switch On or Off.
        /// \return NULL 
        void Trigger(void);
    private:
        uint8_t beepStatus;
        
        device *pbeep;
    };

    /// \fn test_led_module() 
    ///  - Called for test beep module
    /// \return NULL  
    void test_beep_module(void);
}