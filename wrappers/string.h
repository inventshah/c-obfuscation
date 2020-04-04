#include <string.h>

void *(*memch_)(const void *, int, size_t) = memchr;

int (*memcm_)(const void *, const void *, size_t) = memcmp;

void *(*memcp_)(void *, const void *, size_t) = memcpy;

void *(*memmov_)(void *, const void *, size_t) = memmove;

void *(*memse_)(void *, int, size_t) = memset;

char *(*strca_)(char *, const char *) = strcat;

char *(*strnca_)(char *, const char *, size_t) = strncat;

char *(*strch_)(const char *, int) = strchr;

int (*strcm_)(const char *, const char *) = strcmp;

int (*strncm_)(const char *, const char *, size_t) = strncmp;

int (*strcol_)(const char *, const char *) = strcoll;

char *(*strcp_)(char *, const char *) = strcpy;

char *(*strncp_)(char *, const char *, size_t) = strncpy;

size_t (*strcsp_)(const char *, const char *) = strcspn;

char *(*strerro_)(int) = strerror;

size_t (*strle_)(const char *) = strlen;

char *(*strpbr_)(const char *, const char *) = strpbrk;

char *(*strrch_)(const char *, int) = strrchr;

size_t (*strsp_)(const char *, const char *) = strspn;

char *(*strst_)(const char *, const char *) = strstr;

char *(*strto_)(char *, const char *) = strtok;

size_t (*strxfr_)(char *, const char *, size_t) = strxfrm;
