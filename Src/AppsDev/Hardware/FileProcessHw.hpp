/*
 * FileProcessHw.hpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#pragma once
#include "FileProcess.hpp"
#include <map>

#define HARDWART_JSON_DEFINE    "HardwareConfig.json"
#define MAX_ARRAY_STATUS_SIZE   3

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
        FileProcessHw(string file);

        /// - 
    	  ///destructor
        ~FileProcessHw(){};

      	/// \fn getInstance() 
        ///  - get the default Instance of the class
        /// \return the point for the Instance
        static FileProcessHw* getInstance(void);

      	/// \fn releaseInstance() 
        ///  - release the Instance of the class
        /// \return null
        void releaseInstance(void);

      	/// \fn get_device_info() 
        ///  - This method is called for getting device's string info from json structure.
        /// \return true=do success, false=no device string
        string get_device_info(DevInfoEnum dev){
            return m_device[dev];
        }

      	/// \fn set_device_info() 
        ///  - set the device information
        /// \return true=do success, false=no device string
        bool set_device_info(DevInfoEnum dev, string val){
            if(!is_valid_dev(dev))
              return false;
            m_device[dev] = val;
            return true;
        }

      	/// \fn is_valid_dev() 
        ///  - This method is called for setting device's default status.
        /// \return true=valid device, false=invalid device
        bool is_valid_dev(DevInfoEnum dev){
          if(dev>=DIE_SERIAL && dev<DIE_END)
              return true;
          return false;
        }

      	/// \fn get_default_status() 
        ///  - This method is called for getting device's default status.
        /// \return get the device default status value
        int get_default_status(DevInfoEnum dev, uint8_t index){
            return m_status[dev].at(index);
        }

      	/// \fn set_default_status() 
        ///  - This method is called for setting device's default status.
        /// \return set the device default status value
        bool set_default_status(DevInfoEnum dev, uint8_t index, int status){
            if(!is_valid_dev_status(dev) && index>=MAX_ARRAY_STATUS_SIZE)
              return false;
            m_status[dev].at(index) = status;
            return true;
        }
        /// \fn is_valid_dev_status() 
        ///  - This method is called for judge whether device status in the list
        /// \return true=valid device, false=invalid device
        bool is_valid_dev_status(DevInfoEnum dev);

      	/// \fn get_uart_info() 
        ///  - called for get uart infomation.
        /// \return uart information 
        UartInfo get_uart_info(void){
            return m_uart;
        }

        /// \fn update_writer_value() 
        ///  - create and write files
        /// \return NULL
        void update_writer_value(void);

        /// \fn test() 
        ///  - test the modlue function
        /// \return null
        static void test(void);
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
        std::map<int, std::array<int, MAX_ARRAY_STATUS_SIZE> > m_status; 
        static FileProcessHw* pInstance;
    };  
}

