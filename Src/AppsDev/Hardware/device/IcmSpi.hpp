/*
 * ICMSPI.hpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#pragma once

#include "device.hpp"
#include "FileReaderHw.hpp"

namespace USR_DEVICE
{
    struct SIcmInfo
    {   
        /*x-ray angular speed*/
        uint32_t gyro_x_adc;

        /*y-ray angular speed*/
        uint32_t gyro_y_adc;

        /*z-ray angular speed*/
        uint32_t gyro_z_adc;

        /*x-ray accelerated speed*/
        uint32_t accel_x_adc;

        /*y-ray accelerated speed*/
        uint32_t accel_y_adc;

        /*z-ray accelerated speed*/
        uint32_t accel_z_adc;

        /*temperature*/
        uint32_t temp_adc;
    };

    class ICMSPI
    {
    public:
        /// - 
        ///constructor
        ICMSPI(void);

        /// - 
        ///constructor
        ICMSPI(const string& device);

        /// - 
        ///destructor
        ~ICMSPI(void);

        /// \fn update() 
        ///  - update the deivce information from i2c device
        /// \return NULL 
        void update(void);

        /// \fn GetInfo() 
        ///  - get current device ap information
        /// \return information about the device 
        SIcmInfo *get_info(){
            return &m_info;
        }
        
    private:
        struct SIcmInfo m_info;

        device *pIcmSpi{nullptr};
    };

    /// \fn test_icm_spi_module() 
    ///  - Called for test icm spi module
    /// \return NULL  
    void test_icm_spi_module(void);
}
