# logix (tiny C logger)

# Usage:

```
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
```

# Example output:

```
depo@aley logix % cc logix.c -o logix
depo@aley logix % ./logix            
2026-02-14 16:18:04 * [INF] * Info logger xyz:123
2026-02-14 16:18:04 * [ERR] * { logix.c:10 main() } * Error logger xyz:123
2026-02-14 16:18:04 * [INF] * Info logger lala:1421
2026-02-14 16:18:04 * [ERR] * { logix.c:15 main() } * Error logger lala:1421
2026-02-14 16:18:04 * [FTL] * { logix.c:16 main() } * Fatal logger lala:1421

```
