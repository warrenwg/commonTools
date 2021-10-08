#ifndef _TIMEMANAGER_H
#define _TIMEMANAGER_H
#include "CommonDefine.h"

#include "LogTool.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <cstdint>


int64_t mGetTickCount(void);

double mGetTickFrequency(void);




#define initTic double start,end;
#define tic start=mGetTickCount();
#define toc(s) LOGD("toctime:%s:%f \n",s,(mGetTickCount()-start)*1000/mGetTickFrequency());
#define toic(s) LOGI("toctime:%s:%f \n",s,(mGetTickCount()-start)*1000/mGetTickFrequency());
#define tisp(s) LOGI("timestamp:%s:%f \n",s,mGetTickCount()*1000/mGetTickFrequency()) ;


#define CREATECHECK(name) int name##0=0;

#define CHECKRUNNING(name,n) {name##0 = n;}

#define CHECKALIVE(name) {\
                                name##0 -- ; \
                                if(name##0<0){\
                                    LOGW("checkrunning: %s locked \n",#name);\
                                }\
                           }


//#define CHECKDELTAFPS(s) {static double startFps=cv::getTickCount();LOGD(" %s fps:%f \n",s,1000/((cv::getTickCount()-startFps)*1000/cv::getTickFrequency()));startFps=cv::getTickCount();}

#define CHECKDELTA(s) {static double startFps=mGetTickCount();LOGD(" %s delta:%f \n",s,(mGetTickCount()-startFps)*1000/mGetTickFrequency());startFps=mGetTickCount();}


#define CHECKFPS(s) \
{\
    static int m_fps = 0;\
    static double m_lastTime = mGetTickCount(); \
    static int m_frameCount = 0;\
    ++m_frameCount;\
    double m_curTime =mGetTickCount();\
    double deltaTime=((m_curTime - m_lastTime)*1000/mGetTickFrequency());\
    if ( deltaTime> 1000)\
    {\
        m_fps = m_frameCount;\
        m_frameCount = 0;\
        m_lastTime = m_curTime;\
    }\
    LOGD(" %s fps:%d %f\n",s,m_fps,deltaTime);\
}

#else



#endif

