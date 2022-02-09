/*
 * IcmSpi.cpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#include "IcmSpi.hpp"

namespace USR_DEVICE
{
    using namespace USR_READER;

    ICMSPI* ICMSPI::pInstance = nullptr;

    ICMSPI::ICMSPI(void):ICMSPI(DIE_ICM_SPI)
    {
    }

    ICMSPI::ICMSPI(DevInfoEnum dev)
    {
        string spi_dev;
        FileProcessHw *pReader = new FileProcessHw(HARDWART_JSON_DEFINE);

        spi_dev = pReader->get_device_info(dev);
        std::cout<<spi_dev<<std::endl;
        pdev = new USR_DEVICE::device(spi_dev);

        delete pReader;
        pReader = nullptr;
    }

    ICMSPI::~ICMSPI(void)
    {
        if(pdev != nullptr)
        {
            delete pdev;
            pdev = nullptr;
        }
    }

    ICMSPI* ICMSPI::getInstance(void)
    {
        if(pInstance == nullptr)
        {
            pInstance = new(std::nothrow) ICMSPI;
            if(pInstance == nullptr)
            {
                std::cout<<"ICMSPI class new failed!\r\n"<<std::endl;
            }
        }
        return pInstance;
    }

    void ICMSPI::releaseInstance(void)
    {
        if(!pInstance)
        {
            delete pInstance;
            pInstance = nullptr;
        }
    }

    void ICMSPI::update(void)
    {
        char *pBuf;

        pBuf = (char *)&m_info;
        if(pdev->read((char *)pBuf, sizeof(m_info)) > 0)
        {
            printf("\r\n原始值:\r\n");
            printf("gx = %d, gy = %d, gz = %d\r\n", m_info.gyro_x_adc, 
                    m_info.gyro_y_adc, m_info.gyro_z_adc);
            printf("ax = %d, ay = %d, az = %d\r\n", m_info.accel_x_adc, 
                    m_info.accel_y_adc, m_info.accel_z_adc);
            printf("temp = %d\r\n", m_info.temp_adc);
        }
        else
        {
            printf("device %s read failed!\r\n", pdev->get_dev_name().c_str());
        }
    }

    void ICMSPI::test(void)
    {
        ICMSPI::getInstance()->update();
        ICMSPI::getInstance()->releaseInstance();
    }
}