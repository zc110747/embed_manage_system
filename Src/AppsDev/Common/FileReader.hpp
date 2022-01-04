/*
 * FileReader.hpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#pragma once

#include <string>
#include "ExternalPackages/jsoncpp/include/json/json.h"
#include <iostream>

using std::string;

class FileReader
{
public:
    /// - 
    ///constructor
    FileReader(string file);

    /// - 
    ///destructor
    ~FileReader();

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
    Json::Value root;

    /// \fn get_json_member() 
    ///  - get json member through the string member name.
    /// \return true=read member success, false=read member fail.
    bool get_json_member(string member, Json::Value *pIn, Json::Value *pOut);

private:
    string filepath;
    bool is_vaild;
};
