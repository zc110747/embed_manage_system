/*
 * TcpServerThread.cpp
 *
 *  Created on: 2022 Jan 4 15:08:05
 */
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "TcpServerThread.hpp"

TcpServerThread::TcpServerThread(std::string ThreadName, std::string ipaddr, int port):
gThread()
{
    m_ipaddr = ipaddr;
    m_port = port; 
    SetThreadName(ThreadName);
}

TcpServerThread::~TcpServerThread(void)
{
}

bool TcpServerThread::Tmain(void)
{
    int server_fd;
    int result;
    struct sockaddr_in serverip, clientip;
    int is_bind_fail = 0;
    struct SSystemConfig *pSystemConfigInfo;

    printf("Socket Tcp Thread Start!\n");

    memset((char *)&serverip, 0, sizeof(serverip));
    serverip.sin_family = AF_INET;
    serverip.sin_port = htons(m_port);
    serverip.sin_addr.s_addr = inet_addr(m_ipaddr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd != -1)
    {   
        int one = 1;

#ifndef WIN32
        /*Linux平台默认断开后2min内处于Wait Time状态，不允许重新绑定，需要添加配置，允许在该状态下重新绑定*/
        setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (void*) &one, (socklen_t)sizeof(one));
#endif

        do 
        {
            result = bind(server_fd, (struct sockaddr *)&serverip, sizeof(serverip));
            if(result == -1)
            {
                static int check;
                if(is_bind_fail == 0)
                {
                    is_bind_fail = 1;
                    printf("Tcp Bind %s Failed!, error:%s\r\n",  pSystemConfigInfo->m_tcp_ipaddr.c_str(), strerror(errno));
                    if(errno == EADDRINUSE)
                    {
                        server_fd = socket(AF_INET, SOCK_STREAM, 0);
                    }              
                }
                sleep(1);
            }
            else
            {
                break;
            }
        } while (1); //网络等待socket绑定完成后执行后续
        
        printf("Tcp Bind ok, ServerIp:%s, NetPort:%d\n", m_ipaddr.c_str(), m_port);  
        listen(server_fd, 32);
        while(1)
        {
            uint32_t client_size;
            int client_fd;

            client_size = sizeof(clientip);
            client_fd = accept(server_fd, (struct sockaddr *)&clientip, &client_size);
            if(client_fd < 0)
            {
                printf("Tcp accept failed!\r\n");
                continue;
            } 
            else
            {
                TcpProcessThread *pThread = new TcpProcessThread("TcpProcessGThread", client_fd);
                pThread->Start();
            }
        }
    }
    else
    {
        printf("Tcp Init Failed!\r\n");
    }

    close(server_fd);
    pthread_detach(pthread_self()); 
    pthread_exit((void *)0);
}

TcpProcessThread::TcpProcessThread(std::string ThreadName, int client_fd):
gThread()
{
    m_client_fd = client_fd;
    SetThreadName(ThreadName);
}

TcpProcessThread::~TcpProcessThread(void)
{
}

bool TcpProcessThread::Tmain(void)
{

}