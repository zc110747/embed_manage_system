/*
 * main.c
 *
 *  Created on: 2021 May 11 15:08:05
 */

#include "device.hpp"
#include "FileReaderHw.hpp"
#include <string.h>


int main(void)
{
    FileReaderHw *pReader = new FileReaderHw("hardware.json");
    UartInfo Info;

    if(pReader->get_uart_info(&Info))
    {
        std::cout<<Info.baud<<" "<<Info.databits<<" "<<Info.stopbits<<std::endl;
        std::cout<<Info.parity<<std::endl;
    }

    delete pReader;
    pReader = nullptr;
    return 0;
}