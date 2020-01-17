#ifndef _XLOG_H
#define _XLOG_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdio.h>

#define LOG_LEVEL_VERBOSE (0)
#define LOG_LEVEL_DEBUG (1)
#define LOG_LEVEL_INFO (2)
#define LOG_LEVEL_WARN (3)
#define LOG_LEVEL_ERROR (4)
#define LOG_LEVEL_OFF (5)
//#define LOG_CONFIG_LEVEL LOG_LEVEL_VERBOSE
extern int LOG_CONFIG_LEVEL;

#define LOG_TARGET_ANDROID (0x1 << 1) // NOLINT(hicpp-signed-bitwise)
#define LOG_TARGET_CONSOLE (0x1 << 2) // NOLINT(hicpp-signed-bitwise)
//#define LOG_TARGET (LOG_TARGET_ANDROID | LOG_TARGET_CONSOLE)
extern int LOG_CONFIG_TARGET;

#define LOG_LINE_STAR "****************************************************************"
#define LOG_TAG_DEFAULT "XTest"
#define CONSOLE_LOG_CONFIG_METHOD printf

//for MSC
#ifdef _MSC_VER

#include <windows.h>
static long long time_stamp_current(){
    SYSTEMTIME sys_time;
    time_t ltime;
    time(&ltime);
    GetLocalTime(&sys_time);
    return ltime * 1000 + sys_time.wMilliseconds;
}

#define __func__ __FUNCTION__
#define CONSOLE_LOG_CONFIG_NEW_LINE_FORMAT "\r\n"

    //fix MSC macro comma. https://stackoverflow.com/questions/5588855/standard-alternative-to-gccs-va-args-trick
//#define BAR_HELPER(fmt, ...) printf(fmt "\n", __VA_ARGS__)
//#define BAR(...) BAR_HELPER(__VA_ARGS__, 0)

#define CONSOLE_LOG_NO_NEW_LINE_HELPER(level, fmt, ...) if(level >= LOG_CONFIG_LEVEL) { CONSOLE_LOG_CONFIG_METHOD(fmt, __VA_ARGS__); }
#define CONSOLE_LOG_NO_NEW_LINE(level, ...) CONSOLE_LOG_NO_NEW_LINE_HELPER(level, __VA_ARGS__, 0)

#define CONSOLE_LOGV_NO_NEW_LINE(...) CONSOLE_LOG_NO_NEW_LINE(LOG_LEVEL_VERBOSE,__VA_ARGS__)
#define CONSOLE_LOGD_NO_NEW_LINE(...) CONSOLE_LOG_NO_NEW_LINE(LOG_LEVEL_DEBUG,__VA_ARGS__)
#define CONSOLE_LOGI_NO_NEW_LINE(...) CONSOLE_LOG_NO_NEW_LINE(LOG_LEVEL_INFO,__VA_ARGS__)
#define CONSOLE_LOGW_NO_NEW_LINE(...) CONSOLE_LOG_NO_NEW_LINE(LOG_LEVEL_WARN,__VA_ARGS__)
#define CONSOLE_LOGE_NO_NEW_LINE(...) CONSOLE_LOG_NO_NEW_LINE(LOG_LEVEL_ERROR,__VA_ARGS__)
#define CONSOLE_LOGV(fmt, ...) CONSOLE_LOG_NO_NEW_LINE(LOG_LEVEL_VERBOSE,"[%lld][V]" fmt CONSOLE_LOG_CONFIG_NEW_LINE_FORMAT,time_stamp_current(),__VA_ARGS__)
#define CONSOLE_LOGD(fmt, ...) CONSOLE_LOG_NO_NEW_LINE(LOG_LEVEL_DEBUG,"[%lld][D]" fmt CONSOLE_LOG_CONFIG_NEW_LINE_FORMAT,time_stamp_current(),__VA_ARGS__)
#define CONSOLE_LOGI(fmt, ...) CONSOLE_LOG_NO_NEW_LINE(LOG_LEVEL_INFO,"[%lld][I]" fmt CONSOLE_LOG_CONFIG_NEW_LINE_FORMAT,time_stamp_current(),__VA_ARGS__)
#define CONSOLE_LOGW(fmt, ...) CONSOLE_LOG_NO_NEW_LINE(LOG_LEVEL_WARN,"[%lld][W]" fmt CONSOLE_LOG_CONFIG_NEW_LINE_FORMAT,time_stamp_current(),__VA_ARGS__)
#define CONSOLE_LOGE(fmt, ...) CONSOLE_LOG_NO_NEW_LINE(LOG_LEVEL_ERROR,"[%lld][E]" fmt CONSOLE_LOG_CONFIG_NEW_LINE_FORMAT,time_stamp_current(),__VA_ARGS__)
#define CONSOLE_TLOGV(tag, fmt, ...)  CONSOLE_LOGV("[%s] " fmt, tag, ##__VA_ARGS__)
#define CONSOLE_TLOGD(tag, fmt, ...)  CONSOLE_LOGD("[%s] " fmt, tag, ##__VA_ARGS__)
#define CONSOLE_TLOGI(tag, fmt, ...)  CONSOLE_LOGI("[%s] " fmt, tag, ##__VA_ARGS__)
#define CONSOLE_TLOGW(tag, fmt, ...)  CONSOLE_LOGW("[%s] " fmt, tag, ##__VA_ARGS__)
#define CONSOLE_TLOGE(tag, fmt, ...)  CONSOLE_LOGE("[%s] " fmt, tag, ##__VA_ARGS__)
#define CONSOLE_TLOGV_TRACE(tag, fmt, ...)  CONSOLE_TLOGV(tag, "[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define CONSOLE_TLOGD_TRACE(tag, fmt, ...)  CONSOLE_TLOGD(tag, "[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define CONSOLE_TLOGI_TRACE(tag, fmt, ...)  CONSOLE_TLOGI(tag, "[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define CONSOLE_TLOGW_TRACE(tag, fmt, ...)  CONSOLE_TLOGW(tag, "[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define CONSOLE_TLOGE_TRACE(tag, fmt, ...)  CONSOLE_TLOGE(tag, "[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

