#include "xlog.h"
#define LOG_TAG_MAIN "MY_TAG"

int main(int argc, char *argv[]){

    LOGD("\n%s\nHello! current log_priority=%d, log_target=%d\n%s",
            LOG_LINE_STAR, xlog_config_level, xlog_config_target, LOG_LINE_STAR)

    LOGV("this log is printed by LOGV")
    LOGD("this log is printed by LOGD")
    LOGI("this log is printed by LOGI")
    LOGW("this log is printed by LOGW")
    LOGE("this log is printed by LOGE")

    LOGV_TRACE("this log is printed by LOGV_TRACE")
    LOGD_TRACE("this log is printed by LOGD_TRACE")
    LOGI_TRACE("this log is printed by LOGI_TRACE")
    LOGW_TRACE("this log is printed by LOGW_TRACE")
    LOGE_TRACE("this log is printed by LOGE_TRACE")

    TLOGV(LOG_TAG_MAIN,"this log is printed by TLOGV")
    TLOGD(LOG_TAG_MAIN,"this log is printed by TLOGD")
    TLOGI(LOG_TAG_MAIN,"this log is printed by TLOGI")
    TLOGW(LOG_TAG_MAIN,"this log is printed by TLOGW")
    TLOGE(LOG_TAG_MAIN,"this log is printed by TLOGE")

    TLOGV_TRACE(LOG_TAG_MAIN,"this log is printed by TLOGV_TRACE")
    TLOGD_TRACE(LOG_TAG_MAIN,"this log is printed by TLOGD_TRACE")
    TLOGI_TRACE(LOG_TAG_MAIN,"this log is printed by TLOGI_TRACE")
    TLOGW_TRACE(LOG_TAG_MAIN,"this log is printed by TLOGW_TRACE")
    TLOGE_TRACE(LOG_TAG_MAIN,"this log is printed by TLOGE_TRACE")

    xlog_config_level = LOG_LEVEL_ERROR;
    xlog_config_target = LOG_TARGET_ANDROID;
    LOGI("this log won't print because of current level is LOG_LEVEL_ERROR")
    LOGE("this log only print on logcat because of xlog_config_target=LOG_TARGET_ANDROID")

    xlog_config_level = LOG_LEVEL_OFF;
    LOGE("this log won't print because of xlog_config_level = LOG_LEVEL_OFF")

    xlog_config_level = LOG_LEVEL_INFO;
    xlog_config_target = LOG_TARGET_ANDROID | LOG_TARGET_CONSOLE;
    LOGI("TEST finished!!!")

    return 0;
}