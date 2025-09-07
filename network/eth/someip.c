#include "someip.h"
int someip_init(void){ return 0; }
int someip_send(const void *payload, int len){ (void)payload; (void)len; return 0; }
int someip_recv(void *payload, int maxlen){ (void)payload; (void)maxlen; return 0; }
