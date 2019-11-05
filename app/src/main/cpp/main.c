#include "xlog.h"
#define LOG_TAG_MAIN "MAIN"

int main(int argc, char *argv[]){

    LOGD("Hello! current log_priority=%d, log_target=%d",LOG_CONFIG_LEVEL,LOG_CONFIG_TARGET)

    LOGV("this log is printed by LOGV")
    LOGD("this log is printed by LOGD")
    LOGI("this log is printed by LOGI")
    LOGW("this log is printed by LOGW")
    LOGE("this log is printed by LOGE")

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

    return 0;
}