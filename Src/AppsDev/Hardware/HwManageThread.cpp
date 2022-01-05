/*
 * HwManageThread.cpp
 *
 *  Created on: 2022 Jan 4 15:08:05
 */
#include "HwManageThread.hpp"
#include <iostream>

HwManageThread::HwManageThread(std::string ThreadName)
:gThread()
{
    SetThreadName(ThreadName);
}

HwManageThread::~HwManageThread()
{

}

bool HwManageThread::Tmain(void)
{
    while(1)
    {
        std::cout<<"hello world!"<<std::endl;
        sleep(1);
    }
}