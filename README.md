# logix (tiny C logger)

Small header-only logger for C.  
Always prints to console and appends to a file.

## Features

- Stream routing: INFO messages are written to stdout, while -ERROR- and -FATAL- messages are written to stderr.
- Call-site context for failures: -ERROR- and -FATAL- logs include the origin of the log call (\_\_FILE\_\_, \_\_LINE\_\_, \_\_func\_\_) to make debugging faster.
- Crash-stop logging: -FATAL- writes the message (console + file) and then terminates the program.

## Usage

```c
#include "logix.h"

int main(void) {
    logix lg;
    if (!logix_init(&lg, "app.log")) return 1;

    // Direct calls
    logix_info(&lg, "Info logger %s:%d", "xyz", 123);
    logix_error(&lg, __FILE__, __LINE__, __func__, "Error logger %s:%d", "xyz", 123);
    // logix_fatal(&lg, __FILE__, __LINE__, __func__, "Fatal logger %s:%d", "xyz", 123);

    // Macros (recommended)
    LGX_INFO(&lg,  "Info logger %s:%d", "lala", 1421);
    LGX_ERROR(&lg, "Error logger %s:%d", "lala", 1421);
    // LGX_FATAL(&lg, "Fatal logger %s:%d", "lala", 1421);

    logix_close(&lg);
    return 0;
}
```


## Output format:

#### INFO:
```
<DATE> * [INF] * <MSG>
```

#### ERROR / FATAL:
```
<DATE> * [ERR|FTL] * { file:line func() } * <MSG>
```
---

#### Example output
```
2026-02-14 16:18:04 * [INF] * Info logger xyz:123
2026-02-14 16:18:04 * [ERR] * { logix.c:10 main() } * Error logger xyz:123
2026-02-14 16:18:04 * [INF] * Info logger lala:1421
2026-02-14 16:18:04 * [ERR] * { logix.c:15 main() } * Error logger lala:1421
2026-02-14 16:18:04 * [FTL] * { logix.c:16 main() } * Fatal logger lala:1421
```
