/*
 * TcpServerThread.hpp
 *
 *  Created on: 2022 Jan 4 15:08:05
 */
#pragma once

#include "gThread.hpp"

class TcpServerThread:public gThread
{
public:
    /// - 
    ///constructor
    TcpServerThread(std::string ThreadName, std::string ipaddr, int port);

        /// - 
    ///destructor
    virtual ~TcpServerThread();

    /// \fn Tmain() 
    ///  - main() for this thread - This method MUST be implemented in derived class
    /// \return true=success after executed, false=fail after executed
	bool Tmain();
    
private:
    int m_exit_flag;
    std::string m_ipaddr;
    int m_port;
};

class TcpProcessThread:public gThread
{
public:
    /// - 
    ///constructor
    TcpServerThread(std::string ThreadName, int client_fd);

        /// - 
    ///destructor
    virtual ~TcpServerThread();

private:
    int m_client_fd;
};