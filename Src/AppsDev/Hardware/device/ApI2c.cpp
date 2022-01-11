/*
 * ApI2c.cpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#include "ApI2c.hpp"

namespace USR_DEVICE
{
    using namespace USR_READER;

    API2C::API2C(void)
    {
        string I2C_dev;
        FileProcessHw *pReader = new FileProcessHw(HARDWART_JSON_DEFINE);

        if(pReader->get_i2c_device(&I2C_dev))
        {
            std::cout<<I2C_dev<<std::endl;
            pdev = new USR_DEVICE::device(I2C_dev);
        }
        else
            pdev = nullptr;

        delete pReader;
        pReader = nullptr;
    }

    API2C::API2C(const string& device)
    {
        string I2C_dev;
        FileProcessHw *pReader = new FileProcessHw(HARDWART_JSON_DEFINE);

        if(pReader->get_device_info(&I2C_dev, device))
        {
            std::cout<<I2C_dev<<std::endl;
            pdev = new USR_DEVICE::device(I2C_dev);
        }
        else
            pdev = nullptr;

        delete pReader;
        pReader = nullptr;
    }

    API2C::~API2C(void)
    {
        if(pdev != nullptr)
        {
            delete pdev;
            pdev = nullptr;
        }
    }

    void API2C::update(void)
    {
        char *pBuf;

        pBuf = (char *)&m_info;
        if(pdev->read((char *)pBuf, sizeof(m_info)) > 0)
        {
            printf("\r\n原始值:\r\n");
			printf("ir = %d, als = %d, ps = %d\r\n", m_info.ir, 
                    m_info.als, m_info.ps);
        }
        else
        {
            printf("device %s read failed!\r\n", pdev->get_dev_name().c_str());
        }
    }

    void test_ap_i2c_module(void)
    {
        USR_DEVICE::API2C *pdev = new USR_DEVICE::API2C();
        pdev->update();
        delete pdev;
        pdev = nullptr;
    }
}