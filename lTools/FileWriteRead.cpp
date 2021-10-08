#include "FileWriteRead.h"
#include <time.h>
#include "LogTool.h"
#include "csv2.hpp"
#include <iostream>
#include <fstream>

using namespace csv2;

FileWriteRead::FileWriteRead()
{
}
    
FileWriteRead::~FileWriteRead()
{
}

void FileWriteRead::writeBin(char *path, void *data, int datalen, int oneDataSize)
{

    FILE *pFile = NULL;
    if (pFile == NULL)
    {
        pFile = fopen(path, "wb");
    }
    if (pFile != NULL)
    {
        if (0 == fwrite(data, datalen, oneDataSize, pFile))
        {
            LOGE("%s fwrite err\r\n", path);
        }
        fclose(pFile);
    }
}

void FileWriteRead::readBin(char *path, void *data, int datalen, int oneDataSize)
{

    FILE *pFile = NULL;
    pFile = fopen(path, "rb");
    if (pFile != NULL)
    {
        if (0 == fread(data, datalen, oneDataSize, pFile))
        {
            LOGE("%s read file error \n", path);
        }

        fclose(pFile);
    }
}

void FileWriteRead::writeStr(char *path, std::string str)
{
    std::ofstream o_file(path, std::ios::trunc);

    if (!o_file.is_open())
    {
        LOGE("error,write file is not valid :%s \n", path);
        return;
    }

    o_file << str << std::endl;
    o_file.close();
}

std::string FileWriteRead::readStr(char *path)
{
    std::ifstream fin(path);

    if (!fin.is_open())
    {
        LOGE("error,read file is not valid :%s \n", path);
        return "";
    }

    std::string s;
    getline(fin, s);
    fin.close();
    return s;
}


void FileWriteRead::writeOneLine(char *path, std::string strLine)
{
    std::ofstream o_file(path, std::ios::app);

    if (!o_file.is_open())
    {
        LOGE("error,write file is not valid :%s \n", path);
        return;
    }

    o_file << strLine << std::endl;
    o_file.close();
}


int FileWriteRead::getDevice(const char* path,int& value){

    value = 0;
    char cStr[16];
    bzero(cStr,sizeof(cStr));

    FILE* pFile = NULL;
    if (pFile == NULL)
    {
        pFile = fopen(path, "r");
    }
    if (pFile != NULL)
    {
        size_t len= fread(cStr, sizeof(cStr), 1, pFile);
        if (len!=1)
        {
            LOGD("getDevice %s len:%zu %s\n",path,len,cStr);
        }
        value=atoi(cStr);
        LOGD("readDevice:path:%s value:%s value:%d len:%zu \n",path,cStr,value,len);

        fclose(pFile);
        return 1;
    }
    LOGE("Can not open output file :%s \n",path);
    return -1;
}

int FileWriteRead::getDevice(const char* path,char* value){

    memset(value, 0, sizeof(value));
    FILE* pFile = NULL;
    if (pFile == NULL)
    {
        pFile = fopen(path, "r");
    }
    if (pFile != NULL)
    {
        size_t len= fread(value, sizeof(value), 1, pFile);
        if (len!=1)
        {
            LOGD("getDevice %s len:%zu %s\n",path,len,value);
        }
        LOGD("readDevice:path:%s value:%s len:%zu \n",path,value,len);
        fclose(pFile);
        return 1;
    }
    return -1;
}



int FileWriteRead::setDevicePlus(const char* path,int value) {
    char cStr[16];
    memset(cStr, 0, sizeof(cStr));
    sprintf(cStr, "%d\n", value);

    FILE* pFile = NULL;
    if (pFile == NULL)
    {
        pFile = fopen(path, "w+");
    }
    if (pFile != NULL)
    {
        if (1 != fwrite(cStr, sizeof(cStr), 1, pFile))
        {
            // LOGE("fwrite err %s %s \n",path,cStr);
        }
        LOGD("fwrite %s %s \n",path,cStr);        
        fclose(pFile);
        return 1;
    }
    return -1;
}

