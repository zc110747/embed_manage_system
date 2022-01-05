/*
 * device.cpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */

#include "device.hpp"

namespace USR_DEVICE
{
    device::device(std::string dev)
{
    dev_str = dev;

    device_fd = open(dev_str.c_str(), O_RDWR);
    if(device_fd < 0)
    {
        printf("device driver %s open failed!\r\n", dev.c_str());
    }
}

    device::device(std::string dev, int flag, mode_t mode)
    {
        device_fd = open(dev.c_str(), flag, mode);
        if(device_fd < 0)
        {
            printf("device driver %s open failed!\r\n", dev.c_str());
        }
    }

    device::~device()
    {
        if(device_fd >= 0)
            ::close(device_fd);
    }

    int device::read(void *buf, size_t count)
    {
        int nsize;

        if(device_fd < 0)
        {
            printf("No vaild %s device!\r\n", dev_str.c_str());
            return -1;
        }

        nsize = ::read(device_fd, buf, count);
        if(nsize < 0)
        {
            printf("%s device read error!\r\n", dev_str.c_str());
        }
        return nsize;
    }

    void device::close(void)
    {
        if(device_fd >= 0)
        {
            ::close(device_fd);
            device_fd = -1;
        }
    }

    int device::write(const void *buf, size_t count)
    {
        int nsize;

        if(device_fd < 0)
        {
            printf("No vaild %s device!\r\n", dev_str.c_str());
            return -1;
        }

        nsize = ::write(device_fd, buf, count);
        if(nsize < 0)
        {
            printf("%s device write error!\r\n", dev_str.c_str());
        }
        return nsize;
    }

    bool device::ioctl(unsigned long int cmd, void *args)
    {
        int nsize = 0;

        if(device_fd < 0)
        {
            printf("No vaild %s device!\r\n", dev_str.c_str());
            return -1;
        }

        //nsize = ::ioctl(device_fd, cmd, args);
        if(nsize < 0)
        {
            printf("%s device ioctl error!\r\n", dev_str.c_str());
        }
        return nsize;
    }
}