/*
 * FileProcessHw.hpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#pragma once
#include "FileProcess.hpp"
#include <map>

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

    typedef enum
    {
      DIE_SERIAL = 0,
      DIE_LED,
      DIE_BEEP,
      DIE_ICM_SPI,
      DIE_RTC,
      DIE_AP_I2C,
      DIE_LED0,
      DIE_BEEP0,
      DIE_END,
    }DevInfoEnum;

    class FileProcessHw : public FileProcess
    {
    public:
          /// - 
    	  ///constructor
        FileProcessHw():FileProcessHw(HARDWART_JSON_DEFINE){
        }

        /// - 
    	  ///constructor
        FileProcessHw(string file):FileProcess(file){
          int index;

          for(index=0; index<DIE_END; index++)
          {
            get_device_info_interal((DevInfoEnum)index);
          }

          get_default_status_interal(DIE_LED);
          get_default_status_interal(DIE_LED0);
          get_default_status_interal(DIE_BEEP);
          get_default_status_interal(DIE_BEEP0);

          get_uart_info_interal();
        }

        /// - 
    	  ///destructor
        ~FileProcessHw(){};

      	/// \fn get_device_info() 
        ///  - This method is called for getting device's string info from json structure.
        /// \return true=do success, false=no string
        string get_device_info(DevInfoEnum dev){
            return m_device[dev];
        }

        bool set_device_info(DevInfoEnum dev, string val){
            if(!is_valid_dev(dev))
              return false;
            m_device[dev] = val;
            return true;
        }

        bool is_valid_dev(DevInfoEnum dev){
          if(dev>=DIE_SERIAL && dev<DIE_END)
              return true;
          return false;
        }

      	/// \fn set_default_status() 
        ///  - This method is called for setting device's default status.
        /// \return true=do success, false=no device string
        int get_default_status(DevInfoEnum dev){
            return m_status[dev];
        }

        bool set_default_status(DevInfoEnum dev, int status){
            if(!is_valid_dev_status(dev))
              return false;
            m_status[dev] = status;
            return true;
        }

        bool is_valid_dev_status(DevInfoEnum dev);

      	/// \fn get_uart_info() 
        ///  - called for get uart infomation.
        /// \return true=do success, false=no info
        UartInfo get_uart_info(void){
            return m_uart;
        }

        /// \fn update_writer_value() 
        ///  - create and write files
        /// \return NULL
        void update_writer_value(void);
    private:
          	/// \fn get_device_info() 
        ///  - This method is called for getting device's string info from json structure.
        /// \return true=do success, false=no string
        bool get_device_info_interal(DevInfoEnum dev);

      	/// \fn get_default_status() 
        ///  - This method is called for getting device's default status from json structure.
        /// \return true=do success, false=no device string
        bool get_default_status_interal( DevInfoEnum dev);

      	/// \fn get_uart_info() 
        ///  - called for get uart infomation.
        /// \return true=do success, false=no info
        bool get_uart_info_interal(void);

        struct UartInfo m_uart;
        std::map<int, std::string> m_device;
        std::map<int, int> m_status; 
    };  

    void test_file_reader_hw(void);
}

