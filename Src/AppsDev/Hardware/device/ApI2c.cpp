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
        FileReaderHw *pReader = new FileReaderHw(HARDWART_JSON_DEFINE);

        if(pReader->get_i2c_device(&I2C_dev))
        {
            std::cout<<I2C_dev<<std::endl;
            pApI2c = new USR_DEVICE::device(I2C_dev);
        }
        else
            pApI2c = nullptr;

        delete pReader;
        pReader = nullptr;
    }

    API2C::API2C(const string& device)
    {
        string I2C_dev;
        FileReaderHw *pReader = new FileReaderHw(HARDWART_JSON_DEFINE);

        if(pReader->get_device_info(&I2C_dev, device))
        {
            std::cout<<I2C_dev<<std::endl;
            pApI2c = new USR_DEVICE::device(I2C_dev);
        }
        else
            pApI2c = nullptr;

        delete pReader;
        pReader = nullptr;
    }

    API2C::~API2C(void)
    {
        if(pApI2c != nullptr)
        {
            delete pApI2c;
            pApI2c = nullptr;
        }
    }

    void API2C::update(void)
    {
        char *pBuf;

        pBuf = (char *)&m_info;
        if(pApI2c->read((char *)pBuf, sizeof(m_info)) > 0)
        {
            printf("\r\n原始值:\r\n");
			printf("ir = %d, als = %d, ps = %d\r\n", m_info.ir, 
                    m_info.als, m_info.ps);
        }
        else
        {
            printf("device %s read failed!\r\n", pApI2c->get_dev_name().c_str());
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