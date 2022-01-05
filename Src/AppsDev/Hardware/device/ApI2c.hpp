/*
 * ApI2c.hpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#pragma once

#include "device.hpp"
#include "FileReaderHw.hpp"

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
        API2C(const string& device);

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
        
    private:
        struct SApInfo m_info;

        device *pApI2c{nullptr};
    };

    /// \fn test_ap_i2c_module() 
    ///  - Called for test ap i2c module
    /// \return NULL  
    void test_ap_i2c_module(void);
}
