#ifndef H_LOGIX
#define H_LOGIX

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

/*
---
Error/Fatal log format: <DATE> * <TYPE> * <file>:<line> <func>: * <MSG>
-
Info log format:        <DATE> * <TYPE> * <MSG>
---
*/

typedef struct {
    FILE *f;
} logix;

static void now(char *buff, size_t n) {
    time_t t = time(NULL);
    struct tm tmv;
    localtime_r(&t, &tmv);
    strftime(buff, n, "%Y-%m-%d %H:%M:%S", &tmv);
}

static int logix_init(logix *lg, const char *filepath) {
    if (!lg) return -1;
    memset(lg, 0, sizeof(*lg));
    lg->f = fopen(filepath, "a");
    return lg->f != NULL;
}

static void logix_close(logix *lg) {
    if (!lg) return;
    if (lg->f) fclose(lg->f);
    lg->f = NULL;
}

static void logix_v(logix *lg, 
                    const char *prefix, FILE *output,               // log prefix & output fd (stdout/stderr)
                    const char *f, int f_line, const char *func,    // file, code line * code function
                    const char* fmt, va_list ap) {                  // log message & arguments
    if (!lg || !lg->f) return;

    // timestamp
    char ts[32];
    now(ts, sizeof(ts));

    va_list ap_file;
    va_copy(ap_file, ap);

    // console output
    if (f) {
        fprintf(output, "%s * %s * { %s:%d %s() } * ", ts, prefix, f, f_line, func);
    } else {
        fprintf(output, "%s * %s * ", ts, prefix);
    }
    vfprintf(output, fmt, ap);
    fputc('\n', output);


    // file output
    if (f) {
        fprintf(lg->f, "%s * %s * { %s:%d %s() } * ", ts, prefix, f, f_line, func);
    } else {
        fprintf(lg->f, "%s * %s * ", ts, prefix);
    }
    vfprintf(lg->f, fmt, ap);
    fputc('\n', lg->f);

    va_end(ap_file);
}

static void logix_info(logix *lg, const char *fmt, ...) {
    if (!lg || !lg->f) return;
    va_list ap;
    va_start (ap, fmt);
    logix_v(lg, "[INF]", stdout, NULL, 0, NULL, fmt, ap);
    va_end(ap);
}

static void logix_error(logix *lg, 
                        const char *f, int f_line, const char *func,
                        const char *fmt, ...) {
    if (!lg || !lg->f) return;
    va_list ap;
    va_start (ap, fmt);
    logix_v(lg, "[ERR]", stderr, f, f_line , func, fmt, ap);
    va_end(ap);
}

static void logix_fatal(logix *lg, 
                        const char *f, int f_line, const char *func, 
                        const char *fmt, ...) {
    if (!lg || !lg->f) return;
    va_list ap;
    va_start (ap, fmt);
    logix_v(lg, "[FTL]", stderr, f, f_line, func, fmt, ap);
    va_end(ap);

    fflush(lg->f);
    if (lg) logix_close(lg);
    fflush(stderr);
    exit(-1);
}

#define LGX_INFO(lg, ...)logix_info((lg), __VA_ARGS__);
#define LGX_ERROR(lg, ...)logix_error((lg), __FILE__, __LINE__, __func__, __VA_ARGS__);
#define LGX_FATAL(lg, ...)logix_fatal((lg), __FILE__, __LINE__, __func__, __VA_ARGS__);

#endif