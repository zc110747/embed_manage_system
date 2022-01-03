/*
 * FileReader.hpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#pragma once

#include <string>
#include "ExternalPackages/jsoncpp/include/json/json.h"

using std::string;

class FileReader
{
public:
    FileReader(string file);
    ~FileReader();

    string get_file_path(void){
        return filepath;
    };

    bool is_reader_valid(void){
        return is_vaild;
    }
    
    bool get_json_member(string member, Json::Value *pIn, Json::Value *pOut);
protected:
    Json::Value root;

private:
    string filepath;
    bool is_vaild;

}