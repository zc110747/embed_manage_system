/*
 * beep.hpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#pragma once
#include "device.hpp"
#include "FileProcessHw.hpp"

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
        BEEP(USR_READER::DevInfoEnum dev);

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

        /// \fn Status() 
        ///  - get current beep status.
        /// \return led on/off status  
        uint8_t Status(void);
        
        /// \fn getInstance() 
        ///  - get the default Instance of the class
        /// \return the point for the Instance
        static BEEP* getInstance(void);

      	/// \fn releaseInstance() 
        ///  - release the Instance of the class
        /// \return null
        static void releaseInstance(void);

        /// \fn test() 
        ///  - test the modlue function
        /// \return null
        static void test(void);
    private:
        int beepStatus{0};
        device *pdev{nullptr};
        static BEEP* pInstance;
    };
}