/*
 * ICMSPI.hpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#pragma once

#include "device.hpp"
#include "FileProcessHw.hpp"

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
        ICMSPI(USR_READER::DevInfoEnum dev);

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
        
        /// \fn getInstance() 
        ///  - get the default Instance of the class
        /// \return the point for the Instance
        static ICMSPI* getInstance(void);

      	/// \fn releaseInstance() 
        ///  - release the Instance of the class
        /// \return null
        static void releaseInstance(void);

        /// \fn test() 
        ///  - test the modlue function
        /// \return null
        static void test(void);
    private:
        struct SIcmInfo m_info;
        device *pdev{nullptr};
        static ICMSPI *pInstance;
    };
}
