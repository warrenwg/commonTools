//
// Created by vsoon on 2019/8/20.
//
#include "lTools/LogTool.h"
#include "lTools/FileWriteRead.h"
#include <iostream>

int main(){

    LOGD("test log \n");

    FileWriteRead tFileWriteRead;


    std::vector<std::vector<std::string > > rows={{"time","adc","pos"}};

    rows.push_back(std::vector<std::string>{std::to_string(111),std::to_string(222),std::to_string(333)});

    tFileWriteRead.writeCSV("foo.csv",rows);

    std::vector<std::vector<std::string > > outs;

    tFileWriteRead.readCSV("foo.csv",outs);

    tFileWriteRead.writeCSV("out.csv",outs);

    return 1;
}