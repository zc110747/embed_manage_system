/*
 * FileReaderHw.cpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */

#include "FileReaderHw.hpp"

bool FileReaderHw::get_uart_info(UartInfo *pInfo)
{
    if((!is_reader_valid()) || (pInfo == nullptr)){
        return false;
    }

    pInfo->baud = root["Uart"]["Baud"].asInt();
    pInfo->databits = root["Uart"]["DataBits"].asInt();
    pInfo->stopbits = root["Uart"]["StopBits"].asInt();
    pInfo->parity = std::string(root["Uart"]["Parity"].asString());

    return true;
}