/*
 * main.c
 *
 *  Created on: 2021 May 11 15:08:05
 */

#include "device.hpp"
#include <string.h>

int main(void)
{
    USR_DEVICE::device *pdev = new USR_DEVICE::device("hello.txt", O_CREAT | O_RDWR, 0666);

    pdev->write("hello word!", strlen("hello word!"));

    delete pdev;

    return 0;
}