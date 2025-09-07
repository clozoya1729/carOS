#include "nv_storage.h"
int nv_init(void){ return 0; }
int nv_write(unsigned key, const void *data, size_t len){ (void)key; (void)data; (void)len; return 0; }
int nv_read(unsigned key, void *data, size_t maxlen){ (void)key; (void)data; (void)maxlen; return 0; }
