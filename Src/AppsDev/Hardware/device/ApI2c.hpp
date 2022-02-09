/*
 * ApI2c.hpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#pragma once

#include "device.hpp"
#include "FileProcessHw.hpp"

namespace USR_DEVICE
{
    struct SApInfo
    {   
        uint16_t ir;

        uint16_t als;

        uint16_t ps;
    };

    class API2C
    {
    public:
        /// - 
        ///constructor
        API2C(void);

        /// - 
        ///constructor
        API2C(USR_READER::DevInfoEnum dev);
        
        /// - 
        ///destructor
        ~API2C(void);

        /// \fn update() 
        ///  - update the deivce information from i2c device
        /// \return NULL 
        void update(void);

        /// \fn GetInfo() 
        ///  - get current device ap information
        /// \return information about the device 
        SApInfo *get_info(){
            return &m_info;
        }
        
        /// \fn getInstance() 
        ///  - get the default Instance of the class
        /// \return the point for the Instance
        static API2C* getInstance(void);

      	/// \fn releaseInstance() 
        ///  - release the Instance of the class
        /// \return null
        static void releaseInstance(void);

      	/// \fn test() 
        ///  - test the modlue function
        /// \return null
        static void test(void);
    private:
        struct SApInfo m_info;
        device *pdev{nullptr};
        static API2C* pInstance;
    };
}
