/*
 * FileProcessHw.cpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */

#include "FileProcessHw.hpp"
#include <vector>
#include <algorithm>

namespace USR_READER
{
    const std::map<int, std::string> DevSrcVec = {
        {DIE_SERIAL, "Serial"},
        {DIE_LED, "Led"},
        {DIE_BEEP, "Beep"},
        {DIE_ICM_SPI, "IcmSpi"},
        {DIE_RTC, "Rtc"},
        {DIE_AP_I2C, "ApI2c"},
        {DIE_LED0, "Led0"},
        {DIE_BEEP0, "Beep0"}
    };

    const std::vector<int> DevStatusList = {
        DIE_LED, DIE_BEEP, DIE_LED0, DIE_BEEP0
    };

    bool FileProcessHw::is_valid_dev_status(DevInfoEnum dev)
    {
        for(auto val:DevStatusList){
            if(val == (int)dev)
                return true;
        }
        return false;
    }

    bool FileProcessHw::get_uart_info_interal(void)
    {
        bool is_error = false;   

        if(!is_reader_valid())
            return false;
        
        m_uart.baud = Reader["Uart"]["Baud"].isInt()?Reader["Uart"]["Baud"].asInt()
                    :([&is_error](){is_error=true; return 9600;}());
        m_uart.databits = Reader["Uart"]["DataBits"].isInt()?Reader["Uart"]["DataBits"].asInt()
                    :([&is_error](){is_error=true; return 8;}());   
        m_uart.stopbits = Reader["Uart"]["StopBits"].isInt()?Reader["Uart"]["StopBits"].asInt()
                    :([&is_error](){is_error=true; return 1;}());  
        m_uart.parity = Reader["Uart"]["Parity"].isString()?Reader["Uart"]["Parity"].asString()
                    :([&is_error](){is_error=true; return "n";}());      
        
        if(is_error)
        {
            printf("Json Value MemberValue have Invalid members!\r\n");
            return false;
        }
        return true;
    }

    bool FileProcessHw::get_device_info_interal(DevInfoEnum dev)
    {
        Json::Value DeviceMember;
        bool is_error = false; 

        if(!is_reader_valid() && (dev>=DIE_END))
            return false;

        m_device[dev] = Reader["Device"][DevSrcVec.at(dev)].isString()?Reader["Device"][DevSrcVec.at(dev)].asString()
            :([&is_error](){is_error = true; return std::string("null");}());

        if(is_error)
        {
            printf("Json Value Reader have Invalid member %s!\r\n", "Device");
            return false;
        }
        return true;
    }

    bool FileProcessHw::get_default_status_interal(DevInfoEnum dev)
    {
        Json::Value StatusMember;
        bool is_error = false;   

        if(!is_reader_valid())
            return false;
        
        m_status[dev] = Reader["Default"][DevSrcVec.at(dev)].isInt()?Reader["Default"][DevSrcVec.at(dev)].asInt()
            :([&is_error](){is_error = true; return 0;}());

        if(is_error)
        {
            printf("Json Value Reader have Invalid member %s!\r\n", "Device");
            return false;
        }
        return true;
    }

    void FileProcessHw::update_writer_value(void)
    {
        Json::Value Obj;
        int index;

        Writer.clear();
        Obj.clear();

        //add status member
        Obj["Led"] = m_status[DIE_LED];
        Obj["Beep"] = m_status[DIE_BEEP];
        Obj["Led0"] = m_status[DIE_LED0];
        Obj["Beep0"] = m_status[DIE_BEEP0];
        Writer["Default"] = Obj;
        Obj.clear();

        //add device member
        for(index=DIE_SERIAL; index<DIE_END; index++)
        {
            Obj[DevSrcVec.at(index)] = m_device[index];
        }
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
        //writer();
    }

    //test for fileReadHw
    void test_file_reader_hw(void)
    {
        FileProcessHw *pReader = new FileProcessHw(HARDWART_JSON_DEFINE);
        UartInfo UartInfo;
        string DeviceStr;
        int DeviceStatus;
        int index;

        UartInfo = pReader->get_uart_info();
        std::cout<<UartInfo.baud<<" "<<UartInfo.databits<<" "<<UartInfo.stopbits<<std::endl;
        std::cout<<UartInfo.parity<<std::endl;

        for(index=DIE_SERIAL; index<DIE_END; index++)
        {
            DeviceStr = pReader->get_device_info((DevInfoEnum)index);
            std::cout<<DevSrcVec.at(index)<<":"<<DeviceStr<<std::endl;
        }

        DeviceStatus = pReader->get_default_status(DIE_LED);
        std::cout<<DevSrcVec.at(DIE_LED)<<DeviceStatus<<std::endl;

        DeviceStatus = pReader->get_default_status(DIE_BEEP);
        std::cout<<DevSrcVec.at(DIE_LED0)<<DeviceStatus<<std::endl;

        DeviceStatus = pReader->get_default_status(DIE_LED0);
        std::cout<<DevSrcVec.at(DIE_BEEP)<<DeviceStatus<<std::endl;

        DeviceStatus = pReader->get_default_status(DIE_BEEP0);
        std::cout<<DevSrcVec.at(DIE_BEEP0)<<DeviceStatus<<std::endl;

        pReader->set_default_status(DIE_BEEP, 1);
        pReader->set_device_info(DIE_BEEP0, "/dev/beep0");
        pReader->set_device_info(DIE_LED0, "/dev/led0");
        pReader->update_writer_value();
        delete pReader;
        pReader = nullptr;
    }
}


