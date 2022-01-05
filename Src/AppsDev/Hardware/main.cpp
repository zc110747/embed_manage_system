/*
 * main.cpp
 *
 *  Created on: 2021 May 11 15:08:05
 *  Manage Hardware
 *  led, beep, key, rtc, i2c, spi, uart
 */

#include "led.hpp"
#include "beep.hpp"
#include "HwManageThread.hpp"

int main(void)
{
    USR_READER::test_file_reader();
    USR_DEVICE::test_led_module();
    USR_DEVICE::test_beep_module();
    HwManageThread *pThread = new HwManageThread("Hardware");
    pThread->Start();

    while(1)
    {
        sleep(1);
    }
    pThread->Stop();
}