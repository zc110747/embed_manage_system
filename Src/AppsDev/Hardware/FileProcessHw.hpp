/*
 * FileProcessHw.hpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#pragma once
#include "FileProcess.hpp"

#define HARDWART_JSON_DEFINE    "HardwareConfig.json"

namespace USR_READER
{
    using std::string;

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

    struct DevInfo
    {
      string Serial;
      string Led;
      string Beep;
      string IcmSpi;
      string Rtc;      
      string ApI2c;
      string Led0;
      string Beep0;
    };

    struct DefaultStatus
    {
        int led;
        int beep;
        int led0;
        int beep0;
    };

    class FileProcessHw : public FileProcess
    {
    public:
          /// - 
    	  ///constructor
        FileProcessHw():FileProcess(HARDWART_JSON_DEFINE){
        }

        /// - 
    	  ///constructor
        FileProcessHw(string file):FileProcess(file){
        }

        /// - 
    	  ///destructor
        ~FileProcessHw(){};

      	/// \fn get_device_info() 
        ///  - This method is called for getting device's string info from json structure.
        /// \return true=do success, false=no string
        bool get_device_info(string &pInfo, const string& device);

      	/// \fn get_default_status() 
        ///  - This method is called for getting device's default status from json structure.
        /// \return true=do success, false=no device string
        bool get_default_status(int &Status, const string& device);

      	/// \fn get_uart_info() 
        ///  - called for get uart infomation.
        /// \return true=do success, false=no info
        bool get_uart_info(UartInfo *pInfo);

      	/// \fn get_serial_device() 
        ///  - called for get serial device string.
        /// \return true=do success, false=no device string
        bool get_serial_device(string& device);

      	/// \fn get_led_device() 
        ///  - called for get led device string.
        /// \return true=do success, false=no device string
        bool get_led_device(string& device);

      	/// \fn get_beep_device() 
        ///  - called for get beep device string.
        /// \return true=do success, false=no device string
        bool get_beep_device(string& device);

      	/// \fn get_spi_device() 
        ///  - called for get spi device string.
        /// \return true=do success, false=no device string
        bool get_spi_device(string& device);

      	/// \fn get_rtc_device() 
        ///  - called for get rtc device string.
        /// \return true=do success, false=no device string
        bool get_rtc_device(string& device); 

      	/// \fn get_i2c_device() 
        ///  - called for get i2c device string.
        /// \return true=do success, false=no device string
        bool get_i2c_device(string& device); 

      	/// \fn get_led_status() 
        ///  - called for get led device status.
        /// \return true=do success, false=no device status
        bool get_led_status(int& status);

      	/// \fn get_beep_status() 
        ///  - called for get beep device string.
        /// \return true=do success, false=no device status
        bool get_beep_status(int& status); 

        /// \fn update_writer_value() 
        ///  - create and write files
        /// \return NULL
        void update_writer_value(void);
    private:
        struct UartInfo m_uart;
        struct DevInfo  m_device;
        struct DefaultStatus m_status;
    };

    void test_file_reader_hw(void);
}

