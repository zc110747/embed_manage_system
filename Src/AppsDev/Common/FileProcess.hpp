/*
 * FileProcess.hpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#pragma once

#include <string>
#include "json/json.h"
#include <iostream>
#include <ostream>

using std::string;

class FileProcess
{
public:
    /// - 
    ///constructor
    FileProcess(string file);

    /// - 
    ///destructor
    ~FileProcess();

    /// \fn get_file_path() 
    ///  - called for get reader file name.
    /// \return current reader file name.
    string get_file_path(void){
        return filepath;
    };

    /// \fn is_reader_valid() 
    ///  - called for judge reader whether is ok.
    /// \return true=reader valid, false=reader invalid.
    bool is_reader_valid(void){
        return is_vaild;
    }

protected:
    Json::Value Reader;
    Json::Value Writer;

    /// \fn get_json_member() 
    ///  - get json member through the string member name.
    /// \return true=read member success, false=read member fail.
    bool get_json_member(string member, Json::Value *pIn, Json::Value *pOut);

    /// \fn reader() 
    ///  - called for get reader 
    /// \return true=reader valid, false=reader invalid.
    void reader(void);

    /// \fn writer() 
    ///  - called for get reader 
    /// \return true=reader valid, false=reader invalid.
    void writer(void);
private:
    string filepath;
    bool is_vaild;
};
