/*
 * ApI2c.cpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#include "ApI2c.hpp"

namespace USR_DEVICE
{
    using namespace USR_READER;

    API2C* API2C::pInstance = nullptr;
    
    API2C::API2C(void):API2C(DIE_AP_I2C)
    {
    }

    API2C::API2C(DevInfoEnum dev)
    {
        string i2c_dev;
        FileProcessHw *pReader = new FileProcessHw(HARDWART_JSON_DEFINE);

        i2c_dev = pReader->get_device_info(dev);
        std::cout<<i2c_dev<<std::endl;
        pdev = new USR_DEVICE::device(i2c_dev);

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

    API2C* API2C::getInstance(void)
    {
        if(pInstance == nullptr)
        {
            pInstance = new(std::nothrow) API2C;
            if(pInstance == nullptr)
            {
                std::cout<<"API2C class new failed!\r\n"<<std::endl;
            }
        }
        return pInstance;
    }

    void API2C::releaseInstance(void)
    {
        if(!pInstance)
        {
            delete pInstance;
            pInstance = nullptr;
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

    void API2C::test(void)
    {
        API2C::getInstance()->update();
        API2C::getInstance()->releaseInstance();
    }
}