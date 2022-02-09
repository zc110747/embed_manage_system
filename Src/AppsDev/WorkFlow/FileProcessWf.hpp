/*
 * FileProcessWf.hpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#pragma once
#include "FileProcess.hpp"
#include <list>
#include <string>
#include <algorithm>

#define HARDWART_JSON_DEFINE    "WorkFlowConfig.json"

namespace USR_READER
{
    typedef enum
    {
        MODE_CLIENT = 0,
        MODE_SERVER
    }LinkModeEnum;

    typedef enum
    {
        MODE_TCP = 0,
        MODE_UDP
    }ProtocolModeEnum;

    struct SocketInfo
    {
        LinkModeEnum link;
        ProtocolModeEnum protocol;
        std::string ipaddr;
        int port;

        //only valid in client mode
        std::string server_ip;
        int server_port;
    };

    typedef enum
    {
        SOCK_TCP_SERVER_0 = 0,
        SOCK_UDP_SERVER_0,
        SOCK_TCP_CLIENT_0,
        SOCK_LIST_END,
    }SockListEnum;

    class FileProcessWf: public FileProcess
    {
    public:
            /// - 
    	///constructor
        FileProcessWf():FileProcessWf(HARDWART_JSON_DEFINE){
        }

        /// - 
    	///constructor
        FileProcessWf(string file);
        
        /// - 
    	///destructor
        ~FileProcessWf(){};

      	/// \fn getInstance() 
        ///  - get the default Instance of the class
        /// \return the point for the Instance
        static FileProcessWf* getInstance(void);

      	/// \fn releaseInstance() 
        ///  - release the Instance of the class
        /// \return null
        void releaseInstance(void);

      	/// \fn get_sock_info() 
        ///  - called for get sock infomation.
        /// \return true=do success, false=no info
        SocketInfo get_sock_info(SockListEnum sock){
            return m_SockMap[sock];
        }

      	/// \fn is_sock_list() 
        ///  - check whether sock in the list
        /// \return true=ok sock, false=fail find
        bool is_sock_list(SockListEnum sock){
            if(sock>=SOCK_TCP_SERVER_0 && sock<SOCK_LIST_END)
                return true;
            return false;
        }

      	/// \fn set_sock_info() 
        ///  - set sock information
        /// \return true=set ok, false=set failed
        bool set_sock_info(SockListEnum sock, const SocketInfo &info)
        {
            if(!is_sock_list(sock))
                return false;
            m_SockMap[sock] = info;
            return true;
        }

        /// \fn update_writer_value() 
        ///  - create and write files
        /// \return NULL
        void update_writer_value(void);

        /// \fn test() 
        ///  - test the modlue function
        /// \return null
        static void test(void);
    private:
        struct std::map<SockListEnum, SocketInfo> m_SockMap;
        static FileProcessWf* pInstance;

      	/// \fn get_sock_info_internal() 
        ///  - called for get socket info infomation internal.
        /// \return true=do success, false=no info
        bool get_sock_info_internal(SockListEnum sock, std::string SockStr);
    };

    //test for fileReadHw
    void test_file_reader_wf(void);
}