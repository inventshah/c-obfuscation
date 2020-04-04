#include <setjmp.h>

void (*longjm_)(jmp_buf, int) = longjmp;