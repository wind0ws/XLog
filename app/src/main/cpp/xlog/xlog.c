#include "xlog.h"

#ifdef __cplusplus
extern "C" 
{
#endif// __cplusplus

int LOG_CONFIG_LEVEL = LOG_LEVEL_VERBOSE;
int LOG_CONFIG_TARGET = (LOG_TARGET_ANDROID | LOG_TARGET_CONSOLE); // NOLINT(hicpp-signed-bitwise)

#ifdef __cplusplus
}
#endif // __cplusplus

