/*
 * FileProcessWf.cpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */

#include "FileProcessWf.hpp"

namespace USR_READER
{
    const std::map<SockListEnum, std::string> SockStrMap = {
        {SOCK_TCP_SERVER_0, "SOCK_TCP_SERVER_0"},
        {SOCK_UDP_SERVER_0, "SOCK_UDP_SERVER_0"},
        {SOCK_TCP_CLIENT_0, "SOCK_TCP_CLIENT_0"},
    };

    FileProcessWf::FileProcessWf(string file):FileProcess(file)
    {
        for(auto &ref_val:SockStrMap)
            get_sock_info_internal(ref_val.first, ref_val.second);
    }

    bool FileProcessWf::get_sock_info_internal(SockListEnum sock, std::string SockStr)
    {
        bool is_error = false;
        SocketInfo info;

        if(!is_reader_valid())
            return false;

        info.link = (LinkModeEnum)(Reader[SockStr]["link"].isInt()?Reader[SockStr]["link"].asInt()
            :([&is_error](){is_error = true; return -1;}()));
        info.protocol = (ProtocolModeEnum)(Reader[SockStr]["protocl"].isInt()?Reader[SockStr]["protocl"].asInt()
            :([&is_error](){is_error = true; return -1;}()));
        info.ipaddr = Reader[SockStr]["ipaddr"].isString()?Reader[SockStr]["ipaddr"].asString()
            :([&is_error](){is_error = true; return string("10.0.1.99");}());
        info.port = Reader[SockStr]["port"].isInt()?Reader[SockStr]["port"].asInt()
            :([&is_error](){is_error = true; return 8000;}());
        info.server_ip = Reader[SockStr]["server_ip"].isString()?Reader[SockStr]["server_ip"].asString()
            :([&is_error](){is_error = true; return string("10.0.1.99");}());
        info.server_port = Reader[SockStr]["server_port"].isInt()?Reader[SockStr]["server_port"].asInt()
            :([&is_error](){is_error = true; return 8001;}());
        m_SockMap[sock] = info;

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

        std::for_each(SockStrMap.begin(), SockStrMap.end(), [&](const typename std::pair<SockListEnum, std::string> &ref_value){
            SocketInfo info = m_SockMap[ref_value.first];
            Obj["link"] = info.link;
            Obj["protocl"] = info.protocol;
            Obj["ipaddr"] = info.ipaddr;
            Obj["port"] = info.port;
            Obj["server_ip"] = info.server_ip;
            Obj["server_port"] = info.server_port;
            Writer[ref_value.second] = Obj;
            Obj.clear(); 
        });

        std::cout<<Writer<<std::endl;
        writer();
    }

    void test_file_reader_wf(void)
    {
        FileProcessWf *pReader = new FileProcessWf();
        SocketInfo MySockInfo;

        MySockInfo = pReader->get_sock_info(SOCK_TCP_SERVER_0);
        std::cout<<MySockInfo.ipaddr<<" "<<MySockInfo.port<<std::endl;

        MySockInfo = pReader->get_sock_info(SOCK_UDP_SERVER_0);
        std::cout<<MySockInfo.ipaddr<<" "<<MySockInfo.port<<std::endl;
        MySockInfo.port = 3222;
        pReader->set_sock_info(SOCK_UDP_SERVER_0, MySockInfo);

        pReader->update_writer_value();
        delete pReader;
        pReader = nullptr;
    }
}