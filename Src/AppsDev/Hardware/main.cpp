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
#endif
    HwManageThread *pThread;
    pThread = new HwManageThread("Hardware");
    pThread->Start();

    HW_MainLoop();

    pThread->Stop();
    delete pThread;
    pThread = nullptr;
    return 0;
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
    USR_READER::test_file_reader_hw();
    USR_DEVICE::test_led_module();
    USR_DEVICE::test_beep_module();
    USR_DEVICE::test_ap_i2c_module();
    USR_DEVICE::test_icm_spi_module();
}