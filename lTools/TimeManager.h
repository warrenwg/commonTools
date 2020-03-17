#ifndef _TIMEMANAGER_H
#define _TIMEMANAGER_H
#include "CommonDefine.h"

#include "LogTool.h"

#ifdef USE_OCV
#include <opencv2/opencv.hpp>

#define initTic double start,end;
#define tic start=cv::getTickCount();
#define toc(s) LOGD("%s:%f \n",s,(cv::getTickCount()-start)*1000/cv::getTickFrequency());


#define CREATECHECK(name) int name##0=0;

#define CHECKRUNNING(name,n) {name##0 = n;}

#define CHECKALIVE(name) {\
                                name##0 -- ; \
                                if(name##0<0){\
                                    LOGI("checkrunning: %s locked \n",#name);\
                                    LOGE("checkrunning: %s locked \n",#name);\
                                }\
                           }


#define CHECKFPS(s) {static double startFps=cv::getTickCount();LOGD(" %s fps:%f \n",s,1000/((cv::getTickCount()-startFps)*1000/cv::getTickFrequency()));startFps=cv::getTickCount();}



#else



#endif



#endif