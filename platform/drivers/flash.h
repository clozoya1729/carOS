#ifndef DRIVER_FLASH_H
#define DRIVER_FLASH_H
#include <stddef.h>
int flash_init(void);
int flash_read(unsigned addr, void *buf, size_t len);
int flash_write(unsigned addr, const void *buf, size_t len);
int flash_erase(unsigned addr, size_t len);
#endif
