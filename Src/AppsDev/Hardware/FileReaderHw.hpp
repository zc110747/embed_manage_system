/*
 * FileReaderHw.hpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */

#include "../Common/FileReader.hpp"

struct UartInfo
{
    uint32_t baud;
    uint16_t databits;
    uint16_t stopbits;
    string parity;
};

class FileReaderHw : public FileReader
{
private:
    /* data */
public:
    FileReaderHw(string file):FileReader(file){
    }
    ~FileReaderHw(){};

    bool get_uart_info(UartInfo *pInfo);
};

