//
// Created by vsoon on 2019/8/20.
//
#include "LogTool.h"
#include "FileWriteRead.h"

static int logV=5;
static bool loadLogV=false;

void setLogV(int level){
    logV=level;
}

int getLogV(){

    if(!loadLogV){
        loadLogV=true;
        //try to load logV in config
        FileWriteRead tFileWriteRead;
        std::string logVStr=tFileWriteRead.readStr(const_cast<char*>(std::string("config/logVStr.txt").c_str()));
        if(logVStr.size()>0){
             int lev= atoi(logVStr.c_str());
            logV=lev;
            LOGI("load logVStr:%d \n",lev);
        }else{
            LOGW("fail to load logVstr \n");
        }

    }
    return logV;
}
