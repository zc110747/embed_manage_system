/*
 * FileReaderHw.hpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#pragma once
#include "FileReader.hpp"

#define HARDWART_JSON_DEFINE    "HardwareConfig.json"

namespace USR_READER
{
    struct UartInfo
    {
        ///BaudRate for uart
        ///Commonly used:9600, 19200, 38400, 115200
        uint32_t baud;

        ///DataBits for uart
        uint16_t databits;

        ///StopBits for uart
        uint16_t stopbits;

        ///Parity for uart
        ///Commonly used: 'o', 'e', 'n'
        string parity;
    };

    class FileReaderHw : public FileReader
    {
    public:
        /// - 
    	  ///constructor
        FileReaderHw(string file):FileReader(file){
        }

        /// - 
    	  ///destructor
        ~FileReaderHw(){};

      	/// \fn get_device_info() 
        ///  - This method is called for getting device's string info from json structure.
        /// \return true=do success, false=no string
        bool get_device_info(string *pInfo, const string& device);

      	/// \fn get_default_status() 
        ///  - This method is called for getting device's default status from json structure.
        /// \return true=do success, false=no device string
        bool get_default_status(uint8_t *pStatus, const string& device);

      	/// \fn get_uart_info() 
        ///  - called for get uart infomation.
        /// \return true=do success, false=no info
        bool get_uart_info(UartInfo *pInfo);

      	/// \fn get_serial_device() 
        ///  - called for get serial device string.
        /// \return true=do success, false=no device string
        bool get_serial_device(string *pInfo);

      	/// \fn get_led_device() 
        ///  - called for get led device string.
        /// \return true=do success, false=no device string
        bool get_led_device(string *pInfo);

      	/// \fn get_beep_device() 
        ///  - called for get beep device string.
        /// \return true=do success, false=no device string
        bool get_beep_device(string *pInfo);

      	/// \fn get_spi_device() 
        ///  - called for get spi device string.
        /// \return true=do success, false=no device string
        bool get_spi_device(string *pInfo);

      	/// \fn get_rtc_device() 
        ///  - called for get rtc device string.
        /// \return true=do success, false=no device string
        bool get_rtc_device(string *pInfo);  

      	/// \fn get_i2c_device() 
        ///  - called for get i2c device string.
        /// \return true=do success, false=no device string
        bool get_i2c_device(string *pInfo);  

      	/// \fn get_led_status() 
        ///  - called for get led device status.
        /// \return true=do success, false=no device status
        bool get_led_status(uint8_t *pStatus);

      	/// \fn get_beep_status() 
        ///  - called for get beep device string.
        /// \return true=do success, false=no device status
        bool get_beep_status(uint8_t *pStatus); 
    };

    void test_file_reader_hw(void);
}

