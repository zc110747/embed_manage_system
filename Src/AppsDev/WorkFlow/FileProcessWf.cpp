/*
 * FileProcessWf.cpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */

#include "FileProcessWf.hpp"

namespace USR_READER
{
    bool FileProcessWf::get_tcp_server_info(ServerInfo& info)
    {
        bool is_error = false;

        if(!is_reader_valid())
            return false;

        info.ipaddr = Reader["TcpServer"]["ipaddr"].isString()?Reader["TcpServer"]["ipaddr"].asString()
            :([&is_error](){is_error = true; return string("10.0.1.99");}());
        info.port = Reader["TcpServer"]["port"].isInt()?Reader["TcpServer"]["port"].asInt()
            :([&is_error](){is_error = true; return 8000;}());
        m_tcp_info.ipaddr = info.ipaddr;
        m_tcp_info.port = info.port;
        if(is_error)
        {
            printf("Json Value MemberValue have Invalid members!\r\n");
            return false;
        }
        return true;
    }

    bool FileProcessWf::get_udp_server_info(ServerInfo& info)
    {
        bool is_error = false;

        if(!is_reader_valid())
            return false;

        info.ipaddr = Reader["UdpServer"]["ipaddr"].isString()?Reader["UdpServer"]["ipaddr"].asString()
            :([&is_error](){is_error = true; return string("10.0.1.99");}());
        info.port = Reader["UdpServer"]["port"].isInt()?Reader["UdpServer"]["port"].asInt()
            :([&is_error](){is_error = true; return 8000;}());
        m_udp_info.ipaddr = info.ipaddr;
        m_udp_info.port = info.port;
        if(is_error)
        {
            printf("Json Value MemberValue have Invalid members!\r\n");
            return false;
        }
        return true;
    }

    void FileProcessWf::update_writer_value(void)
    {
        Json::Value Obj;

        Writer.clear();
        Obj.clear();

        //add status member
        Obj["ipaddr"] = m_udp_info.ipaddr;
        Obj["port"] = m_udp_info.port;
        Writer["UdpServer"] = Obj;
        Obj.clear();

        Obj["ipaddr"] = m_tcp_info.ipaddr;
        Obj["port"] = m_tcp_info.port;
        Writer["TcpServer"] = Obj;
        Obj.clear();

        std::cout<<Writer<<std::endl;
        writer();
    }

    void test_file_reader_wf(void)
    {
        FileProcessWf *pReader = new FileProcessWf();
        ServerInfo sock_info;

        if(pReader->get_tcp_server_info(sock_info))
        {
            std::cout<<sock_info.ipaddr<<" "<<sock_info.port<<std::endl;
        }

        if(pReader->get_udp_server_info(sock_info))
        {
            std::cout<<sock_info.ipaddr<<" "<<sock_info.port<<std::endl;
        }

        pReader->update_writer_value();
        delete pReader;
        pReader = nullptr;
    }
}