#include <time.h>

char *(*asctim_)(const struct tm *) = asctime;

clock_t (*cloc_)(void) = clock;

char *(*ctim_)(const time_t *) = ctime;

double (*difftim_)(time_t, time_t) = difftime;

struct tm *(*gmtim_)(const time_t *) = gmtime;

struct tm *(*localtim_)(const time_t *) = localtime;

time_t (*mktim_)(struct tm *) = mktime;

size_t (*strftim_)(char *, size_t, const char *, const struct tm *) = strftime;

time_t (*tim_)(time_t *) = time;
