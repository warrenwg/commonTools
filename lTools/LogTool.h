#ifndef _LOG_TOOL_H
#define _LOG_TOOL_H
#include "CommonDefine.h"

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

#ifdef MANDROID
#include <android/log.h>
#endif

#include "stdio.h"

#define TAG __FILE__
#define TAGLINE __LINE__
#define TAGFUN __FUNCTION__

int getLogV();
void setLogV(int level);

#ifdef MANDROID

// #define LOGV(...) (getLogV() > 0 ? __android_log_print(ANDROID_LOG_VERBOSE, TAG, ##__VA_ARGS__) : 1)
// #define LOGD(...) (getLogV() > 1 ? __android_log_print(ANDROID_LOG_DEBUG, TAG, ##__VA_ARGS__) : 1)
// #define LOGI(...) (getLogV() > 2 ? __android_log_print(ANDROID_LOG_INFO, TAG, ##__VA_ARGS__) : 1)
// #define LOGW(...) (getLogV() > 3 ? __android_log_print(ANDROID_LOG_WARN, TAG, ##__VA_ARGS__) : 1)
// #define LOGE(...) (getLogV() > 4 ? __android_log_print(ANDROID_LOG_ERROR, TAG, ##__VA_ARGS__) : 1)

#define LOGV(...)                                                         \
    {                                                                     \
        if (getLogV() > 0)                                                \
        {                                                                 \
            char tag[512];                                                \
            sprintf(tag, "%s:fun:%s:line:%d", TAG, TAGFUN, TAGLINE);   \
            __android_log_print(ANDROID_LOG_VERBOSE, tag, ##__VA_ARGS__); \
        }                                                                 \
    }
#define LOGD(...)                                                       \
    {                                                                   \
        if (getLogV() > 0)                                              \
        {                                                               \
            char tag[512];                                              \
            sprintf(tag, "%s:fun:%s:line:%d", TAG, TAGFUN, TAGLINE); \
            __android_log_print(ANDROID_LOG_DEBUG, tag, ##__VA_ARGS__); \
        }                                                               \
    }
#define LOGI(...)                                                       \
    {                                                                   \
        if (getLogV() > 0)                                              \
        {                                                               \
            char tag[512];                                              \
            sprintf(tag, "%s:fun:%s:line:%d", TAG, TAGFUN, TAGLINE); \
            __android_log_print(ANDROID_LOG_INFO, tag, ##__VA_ARGS__);  \
        }                                                               \
    }
#define LOGW(...)                                                       \
    {                                                                   \
        if (getLogV() > 0)                                              \
        {                                                               \
            char tag[512];                                              \
            sprintf(tag, "%s:fun:%s:line:%d", TAG, TAGFUN, TAGLINE); \
            __android_log_print(ANDROID_LOG_WARN, tag, ##__VA_ARGS__);  \
        }                                                               \
    }
#define LOGE(...)                                                       \
    {                                                                   \
        if (getLogV() > 0)                                              \
        {                                                               \
            char tag[512];                                              \
            sprintf(tag, "%s:fun:%s:line:%d", TAG, TAGFUN, TAGLINE); \
            __android_log_print(ANDROID_LOG_ERROR, tag, ##__VA_ARGS__); \
        }                                                               \
    }

#else

#define LOGV(...)                                                       \
    {                                                                   \
        if (getLogV() > 0)                                              \
        {                                                               \
            char tag[512];                                              \
            sprintf(tag, "%s:fun:%s:line:%d", TAG, TAGFUN, TAGLINE); \
            printf("%s:", tag);                                         \
            printf(__VA_ARGS__);                                        \
        }                                                               \
    }
#define LOGD(...)                                                       \
    {                                                                   \
        if (getLogV() > 1)                                              \
        {                                                               \
            char tag[512];                                              \
            sprintf(tag, "%s:fun:%s:line:%d", TAG, TAGFUN, TAGLINE); \
            printf("%s:", tag);                                         \
            printf(__VA_ARGS__);                                        \
        }                                                               \
    }
#define LOGI(...)                                                       \
    {                                                                   \
        if (getLogV() > 2)                                              \
        {                                                               \
            char tag[512];                                              \
            sprintf(tag, "%s:fun:%s:line:%d", TAG, TAGFUN, TAGLINE); \
            printf("%s:", tag);                                         \
            printf(__VA_ARGS__);                                        \
        }                                                               \
    }
#define LOGW(...)                                                       \
    {                                                                   \
        if (getLogV() > 3)                                              \
        {                                                               \
            char tag[512];                                              \
            sprintf(tag, "%s:fun:%s:line:%d", TAG, TAGFUN, TAGLINE); \
            printf("%s:", tag);                                         \
            printf(__VA_ARGS__);                                        \
        }                                                               \
    }
#define LOGE(...)                                                       \
    {                                                                   \
        if (getLogV() > 4)                                              \
        {                                                               \
            char tag[512];                                              \
            sprintf(tag, "%s:fun:%s:line:%d", TAG, TAGFUN, TAGLINE); \
            printf("%s:", tag);                                         \
            printf(__VA_ARGS__);                                        \
        }                                                               \
    }

#endif

#endif