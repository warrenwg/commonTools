#ifndef _TIMEMANAGER_H
#define _TIMEMANAGER_H
#include "CommonDefine.h"

#include "LogTool.h"

#ifdef USE_OCV
#include <opencv2/opencv.hpp>

#define initTic double start,end;
#define tic start=cv::getTickCount();
#define toc(s) LOGD("%s:%f \n",s,(cv::getTickCount()-start)*1000/cv::getTickFrequency());

#else



#endif



#endif