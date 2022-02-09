/*
 * main.cpp
 *
 *  Created on: 2021 May 11 15:08:05
 *  Manage Hardware
 *  led     --
 *  beep    --
 *  rtc     --
 *  i2c     --
 *  spi     --
 *  key, pwm
 */
#include "HwManageThread.hpp"

#define MODULE_TEST 1

int g_main_exit_flag;

static void HW_MainLoop(void);
static void module_test(void);

int main(int argc, char **argv)
{
#if MODULE_TEST == 1
    module_test();
#else
    HwManageThread::getInstance()->Start();

    HW_MainLoop();

    HwManageThread::getInstance()->Stop();
    HwManageThread::getInstance()->releaseInstance();
    return 0;
#endif
}

static void HW_MainLoop(void)
{
    g_main_exit_flag = 0;

    while(!g_main_exit_flag)
    {
        sleep(1);
    }
}

static void module_test(void)
{
    USR_READER::FileProcessHw::test();
    USR_DEVICE::LED::test();
    USR_DEVICE::BEEP::test();
    USR_DEVICE::API2C::test();
    USR_DEVICE::ICMSPI::test();
}