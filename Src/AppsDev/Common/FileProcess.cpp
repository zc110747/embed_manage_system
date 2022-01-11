/*
 * FileProcess.cpp
 *
 *  Created on: 2021 Dec 11 15:08:05
 */
#include <fstream>
#include <istream>
#include "FileProcess.hpp"

FileProcess::FileProcess(string file)
{
    is_vaild = false;
    Reader.clear();
    Writer.clear();
    filepath.swap(file);

    //open and reader current value
    reader();
}

void FileProcess::reader(void)
{
    std::ifstream ifs;
    ifs.open(filepath.c_str());

    Json::CharReaderBuilder builder;
    builder["collectComments"] = true;
    JSONCPP_STRING errs;
    if (!parseFromStream(builder, ifs, &Reader, &errs)) {
        is_vaild = false;
        std::cout << errs << std::endl;
    }
    else{
        is_vaild = true;
    }

    ifs.close();
}

void FileProcess::writer(void)
{
    std::string out = Writer.toStyledString();
    std::fstream fs(filepath, std::fstream::out | std::ios_base::trunc);
    fs.write(out.c_str(), out.size());
    fs.close();
}

FileProcess::~FileProcess()
{
    is_vaild = false;
    Reader.clear();
    Writer.clear();
}

bool FileProcess::get_json_member(string member, Json::Value *pIn, Json::Value *pOut)
{
    if(pIn->isMember(member))
        *pOut = (*pIn)[member];
    else
        return false;
    return true;
}