#ifndef DIAG_ISOTP_H
#define DIAG_ISOTP_H
int isotp_init(void);
int isotp_send(const void *payload, int len);
int isotp_recv(void *payload, int maxlen);
#endif
