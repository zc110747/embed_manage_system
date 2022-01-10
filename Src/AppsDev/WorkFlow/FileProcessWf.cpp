/*
 * FileProcessWf.cpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */

#include "FileProcessWf.hpp"

namespace USR_READER
{
    bool FileProcessWf::get_tcp_server_info(ServerInfo *pInfo)
    {
        Json::Value TcpMember;

        if((!is_reader_valid()) || (pInfo == nullptr)){
            return false;
        }

        if(get_json_member("TcpServer", &Reader, &TcpMember))
        {
            bool is_error = false;
            Json::Value MemberValue;    

            if(get_json_member("ipaddr", &TcpMember, &MemberValue))
                pInfo->ipaddr = MemberValue.isString()?MemberValue.asString():string();
            else
                is_error = true;

            if(get_json_member("port", &TcpMember, &MemberValue))
            {   
                pInfo->port = MemberValue.isInt()?MemberValue.asInt():0;
            }
            else
                is_error = true;

            if(is_error)
            {
                m_tcp_info.ipaddr = "0.0.0.0";
                m_tcp_info.port = 0;
                printf("Json Value MemberValue have Invalid members!\r\n");
                return false;
            }
            else
            {
                m_tcp_info.ipaddr = pInfo->ipaddr;
                m_tcp_info.port = pInfo->port;
            }
        }
        else
        {
            printf("Json Value Reader have Invalid member %s!\r\n", "TcpServer");
            return false;
        }
        return true;
    }

    bool FileProcessWf::get_udp_server_info(ServerInfo *pInfo)
    {
        Json::Value UdpMember;
        
        if((!is_reader_valid()) || (pInfo == nullptr)){
            return false;
        }

        if(get_json_member("UdpServer", &Reader, &UdpMember))
        {
            bool is_error = false;
            Json::Value MemberValue;    

            if(get_json_member("ipaddr", &UdpMember, &MemberValue))
                pInfo->ipaddr = MemberValue.isString()?MemberValue.asString():string();
            else
                is_error = true;

            if(get_json_member("port", &UdpMember, &MemberValue))
                pInfo->port = MemberValue.isInt()?MemberValue.asInt():0;
            else
                is_error = true;

            if(is_error)
            {
                m_udp_info.ipaddr = "0.0.0.0";
                m_udp_info.port = 0;
                printf("Json Value MemberValue have Invalid members!\r\n");
                return false;
            }
            else
            {
                m_udp_info.ipaddr = pInfo->ipaddr;
                m_udp_info.port = pInfo->port;
            }
        }
        else
        {
            printf("Json Value Reader have Invalid member %s!\r\n", "UdpServer");
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
        FileProcessWf *pReader = new FileProcessWf(HARDWART_JSON_DEFINE);
        ServerInfo sock_info;

        if(pReader->get_tcp_server_info(&sock_info))
        {
            std::cout<<sock_info.ipaddr<<" "<<sock_info.port<<std::endl;
        }

        if(pReader->get_udp_server_info(&sock_info))
        {
            std::cout<<sock_info.ipaddr<<" "<<sock_info.port<<std::endl;
        }

        pReader->update_writer_value();
        delete pReader;
        pReader = nullptr;
    }
}