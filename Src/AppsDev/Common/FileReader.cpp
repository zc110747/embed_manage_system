/*
 * FileReader.cpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#include <fstream>
#include <istream>
#include "FileReader.hpp"

FileReader::FileReader(string file)
{
    std::ifstream ifs;
    ifs.open(file.c_str());

    Json::CharReaderBuilder builder;
    builder["collectComments"] = true;
    JSONCPP_STRING errs;
    if (!parseFromStream(builder, ifs, &root, &errs)) {
        is_vaild = false;
        std::cout << errs << std::endl;
    }
    else{
        is_vaild = true;
        std::cout << root << std::endl;
        ifs.close();
    }
    filepath.swap(file);
}

FileReader::~FileReader()
{
    is_vaild = false;
    root.clear();
}

bool FileReader::get_json_member(string member, Json::Value *pIn, Json::Value *pOut)
{
    if(pIn->isMember(member))
    {
        *pOut = (*pIn)[member];
    }
    else
        return false;
}