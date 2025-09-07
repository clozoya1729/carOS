#ifndef OS_KERNEL_H
#define OS_KERNEL_H
#include <stdint.h>
void os_init(void);
void os_start(void);
void os_tick_isr(void);
#endif
