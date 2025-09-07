#include "isotp.h"
int isotp_init(void){ return 0; }
int isotp_send(const void *payload, int len){ (void)payload; (void)len; return 0; }
int isotp_recv(void *payload, int maxlen){ (void)payload; (void)maxlen; return 0; }
