/*
 * FileProcessHw.cpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */

#include "FileProcessHw.hpp"

namespace USR_READER
{
    bool FileProcessHw::get_uart_info(UartInfo *pInfo)
    {
        bool is_error = false;   

        if((!is_reader_valid()) || (pInfo == nullptr))
            return false;
        
        pInfo->baud = Reader["Uart"]["Baud"].isInt()?Reader["Uart"]["Baud"].asInt()
                    :([&is_error](){is_error=true; return 9600;}());
        pInfo->databits = Reader["Uart"]["DataBits"].isInt()?Reader["Uart"]["DataBits"].asInt()
                    :([&is_error](){is_error=true; return 8;}());   
        pInfo->stopbits = Reader["Uart"]["StopBits"].isInt()?Reader["Uart"]["StopBits"].asInt()
                    :([&is_error](){is_error=true; return 1;}());  
        pInfo->parity = Reader["Uart"]["Parity"].isString()?Reader["Uart"]["Parity"].asString()
                    :([&is_error](){is_error=true; return "n";}());         
        m_uart.baud = pInfo->baud;
        m_uart.databits = pInfo->databits;
        m_uart.stopbits = pInfo->stopbits;
        m_uart.parity = pInfo->parity;
        
        if(is_error)
        {
            printf("Json Value MemberValue have Invalid members!\r\n");
            return false;
        }
        return true;
    }

    bool FileProcessHw::get_device_info(string &pInfo, const string& device)
    {
        Json::Value DeviceMember;
        bool is_error = false;   

        if(!is_reader_valid())
            return false;

        pInfo = Reader["Device"][device].isString()?Reader["Device"][device].asString()
            :([&is_error](){is_error = true; return std::string("null");}());

        if(is_error)
        {
            printf("Json Value Reader have Invalid member %s!\r\n", "Device");
            return false;
        }
        return true;
    }

    bool FileProcessHw::get_default_status(int &status, const string& device)
    {
        Json::Value StatusMember;
        bool is_error = false;   

        if(!is_reader_valid())
            return false;
        
        status = Reader["Default"][device].isInt()?Reader["Default"][device].asInt()
            :([&is_error](){is_error = true; return 0;}());

        if(is_error)
        {
            printf("Json Value Reader have Invalid member %s!\r\n", "Device");
            return false;
        }
        return true;
    }

    bool FileProcessHw::get_serial_device(string& device)
    {
        bool flag;

        flag = get_device_info(device, "Serial");
        m_device.Serial = device;
        return flag;
    }
    
    bool FileProcessHw::get_led_device(string& device)
    {
        bool flag;

        flag = get_device_info(device, "Led");
        m_device.Led = device;
        return flag;
    }

    bool FileProcessHw::get_beep_device(string& device)
    {
        bool flag;

        flag = get_device_info(device, "Beep");
        m_device.Beep = device;
        return flag;
    }

    bool FileProcessHw::get_spi_device(string& device)
    {
        bool flag;    

        flag = get_device_info(device, "IcmSpi");
        m_device.IcmSpi = device;
        return flag;
    }

    bool FileProcessHw::get_rtc_device(string& device)
    {
        bool flag;    

        flag = get_device_info(device, "Rtc");
        m_device.Rtc = device;
        return flag;
    }

    bool FileProcessHw::get_i2c_device(string& device)
    {
        bool status;    

        status = get_device_info(device, "ApI2c");
        m_device.ApI2c = device;
        return status;
    }

    bool FileProcessHw::get_led_status(int& status)
    {
        bool flag;    

        flag = get_default_status(status, "Led");
        m_status.led = status;
        return flag;
    }

    bool FileProcessHw::get_beep_status(int& status)
    {
        bool flag;    

        flag = get_default_status(status, "Beep");
        m_status.beep = status;
        return flag;
    }

    void FileProcessHw::update_writer_value(void)
    {
        Json::Value Obj;

        Writer.clear();
        Obj.clear();

        //add status member
        Obj["Led"] = m_status.led;
        Obj["Beep"] = m_status.beep;
        Obj["Led0"] = m_status.led0;
        Obj["Beep0"] = m_status.beep0;
        Writer["Default"] = Obj;
        Obj.clear();

        //add device member
        Obj["Serial"] = m_device.Serial;
        Obj["Led"] = m_device.Led;
        Obj["Beep"] = m_device.Beep;
        Obj["IcmSpi"] = m_device.IcmSpi;
        Obj["Rtc"] = m_device.Rtc;
        Obj["ApI2c"] = m_device.ApI2c;
        Obj["Led0"] = m_device.Led0;
        Obj["Beep0"] = m_device.Beep0;
        Writer["Device"] = Obj;
        Obj.clear();

        //add uart member
        Obj["Baud"] = m_uart.baud;
        Obj["DataBits"] = m_uart.databits;
        Obj["StopBits"] = m_uart.stopbits;
        Obj["Parity"] = m_uart.parity;
        Writer["Uart"] = Obj;
        Obj.clear();

        std::cout<<Writer<<std::endl;
        writer();
    }

    //test for fileReadHw
    void test_file_reader_hw(void)
    {
        FileProcessHw *pReader = new FileProcessHw(HARDWART_JSON_DEFINE);
        UartInfo UartInfo;
        string DeviceStr;
        int DeviceStatus;

        if(pReader->get_uart_info(&UartInfo))
        {
            std::cout<<UartInfo.baud<<" "<<UartInfo.databits<<" "<<UartInfo.stopbits<<std::endl;
            std::cout<<UartInfo.parity<<std::endl;
        }

        if(pReader->get_beep_device(DeviceStr))
        {
            std::cout<<DeviceStr<<std::endl;
        }

        if(pReader->get_i2c_device(DeviceStr))
        {
            std::cout<<DeviceStr<<std::endl;
        }

        if(pReader->get_led_device(DeviceStr))
        {
            std::cout<<DeviceStr<<std::endl;
        }

        if(pReader->get_rtc_device(DeviceStr))
        {
            std::cout<<DeviceStr<<std::endl;
        }

        if(pReader->get_serial_device(DeviceStr))
        {
            std::cout<<DeviceStr<<std::endl;
        }

        if(pReader->get_spi_device(DeviceStr))
        {
            std::cout<<DeviceStr<<std::endl;
        }

        if(pReader->get_led_status(DeviceStatus))
        {
            std::cout<<DeviceStatus<<std::endl;
        }

        if(pReader->get_beep_status(DeviceStatus))
        {
            std::cout<<DeviceStatus<<std::endl;
        }

        pReader->update_writer_value();
        delete pReader;
        pReader = nullptr;
    }
}


