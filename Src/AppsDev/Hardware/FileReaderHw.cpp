/*
 * FileReaderHw.cpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */

#include "FileReaderHw.hpp"

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