#else

#include <sys/time.h>

static long long time_stamp_current() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    return te.tv_sec * 1000LL + te.tv_usec / 1000;
}

#define CONSOLE_LOG_CONFIG_NEW_LINE_FORMAT "\n"
#define CONSOLE_LOGV_NO_NEW_LINE(...) if(LOG_LEVEL_VERBOSE >= LOG_CONFIG_LEVEL ) { CONSOLE_LOG_CONFIG_METHOD(__VA_ARGS__); }
#define CONSOLE_LOGD_NO_NEW_LINE(...) if(LOG_LEVEL_DEBUG >= LOG_CONFIG_LEVEL) { CONSOLE_LOG_CONFIG_METHOD(__VA_ARGS__); }
#define CONSOLE_LOGI_NO_NEW_LINE(...) if(LOG_LEVEL_INFO >= LOG_CONFIG_LEVEL) { CONSOLE_LOG_CONFIG_METHOD(__VA_ARGS__); }
#define CONSOLE_LOGW_NO_NEW_LINE(...) if(LOG_LEVEL_WARN >= LOG_CONFIG_LEVEL) { CONSOLE_LOG_CONFIG_METHOD(__VA_ARGS__); }
#define CONSOLE_LOGE_NO_NEW_LINE(...) if(LOG_LEVEL_ERROR >= LOG_CONFIG_LEVEL) { CONSOLE_LOG_CONFIG_METHOD(__VA_ARGS__); }
#define CONSOLE_LOGV(fmt, ...) CONSOLE_LOGV_NO_NEW_LINE("[%lld][V]" fmt CONSOLE_LOG_CONFIG_NEW_LINE_FORMAT, time_stamp_current(), ##__VA_ARGS__)
#define CONSOLE_LOGD(fmt, ...) CONSOLE_LOGD_NO_NEW_LINE("[%lld][D]" fmt CONSOLE_LOG_CONFIG_NEW_LINE_FORMAT, time_stamp_current(), ##__VA_ARGS__)
#define CONSOLE_LOGI(fmt, ...) CONSOLE_LOGI_NO_NEW_LINE("[%lld][I]" fmt CONSOLE_LOG_CONFIG_NEW_LINE_FORMAT, time_stamp_current(), ##__VA_ARGS__)
#define CONSOLE_LOGW(fmt, ...) CONSOLE_LOGW_NO_NEW_LINE("[%lld][W]" fmt CONSOLE_LOG_CONFIG_NEW_LINE_FORMAT, time_stamp_current(), ##__VA_ARGS__)
#define CONSOLE_LOGE(fmt, ...) CONSOLE_LOGE_NO_NEW_LINE("[%lld][E]" fmt CONSOLE_LOG_CONFIG_NEW_LINE_FORMAT, time_stamp_current(), ##__VA_ARGS__)
#define CONSOLE_TLOGV(tag, fmt, ...)  CONSOLE_LOGV("[%s] " fmt, tag, ##__VA_ARGS__)
#define CONSOLE_TLOGD(tag, fmt, ...)  CONSOLE_LOGD("[%s] " fmt, tag, ##__VA_ARGS__)
#define CONSOLE_TLOGI(tag, fmt, ...)  CONSOLE_LOGI("[%s] " fmt, tag, ##__VA_ARGS__)
#define CONSOLE_TLOGW(tag, fmt, ...)  CONSOLE_LOGW("[%s] " fmt, tag, ##__VA_ARGS__)
#define CONSOLE_TLOGE(tag, fmt, ...)  CONSOLE_LOGE("[%s] " fmt, tag, ##__VA_ARGS__)
#define CONSOLE_TLOGV_TRACE(tag, fmt, ...)  CONSOLE_TLOGV(tag, "[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define CONSOLE_TLOGD_TRACE(tag, fmt, ...)  CONSOLE_TLOGD(tag, "[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define CONSOLE_TLOGI_TRACE(tag, fmt, ...)  CONSOLE_TLOGI(tag, "[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define CONSOLE_TLOGW_TRACE(tag, fmt, ...)  CONSOLE_TLOGW(tag, "[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define CONSOLE_TLOGE_TRACE(tag, fmt, ...)  CONSOLE_TLOGE(tag, "[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

