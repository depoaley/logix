#include "logix.h"

int main(void) {

    // Init Logger
    logix lg;
    if (!logix_init(&lg, "app.log")) return 1;

    logix_info(&lg, "Info logger %s:%d", "xyz", 123);
    logix_error(&lg, __FILE__, __LINE__, __func__, "Error logger %s:%d", "xyz", 123);
    //logix_fatal(&lg, __FILE__, __LINE__, __func__, "Fatal logger %s:%d", "xyz", 123);

    // Log via macros
    LGX_INFO(&lg, "Info logger %s:%d", "lala", 1421);
    LGX_ERROR(&lg, "Error logger %s:%d", "lala", 1421);
    LGX_FATAL(&lg, "Fatal logger %s:%d", "lala", 1421);

    // Close logger
    logix_close(&lg);
    return 0;
}