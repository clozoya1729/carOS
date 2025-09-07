#include "flash.h"
int flash_init(void){ return 0; }
int flash_read(unsigned addr, void *buf, size_t len){ (void)addr; (void)buf; (void)len; return 0; }
int flash_write(unsigned addr, const void *buf, size_t len){ (void)addr; (void)buf; (void)len; return 0; }
int flash_erase(unsigned addr, size_t len){ (void)addr; (void)len; return 0; }
