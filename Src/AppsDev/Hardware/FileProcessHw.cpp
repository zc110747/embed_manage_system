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
        Json::Value UartMember;

        reader();

        if((!is_reader_valid()) || (pInfo == nullptr)){
            return false;
        }

        if(get_json_member("Uart", &Reader, &UartMember))
        {
            bool is_error = false;
            Json::Value MemberValue;

            if(get_json_member("Baud", &UartMember, &MemberValue))
                pInfo->baud = MemberValue.asInt();
            else
                is_error = false;

            if(get_json_member("DataBits", &UartMember, &MemberValue))
                pInfo->databits = MemberValue.asInt();
            else
                is_error = false;

            if(get_json_member("StopBits", &UartMember, &MemberValue))
                pInfo->stopbits = MemberValue.asInt();
            else
                is_error = false;

            if(get_json_member("Parity", &UartMember, &MemberValue))
                pInfo->parity = MemberValue.asString();
            else
                is_error = false;

            if(is_error)
            {
                printf("Json Value MemberValue have Invalid members!\r\n");
            }
            else
            {
                m_uart.baud = pInfo->baud;
                m_uart.databits = pInfo->databits;
                m_uart.stopbits = pInfo->stopbits;
                m_uart.parity = pInfo->parity;
                return true;
            }
        }
        else
        {
            printf("Json Value Reader have Invalid member %s!\r\n", "Uart");
            return false;
        }

        return true;
    }

    bool FileProcessHw::get_led_device(string *pInfo)
    {
        bool status;

        status = get_device_info(pInfo, "Led");
        if(status)
            m_device.Led = *pInfo;

        return status;
    }

    bool FileProcessHw::get_serial_device(string *pInfo)
    {
        bool status;

        status = get_device_info(pInfo, "Serial");
        if(status)
            m_device.Serial = *pInfo;

        return status;
    }

    bool FileProcessHw::get_beep_device(string *pInfo)
    {
        bool status;    

        status = get_device_info(pInfo, "Beep");
        if(status)
            m_device.Beep = *pInfo;

        return status;
    }

    bool FileProcessHw::get_spi_device(string *pInfo)
    {
        bool status;    

        status = get_device_info(pInfo, "IcmSpi");
        if(status)
            m_device.IcmSpi = *pInfo;

        return status;
    }

    bool FileProcessHw::get_rtc_device(string *pInfo)
    {
        bool status;    

        status = get_device_info(pInfo, "Rtc");
        if(status)
            m_device.Rtc = *pInfo;

        return status;
    }

    bool FileProcessHw::get_i2c_device(string *pInfo)
    {
        bool status;    

        status = get_device_info(pInfo, "ApI2c");
        if(status)
            m_device.ApI2c = *pInfo;

        return status;
    }

    bool FileProcessHw::get_led_status(int *pStatus)
    {
        bool status;    

        status = get_default_status(pStatus, "Led");
        if(status)
            m_status.led = *pStatus;

        return status;
    }

    bool FileProcessHw::get_beep_status(int *pStatus)
    {
        bool status;    

        status = get_default_status(pStatus, "Beep");
        if(status)
            m_status.beep = *pStatus;

        return status;
    }

    bool FileProcessHw::get_device_info(string *pInfo, const string& device)
    {
        Json::Value DeviceMember;

        reader();

        if((!is_reader_valid()) || (pInfo == nullptr)){
            return false;
        }

        if(get_json_member("Device", &Reader, &DeviceMember))
        {
            Json::Value MemberValue;

            if(get_json_member(device, &DeviceMember, &MemberValue))
                *pInfo = MemberValue.isString()?MemberValue.asString():string();
            else
            {
                printf("Json Value MemberValue have Invalid members %s!\r\n", device.c_str());
                return false;
            }
        } 
        else
        {
            printf("Json Value Reader have Invalid member %s!\r\n", "Device");
            return false;
        }
        return true;
    }

    bool FileProcessHw::get_default_status(int *pStatus, const string& device)
    {
        Json::Value StatusMember;

        reader();

        if((!is_reader_valid()) || (pStatus == nullptr)){
            return false;
        }

        if(get_json_member("Default", &Reader, &StatusMember))
        {
            Json::Value MemberValue;

            if(get_json_member(device, &StatusMember, &MemberValue))
                *pStatus = MemberValue.isInt()?MemberValue.asInt():0;
            else
            {
                printf("Json Value MemberValue have Invalid members %s!\r\n", device.c_str());
                return false;
            }
        } 
        else
        {
            printf("Json Value Reader have Invalid member %s!\r\n", "Default");
            return false;
        }
        return true;
    }

    void FileProcessHw::update_writer_value(void)
    {
        Json::Value Obj;

        //add status member
        Obj["Led"] = m_status.led;
        Obj["Beep"] = m_status.beep;
        Obj["Led0"] = m_status.led0;
        Obj["Beep0"] = m_status.beep0;
        Writer["Default"] = Obj;

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

        if(pReader->get_beep_device(&DeviceStr))
        {
            std::cout<<DeviceStr<<std::endl;
        }

        if(pReader->get_i2c_device(&DeviceStr))
        {
            std::cout<<DeviceStr<<std::endl;
        }

        if(pReader->get_led_device(&DeviceStr))
        {
            std::cout<<DeviceStr<<std::endl;
        }

        if(pReader->get_rtc_device(&DeviceStr))
        {
            std::cout<<DeviceStr<<std::endl;
        }

        if(pReader->get_serial_device(&DeviceStr))
        {
            std::cout<<DeviceStr<<std::endl;
        }

        if(pReader->get_spi_device(&DeviceStr))
        {
            std::cout<<DeviceStr<<std::endl;
        }

        if(pReader->get_led_status(&DeviceStatus))
        {
            std::cout<<DeviceStatus<<std::endl;
        }

        if(pReader->get_beep_status(&DeviceStatus))
        {
            std::cout<<DeviceStatus<<std::endl;
        }

        pReader->update_writer_value();
        delete pReader;
        pReader = nullptr;
    }
}


