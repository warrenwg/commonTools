//
// Created by vsoon on 2019/8/20.
//
#include "AndroidLog.h"

static int logV=5;

void setLogV(int level){
    logV=level;
}

int getLogV(){
    return logV;
}
