#pragma once
/*
 * device.hpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */

#include <string>
#include <unistd.h>
#include <fcntl.h>

namespace USR_DEVICE
{
    using std::string;

    class device
    {
    public:
        /////////////////////////////
        //
        device(string dev);
        device(string dev, int flag);
        device(string dev, int flag, mode_t mode);
        ~device();

        int read(void *buf, size_t count);
        int write(const void *buf, size_t count);
        bool ioctl(unsigned long int cmd, void *args);

        int get_device_fd(void){ return device_fd; }
        bool is_device_valid(void) { 
            if(device_fd>=0) 
                return true;
            return false;
        } 

    private:
        int device_fd;

        std::string dev_str;
    };
}
