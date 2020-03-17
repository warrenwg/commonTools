#include "StringManager.h"


StringManager::StringManager()
{
}


StringManager::~StringManager()
{
}

std::vector<std::string> StringManager::vStringSplit(const  std::string s, const std::string delim)
{
    std::vector<std::string> elems;
    size_t pos = 0;
    size_t len = s.length();
    size_t delim_len = delim.length();
    if (delim_len == 0) return elems;
    while (pos < len)
    {
        int find_pos = s.find(delim, pos);
        if (find_pos < 0)
        {
            elems.push_back(s.substr(pos, len - pos));
            break;
        }
        elems.push_back(s.substr(pos, find_pos - pos));
        pos = find_pos + delim_len;
    }
    return elems;
}


int StringManager::findStringIndex(std::vector<std::string> list,std::string s){

    int index=-1;
    for (int i = 0; i < list.size(); ++i) {

//        LOGD("findString :%s %s \n",list[i].c_str(),s.c_str());
        int equal=strcmp(list[i].c_str(),s.c_str());
        if(equal==0){
            index=i;
            return index;
        }
    }

    return index;
}



