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
    using namespace std;

    FileProcessHw* FileProcessHw::pInstance = nullptr;

    const std::map<int, std::string> DevSrcVec = {
        {DIE_SERIAL, "Serial"},
        {DIE_LED, "Led"},
        {DIE_BEEP, "Beep"},
        {DIE_ICM_SPI, "IcmSpi"},
        {DIE_RTC, "Rtc"},
        {DIE_AP_I2C, "ApI2c"},
    };

    const std::vector<int> DevStatusList = {
        DIE_LED, DIE_BEEP
    };

    FileProcessHw::FileProcessHw(std::string file):FileProcess(file)
    {
        int index;

        for_each(DevSrcVec.begin(), DevSrcVec.end(), [&](const typename std::pair<int, std::string> &ref){
            get_device_info_interal((DevInfoEnum)ref.first);
        });

        for_each(DevStatusList.begin(), DevStatusList.end(), [&](const int &ref){
            get_default_status_interal((DevInfoEnum)ref);
        });

        get_uart_info_interal();
    }

    FileProcessHw* FileProcessHw::getInstance(void)
    {
        if(pInstance == nullptr)
        {
            pInstance = new(std::nothrow) FileProcessHw;
            if(pInstance == nullptr)
            {
                std::cout<<"FileProcessHw class new failed!\r\n"<<std::endl;
            }
        }
        return pInstance;
    }

    void FileProcessHw::releaseInstance(void)
    {
        if(pInstance != nullptr)
        {
            delete pInstance;
            pInstance = nullptr;
        }
    }

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

        if(!is_reader_valid() && !Reader["Default"][DevSrcVec.at(dev)].isArray())
        {
            printf("Json Value Reader have Invalid member %s!\r\n", "Device");
            return false;
        }
        
        for(int index=0; index<MAX_ARRAY_STATUS_SIZE; index++)
        {
            m_status[dev].at(index) = Reader["Default"][DevSrcVec.at(dev)][index].asInt();
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
        for_each(m_status[DIE_LED].begin(), m_status[DIE_LED].end(), [&](const int &ref){
            Obj["Led"].append(ref);
        });
        for_each(m_status[DIE_BEEP].begin(), m_status[DIE_BEEP].end(), [&](const int &ref){
            Obj["Beep"].append(ref);
        });
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
        writer();
    }

    //test for fileReadHw
    void FileProcessHw::test(void)
    {
        UartInfo UartInfo;
        string DeviceStr;
        int DeviceStatus;
        int index;

        UartInfo = FileProcessHw::getInstance()->get_uart_info();
        std::cout<<UartInfo.baud<<" "<<UartInfo.databits<<" "<<UartInfo.stopbits<<std::endl;
        std::cout<<UartInfo.parity<<std::endl;

        for(index=DIE_SERIAL; index<DIE_END; index++)
        {
            DeviceStr = FileProcessHw::getInstance()->get_device_info((DevInfoEnum)index);
            std::cout<<DevSrcVec.at(index)<<":"<<DeviceStr<<std::endl;
        }

        DeviceStatus = FileProcessHw::getInstance()->get_default_status(DIE_LED, 0);
        std::cout<<DevSrcVec.at(DIE_LED)<<":"<<DeviceStatus<<std::endl;

        DeviceStatus = FileProcessHw::getInstance()->get_default_status(DIE_BEEP, 0);
        std::cout<<DevSrcVec.at(DIE_BEEP)<<":"<<DeviceStatus<<std::endl;

        FileProcessHw::getInstance()->set_default_status(DIE_BEEP, 0,  1);
        FileProcessHw::getInstance()->set_device_info(DIE_BEEP, "/dev/beep0");
        FileProcessHw::getInstance()->set_device_info(DIE_LED, "/dev/led0");
        FileProcessHw::getInstance()->update_writer_value();
        FileProcessHw::getInstance()->releaseInstance();
    }
}


