#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <time.h>

static void dbg(const char *format, ...) {
    static FILE *logfile = NULL;
    static int init = 0;
    static char buf[4096];
    static time_t t;

    if (!init) {
        char p[PATH_MAX];
        snprintf(p, sizeof(p), "/tmp/dwm.%s.log", getenv("USER"));
        logfile = fopen(p, "w");
        init = 1;
    }

    if (!logfile)
        return;

    time(&t);
    struct tm *tm = localtime(&t);
    snprintf(buf, sizeof(buf), "%02d:%02d %s\n", tm->tm_min, tm->tm_sec, format);

    va_list args;
    va_start(args, format);
    vfprintf(logfile, buf, args);
    fflush(logfile);
    va_end(args);
}

static void dbgc(Client *c, const char *format, ...) {
    static char buf[4096];

    va_list args;
    va_start(args, format);
    vsnprintf(buf, sizeof(buf), format, args);
    va_end(args);

    if (c == NULL)
        dbg(buf);
    else
        dbg("%s %dx%d%+d%+d*%d %dx%d%+d%+d*%d %s%s%s%s'%s'", buf,
            c->w, c->h, c->x, c->y, c->bw,
            c->oldw, c->oldh, c->oldx, c->oldy, c->oldbw,
            c->isfloating ? "FL " : "",
            c->isfixed ? "FI " : "",
            c->isfullscreen ? "FU " : "",
            c->oldstate ? "OS " : "",
            c->name);
}
