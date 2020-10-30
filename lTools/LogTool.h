#ifndef _LOG_TOOL_H
#define _LOG_TOOL_H
#include "CommonDefine.h"
#include "stdio.h"
#include "cstring"

/*****************这段警告是针对所以android native库的
*  重要提示:
*      这个文件是在Android NDK 1.5版本以上的一部分。
*      如果在第三方源码或二进制代码中依赖此定义需要遵守：
*      - 不要修改枚举（除了你想新增一个32位的值）
*      - 不要修改常量或者函数式宏
*      - 不要改变方法的签名
*      - 不要改变结构体的前后顺序或大小
*/

/* 支持Android内核程序将消息发送到日志缓冲区，稍后将可以在logcat浏览日志。
 * 每一个日志必须包含
 *      - 一个优先级
 *      - 一个标签
 *      - 一些文字
 * 标签通常对应于发出日志消息的组件，应该小且合理。
 *
 * 日志消息可能被特定实现截断（例如：最大1023个字符）
 *
 * 如果日志消息没有以"\n"结尾那么将会自动追加。不可能出现多个日志在Logcat中被打印成一行。
 *
 * 请适度的使用LOGS
 *      - 发送日志消息吃CPU和减缓你的应用程序和系统。
 *      - 循环日志缓冲区很小(<64kb),发送很多消息可能推迟系统中剩下的其他重要的日志消息。
 *      - 在版本发布,只有发送日志消息来考虑异常情况。
 * 提示：这些方法必须实现/system/lib/liblog.so
 */



#if defined(MANDROID)|| defined(__ANDROID__) || defined(__ANDROID_NDK__)
#include <android/log.h>
#endif


#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)

#define TAG __FILENAME__
#define TAGLINE __LINE__
#define TAGFUN __FUNCTION__

int getLogV();
void setLogV(int level);

#if defined(MANDROID)|| defined(__ANDROID__)|| defined(__ANDROID_NDK__)

// #define LOGV(...) (getLogV() > 0 ? __android_log_print(ANDROID_LOG_VERBOSE, TAG, ##__VA_ARGS__) : 1)
// #define LOGD(...) (getLogV() > 1 ? __android_log_print(ANDROID_LOG_DEBUG, TAG, ##__VA_ARGS__) : 1)
// #define LOGI(...) (getLogV() > 2 ? __android_log_print(ANDROID_LOG_INFO, TAG, ##__VA_ARGS__) : 1)
// #define LOGW(...) (getLogV() > 3 ? __android_log_print(ANDROID_LOG_WARN, TAG, ##__VA_ARGS__) : 1)
// #define LOGE(...) (getLogV() > 4 ? __android_log_print(ANDROID_LOG_ERROR, TAG, ##__VA_ARGS__) : 1)

#define LOGV(...)                                                         \
    {                                                                     \
        if (getLogV() > 4)                                                \
        {                                                                 \
            char tag[512];                                                \
            sprintf(tag, "%s:%s:%d - >", TAG, TAGFUN, TAGLINE);   \
            __android_log_print(ANDROID_LOG_VERBOSE, tag, ##__VA_ARGS__); \
        }                                                                 \
    }
#define LOGD(...)                                                       \
    {                                                                   \
        if (getLogV() > 3)                                              \
        {                                                               \
            char tag[512];                                              \
            sprintf(tag, "%s:%s:%d - >", TAG, TAGFUN, TAGLINE); \
            __android_log_print(ANDROID_LOG_DEBUG, tag, ##__VA_ARGS__); \
        }                                                               \
    }
#define LOGI(...)                                                       \
    {                                                                   \
        if (getLogV() > 2)                                              \
        {                                                               \
            char tag[512];                                              \
            sprintf(tag, "%s:%s:%d - >", TAG, TAGFUN, TAGLINE); \
            __android_log_print(ANDROID_LOG_INFO, tag, ##__VA_ARGS__);  \
        }                                                               \
    }
#define LOGW(...)                                                       \
    {                                                                   \
        if (getLogV() > 1)                                              \
        {                                                               \
            char tag[512];                                              \
            sprintf(tag, "%s:%s:%d - >", TAG, TAGFUN, TAGLINE); \
            __android_log_print(ANDROID_LOG_WARN, tag, ##__VA_ARGS__);  \
        }                                                               \
    }
#define LOGE(...)                                                       \
    {                                                                   \
        if (getLogV() > 0)                                              \
        {                                                               \
            char tag[512];                                              \
            sprintf(tag, "%s:%s:%d - >", TAG, TAGFUN, TAGLINE); \
            __android_log_print(ANDROID_LOG_ERROR, tag, ##__VA_ARGS__); \
        }                                                               \
    }

#else

#define HL_RED "\033[1;31m" //高亮红色 
#define HL_GREEN "\033[1;32m" //高亮绿色 
#define HL_YEL "\033[1;33m" //高亮黄色 
#define BROWN "\033[0;33m" //灰色



#define LOGV(...)                                                       \
    {                                                                   \
        if (getLogV() > 4)                                              \
        {                                                               \
            char tag[512];                                              \
            sprintf(tag, "verbase:%s:%s:%d - >", TAG, TAGFUN, TAGLINE); \
            printf(BROWN "%s:", tag);                                         \
            printf(__VA_ARGS__);                                        \
        }                                                               \
    }
#define LOGD(...)                                                       \
    {                                                                   \
        if (getLogV() > 3)                                              \
        {                                                               \
            char tag[512];                                              \
            sprintf(tag, "debug:%s:%s:%d - >", TAG, TAGFUN, TAGLINE); \
            printf(BROWN "%s:", tag);                                         \
            printf(__VA_ARGS__);                                        \
        }                                                               \
    }
#define LOGI(...)                                                       \
    {                                                                   \
        if (getLogV() > 2)                                              \
        {                                                               \
            char tag[512];                                              \
            sprintf(tag, "info:%s:%s:%d - >", TAG, TAGFUN, TAGLINE); \
            printf(HL_GREEN "%s:", tag);                                         \
            printf(__VA_ARGS__);                                        \
        }                                                               \
    }
#define LOGW(...)                                                       \
    {                                                                   \
        if (getLogV() > 1)                                              \
        {                                                               \
            char tag[512];                                              \
            sprintf(tag, "warn:%s:%s:%d - >", TAG, TAGFUN, TAGLINE); \
            printf(HL_YEL "%s:", tag);                                         \
            printf(__VA_ARGS__);                                        \
        }                                                               \
    }
#define LOGE(...)                                                       \
    {                                                                   \
        if (getLogV() > 0)                                              \
        {                                                               \
            char tag[512];                                              \
            sprintf(tag, "error:%s:%s:%d - >", TAG, TAGFUN, TAGLINE); \
            printf(HL_RED "%s:", tag);                                         \
            printf(__VA_ARGS__);                                        \
        }                                                               \
    }


#define TIP LOGD("TEST\n");    

#endif

#endif