#endif // _MSC_VER


#if defined(__ANDROID__)

#include <android/log.h>

#define A_TLOGV(TAG, fmt, ...) if(LOG_LEVEL_VERBOSE >= LOG_CONFIG_LEVEL) {\
        __android_log_print(ANDROID_LOG_VERBOSE, TAG, fmt, ##__VA_ARGS__);\
    }
#define A_TLOGD(TAG, fmt, ...) if(LOG_LEVEL_DEBUG >= LOG_CONFIG_LEVEL) {\
        __android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, ##__VA_ARGS__);\
    }
#define A_TLOGI(TAG, fmt, ...) if(LOG_LEVEL_INFO >= LOG_CONFIG_LEVEL) {\
        __android_log_print(ANDROID_LOG_INFO, TAG, fmt, ##__VA_ARGS__);\
    }
#define A_TLOGW(TAG, fmt, ...) if(LOG_LEVEL_WARN >= LOG_CONFIG_LEVEL) {\
        __android_log_print(ANDROID_LOG_WARN, TAG, fmt, ##__VA_ARGS__);\
    }
#define A_TLOGE(TAG, fmt, ...) if(LOG_LEVEL_ERROR >= LOG_CONFIG_LEVEL) {\
        __android_log_print(ANDROID_LOG_ERROR, TAG, fmt, ##__VA_ARGS__);\
    }

#define A_TLOGV_TRACE(TAG, fmt, ...) A_TLOGV(TAG, "[%s:%d] " fmt , __func__, __LINE__, ##__VA_ARGS__)
#define A_TLOGD_TRACE(TAG, fmt, ...) A_TLOGD(TAG, "[%s:%d] " fmt , __func__, __LINE__, ##__VA_ARGS__)
#define A_TLOGI_TRACE(TAG, fmt, ...) A_TLOGI(TAG, "[%s:%d] " fmt , __func__, __LINE__, ##__VA_ARGS__)
#define A_TLOGW_TRACE(TAG, fmt, ...) A_TLOGW(TAG, "[%s:%d] " fmt , __func__, __LINE__, ##__VA_ARGS__)
#define A_TLOGE_TRACE(TAG, fmt, ...) A_TLOGE(TAG, "[%s:%d] " fmt , __func__, __LINE__, ##__VA_ARGS__)

#define A_LOGV(...) A_TLOGV(LOG_TAG_DEFAULT, ##__VA_ARGS__)
#define A_LOGD(...) A_TLOGD(LOG_TAG_DEFAULT, ##__VA_ARGS__)
#define A_LOGI(...) A_TLOGI(LOG_TAG_DEFAULT, ##__VA_ARGS__)
#define A_LOGW(...) A_TLOGW(LOG_TAG_DEFAULT, ##__VA_ARGS__)
#define A_LOGE(...) A_TLOGE(LOG_TAG_DEFAULT, ##__VA_ARGS__)

//Android logcat echo log is new line, so redirect NO_NEW_LINE to default.
#define A_LOGV_NO_NEW_LINE(...) A_LOGV(...)
#define A_LOGD_NO_NEW_LINE(...) A_LOGD(...)
#define A_LOGI_NO_NEW_LINE(...) A_LOGI(...)
#define A_LOGW_NO_NEW_LINE(...) A_LOGW(...)
#define A_LOGE_NO_NEW_LINE(...) A_LOGE(...)

#else

#define A_TLOGV(TAG, fmt, ...)
#define A_TLOGD(TAG, fmt, ...)
#define A_TLOGI(TAG, fmt, ...)
#define A_TLOGW(TAG, fmt, ...)
#define A_TLOGE(TAG, fmt, ...)

