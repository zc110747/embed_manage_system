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
        /// - 
        ///constructor
        device(string dev);

        /// - 
        ///constructor
        device(string dev, int flag);

        /// - 
        ///constructor
        device(string dev, int flag, mode_t mode);

        /// - 
        ///destructor
        ~device();

      	/// \fn read() 
        ///  - called for read data from the device.
        /// \return -1=error, other=read data size.
        int read(void *buf, size_t count);

        /// \fn write() 
        ///  - called for write data to the device.
        /// \return -1=error, other=write data size.
        int write(const void *buf, size_t count);

        /// \fn ioctl() 
        ///  - called for ioctl the device.
        /// \return true=process ok, false=process fail.
        bool ioctl(unsigned long int cmd, void *args);

        /// \fn close() 
        ///  - close the open device.
        /// \return NULL
        void close(void);

        /// \fn get_device_fd() 
        ///  - called for get the open device fd.
        /// \return the fd open by construct.
        int get_device_fd(void){ return device_fd; }

        /// \fn is_device_valid() 
        ///  - called for judge whether the device open success.
        /// \return true=open success, false=open fail.
        bool is_device_valid(void) { 
            if(device_fd>=0) 
                return true;
            return false;
        } 

        std::string get_dev_name(void){
            return dev_str;
        }

    private:
        int device_fd;

        std::string dev_str;
    };
}
