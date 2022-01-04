/*
 * main.cpp
 *
 *  Created on: 2021 May 11 15:08:05
 */

#include "led.hpp"
#include "beep.hpp"

int main(void)
{
    USR_READER::test_file_reader();
    USR_DEVICE::test_led_module();
    USR_DEVICE::test_beep_module();
}