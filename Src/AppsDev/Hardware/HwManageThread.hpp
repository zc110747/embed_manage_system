/*
 * HwManageThread.hpp
 *
 *  Created on: 2022 Jan 4 15:08:05
 */
#pragma once

#include "../Common/gThread.hpp"

class HwManageThread : public gThread
{
public:
    /// - 
    ///constructor
    HwManageThread(std::string ThreadName);

    /// - 
    ///destructor
    virtual ~HwManageThread();

    /// \fn Tmain() 
    ///  - main() for this thread - This method MUST be implemented in derived class
    /// \return true=success after executed, false=fail after executed
	bool Tmain();
};