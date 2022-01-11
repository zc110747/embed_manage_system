/*
 * FileProcessWf.hpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#pragma once
#include "FileProcess.hpp"

#define HARDWART_JSON_DEFINE    "WorkFlowConfig.json"

namespace USR_READER
{
    struct ServerInfo
    {
        std::string ipaddr;
        int port;
    };

    class FileProcessWf: public FileProcess
    {
    public:
            /// - 
    	///constructor
        FileProcessWf():FileProcess(HARDWART_JSON_DEFINE){
        }

        /// - 
    	///constructor
        FileProcessWf(string file):FileProcess(file){
        }

        /// - 
    	///destructor
        ~FileProcessWf(){};

      	/// \fn get_uart_info() 
        ///  - called for get uart infomation.
        /// \return true=do success, false=no info
        bool get_tcp_server_info(ServerInfo& info);

      	/// \fn get_uart_info() 
        ///  - called for get uart infomation.
        /// \return true=do success, false=no info
        bool get_udp_server_info(ServerInfo& info);

        /// \fn update_writer_value() 
        ///  - create and write files
        /// \return NULL
        void update_writer_value(void);
    private:
        struct ServerInfo m_tcp_info;
        struct ServerInfo m_udp_info;
    };

    //test for fileReadHw
    void test_file_reader_wf(void);
}