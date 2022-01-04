/*
 * FileReaderHw.cpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */

#include "FileReaderHw.hpp"

namespace USR_READER
{
    bool FileReaderHw::get_uart_info(UartInfo *pInfo)
    {
        Json::Value UartMember;

        if((!is_reader_valid()) || (pInfo == nullptr)){
            return false;
        }

        if(get_json_member("Uart", &root, &UartMember))
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
                return true;
            }
        }
        else
        {
            printf("Json Value root have Invalid member %s!\r\n", "Uart");
            return false;
        }

        return true;
    }

    bool FileReaderHw::get_led_device(string *pInfo)
    {
        return get_device_info(pInfo, "Led");
    }

    bool FileReaderHw::get_serial_device(string *pInfo)
    {
        return get_device_info(pInfo, "Serial");
    }

    bool FileReaderHw::get_beep_device(string *pInfo)
    {
        return get_device_info(pInfo, "Beep");
    }

    bool FileReaderHw::get_spi_device(string *pInfo)
    {
        return get_device_info(pInfo, "IcmSpi");
    }

    bool FileReaderHw::get_rtc_device(string *pInfo)
    {
        return get_device_info(pInfo, "Rtc");
    }

    bool FileReaderHw::get_i2c_device(string *pInfo)
    {
        return get_device_info(pInfo, "ApI2c"); 
    }

    bool FileReaderHw::get_led_status(uint8_t *pStatus)
    {
        return get_default_status(pStatus, "Led"); 
    }

    bool FileReaderHw::get_beep_status(uint8_t *pStatus)
    {
        return get_default_status(pStatus, "Beep"); 
    }

    bool FileReaderHw::get_device_info(string *pInfo, const string& device)
    {
        Json::Value DeviceMember;

        if((!is_reader_valid()) || (pInfo == nullptr)){
            return false;
        }

        if(get_json_member("Device", &root, &DeviceMember))
        {
            Json::Value MemberValue;

            if(get_json_member(device, &DeviceMember, &MemberValue))
                *pInfo = MemberValue.asString();
            else
            {
                printf("Json Value MemberValue have Invalid members %s!\r\n", device.c_str());
                return false;
            }
        } 
        else
        {
            printf("Json Value root have Invalid member %s!\r\n", "Device");
            return false;
        }
        return true;
    }

    bool FileReaderHw::get_default_status(uint8_t *pStatus, const string& device)
    {
        Json::Value StatusMember;

        if((!is_reader_valid()) || (pStatus == nullptr)){
            return false;
        }

        if(get_json_member("Default", &root, &StatusMember))
        {
            Json::Value MemberValue;

            if(get_json_member(device, &StatusMember, &MemberValue))
                *pStatus = MemberValue.asInt();
            else
            {
                printf("Json Value MemberValue have Invalid members %s!\r\n", device.c_str());
                return false;
            }
        } 
        else
        {
            printf("Json Value root have Invalid member %s!\r\n", "Default");
            return false;
        }
        return true;
    }

    //test for fileReadHw
    void test_file_reader(void)
    {
        FileReaderHw *pReader = new FileReaderHw(HARDWART_JSON_DEFINE);
        UartInfo UartInfo;
        string DeviceStr;
        uint8_t DeviceStatus;

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

        delete pReader;
        pReader = nullptr;
    }
}
