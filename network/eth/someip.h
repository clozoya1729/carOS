#ifndef NETWORK_SOMEIP_H
#define NETWORK_SOMEIP_H
int someip_init(void);
int someip_send(const void *payload, int len);
int someip_recv(void *payload, int maxlen);
#endif
