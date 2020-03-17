#ifndef _COMMONDEFINE_H
#define _COMMONDEFINE_H


#if (defined(__ANDROID)||defined(__ANDROID__))
#define MANDROID

#elif (defined(__linux)||defined(__linux__))
#define MLINUX

#elif _WIN32
#define MWINDOW

#endif




#endif