#define A_TLOGV_TRACE(TAG, fmt, ...)
#define A_TLOGD_TRACE(TAG, fmt, ...)
#define A_TLOGI_TRACE(TAG, fmt, ...)
#define A_TLOGW_TRACE(TAG, fmt, ...)
#define A_TLOGE_TRACE(TAG, fmt, ...)

#define A_LOGV(...)
#define A_LOGD(...)
#define A_LOGI(...)
#define A_LOGW(...)
#define A_LOGE(...)

#define A_LOGV_NO_NEW_LINE(...)
#define A_LOGD_NO_NEW_LINE(...)
#define A_LOGI_NO_NEW_LINE(...)
#define A_LOGW_NO_NEW_LINE(...)
#define A_LOGE_NO_NEW_LINE(...)

#endif // defined(__ANDROID__)


#define LOGV_NO_NEW_LINE(...) do{ \
    if(LOG_CONFIG_TARGET & LOG_TARGET_CONSOLE){CONSOLE_LOGV_NO_NEW_LINE(##__VA_ARGS__);}\
    if(LOG_CONFIG_TARGET & LOG_TARGET_ANDROID){A_LOGV_NO_NEW_LINE(##__VA_ARGS__);}\
}while(0);
#define LOGD_NO_NEW_LINE(...) do{ \
    if(LOG_CONFIG_TARGET & LOG_TARGET_CONSOLE){CONSOLE_LOGD_NO_NEW_LINE(##__VA_ARGS__);}\
    if(LOG_CONFIG_TARGET & LOG_TARGET_ANDROID){A_LOGD_NO_NEW_LINE(##__VA_ARGS__);}\
}while(0);
#define LOGI_NO_NEW_LINE(...) do{ \
    if(LOG_CONFIG_TARGET & LOG_TARGET_CONSOLE){CONSOLE_LOGI_NO_NEW_LINE(##__VA_ARGS__);}\
    if(LOG_CONFIG_TARGET & LOG_TARGET_ANDROID){A_LOGI_NO_NEW_LINE(##__VA_ARGS__);}\
}while(0);
#define LOGW_NO_NEW_LINE(...) do{ \
    if(LOG_CONFIG_TARGET & LOG_TARGET_CONSOLE){CONSOLE_LOGW_NO_NEW_LINE(##__VA_ARGS__);}\
    if(LOG_CONFIG_TARGET & LOG_TARGET_ANDROID){A_LOGW_NO_NEW_LINE(##__VA_ARGS__);}\
}while(0);
#define LOGE_NO_NEW_LINE(...) do{ \
if(LOG_CONFIG_TARGET & LOG_TARGET_CONSOLE){CONSOLE_LOGE_NO_NEW_LINE(##__VA_ARGS__);}\
if(LOG_CONFIG_TARGET & LOG_TARGET_ANDROID){A_LOGE_NO_NEW_LINE(##__VA_ARGS__);}\
}while(0);

#define LOGV(fmt, ...) do{ \
    if(LOG_CONFIG_TARGET & LOG_TARGET_CONSOLE){CONSOLE_LOGV(fmt, ##__VA_ARGS__);}\
    if(LOG_CONFIG_TARGET & LOG_TARGET_ANDROID){A_LOGV(fmt, ##__VA_ARGS__);}\
}while(0);
#define LOGD(fmt, ...) do{ \
    if(LOG_CONFIG_TARGET & LOG_TARGET_CONSOLE){CONSOLE_LOGD(fmt, ##__VA_ARGS__);}\
    if(LOG_CONFIG_TARGET & LOG_TARGET_ANDROID){A_LOGD(fmt, ##__VA_ARGS__);}\
}while(0);
#define LOGI(fmt, ...) do{ \
    if(LOG_CONFIG_TARGET & LOG_TARGET_CONSOLE){CONSOLE_LOGI(fmt, ##__VA_ARGS__);}\
    if(LOG_CONFIG_TARGET & LOG_TARGET_ANDROID){A_LOGI(fmt, ##__VA_ARGS__);}\
}while(0);
#define LOGW(fmt, ...) do{ \
    if(LOG_CONFIG_TARGET & LOG_TARGET_CONSOLE){CONSOLE_LOGW(fmt, ##__VA_ARGS__);}\
    if(LOG_CONFIG_TARGET & LOG_TARGET_ANDROID){A_LOGW(fmt, ##__VA_ARGS__);}\
}while(0);
#define LOGE(fmt, ...) do{ \
    if(LOG_CONFIG_TARGET & LOG_TARGET_CONSOLE){CONSOLE_LOGE(fmt, ##__VA_ARGS__);}\
    if(LOG_CONFIG_TARGET & LOG_TARGET_ANDROID){A_LOGE(fmt, ##__VA_ARGS__);}\
}while(0);

#define TLOGV(tag, fmt, ...)  do{ \
    if(LOG_CONFIG_TARGET & LOG_TARGET_CONSOLE){CONSOLE_TLOGV(tag, fmt, ##__VA_ARGS__);}\
    if(LOG_CONFIG_TARGET & LOG_TARGET_ANDROID){A_TLOGV(tag, fmt, ##__VA_ARGS__);}\
}while(0);
#define TLOGD(tag, fmt, ...)  do{ \
    if(LOG_CONFIG_TARGET & LOG_TARGET_CONSOLE){CONSOLE_TLOGD(tag, fmt, ##__VA_ARGS__);}\
    if(LOG_CONFIG_TARGET & LOG_TARGET_ANDROID){A_TLOGD(tag, fmt, ##__VA_ARGS__);}\
}while(0);
#define TLOGI(tag, fmt, ...)  do{ \
    if(LOG_CONFIG_TARGET & LOG_TARGET_CONSOLE){CONSOLE_TLOGI(tag, fmt, ##__VA_ARGS__);}\
    if(LOG_CONFIG_TARGET & LOG_TARGET_ANDROID){A_TLOGI(tag, fmt, ##__VA_ARGS__);}\
}while(0);
#define TLOGW(tag, fmt, ...)  do{ \
    if(LOG_CONFIG_TARGET & LOG_TARGET_CONSOLE){CONSOLE_TLOGW(tag, fmt, ##__VA_ARGS__);}\
    if(LOG_CONFIG_TARGET & LOG_TARGET_ANDROID){A_TLOGW(tag, fmt, ##__VA_ARGS__);}\
}while(0);
#define TLOGE(tag, fmt, ...)  do{ \
    if(LOG_CONFIG_TARGET & LOG_TARGET_CONSOLE){CONSOLE_TLOGE(tag, fmt, ##__VA_ARGS__);}\
    if(LOG_CONFIG_TARGET & LOG_TARGET_ANDROID){A_TLOGE(tag, fmt, ##__VA_ARGS__);}\
}while(0);

#define TLOGV_TRACE(tag, fmt, ...)  do{ \
    if(LOG_CONFIG_TARGET & LOG_TARGET_CONSOLE){CONSOLE_TLOGV_TRACE(tag, fmt, ##__VA_ARGS__);}\
    if(LOG_CONFIG_TARGET & LOG_TARGET_ANDROID){A_TLOGV_TRACE(tag, fmt, ##__VA_ARGS__);}\
}while(0);
#define TLOGD_TRACE(tag, fmt, ...)  do{ \
    if(LOG_CONFIG_TARGET & LOG_TARGET_CONSOLE){CONSOLE_TLOGD_TRACE(tag, fmt, ##__VA_ARGS__);}\
    if(LOG_CONFIG_TARGET & LOG_TARGET_ANDROID){A_TLOGD_TRACE(tag, fmt, ##__VA_ARGS__);}\
}while(0);
#define TLOGI_TRACE(tag, fmt, ...)  do{ \
    if(LOG_CONFIG_TARGET & LOG_TARGET_CONSOLE){CONSOLE_TLOGI_TRACE(tag, fmt, ##__VA_ARGS__);}\
    if(LOG_CONFIG_TARGET & LOG_TARGET_ANDROID){A_TLOGI_TRACE(tag, fmt, ##__VA_ARGS__);}\
}while(0);
#define TLOGW_TRACE(tag, fmt, ...)  do{ \
    if(LOG_CONFIG_TARGET & LOG_TARGET_CONSOLE){CONSOLE_TLOGW_TRACE(tag, fmt, ##__VA_ARGS__);}\
    if(LOG_CONFIG_TARGET & LOG_TARGET_ANDROID){A_TLOGW_TRACE(tag, fmt, ##__VA_ARGS__);}\
}while(0);
#define TLOGE_TRACE(tag, fmt, ...)  do{ \
    if(LOG_CONFIG_TARGET & LOG_TARGET_CONSOLE){CONSOLE_TLOGE_TRACE(tag, fmt, ##__VA_ARGS__);}\
    if(LOG_CONFIG_TARGET & LOG_TARGET_ANDROID){A_TLOGE_TRACE(tag, fmt, ##__VA_ARGS__);}\
}while(0);


#ifdef __cplusplus
}
#endif

#endif //_XLOG_H
