#ifndef NV_STORAGE_H
#define NV_STORAGE_H
#include <stddef.h>
int nv_init(void);
int nv_write(unsigned key, const void *data, size_t len);
int nv_read(unsigned key, void *data, size_t maxlen);
#endif
