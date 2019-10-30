#ifndef _ANDROID_LOGD_H
#define _ANDROID_LOGD_H


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

#include <opencv2/opencv.hpp>
//#include <android/log.h>

#define TAG __FILE__

//#include <android/log.h>

int getLogV();
void setLogV(int level);

//#define LOGV(...) (getLogV()>0?__android_log_print(ANDROID_LOG_VERBOSE, TAG, ##__VA_ARGS__):1)
//#define LOGD(...) (getLogV()>1?__android_log_print(ANDROID_LOG_DEBUG, TAG, ##__VA_ARGS__):1)
//#define LOGI(...) (getLogV()>2?__android_log_print(ANDROID_LOG_INFO, TAG, ##__VA_ARGS__):1)
//#define LOGW(...) (getLogV()>3?__android_log_print(ANDROID_LOG_WARN, TAG, ##__VA_ARGS__):1)
//#define LOGE(...) (getLogV()>4?__android_log_print(ANDROID_LOG_ERROR, TAG, ##__VA_ARGS__):1)

#define LOGV printf
#define LOGD printf
#define LOGI printf
#define LOGW printf
#define LOGE printf

#define initTic double start,end;
#define tic start=cv::getTickCount();
#define toc(s) LOGD("%s:%f \n",s,(cv::getTickCount()-start)*1000/cv::getTickFrequency());

#endif