int FileWriteRead::setDevice(const char* path,int value) {
    char cStr[16];
    memset(cStr, 0, sizeof(cStr));
    sprintf(cStr, "%d\n", value);

    FILE* pFile = NULL;
    if (pFile == NULL)
    {
        pFile = fopen(path, "w");
    }
    if (pFile != NULL)
    {
        if (1 != fwrite(cStr, sizeof(cStr), 1, pFile))
        {
            // LOGE("fwrite err %s %s \n",path,cStr);
        }
        LOGD("fwrite %s %s \n",path,cStr);        
        fclose(pFile);
        return 1;
    }
    return -1;
}


int FileWriteRead::setDevice(const char* path,char* value) {
    char cStr[256];
    memset(cStr, 0, sizeof(cStr));
    sprintf(cStr, "%s\n", value);

    LOGI("setDevice:%s %s\n",path,value);

    FILE* pFile = NULL;
    if (pFile == NULL)
    {
        pFile = fopen(path, "w");
    }
    if (pFile != NULL)
    {
        if (1 != fwrite(value, sizeof(value), 1, pFile))
        {
            LOGE("fwrite err %s %s \n",path,cStr);
        }
        LOGD("fwrite success %s %s \n",path,cStr);    
        fclose(pFile);
        return 1;
    }
    return -1;
}




int FileWriteRead::getProp(const char* prop,const char* defaultValue,int& value){

    FILE *fp = NULL;
    char data[100] = {'0'};
    strcpy(data,defaultValue);
    char command[256];
    sprintf(command,"getprop %s\n",prop);
    fp = popen(command, "r");
    if (fp == NULL)
    {
        LOGE("popen error %s \n",prop);
        return -1;
    }

    while (fgets(data, sizeof(data), fp) != NULL)
    {
        // LOGD("%s", data);
    }
    pclose(fp);

    std::string dataStr=std::string(data);
    if(dataStr.empty())
    {
        LOGD("isempty by empty ,set defaultValue\n");
        strcpy(data,defaultValue);
    }
    else
    {
        if(dataStr.size()>0){
            if(data[0]=='\n'){
                LOGD("isempty by data[0]=n ,set defaultValue\n");
                strcpy(data,defaultValue);
            }
        }
    }
    value = atoi(data);
    LOGD("prop:%s getProp:%s value:%d\n",prop,data,value);

    return 1;
}


int FileWriteRead::setProp(const char* prop,int value){

    FILE *fp = NULL;
    char data[100] = {'0'};
    char command[256];
    sprintf(command,"setprop %s %d\n",prop,value);
    fp = popen(command, "r");
    if (fp == NULL)
    {
        LOGE("popen error %s \n",prop);
        return -1;
    }
    pclose(fp);

    return 1;
}


int FileWriteRead::writeCSV(std::string path,std::vector<std::vector<std::string> > datas){

    std::ofstream stream(path.c_str());
    Writer<delimiter<','>> writer(stream);
    writer.write_rows(datas);
    stream.close(); 

    return 1;
}

int FileWriteRead::readCSV(std::string path,std::vector<std::vector<std::string> >& datas){

    csv2::Reader<delimiter<','>, 
                quote_character<'"'>, 
                first_row_is_header<true>,
                trim_policy::trim_whitespace> csv;

    datas.clear();
    if (csv.mmap(path.c_str())) {
        const auto header = csv.header();
        std::vector<std::string > oneDatas0;
        for (const auto cell: header) {
            std::string value;
            cell.read_value(value);
            oneDatas0.push_back(value);
        }
        datas.push_back(oneDatas0);
        for (const auto row: csv) {
            std::vector<std::string > oneDatas1;
            for (const auto cell: row) {
                std::string value;
                cell.read_value(value);
                oneDatas1.push_back(value);
            }
            if(oneDatas1.size()==oneDatas0.size()){
                datas.push_back(oneDatas1);
            }
        }
    }
    else
    {
        LOGE("not read valid csv file\n");
        return -1;
    }
    
    return 1;
}
