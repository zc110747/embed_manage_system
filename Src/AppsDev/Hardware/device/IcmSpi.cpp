/*
 * IcmSpi.cpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#include "IcmSpi.hpp"

namespace USR_DEVICE
{
    using namespace USR_READER;

    ICMSPI::ICMSPI(void)
    {
        string SPI_dev;
        FileProcessHw *pReader = new FileProcessHw(HARDWART_JSON_DEFINE);

        if(pReader->get_spi_device(&SPI_dev))
        {
            std::cout<<SPI_dev<<std::endl;
            pdev = new USR_DEVICE::device(SPI_dev);
        }
        else
            pdev = nullptr;

        delete pReader;
        pReader = nullptr;
    }

    ICMSPI::ICMSPI(const string& device)
    {
        string SPI_dev;
        FileProcessHw *pReader = new FileProcessHw(HARDWART_JSON_DEFINE);

        if(pReader->get_device_info(&SPI_dev, device))
        {
            std::cout<<SPI_dev<<std::endl;
            pdev = new USR_DEVICE::device(SPI_dev);
        }
        else
            pdev = nullptr;

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

    void test_icm_spi_module(void)
    {
        USR_DEVICE::ICMSPI *pdev = new USR_DEVICE::ICMSPI();
        pdev->update();
        delete pdev;
        pdev = nullptr;
    }
}